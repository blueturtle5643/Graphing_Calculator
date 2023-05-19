#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "IteratedLists.h"
#include "Graph_Info.h"

using namespace std;

class Sidebar
{
    private:

        sf::RectangleShape rect;            //sidebar rectangle

        //vector<string> items;               //strings to place on the sidebar

        sf::Font font;                      //used to draw text

        sf::Text sb_text;          //used to draw strings on the window object

        float _left;

        float _width;


        IteratedList <sf::Text> items;   //Text objects to place on the sidebar

        IteratedList <sf::RectangleShape> history_backgrounds; //buttons

        Graph_info *_info;


    public:

        Sidebar();

        Sidebar(float left, float width, Graph_info* info);

        //added graph info to use equation

        void draw(sf::RenderWindow& window);

        string& operator [](int index);


        void add_equation(const string& equation);

        string get_equation(sf::Vector2f mouse_coord);


//        void openfiles(ifstream& instream, ofstream& outstream);

        void loadfile();

        void savefile();


        const int CHAR_SIZE = 20 - 7;




        double box_gaps = 50;

        double horizontal_box_spacing = (_left + 0.05 * _width);

        double space_from_top_to_first = 20;

        //gap from top of sidebar to top of the first box

        double space_from_first_to_second = space_from_top_to_first + 120;

        //gap from the top of the first box to the top of the second box;


        double space_from_top_to_second = (space_from_top_to_first
                                                 + space_from_first_to_second);

        //gap from the top of sidebar to the top of the second box


        double box_width = (0.9 * _width);    //width of box

        double box_height = (CHAR_SIZE + 20); //height of box

};
#endif // SIDEBAR_H
