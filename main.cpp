#include <QCoreApplication>
#include <iostream>
#include "node.h"
using namespace std;

void intcout(int i){
    cout << "intcout "<< i << endl;
}
void boolcout(bool i){
    cout << "boolcout "<< i << endl;
}

void charcout(const char*h){
    cout << "charcout" << h <<endl;
}

void charpcout(const char * i){
    cout << i << endl;
}

int main(int argc, char *argv[])
{
    using namespace std;

    QCoreApplication a(argc, argv);
    Value v;
    cout<<"测试添加数据\n";
    v.addValue(18);
    v.addValue(15.4);
    v.addValue("hello");
    v.addValue(v);
    v.addValue(true);
    v.addValue('h');
    v.addValue(QString(""));
    v.print();
    cout<< "测试拷贝构造函数\n";
    v.print();
    Value b1 = v;
    b1.print();
    Value b2 = 5;
    b2.print();
    Value b3 ="55.5";
    b3.print();
    Value b4 = true;
    b4.print();
    Value b5 = 'h';
    b5.print();
    Value b6 = 8;
    b6.print();
    Value b7 = QString();
    b7.print();


    cout << "测试赋值符号";
    Value c;
    c.print();
    c=v;
    c.print();
    c=1;
    c.print();
    c="efsdf";
    c.print();
    c=true;
    c.print();
    c=1.0;
    c.print();
    c=QString("hello");
    c.print();
    c='h';
    c.print();


    cout << "测试clear\n";
    Value d = v;
    d.print();
    d.clear();
    d.print();

    cout << "测试set函数\n";
    Value e(v);
    e.print();
    e.setValue(0,15);
    e.setValue(1,11.5);
    e.setValue(2,"hel");
    e.setValue(3,v);
    e.setValue(4,'7');
    e.setValue(5,"helo");
    e.setValue(6,QString("hl"));
    e.print();

    cout<< "测试delete\n";
    Value f(v);
    f.print();
    f.deleteValue(2);
    f.print();

    cout << "测试[]\n";
    v.print();
    for (int i=0;i<v.getSize();i++){
    ((Value)v[i]).print();
    }
    cout <<"测试[]=\n";
    v.print();
    v[0] = 0;
    v[1] = 'h';
    v[2] = "String";
    v[3] = QString("he");
    v[4] = 8.0;
    v[5] = v;
    v[6] = true;
    v.print();
    cout<< "测试类型转化\n";
    Value g = v;
    v=5;
    Value h =8;
    cout << h * 5.0 <<endl;

    intcout(v);

    cout << "isempty\n";

    Value i = 0;
    Value j;
    cout << h.isEmpty() << endl;
    cout << i.isEmpty() << endl;
    cout << j.isEmpty() << endl;
    Value k("");
    cout <<k.isEmpty() << endl;

    cout << "隐式转换的测试\n";
    Value m1("0");
    Value m2(0);
    Value m3("1");
    Value m4(1);
    intcout(m1);
    intcout(m2);
    intcout(m3);
    intcout(m4);
    boolcout(m1);
    boolcout(m2);
    boolcout(m3);
    boolcout(m4);

    cout << "测试当一个数组用";
    Value l;
    for(int i =0;i<5;i++){
        Value k;
        for (int j =0;j<5;j++){
            k.addValue(j+i*10);
        }
        l.addValue(k);
    }
    l.print();
    l[2][4]=3;
    l[3][2]=3;
    cout <<((QString)(Value)l[2][2]).toStdString().data()<<endl;
    l.print();
    cout<<"测试一些错误情况\n";
    try{
        Value n; // a list;
        cout << double(n)<<endl;
    }catch(exception & e){
        cout << e.what()<<endl;
    }

    return a.exec();
}
