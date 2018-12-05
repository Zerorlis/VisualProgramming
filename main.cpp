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
    Value b2 = 5.2;
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
    v[0] = 1;
    v[1] = 'h';
    v[2] = "String";
    v[3] = QString("he");
    v[4] = 8.0;
    v[5] = v;
    v[6] = true;
    v.print();
//    todo:
//    v[5][1]='helo';
//    v.print();

    cout<< "测试类型转化\n";
    Value g = v;
    v=5;
    Value h =8;
    Value i = 7;
    cout << h * 7;

    intcout(v);
    boolcout(v);

    return a.exec();
}
