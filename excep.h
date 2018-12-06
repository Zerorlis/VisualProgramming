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
