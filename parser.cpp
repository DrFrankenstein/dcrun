#include <iostream>
#include <sstream>
#include <cctype>
#include <cstdlib>

#include "parser.h"
#include "value.h"
#include "number_value.h"
#include "string_value.h"
#include "vm.h"
#include "exceptions.h"

namespace dcrun
{
    using std::istream;

    parser::parser(std::istream& stream)
        :stream(stream), has_gnu_ext(true)
    {
    }

    void parser::run()
    {
        using std::isdigit;
        using std::isspace;
        using std::ostringstream;

        using std::exception;

        using std::cout;
        using std::endl;

        vm& dcvm = vm::get();

        for(;;)
        {
            int c = this->stream.peek();
            if(c == istream::traits_type::eof())
            {
                break;
            }

            try
            {
                if(isdigit(c) || c == '_' || c == '.')
                {
                    ostringstream ss;
                    bool had_sign = false, had_point = false;
                    
                    if(c == '_')
                    {
                        had_sign = true;
                        stream.get();
                        ss << '-';
                    }

                    while(
                        isdigit(c = this->stream.peek())
                        || !had_point && this->stream.peek() == '.'
                        || had_sign && isspace(this->stream.peek()))
                    {
                        c = this->stream.get();
                        if(!isspace(c))
                        {
                            ss << static_cast<char>(c);
                            had_sign = false;
                        }
                        if(c == '.')
                        {
                            had_point = true;
                        }
                    }

                    dcvm.push(value_factory::get_value(value::NUMBER, ss.str()));
                }
                else if(c == '[')
                {
                    ostringstream ss;
                    unsigned int depth = 0;

                    this->stream.get(); // consume [
                    while((c = this->stream.get()) != ']' || depth)
                    {
                        if(c == '[')
                            depth++;
                        else if(depth && c == ']')
                            depth--;

                        ss << static_cast<char>(c);
                    }

                    dcvm.push(value_factory::get_value(value::STRING, ss.str()));
                }
                else
                {
                    c = this->stream.get();
                    switch(static_cast<char>(c))
                    {
                        case 'p':
                            dcvm.print();
                            break;
                        case 'n':
                            if(this->has_gnu_ext)
                                dcvm.print_and_pop();
                            else
                                throw bad_command(string(1, static_cast<char>(c)));
                            break;
                        case 'f':
                            dcvm.dump();
                            break;

                        case '+':
                            dcvm.add();
                            break;
                        case '-':
                            dcvm.subtract();
                            break;
                        case '*':
                            dcvm.multiply();
                            break;
                        case '/':
                            dcvm.divide();
                            break;

                        case 'q':
                            return;
                            
                        default:
                            if(!isspace(c))
                                throw bad_command(string(1, static_cast<char>(c)));
                    }
                }
            }
            catch(exception& x)
            {
                cout << "dc: " << x.what() << endl;
            }
        } 
    }

    void parser::gnu_ext(bool setting)
    {
        this->has_gnu_ext = setting;
    }

    bool parser::gnu_ext()
    {
        return this->has_gnu_ext;
    }

}