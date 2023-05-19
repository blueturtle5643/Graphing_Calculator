#include "RPN.h"
#include "Stack.h"

#include "Numbers.h"
#include "Operators.h"
#include "Variables.h"

#include <cmath>

RPN::RPN(Queue<Token*> postfix) : _postfix(postfix)
{

}

float RPN::operator() (float x)
{

    //LOGIC: RPN will be dealing with an postfix queue of shuntingyard
    //nodes of different categories. Using type, RPN will differentiate
    //and sort and evaluate

    //NOTE: CREATE AN ITERATED LIST/QUEUE TO PLAY WITH /professor insists on
    //vector but linked list instills more confidence :)

    //NOTE: RPN stack will be a float stack (NOT Numbers Token)

    //using get the function will return an int

    Queue <Token*> temp = _postfix;

    Stack <float> stack;

    while(!temp.empty())
    {
        //Even though everything is sorted in categories, popping them
        //will require an variable to access all types, which is tokens
        //job as parent class

        Token* token = temp.pop();

        token->type();

        if(token->type() == 1) // if is a number
        {
            //stack takes an token and static casts it to Number
            //and uses the get function exclusive to the Numbers class

            stack.push(static_cast <Numbers*> (token)->get());
        }
        else if(token->type() == 6) // if is a variable
        {
            //x passed in as an parameter will be pushed in stack as number

            stack.push(x);
        }
        else if(token->type() == 2)  // if is operator
        {
            Operators *binaryop = static_cast <Operators*> (token);

            //operators +-*/^ categorized as binary

            string optype = binaryop->op();

            //op function finally gets used, extracted as string

            float number2 = stack.pop();

            float number1 = stack.pop();

            //2 numbers are designated as float once popped from stack

            //BUG: converting an decimal from input to int and back to float

            //will need to deal with shunting yard Numbers value storage

            //string on string comparison

            if(optype == "+")
            {
                stack.push(number1 + number2);
            }

            else if(optype == "-")
            {
                stack.push(number1 - number2);
            }

            else if(optype == "*")
            {
                stack.push(number1 * number2);
            }

            else if(optype == "/")
            {
                stack.push(number1 / number2);
            }

            else if(optype == "^")
            {
                stack.push(pow(number1, number2));
            }
        }

        //TO BE IMPLEMENTED:
        //accounting for 3 argument monster, all functions are treated
        //with an stack containing num of args and each function will get
        //matched properly and pop accordingly

        else if(token->type() == 5)
        {
            Operators *function = static_cast <Operators*> (token);

            if(function->op() == "sin")
            {
                stack.push(sin(stack.pop()));
            }

            else if(function->op() == "cos")
            {
                stack.push(cos(stack.pop()));
            }

            else if(function->op() == "tan")
            {
                stack.push(tan(stack.pop()));
            }

            else if(function->op() == "exp")
            {
                stack.push(exp(stack.pop()));
            }

            else if(function->op() == "sqrt")
            {
                stack.push(sqrt(stack.pop()));
            }
            else if(function->op() == "abs")
            {
                stack.push(abs(stack.pop()));
            }

            else if (function->op() == "pow")
            {
                //float number2 = stack.pop();

                //float number1 = stack.pop();

                double number2 = stack.pop();   //logic to clean up pow
                                                //unable to detect double
                double number1 = stack.pop();   //exponent with negative base

                if(number1 < 0)
                {
                    number1 *= -1;
                }

                float result = pow(number1, number2);

                if(number1 < 0)
                {
                    result *= -1;
                }

                //stack.push(pow(number1, number2));

                //cout << "\nY is: " << result << endl;

                stack.push(result);
            }

            else if (function->op() == "ln")
            {
                stack.push(log(stack.pop()));
            }

            else if (function->op() == "log")
            {
                stack.push(log10(stack.pop()));
            }

            else if (function->op() == "neg")
            {
                stack.push(-1 * stack.pop());
            }
        }
    }

    return stack.pop();
}
