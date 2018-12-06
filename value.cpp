///
/// \file value.cpp
/// \brief 值的实现，见value.h 见声明
/// \author zeorlis
/// \date 2018.12.7
/// \email zerorlis@163.com
//
#include "value.h"
#include <iostream>
#include <QString>
#include <exception>
#include "excep.h"

Value::Value()
{

}
Value::Value(const refValue &value):Value(value.operator Value()){ // 这里实际上调用的是右值构造函数！！！可以通过这种方法，来指定转化方式

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

Value::Value(const int value){
    addValue(double(value));
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
                throw convert_error("can't convert the String to Number");
                return 0;
            }
        }
            break;
        default:
            throw convert_error("can't convert the List to Number");
            return 0;
            break;
        }
    }else{
        throw convert_error("can't convert the List to Number");
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
            return QString(*static_cast<QString*>(valuelist[0])); //返回值要是一个新的对象
            break;
        default:
            throw convert_error("can't convert a list to QString");
            break;
        }
    }else{
        throw convert_error("can't convert a list to QString");
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

Value & Value::operator=(const int value){
    return operator =(double(value));
}
Value::refValue Value::operator [](int i) {
    if (i<0 || i>getSize()-1)
        throw std::out_of_range("out of range");
    return refValue(this,i);
}

Value::refValue Value::refValue::operator [](int i) const{
    void * obj = val->valuelist[pos];
    TYPE type = val->typelist[pos];
    switch (type) {
    case LIST:{
        Value * p = static_cast<Value*>(obj);
        if (i<0||i>p->getSize()){
            throw std::out_of_range("out of range");
        }
        return refValue(p,i);
        break;
    }
    default:
        throw convert_error("can't use [] to a number or string");
    }
}

Value::refValue::refValue( Value *value, int position):val(value),pos(position){

}

Value::refValue::operator double() const{
    return double(val->getValue(pos));
}

Value::refValue::operator QString() const{
    return QString(val->getValue(pos));
}

Value::refValue::operator Value() const{
    return val->getValue(pos);
}

bool Value::refValue::operator == (const Value & value) const{
    return val->getValue(pos) == value;
}

bool Value::refValue::operator != (const Value & value) const{
    return val->getValue(pos) != value;
}

QString Value::refValue::getDate(char f, int prec) const{
    return val->getValue(pos).getDate(f,prec);
}

void Value::refValue::getValue(int i) const{
    val->getValue(pos).getValue(i);
}

void Value::refValue::clear(){
    val->getValue(pos).clear();
}

void Value::refValue::deleteValue(int i){
    val->getsetValue(pos)->deleteValue(i);
}

int Value::refValue::getSize() const{
    return val->getValue(pos).getSize();
}

Value::TYPE Value::refValue::getType() const{
    return val->getValue(pos).getType();
}

void Value::refValue::print() const{
    val->getValue(pos).print();
}
double Value::refValue::toDouble() const{
    return val->getValue(pos).toDouble();
}
QString Value::refValue::toQString() const{
    return val->getValue(pos).toQString();
}
int Value::refValue::toInt() const{
    return val->getValue(pos).toInt();
}
bool Value::refValue::isEmpty() const{
    return val->getValue(pos).isEmpty();
}



Value Value::getValue(int i) const{
    if (i<0 || i >  getSize()-1)
        throw std::out_of_range("out of range");
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
        throw std::out_of_range("out of range");
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
        throw std::out_of_range("out_of_range");
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
        throw std::out_of_range("out_of_range");
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
void Value::setValue(int i, const int value){
    setValue(i,double(value));
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
void Value::addValue(const int value){
    addValue(double(value));
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

Value::TYPE Value::getType() const{
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
        case LIST:
            return false;
            break;
        case DOUBLE:
            throw convert_error("double can't use isEmpty");
            return false;
            break;
        }
    }else if(typelist.size()==0){
        return true;
    }
    return false;

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
Value * Value::getsetValue(int i){
    void * obj = valuelist[i];
    switch (typelist[i]) {
    case LIST:{
        Value * p = static_cast<Value*>(obj);
        return p;
        break;
    }
    default:
        throw convert_error("can't use addValue to a number or string");
    }
}
