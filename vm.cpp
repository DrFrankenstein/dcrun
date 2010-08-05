#include <iostream>
#include <memory>
#include <deque>

#include "vm.h"
#include "value.h"
#include "number_value.h"
#include "exceptions.h"

namespace dcrun
{
    using std::cout;
    using std::endl;

    vm vm::instance;

    vm::vm()
        : scale(0)
    {}

    vm& vm::get()
    {
        return vm::instance;
    }

    unsigned int vm::precision()
    {
        return this->scale;
    }

    void vm::precision(unsigned int prec)
    {
        this->scale = prec;
    }

    void vm::push(value* val)
    {
        this->valstack.push_back(val);
    }

    void vm::pop()
    {
        if(this->valstack.empty())
        {
            throw stack_underflow();
        }

        value* top = this->valstack.back();
        this->valstack.pop_back();

        delete top;
    }

    value* vm::top()
    {
        if(this->valstack.empty())
        {
            throw stack_underflow();
        }

        return this->valstack.back();
    }

    number_value* vm::get_number()
    {
        number_value* num = dynamic_cast<number_value*>(this->top());
        if(num == NULL)
        {
            throw not_a_number();
        }
        return num;
    }

    void vm::print()
    {
        cout << *this->top() << endl;
    }
    void vm::print_and_pop()
    {
        value* val = this->top();
        cout << *val;

        this->pop();
    }
    void vm::dump()
    {
        for(deque<value*>::const_reverse_iterator i = this->valstack.rbegin(); i != this->valstack.rend(); i++)
        {
            cout << **i << endl;
        }
    }

    void vm::add()
    {
        number_value right = *this->get_number();
        this->pop();

        number_value left  = *this->get_number();
        this->pop();

        this->push(new number_value(left.get() + right.get()));
    }

    void vm::subtract()
    {
        number_value right = *this->get_number();
        this->pop();

        number_value left  = *this->get_number();
        this->pop();

        this->push(new number_value(left.get() - right.get()));
    }

    void vm::multiply()
    {
        number_value right = *this->get_number();
        this->pop();

        number_value left  = *this->get_number();
        this->pop();

        this->push(new number_value(left.get() * right.get()));
    }

    void vm::divide()
    {
        number_value right = *this->get_number();
        if(right.get() == 0)
        {
            throw divide_by_zero();
        }
        this->pop();

        number_value left  = *this->get_number();
        this->pop();

        this->push(new number_value(left.get() / right.get()));
    }

    void vm::exponentiate()
    {
        number_value exponent = *this->get_number();
        this->pop();

        number_value base     = *this->get_number();
        this->pop();

        mpf_t res;
        mpf_init(res);
        mpf_pow_ui(res, base.get().get_mpf_t(), mpf_class(abs(exponent.get())).get_ui());

        this->push(new number_value(mpf_class(res)));

        mpf_clear(res);
    }

    void vm::sqrt()
    {
        number_value val = *this->get_number();
        this->pop();

        this->push(new number_value(::sqrt(val.get())));
    }
}
