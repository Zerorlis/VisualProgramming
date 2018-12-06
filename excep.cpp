#include "excep.h"

convert_error::convert_error(const char *what_arg):logic_error(what_arg){

}

convert_error::convert_error(const std::string &what_arg):logic_error(what_arg){

}
