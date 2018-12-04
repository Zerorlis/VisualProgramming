#include "node.h"
#include <iostream>
#include <QString>
#include <float.h>

Node::Node()
{

}

Value::Value()
{

}
Value::Value(const Value & value){
    for (int i =0 ;i < value.valuelist.size();i++){
        switch (value.typelist[i]){
        // 这里switch里面加括号是为了下面所有变量都叫v
        case DOUBLE:{
            double v = *(static_cast<double*>(value.valuelist[i]));
            addValue(v);
            break;
        }
        case STRING:{
            QString v = *(static_cast<QString *>(value.valuelist[i]));
            addValue(v);
            break;
        }
        case LIST:{
            Value v = *(static_cast<Value *> (value.valuelist[i]));
            addValue(v);
            break;
        }
        }
    }
}
Value::Value(double value){
    addValue(value);
}
Value::Value(QString value){
    addValue(value);
}

//Value & Value::operator =(const Value& value){
//    clear();
//    for (int i = 0;i<value.getSize();
//}
Value::~Value(){
    for (int i =0;i<valuelist.size();i++){
        switch (typelist[i]) {
        case DOUBLE:{
            double * v = static_cast<double *>(valuelist[i]);
            delete v;
            break;
        }
        case STRING:{
            QString * v = static_cast<QString*>(valuelist[i]);
            delete v;
            break;
        }
        case LIST:{
            Value * v = static_cast<Value *>(valuelist[i]);
            delete v;
            break;
        }
        }
    }

}


void Value::addValue(const double  value){
    double * i = new double{value};
    valuelist.append(static_cast<void *>(i));
    typelist.append(DOUBLE);
}

void Value::addValue(const QString & value){
    QString * i = new QString(value);
    valuelist.append(static_cast<void *>(i));
    typelist.append(STRING);
}

void Value::addValue(const Value & value){
    Value *  i = new Value(value);
    valuelist.append(static_cast<void * >(i));
    typelist.append(LIST);
}
void Value::deleteValue(int i){
    if (i < 0 && i > valuelist.size()-1){
        return ;
    }
    switch (typelist[i]) {
    case DOUBLE:{
        double * v = static_cast<double *>(valuelist[i]);
        delete v;
        break;
    }
    case STRING:{
        QString * v = static_cast<QString*>(valuelist[i]);
        delete v;
        break;
    }
    case LIST:{
        Value * v = static_cast<Value *>(valuelist[i]);
        delete v;
        break;
    }
    }

    valuelist.remove(i);
    typelist.remove(i);

}

void Value::clear(){
    for (int i =0;i<valuelist.size();i++){
        switch (typelist[i]) {
        case DOUBLE:{
            double * v = static_cast<double *>(valuelist[i]);
            delete v;
            break;
        }
        case STRING:{
            QString * v = static_cast<QString*>(valuelist[i]);
            delete v;
            break;
        }
        case LIST:{
            Value * v = static_cast<Value *>(valuelist[i]);
            delete v;
            break;
        }
        }
    }
    typelist.clear();
    valuelist.clear();
}

Value::operator double() const {
    // 当size只有1的时候
    if (valuelist.size()==1){
        switch (typelist[0]) {
        case DOUBLE:
            return *(static_cast<double *>(valuelist[0]));
            break;
        case STRING:{
            bool b = true;
            QString* v = static_cast<QString *>(valuelist[0]);
            double r = v->toDouble(&b);
            if(b){
                //转化成功
                return r;
            }else{
                return DBL_MAX;
            }
        }
            break;
        default:
            return DBL_MAX;
            break;
        }
    }else{
        return DBL_MAX;
    }
}

Value::operator QString() const {
    if(valuelist.size()==1){
        switch (typelist[0]) {
        case DOUBLE:
            return QString::number(*(static_cast<double*>(valuelist[0])));
            break;
        case STRING:
            return *static_cast<QString*>(valuelist[0]); //返回值为一个表达式的结果，所以不是那块内存，而是一个临时对象，会调用拷贝构造函数
            break;
        default:
            return QString("");
            break;
        }
    }else{
        return QString("");
    }
}



int Value::getSize()const {
    return typelist.size();
}

Value::type Value::getType() const{
    if(valuelist.size()==1){
       return typelist[0];
    }else{
        return LIST;
    }
}
QString Value::getDate(char f, int prec) const{
    QString q;
    //当只有double，string单个元素的时候，不输出前后的括号
    if (valuelist.size()!=1){
        q.append('[');
    }
    if (valuelist.size()==1 && typelist[0]==LIST){
        q.append('[');
    }
    for (int i = 0;i<valuelist.size();i++){
        switch (typelist[i]){
        case DOUBLE:
            q.append(QString::number(*static_cast<double *> (valuelist[i]),f,prec));
            break;
        case STRING:
            q.append('"');
            q.append( static_cast<QString *> (valuelist[i]));
            q.append('"');
            break;
        case LIST:
            Value * v = static_cast<Value *>(valuelist[i]);
            // 被夹在内部的元素要输出括号
            if (v->valuelist.size()==1&&v->typelist[0]!=LIST){
                q.append('[');
            }
            q.append(v->getDate());
            if (v->valuelist.size()==1&&v->typelist[0]!=LIST){
                q.append(']');
            }
            break;
        }
        if(i!=valuelist.size()-1){
            q.append(',');
        }

    }
    if(valuelist.size()!=1){
        q.append(']');
    }
    if(valuelist.size()==1&&typelist[0]==LIST){
        q.append(']');
    }
    return q;
}
