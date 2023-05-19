#ifndef ANIMATE_H
#define ANIMATE_H

#include <SFML/Graphics.hpp>
#include "system.h"
#include "Graph_Info.h"
#include "sidebar.h"

class animate
{
    private:

        Graph_info* _info;

        sf::RenderWindow window;

        System system;              //container for all the animated objects

        int command;                        //command to send to system


        bool entering_input = false;   // flag to indicate taking input or not

        bool viewing_help = false;

        string temp_input;            // holds input equation to be validated


        Sidebar sidebar;                    //rectangular message sidebar

        sf::Font font;                      //font to draw on main screen

        sf::Text myTextLabel;               //text to draw on main screen

    public:

        animate();

        ~animate();

        void run();

        void processEvents();

        void update();

        void render();

        void Draw();



        void draw_input_box();

        void draw_help_box();

        bool validate_input(const string& input) const;

        IteratedList <sf::Text> helptext;
};
#endif // ANIMATE_H
