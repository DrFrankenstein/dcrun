#ifndef DCRUN_NUMBER_VALUE_INC
#define DCRUN_NUMBER_VALUE_INC

#include <string>
#include <gmpxx.h>

#include "value.h"

namespace dcrun
{
    using std::string;

    class number_value : public value
    {
        mpf_class data;

    public:
        number_value(const mpf_class& mpf);

        const mpf_class& get() const;

        virtual string str() const;
    };

}

#endif
