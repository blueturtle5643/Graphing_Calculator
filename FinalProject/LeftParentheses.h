#ifndef LEFTPARENTHESES_H
#define LEFTPARENTHESES_H

#include "Token.h"

class LeftParentheses : public Token
{
    public:

        virtual int type() const;

        virtual void print() const;

        virtual ~LeftParentheses()
        {

        }
};

#endif // LEFTPARENTHESES_H
