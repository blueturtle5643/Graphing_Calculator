#include "Plot.h"
#include "RPN.h"
#include "Coordinate_Translator.h"

#include "ShuntingYard.h"
#include "LeftParentheses.h"
#include "RightParentheses.h"

#include "Numbers.h"
#include "Operators.h"
#include "Variables.h"
#include "Functions.h"
#include "Negatives.h"

#include <sstream>

Plot::Plot(Graph_info* graph_info)
{
    Set_Info(graph_info);   //calls set info from this class
}                           //functions as a refresh sorta

void Plot::Set_Info(Graph_info *graph_info)
{
    _info = graph_info;     //basically reassigns
    
    // vector<Token *> infix_tokens = Tokenizer(graph_info.equation).generate();
    
    //gotta call delete after?

    // (tan(x)/sin(x))+(100-x^2)^(1/2)

    //_info->_equation = "2.5 * sin ( x ) + 2.5";

    //_info->_equation = "( tan ( x ) / sin ( x ) ) + ( 100 - x ^ 2 ) ^ ( ( 1 / 2 ) ) ";

    //_info->_equation = " sin ( 1 / x ) ";

    //_info->_equation = " tan ( x ) ";

    //_info->_equation = " cos ( x ^ 2 ) ";

    //_info->_equation = " sin ( x ) ";

    //tokenize takes care of converting string to tokens of appropriate
    //categories

    Queue <Token*> infix_tokens = tokenize(_info->_equation);

    //MEMORYLEAKMEMORYLEAKMEMORYLEAKMEMORYLEAKMEMORYLEAKMEMORYLEAKMEMORYLEAK


    ShuntingYard sy(infix_tokens);

    _post_fix = sy.postfix();
}


MyVector <sf::Vector2f> Plot::operator()()
{
    MyVector <sf::Vector2f> result;

    //Plot operator overload performs the entire task of the graphing
    //calulator display

    //1. Equation assumed to have been dismantled and re-assembled
    //as an infix queue. Tokenizer is the class that will do it?

     // vector<Token*> infix_tokens = Tokenizer(graph_info.equation).generate();

    //2. infix goes into SY and returns an postfix Queue

    //_post_fix = get_postfix(infix_tokens);

    //3. RPN will convert the postfix Queue into an rpn object or queue?

    // RPN rpn(_post_fix);

    //4. Insert the X value into RPN equation to evaluate?

    /* Now we can do;

    int x = something;

    int y = rpn.calculate(x);
    */

    RPN rpn(_post_fix);

    Coordinate_Translator translator(_info);

    // generate graph coordinate points

    float increment =
            (_info->_domain.y - _info->_domain.x) / (_info->_points - 1);

    //increment uses the domain pair of points (min,max) and the amount of
    //points to determine how to plot that many points between the minimum
    //and maximum. In order to accomodate for an case where a crap ton of
    //points will be plotted, USE FLOAT

    
    // draws single point
    //result.push_back(translator.translate(sf::Vector2f(0,0)));
    
    // draws curve

    for(float x = _info->_domain.x; x <= _info->_domain.y; x += increment)

    //floats are difficult to do comparisons with since they can result
    //in more or less points so logic will need to be revisited

    //basically, if minimum hasn't reached maximum, increment by the
    //evenly distributed value (increment)

    {
        float y = rpn(x);

        //RPN logic implemented

//        cout << "\nX: " << x << endl;

//        cout << "\nY: " << y << endl;

        sf::Vector2f graph_point(x,y);

        //creates an vector2f of x and y as coordinate points

        result.pushback(translator.translate(graph_point));

        //uses the coordinate translator(with graph info (origin))
        //and translates the points according to the current origin
        //to an display
    }

    return result;
}

Queue <Token*> Plot::tokenize(const string& equation) const
{
    Queue<Token *> tokens;

    stringstream ss(equation);

    string symbol;

    while(ss >> symbol)
    {
        if(symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/" |
           symbol == "^")
        {
            tokens.push(new Operators(symbol)); //grouping based on shunting
        }

        else if(symbol == "sin" || symbol == "cos" ||symbol == "tan" ||
                symbol == "exp" || symbol == "sqrt" ||symbol == "abs" ||
                symbol == "pow" || symbol == "ln" ||symbol == "log" ||
                symbol == "neg")
        {
            tokens.push(new Functions(symbol));
        }

        else if (symbol == "neg")
        {
            tokens.push(new Negatives());
        }

        else if(symbol == "(")
        {
            tokens.push(new LeftParentheses());
        }

        else if(symbol == ")")
        {
            tokens.push(new RightParentheses());
        }

        else if(symbol == "x")
        {
            tokens.push(new Variables("x"));
        }

        else
        {
            //no way to detect multiple inputs from num easily so
            //shove into num category

            stringstream ss2(symbol);

            float num;

            ss2 >> num;

            tokens.push(new Numbers(num));
        }
    }

    return tokens;
}

Plot::~Plot()
{
    Queue <Token*> copy(_post_fix);

    while(copy.empty() == false)
    {
        Token *ptr = copy.pop();
                                    //cleans up all the dynamically created
        delete ptr;                 //tokens
    }
}
