///
/// \file excep.cpp
/// \brief 异常类的实现，见excep.h 见声明
/// \author zeorlis
/// \date 2018.12.7
/// \email zerorlis@163.com
///
#include "excep.h"

convert_error::convert_error(const char *what_arg):logic_error(what_arg){

}

convert_error::convert_error(const std::string &what_arg):logic_error(what_arg){

}
