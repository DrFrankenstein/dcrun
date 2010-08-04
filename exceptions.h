#ifndef DCRUN_EXCEPTIONS_INC
#define DCRUN_EXCEPTIONS_INC

#include <string>
#include <exception>

namespace dcrun
{
    using std::string;
    using std::exception;

    class stack_underflow : public exception
    {
    public:
        stack_underflow();
    };

    class bad_command : public exception
    {
    public:
        bad_command(string command);
    };

    class not_a_number : public exception
    {
    public:
        not_a_number();
    };

    class divide_by_zero : public exception
    {
    public:
        divide_by_zero();
    };
}

#endif