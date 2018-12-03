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
//    v.print();
    cout << endl;
    Value x;
//    x.print();
    cout <<endl;
    Value z;
    z.addValue(12);
//    z.print();
    cout<<endl;

    return a.exec();
}
