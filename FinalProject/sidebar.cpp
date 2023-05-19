#include "sidebar.h"
#include "constants.h"

#include <cstring>
//#include <fstream>

Sidebar::Sidebar()
{

}

Sidebar::Sidebar(float left, float width, Graph_info* info) :
    _left(left), _width(width), _info(info)
{
//    cout<<"Sidebar CTOR: TOP" << endl;

//    cout << "\nLeft: " << left << endl;

//    cout << "\nWidth: " << width << endl;

    //items.reserve(50);

    //set up the sidebar rectangle:
    //rect.setFillColor(sf::Color(105,105,105)); //(192,192,192)); //silver

    //rect.setFillColor(sf::Color(204, 255, 204));

    //rect.setFillColor(sf::Color(102, 102, 153));

    //rect.setFillColor(sf::Color(53, 55, 88));

    rect.setFillColor(sf::Color(38, 93, 97));   //side bar equation colors

    rect.setPosition(sf::Vector2f(left, 0));

    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));

    //cout<<"Sidebar CTOR: about to load font."<<endl;

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //the font file must be in the "working directory"
    // check projects->run->working directory
    //      [Make sure it's not pointing to the app file]

    if (!font.loadFromFile("Roboto-Thin.ttf"))
    {
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;

        cin.get();

        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    //cout<<"Sidebar CTOR: loaded font."<<endl;

    //. . . . . text / font problems: . . . . . . . .
    //initializing text object in this way caused problems
    // (hangs!)
    //only when sb_text was a private member and worked fine
    //when it was a public member. Probably not releavant,
    //but still strange!
    //
    //sb_text = sf::Text("Initial String for myTextLabel", font);
    //
    //. . . . . . . . . . . . . . . . . . . . . . . . .

    //cout<<"Sidebar CTOR: Text object initialized."<<endl;

    //sb_text.setFont(font);


    sf::RectangleShape rect;

    //rect.setFillColor(sf::Color::Red);

    //rect.setFillColor(sf::Color(199, 227, 220));  //light blue v1

    rect.setFillColor(sf::Color(53, 55, 88));       //dark blue v2

    rect.setSize(sf::Vector2f(box_width, box_height));

    rect.setPosition(horizontal_box_spacing, space_from_top_to_second);

    IteratedList<sf::RectangleShape>::Iterator it =
            history_backgrounds.Begin();

    for(int i = 0; i < 7; i++)
    {
        rect.setPosition((horizontal_box_spacing),  space_from_top_to_second
                         + i * (box_height + box_gaps));

        it = history_backgrounds.InsertAfter(rect, it);
    }

}

void Sidebar::draw(sf::RenderWindow& window)
{
    sb_text.setCharacterSize(CHAR_SIZE);

    sb_text.setColor(sf::Color::White);

    sb_text.setStyle(sf::Text::Bold);

    sb_text.setFont(font);

    window.draw(rect);


    //Draws current equation box

    sf::RectangleShape current_equation_background;

    //current_equation_background.setFillColor(sf::Color::Blue);

    //current_equation_background.setFillColor(sf::Color(52,152,220));

    //current_equation_background.setFillColor(sf::Color(69, 65, 107));

    current_equation_background.setFillColor(sf::Color(53, 55, 88));

    current_equation_background.setSize(sf::Vector2f((box_width),
                                                     (CHAR_SIZE + 50)));

    current_equation_background.setPosition((horizontal_box_spacing),
                              (space_from_top_to_first));


    window.draw(current_equation_background);


    //Draws current equation

    sb_text.setString(_info->_equation);

    sb_text.setPosition((horizontal_box_spacing + 8),
                        (space_from_top_to_first + 25));

    window.draw(sb_text);


    // get items size

    int size = 0;

    IteratedList <sf::Text> :: Iterator it = items.Begin();

    while(it != items.End())
    {
        ++size;

        ++it;
    }


    // draw equation history boxes

    for(int i = 0; i < 7; i++)
    {
        window.draw(history_backgrounds[i]);
    }


    //draw equation texts

    for(int i = 0; i < size; i++)
    {
        items[i].setColor(sf::Color::White);

        //items[i].setColor(sf::Color(119,136,153));

        items[i].setStyle(sf::Text::Bold);

        items[i].setFont(font);

        items[i].setPosition((horizontal_box_spacing + 8),
         space_from_top_to_second + i * ((box_height + box_gaps)) + 6);

        window.draw(items[i]);
    }
}

void Sidebar::add_equation(const string& equation)
{
    int size = 0;

    bool repeated_equation = false;

    IteratedList <sf::Text>::Iterator it = items.Begin();

    while(it != items.End())
    {
        ++size;
                //get size
        ++it;
    }

    it = items.Begin();

    for(int i = 0; it != items.End(); i++)
    {
        string temp = items[i].getString();

        if(temp == equation)
        {
            repeated_equation = true;

            break;
        }

        ++it;
    }

    it = items.Begin();

//    for(int i = 0; it != items.End(); i++)
//    {
//        string temp = items[i].getString();

//        cout << "\nEquation is: " << temp << endl;

//        ++it;
//    }

    //prevents equations from exceeding limit, doesn't display multiple
    //equations that are the same

    if(size >= 6 && repeated_equation == false)
    {
        items.Delete(items.LastNode());

        items.InsertHead(sf::Text(equation, font, CHAR_SIZE));
    }
}

string Sidebar::get_equation(sf::Vector2f mouse_coord)
{
    int index = -1;

//    cout << "\nMouse coord x: " << mouse_coord.x << endl;

//    cout << "\nMouse coord y: " << mouse_coord.y << endl;

    bool clicked_rectangle = false;

    IteratedList <sf::RectangleShape> :: Iterator it =
            history_backgrounds.Begin();

    //accesses rectangle list and uses global bounds to detect if
    //the mouse coords are within the rectangle parameters AKA
    //if the mouse clicked the button

    while(it != history_backgrounds.End() && !clicked_rectangle)
    {
        if((*it).getGlobalBounds().contains(mouse_coord))
        {
            clicked_rectangle = true;
        }

        ++it;

        ++index;
    }

    if(clicked_rectangle == true)
    {
        if(!items.empty())  //program crashes if rectangle clicked but
                            //nothing inside
        {
            return items[index].getString();
        }
    }

    return string();
}

void Sidebar :: loadfile()
{
    // clears the list to prevent any bugs with storage

    while(!items.empty())
    {
        items.Delete(items.LastNode());
    }

    //char symbol;

    string equation;

    IteratedList<sf::Text>::Iterator it = items.Begin();

    //int i = 0;

    ifstream instream;

    if(instream.fail())
    {
        cout << "\nInput file opening failed.\n";

        exit(1);
    }

    instream.open("file.txt");

    //bug with symbol extraction, switched to getline

    while(getline(instream, equation))
    {
        it = items.InsertAfter(sf::Text(equation, font, CHAR_SIZE), it);
    }

    instream.close();


    int size = 0;

    it = items.Begin();

    while(it != items.End())
    {
        ++size;

        ++it;
    }

    //cout << "\nSize is: " << size << endl;

    it = items.Begin();

//    for(int i = 0; it != items.End(); i++)
//    {
//        string temp = items[i].getString();


//         cout << "\nEquation is: " << temp << endl;


//        ++it;
//    }
    it = items.Begin();

    for(int i = 0; it != items.End(); i++)
    {
        string temp = items[i].getString();

        if(temp == " " || temp == "\n")
        {
            items.Delete(it);
        }

        it++;
    }
}

void Sidebar :: savefile()
{
    // get items size
    int size = 0;

    IteratedList<sf::Text>::Iterator it = items.Begin();

    while(it != items.End())
    {
        ++size;

        ++it;
    }

    ofstream outstream;

    if(outstream.fail())
    {
        cout << "Output file opening failed.\n";

        exit(1);
    }

    outstream.open("file.txt");

    if(size > 0)    //if there is anything to save
    {
        it = items.Begin();

        for(int i = 0; it != items.End(); i++)
        {
            //cout << "\nEquation: " << equation << endl;

            string equation = items[i].getString();

            outstream << equation;// << '\n';

            outstream << "\n";

            ++it;
        }

        outstream.close();
    }
}
