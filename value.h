///
/// \file value.h
/// \brief Value类的定义，见value.cpp 看详细定义
/// \author zeorlis
/// \date 2018.12.7
/// \email zerorlis@163.com
///
#ifndef VALUE_H
#define VALUE_H


#include <QString>
#include <QVector>
#include <QLinkedList>
#include <QList>
#include "excep.h"
///
/// \brief The Value class 用于表示node的值
///
class Value
{
private:
    enum TYPE{
        DOUBLE,STRING,LIST
    };
private:
    QVector<void *> valuelist; ///< 用于保存值，用void指针指着
    QVector<TYPE> typelist; ///< 用于保存上面的list的列表,存的内容代表类型，用于多状态存储
    ///
    /// \brief The ref class ,一个代理类，用于[]的返回值的赋值和给值操作
    ///
    class refValue{
    private:
        Value * val;
        int pos;
    public:
        refValue( Value * val, int pos);

        template<typename T>
        refValue & operator = (const T & value){
            val->setValue(pos,value);
            return *this;
        }//处理[]= 赋值用

        refValue operator [](int i) const;// 用于[][]这样的多重结构
        operator Value() const; // 处理[]
        // 以下的都是value的重载,直接调用对应的
        operator double() const;
        operator QString() const;
        template<typename T>
        void addValue(const T & value){
            val->getsetValue(pos)->addValue(value);
        } //因为直接调用内部，所有模板函数走起
        template<typename T>
        void setValue(int i, const T & value){
            val->getsetValue(pos)->setValue(i,value);
        }
        bool operator == (const Value & value) const;
        bool operator != (const Value & value) const;
        QString getDate(char f = 'g', int prec = 6 ) const ;
        void setDate(QString date); //对于会有写操作的函数，需要写具体的做法。
        void getValue(int i) const;
        void clear();

        void deleteValue(int i);
        int getSize() const ;
        TYPE getType() const;
        void print() const;
        bool toBool() const;
        double toDouble() const; //QString和double可以互相转化，转化失败返回错误，list返回错误
        QString toQString() const; // QString和double可以互相转化，list返回错误
        int toInt() const;
        bool isEmpty() const;
    };
public:
    Value();
    Value(const Value & value); /// 拷贝构造函数，策略是一个Value内的对象都是自己的，不公用，还需重载等号的拷贝函数
    Value(const double value);
    Value(const QString & value);
    Value(const char* const value); // 指针会在没有匹配的时候匹配到整数值的函数，bool的话就成功了，int会报错
    Value(const int value); // 为了防止0的时候，走上面的那个函数。
    Value(const refValue & value); //有这个的目的是因为refValue强制转换的时候，会导致歧义，所以有这个，强制。
    virtual ~Value();
    Value & operator = (const Value & value);
    Value & operator = (const double value);
    Value & operator = (const QString & value);
    Value & operator = (const char * const value);
    Value & operator = (const int value);
    ///
    /// \brief operator []
    /// \param i 位置
    /// \return 返回一个代理类，这个类和这个Value对象链接，访问的时候会自动转化为Value，value有更新的时候会跟着更新，可以对其赋值
    /// 但是放问value的内容需要具体的内容需要使用显式转换,返回都是Value的形式。
    refValue operator [] (int i) ;
    bool operator == (const Value & value) const;
    bool operator != (const Value & value) const;

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
    void addValue(const QString & value);
    void addValue(const Value & value);
    void addValue(const char* const value);
    void addValue(const int value);


    ///
    /// \brief setValue 设置第i个变量为Value,当i不对的时候就什么都不做
    /// \param i 第几个值，只能在为正数
    /// \param value double 要设置的值
    ///
    void setValue(int i, const double value);
    void setValue(int i, const QString & value);
    void setValue(int i, const Value & value);
    void setValue(int i, const char* const value);
    void setValue(int i, const int value);

    ///
    /// \brief getValue 获得某个位置的值，以一个Value形式弄出
    /// \param i 第几个
    /// \return 一个赋值的value值
    ///
    Value getValue(int i) const;

    ///
    /// \brief clear 清除所有的值
    ///
    void clear();


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
    TYPE getType() const;
    void print() const;
    bool toBool() const;
    double toDouble() const; //QString和double可以互相转化，转化失败返回错误，list返回错误
    QString toQString() const; // QString和double可以互相转化，list返回错误
    int toInt() const;
    ///
    /// \brief isEmpty 这个字符串是不是空的，如果是数字，返回错误，如果是list,空的list返回true，否则返回false
    /// \return
    ///
    bool isEmpty() const;

private:
    void copy(const Value & value); // 提供拷贝构造函数和=重载使用
    Value * getsetValue(int i); // 用于被嵌套的value写的操作，只有被嵌套的Value可以被写，其他的类型不允许被写


};

#endif // VALUE_H