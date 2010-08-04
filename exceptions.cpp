#include <exception>
#include <string>

#include "exceptions.h"

namespace dcrun
{
    using std::exception;
    using std::string;

    stack_underflow::stack_underflow()
        : exception("stack empty")
    {
    }

    bad_command::bad_command(string command)
        : exception((string("'") + command + "': unimplemented").c_str())
    {
    }

    not_a_number::not_a_number()
        : exception("non-numeric value")
    {
    }

    divide_by_zero::divide_by_zero()
        : exception("divide by zero")
    {
    }
}