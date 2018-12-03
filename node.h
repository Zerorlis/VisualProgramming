/// \file node.h
/// \author zerorlis
/// \email zerorlis@163.com
/// \date 2018.12.3
/// \version 0.1
///
///
#ifndef NODE_H
#define NODE_H
#include <QString>
#include <QVector>
#include <QLinkedList>

///
/// \brief The Value class 用于表示node的值
///
class Value
{
private:
    enum type{
        DOUBLE,STRING,LIST
    };
public:
    Value();
    Value(const Value & value);
    Value(double value);
    virtual ~Value();
    QVector<void *> valuelist; ///< 用于保存值，用void指针指着
    QVector<type> typelist; ///< 用于保存上面的list的列表,存的内容代表类型，用于多状态存储

    operator QString(); /// 可以转化为一个QString对象，注意，list也是通过QString输出的
    operator double(); ///可以转化为一个double对象

    ///
    /// \brief addValue 添加一个值到最后面
    /// \param value double 添加的值
    ///
    void addValue(const double  value );

    ///
    /// \brief addValue 添加一个值到最后面
    /// \param value QString 添加的值
    ///
    void addValue(const QString & value);

    ///
    /// \brief addValue 添加一个值到最后面
    /// \param value Value 添加的值,Value相当于一个数组
    ///
    void addValue(const Value & value);

    ///
    /// \brief clear 清除所有的值
    ///
    void clear();


    ///
    /// \brief setValue 设置第i个变量为Value,当i不对的时候就什么都不做
    /// \param i 第几个值，只能在为正数
    /// \param value double 要设置的值
    ///
    void setValue(int i, double value);

    ///
    /// \brief setValue 设置第i个变量为Value,当i不对的时候就什么都不做
    /// \param i 第几个值，只能在为正数
    /// \param value QString要设置的值
    ///
    void setValue(int i, QString value);

    ///
    /// \brief setValue 设置第i个变量为Value,当i不对的时候就什么都不做
    /// \param i 第几个值，只能在为正数
    /// \param value Value 要设置的值
    ///
    void setValue(int i, Value value);

    ///
    /// \brief deleteValue 删除第i个值，当i不对什么都不做
    /// \param i 第几个i
    ///
    void deleteValue(int i);

    ///
    /// \brief getSize 获取当前Value内有多少个值
    /// \return  返回Value内多少值
    ///
    int getSize();



};

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
