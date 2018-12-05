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
    copy(value);
}

Value::Value(const double value){
    addValue(value);
}

Value::Value(const QString & value){
    addValue(value);
}


Value::Value(const char * const value){
    addValue(QString(value));
}

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

void Value::copy(const Value&value){
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

Value::operator double() const {
    return toDouble();
}


double Value::toDouble() const{
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
                return 0;
            }
        }
            break;
        default:
            return 0;
            break;
        }
    }else{
        return 0;
    }

}

Value::operator QString() const {
    return toQString();
}

QString Value::toQString()const{

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


bool Value::toBool()const{
    return bool(toDouble());

}

int Value::toInt() const{
    return int(toDouble());
}

bool Value::operator ==(const Value & value) const{
    if (this==&value)
        return true;
    if(getSize()!=value.getSize()){
        return false;
    }
    for(int i =0 ;i < getSize();i++){
        if(typelist[i]!=value.typelist[i]){
            return false;
        }
        switch (typelist[i]) {
        case DOUBLE:{
            double v1 = *static_cast<double*>(valuelist[i]);
            double v2 = *static_cast<double*>(value.valuelist[i]);
            if (v1!=v2){
                return false;
            }
            break;
        }
        case STRING:{
            QString& v1 = *static_cast<QString*>(valuelist[i]);
            QString& v2 = *static_cast<QString*>(value.valuelist[i]);
            if(v1!=v2){
                return false;
            }
            break;
        }
        case LIST:{
            Value & v1 = *static_cast<Value*>(valuelist[i]);
            Value & v2 = *static_cast<Value*>(value.valuelist[i]);
            if(v1!=v2){
                return false;
            }
            break;
        }
        default:
            return false;
        }
    }
    return true;
}

bool Value::operator !=(const Value & value) const{
    return !(*this==value);
}

Value & Value::operator =(const Value& value){
    if (this == &value){
        return *this;
    }
    clear();
    copy(value);
    return *this; //记得返回自己，是左值，所以为了能多次
}

Value & Value::operator =(const double value){
    clear();
    addValue(value);
    return *this;
}

Value & Value::operator =(const QString & value){
    clear();
    addValue(value);
    return *this;
}


Value & Value::operator = (const char * const value){
    return operator=(QString(value));
}
Value::refValue Value::operator [](int i){
    return refValue(this,i);
}


Value::refValue::refValue( Value *value, int position):val(value),pos(position){

}

Value::refValue & Value::refValue::operator =(const Value & value){
    val->setValue(pos,value);
    return *this;
}

Value::refValue & Value::refValue::operator =(const double  value){
    val->setValue(pos,value);
    return *this;
}

Value::refValue & Value::refValue::operator =(const QString & value){
    val->setValue(pos,value);
    return *this;
}

Value::refValue & Value::refValue::operator =(const char* const value){
    val->setValue(pos,QString(value));
    return *this;
}

Value::refValue::operator Value() const{
    return val->getValue(pos);
}

Value Value::getValue(int i) const{
    if (i<0 || i >  getSize()-1)
        return Value();
    switch (typelist[i]) {
    case DOUBLE:
        return Value(*static_cast<double *>(valuelist[i]));
        break;
    case STRING:
        return Value(*static_cast<QString*>(valuelist[i]));
        break;
    case LIST:
        return Value(*static_cast<Value *> (valuelist[i]));
    default:
        return Value();
        break;
    }

}

void Value::setValue(int i, const double value){
    if (i < 0 || i > valuelist.size()-1){
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
    typelist[i]=DOUBLE;
    valuelist[i]=static_cast<void*>(new double{value});
}

void Value::setValue(int i, const QString & value){
    if (i < 0 || i > valuelist.size()-1){
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
    typelist[i]=STRING;
    valuelist[i]=static_cast<void*>(new QString(value));
}

void Value::setValue(int i, const Value & value){
    if (i < 0 || i > valuelist.size()-1){
        return ;
    }
    // 先保存一遍value的值，因为可能会添加自己，导致自己变了
    Value * self = NULL;
    if (this==&value){
        self = new Value(value);
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
    typelist[i]=LIST;
    if(this==&value){
        valuelist[i]=static_cast<void*>(self);
    }else{
        valuelist[i]=static_cast<void*>(new Value(value));

    }
}

void Value::setValue(int i, const char * const value){
    setValue(i,QString(value));
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

void Value::addValue(const char *value){
    addValue(QString(value));
}

void Value::deleteValue(int i){
    if (i < 0 || i > valuelist.size()-1){
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

bool Value::isEmpty() const{
    if(typelist.size()==1){
        switch (typelist[0]) {
        case STRING:{
            QString* v = static_cast<QString *> (valuelist[0]);
            return v->isEmpty();
            break;
        }
        default:
            return false;
            break;
        }
    }else if(typelist.size()==0){
        return true;
    }else{
        return false;
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

void Value::print() const{
    std::cout<<getDate().toStdString().data()<<std::endl;
}
