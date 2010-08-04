#ifndef DCRUN_STRING_VALUE_INC
#define DCRUN_STRING_VALUE_INC

#include <string>

#include "value.h"

namespace dcrun
{
    using std::string;

    class string_value : public value
    {
        string data;

    public:
        string_value(const string& str);

        virtual string str() const;
    };

}

#endif
