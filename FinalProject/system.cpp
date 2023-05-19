#include "system.h"
#include <iostream>

#include "Graph.h"

System::System(Graph_info *graph_info) : _g(graph_info)
{
    //uses graph info in initializer list
}


void System::Set_Info(Graph_info *graph_info)
{
    _g.Set_Info(graph_info);    //uses set info from graph class
}

void System::Step(int command, Graph_info *graph_info)
//void System::Step(int command, Graph_info *graph_info,
//sf::RenderWindow& window)
{
    switch(command)
    {
        case 4:
        {
            graph_info->_equation = "";

            _g.Update(*graph_info);     //uses update from graph info object
                                    //in the future it'll take commands

            break;
        }

        case 5:
        {
            graph_info->_domain.x = -5;

            graph_info->_domain.y = 5;

            graph_info->_origin.x = 0;

            graph_info->_origin.y = 0;

            _g.Update(*graph_info);     //uses update from graph info object
                                        //in the future it'll take commands

            break;
        }

//        case 6:
//        {
//            ofstream outstream;

//            savefile(outstream, items);

//            cout << "\nSave Completed." << endl;
//        }

//        case 7:
//        {
//            ifstream instream;

//            //loadfile(instream, graph_info->items);

//        }

        default:
        {
            _g.Update(*graph_info);     //uses update from graph info object
                                        //in the future it'll take commands
        }
    }
}


void System::Draw(sf::RenderWindow& window)
{
    _g.Draw(window);            //calls draw from graph class
}
