#include <string>

#include "string_value.h"

namespace dcrun
{
    using std::string;

    string_value::string_value(const string& str)
        : value(STRING), data(str)
    {
    }

    string string_value::str() const
    {
        return this->data;
    }

}