///
/// \file excep.h
/// \brief 一些自定义的异常，见excep.cpp看详细定义
/// \author zeorlis
/// \date 2018.12.7
/// \email zerorlis@163.com
///
#ifndef EXCEP_H
#define EXCEP_H
#include<string>
#include<exception>
#include<stdexcept>
class convert_error : public std::logic_error {
public:
    explicit convert_error( const std::string& what_arg );
    explicit convert_error( const char* what_arg );

};

#endif // EXCEP_H
