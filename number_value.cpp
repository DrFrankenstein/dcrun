#include <iostream>
#include <string>
#include <sstream>

#include <gmpxx.h>

#include "number_value.h"

namespace dcrun
{
    using std::string;
    using std::ostringstream;

    number_value::number_value(const mpf_class& mpf)
        : value(NUMBER), data(mpf)
    {
    }

    const mpf_class& number_value::get() const
    {
        return this->data;
    }

    string number_value::str() const
    {
        mp_exp_t exp;

        // Get digits and sign if needed.
        string str = this->data.get_str(exp);

        bool neg = (str[0] == '-');

        if(exp < 0)
        {
            // Add point and zeroes if 0 < n < 1
            str.insert(neg? 1 : 0, 1, '.');
            str.insert(neg? 2 : 1, -exp, '0');
        }
        else
        {
            // Add point or trailing zeroes if needed too.
            if(neg)
            {
                if(exp < str.size() - 1)
                    str.insert(exp + 1, 1, '.');
                else
                    str.append(exp - (str.size() - 1), '0');
            }
            else
            {
                if(exp < str.size())
                    str.insert(exp, 1, '.');
                else if(str == "")
                    str = "0";
                else
                    str.append(exp - str.size(), '0');
            }
        }
#if 0    
        // TODO
        // Would use this, but linking fails because both of us and GMP declare
        // C++ library names, and the linker complains. Need to look into this.
        ostringstream ss;
        ss << this->data;
        string str = ss.str();
#endif
        // Wrap at 70th column.
        if(str.size() > 70)
        {
            for(string::size_type idx = 69; idx < str.size(); idx += 71)
                str.insert(idx, "\\\n");
        }

        return str;
    }
}

using std::ostream;
using namespace dcrun;

ostream& operator <<(ostream& stream, const value& val)
{
    return stream << val.str();
}
