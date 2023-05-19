#ifndef RIGHTPARENTHESES_H
#define RIGHTPARENTHESES_H

#include "Token.h"

class RightParentheses : public Token
{
    public:

        virtual int type() const;

        virtual void print() const;

        virtual ~RightParentheses()
        {

        }
};

#endif // RIGHTPARENTHESES_H
