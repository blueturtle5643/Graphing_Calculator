#ifndef RPN_H
#define RPN_H

#include "Token.h"
#include "Queue.h"

class RPN
{
    private:

        Queue <Token*> _postfix;

    public:

        RPN(Queue <Token*> postfix);

        float operator() (float x);

        //float evaluate(float x)
};

#endif
