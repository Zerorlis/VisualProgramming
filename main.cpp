#include <QCoreApplication>
#include <iostream>
#include "node.h"
#include "test.h"
using namespace std;



int main(int argc, char *argv[])
{
    using namespace std;

    QCoreApplication a(argc, argv);
    testvalue();

    return a.exec();
}
