#ifndef DCRUN_PARSER_INC
#define DCRUN_PARSER_INC

#include <iostream>

namespace dcrun
{
    using std::istream;
    using std::cin;

    class parser
    {
        istream& stream;

        bool has_gnu_ext;

    public:
        parser(istream& stream = cin);

        void run();

        void gnu_ext(bool setting);
        bool gnu_ext();
    };
}

#endif