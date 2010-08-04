#include <string>
#include <exception>

#include "value.h"
#include "string_value.h"
#include "number_value.h"

namespace dcrun
{
    using std::string;
    using std::exception;

    value::value()
        : _type(UNDEFINED)
    {
    }

    value::value(value::valtype t)
        : _type(t)
    {
    }

    value::valtype value::type()
    {
        return this->_type;
    }

    string value::str() const
    {
        throw exception(__FUNCTION__": undefined value");
    }

    value* value_factory::get_value(value::valtype type, const string& str)
    {
        switch(type)
        {
        case value::STRING:
            return new string_value(string(str));

        case value::NUMBER:
            return new number_value(mpf_class(str));

        case value::UNDEFINED:
        default:
            throw exception(__FUNCTION__": tried to instantiate a value of undefined type");
        }
    }

}
