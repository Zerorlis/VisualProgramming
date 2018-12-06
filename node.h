///
/// \file node.h
/// \author zerorlis
/// \email zerorlis@163.com
/// \date 2018.12.3
/// \brief node节点类，见node.cpp看详细定义
///
#ifndef NODE_H
#define NODE_H
#include "value.h"

class Node
{
public:
    Node();
public:
    QString description;
    QString usrFunction;
    int nodeId;
    QLinkedList<Value> input;
    QString function;
    Value value;


};

#endif // NODE_H
