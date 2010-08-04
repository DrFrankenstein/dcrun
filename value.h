#ifndef DCRUN_VALUE_INC
#define DCRUN_VALUE_INC

#include <string>

namespace dcrun
{
    using std::string;

    class value
    {
    public:
        enum valtype
        {
            UNDEFINED,
            NUMBER,
            STRING
        };

    protected:
        valtype _type;

    public:
        value();
        value(valtype t);

        valtype type();

        virtual string str() const;
    };

    class value_factory
    {
    public:
        static value* get_value(value::valtype type, const string& str = "");
    };

}

std::ostream& operator <<(std::ostream& stream, const dcrun::value& val);

#endif
