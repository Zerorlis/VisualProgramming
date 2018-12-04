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
private:
    QVector<void *> valuelist; ///< 用于保存值，用void指针指着
    QVector<type> typelist; ///< 用于保存上面的list的列表,存的内容代表类型，用于多状态存储
public:
    Value();
    Value(const Value & value); /// 拷贝构造函数，策略是一个Value内的对象都是自己的，不公用，还需重载等号的拷贝函数
    Value(double value);
    Value(QString value);
    virtual ~Value();
    Value & operator = (const Value & value);
    Value & operator = (const double & value);
    Value & operator = (const QString & value);
    Value operator [] (int i) const;
    bool operator == (const Value & Value) const;
    operator bool() const;


    ///
    /// \brief operator QString
    /// 转化为QString,只有值只有一个且为double的时候才能转化
    /// 如果有多个，输出[]
    /// 如果有1个，但是是double，输出这个数字 double<->QString转化,默认小数点后6位
    /// 如果有1个，但是是List，输出空字串
    ///
    operator QString() const;

    ///
    /// \brief operator double
    /// 转化为一个double数值，只有当值只有一个的时候才能正确转化，且为double的时候才能转化
    /// 如果值有多个，输出无限大
    /// 如果值是1个，但是是个QString，如果可以转化，输出数组，否则输出无限大，double<-> QStirng
    /// 如果值是1个，但是是个List，输出无限大
    operator double() const;


    ///
    /// \brief getDate 获取当前的数据，以一个字符串输出，和setDate相反
    /// \return 一个字符串，和python的list差不多
    ///  数字根据fmt指定的格式，参数n被格式化，g为默认情况并且可以为下列之一：
    /// e - 格式化为[-]9.9e[+|-]999
    /// E - 格式化为[-]9.9E[+|-]999
    /// f - 格式化为[-]9.9
    /// g - 使用e或f格式，看哪一个更简练
    /// G - 使用E或f格式，看哪一个更简练
    /// 在所有的情况下，小数点之后数字的个数等于prec指定的精度。
    ///
    QString getDate(char f = 'g', int prec = 6 ) const ;

    ///
    /// \brief setDate 设置当前的数据，一种比较高级的形式，和getDate相反
    /// \param date 一个字符串，和python 的list差不多
    ///
    void setDate(QString date);

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
    int getSize() const ;
    ///
    /// \brief getType 获取当前value的type
    /// \return LIST,DOUBLE,STRING，class内部的枚举类型
    ///
    type getType() const;

private:
    void copy(const Value & value); // 提供拷贝构造函数和=重载使用


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
