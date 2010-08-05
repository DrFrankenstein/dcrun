#ifndef DCRUN_VM_INC
#define DCRUN_VM_INC

#include <stack>
#include <climits>

#include "value.h"
#include "number_value.h"

namespace dcrun
{
    using std::deque;

    class vm
    {
        deque<value*>   valstack;
        value           registers[UCHAR_MAX];
        unsigned int    scale;

        static vm       instance;

        void            pop();
        value*          top();
        number_value*   get_number();

    public:
        static vm&      get();

        unsigned int   precision();
        void            precision(unsigned int prec);

        void            push(value* val);

        void            print();
        void            print_and_pop();
        void            dump();

        void            add();
        void            subtract();
        void            multiply();
        void            divide();
        void            exponentiate();
        void            sqrt();

    private:
        vm();
        vm(const vm&);
        vm& operator =(const vm&);
    };

}

#endif