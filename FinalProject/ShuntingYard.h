#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include "Queue.h"
#include "Stack.h"
#include "Token.h"

class ShuntingYard
{
    private:

        Queue <Token*> _get_post_fix(Queue <Token*> infix);   //logic

        Queue <Token*> _post_fix;   //storage variable

    public:

        ShuntingYard(Queue <Token*> infix); //creates an shunting yard with Q

        Queue <Token*> postfix() const; //stores result in another Q

        Stack<int> input_counts;
};

#endif
