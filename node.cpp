#include "node.h"
#include <iostream>

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
//        case INT:{
//            int v = *(static_cast<int *> (value.valuelist[i]));
//            addValue(v);
//            break;
//        }
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
Value::~Value(){
    for (int i =0;i<valuelist.size();i++){
        switch(typelist[i]){
//        case INT:{
//            int * v = static_cast<int *>(valuelist[i]);
//            delete v;
//            break;
//        }
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

//void Value::addValue(const int  value){
//    int * i = new int{value };
//    valuelist.append(static_cast<void *>(i));
//    typelist.append(INT);
//}

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
    valuelist.remove(i);
    typelist.remove(i);
}

//void print(){

//    using namespace std;
//    //当只有int，double，string单个元素的时候，不输出前后的括号
//    if (valuelist.size()!=1){
//        cout <<"[";
//    }
//    if (valuelsit.size()==1 && typelist[0]==LIST){
//        cout<<"[";
//    }
//    for (int i = 0;i<valuelist.size();i++){
//        switch (typelist[i]){
////        case INT:
////            cout << *static_cast<int*>(valuelist[i]);
////            break;
//        case DOUBLE:
//            cout << *static_cast<double *> (valuelist[i]);
//            break;
//        case STRING:
//            cout << static_cast<QString *> (valuelist[i])->toStdString().data();
//            break;
//        case LIST:
//            Value * v = static_cast<Value *>(valuelist[i]);
//            // 被夹在内部的元素要输出括号
//            if (v->valuelist.size()==1&&v->typelist[0]!=LIST){
//                cout << '[';
//            }
//            v->print();
//            if (v->valuelist.size()==1&&v->typelist[0]!=LIST){
//                cout<<']';
//            }
//            break;
//        }
//        if(i!=valuelist.size()-1){
//            cout << ",";
//        }

//    }
//    if(valuelist.size()!=1){
//        cout<<"]";
//    }
//    if(valuelist.size()==1&&typelist[0]==LIST){
//        cout<<"]";
//    }
//}
