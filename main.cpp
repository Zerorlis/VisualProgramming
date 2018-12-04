#include <QCoreApplication>
#include <iostream>
#include "node.h"
using namespace std;

int main(int argc, char *argv[])
{
    using namespace std;

    QCoreApplication a(argc, argv);
    Value v;
    v.addValue(18);
    v.addValue(15.4);
    v.addValue("hello");
    v.addValue(v);
    v.print();
    v.setValue(0,15);
    v.setValue(1,11.5);
    v.setValue(2,"hel");
    v.print();
    v.setValue(3,v);
    v.print();
    return a.exec();
}
