#ifndef INPUT_H
#define INPUT_H


class Input
{
public:
    Input();
};

#endif // INPUT_H


//istream& operator >>(istream& ins, Polynomial& poly)
//{
//    Polynomial result;      //Creating empty poly to be used later

//    Term term(0,-1);        //Creating an "empty" term to store stuff in

//    string input;           //input uses sstream functions to accept an

//    cin.ignore();

//    getline(ins, input);    //an poly

//    istringstream sstream(input);   //getline takes entire line ended by enter
//                                    //creates sstream object using input
//    while(sstream >> term)          //loops while sstream can detect an term
//    {                               //formula to take
//        result += term;              //result poly object takes terms
//    }

//    poly = result;                  //poly object passed in takes result poly

//    return ins;
//}
