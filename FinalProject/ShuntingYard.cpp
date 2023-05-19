#include "ShuntingYard.h"
#include "Operators.h"

ShuntingYard::ShuntingYard(Queue<Token *> infix)
{
    _post_fix = _get_post_fix(infix);
}

Queue<Token *> ShuntingYard::postfix() const
{
    return _post_fix;
}

Queue<Token*> ShuntingYard::_get_post_fix(Queue<Token*> infix)
{
    //LOGIC: Based of wiki

    Queue<Token *> output;

    Stack<Operators *> stack;

    bool foundfunction = false;    //3 argument monster logic

    int counter = 0;

    while(!infix.empty() == true)   //while infix queue isn't empty
    {
        Token *token = infix.pop(); //take the value, stick it into a token
                                    //that was popped from infix queue

        if(token->type() == 1 || token->type() == 6) //if is number or variable
        {
            output.push(token); //output takes value

            if(foundfunction == true)      //if an function is being tracked
            {                               //number of arguments increases
                counter++;
            }
        }
        else if(token->type() == 5) // if is function
        {
            stack.push(static_cast <Operators*>(token));

            foundfunction = true;  //function switch to calculate num of arg
        }

        else if(token->type() == 2) // if is operator
        {
            Operators* op = static_cast <Operators*>(token);

            while(!stack.empty() && (stack.top()->type() != 3 &&
                                     stack.top()->precedence() >=
                                     op->precedence()) && op->type() != 3)
                // not left parenth
            {
                output.push(stack.pop());   //pop stack, push into postfix Q
            }

            stack.push(op);

            if(foundfunction == true)       //makes sure op doesn't include
            {                               //num of arg
                counter--;
            }
        }

        else if(token->type() == 3) // if is left parenth
        {
            stack.push(static_cast <Operators*>(token));
        }

        else if(token->type() == 4) // if is right parenth
        {
            delete token;

            while(stack.top()->type() != 3)
            {
                output.push(stack.pop());
            }                                   //encountering an right P,
                                                //push every op until reaches
            if(stack.top()->type() == 3)        //left P
            {
                delete stack.pop();
            }

            if(foundfunction == true)           //if function exists
            {
                input_counts.push(counter);     //inserts the num of args
                                                //as an int into an stack
                foundfunction = false;          //reset function bool

                counter = 0;                    //reset function count
            }
        }
    }

    if(infix.empty())
    {
        while(!stack.empty())               //check to make sure infix is empty
        {                                   //cleans up remaining ops in stack
            output.push(stack.pop());
        }
    }

    return output;
}


