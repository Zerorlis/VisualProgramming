#include <QCoreApplication>
#include <iostream>
#include "node.h"
using namespace std;

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
    v.print();
    cout<< "测试拷贝构造函数\n";
    Value b = v;
    v.print();
    b.print();

    cout << "测试赋值符号";
    Value c;
    c.print();
    c=v;
    c.print();
    c=1;
    c.print();
    c="efsdf";
    c.print();

    cout << "测试set函数\n";
    v.print();
    v.setValue(0,15);
    v.setValue(1,11.5);
    v.setValue(2,"hel");
    v.setValue(3,v);
    v.print();

    cout<< "测试delete";
    v.print();
    v.deleteValue(2);
    v.print();

    return a.exec();
}
