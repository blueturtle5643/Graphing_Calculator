#include "animate.h"
#include "constants.h"

#include <iostream>
#include <sstream>

animate::animate() :
    _info(new Graph_info), system(_info), sidebar(WORK_PANEL, SIDE_BAR, _info)
{   
    _info->_window_dimensions = sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT);

    _info->_domain = sf::Vector2f(-5, 5);

    _info->_points = 5000;

    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                  "Graphing Calculator");

    window.setFramerateLimit(60);

    command = 0;

    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration

    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "\nAnimate() Constructor: Font failed to load." << endl;

        cin.get();

        exit(-1);
    }

    int CHAR_SIZE = 20;

    IteratedList <sf::Text> :: Iterator it = helptext.Begin();

    it = helptext.InsertHead(sf::Text("F: Input function EX. sin ( x )", font,
                                       CHAR_SIZE));

    it = helptext.InsertAfter(sf::Text("R: Resets the size.",
                                       font, CHAR_SIZE), it);

    it = helptext.InsertAfter
            (sf::Text("C: Clears the screen of current plotted graph.",
                      font, CHAR_SIZE), it);

    it = helptext.InsertAfter(sf::Text("S: Saves current history.", font,
                                       CHAR_SIZE), it);

    it = helptext.InsertAfter(sf::Text("L: Loads history from file.txt.",
                                       font, CHAR_SIZE), it);

    it = helptext.InsertAfter(sf::Text("ESC: Exits from Input and Help.",
                                       font, CHAR_SIZE), it);

    it = helptext.Begin();

    cout << "\nPress H in the graphing calculator for help." << endl;
}

animate::~animate()
{
    delete _info;
}

void animate::Draw()
{
    //Look at the data and based on the data, draw shapes on window object.

    system.Draw(window);

    if(entering_input == true)
    {
        draw_input_box();
    }

    if(viewing_help == true)
    {
        draw_help_box();
    }

    sidebar.draw(window);
}

void animate::update()
{
    system.Step(command, _info);

    command = 0; // reset, then take next command
}

void animate::render()
{
       window.clear();

       Draw();

       window.display();
}

void animate::processEvents()
{
    sf::Event event;

    while (window.pollEvent(event))//or waitEvent
    {
        // check the type of the event...

        switch (event.type)
        {
            // window closed

            case sf::Event::Closed:
            {
                window.close();

                break;
            }

            case sf::Event::TextEntered:
            {
                //LOGIC: played around with unicode to detect keyboard
                //inputs, basically allow anything but when keyboard detects
                //"interesting" elements such as a number, symbol, char
                //then the corresponding bool switch will be flipped
                //and the item will be stored

                //NOTE: UNICODE DECIMAL TO DETECT

                if(entering_input == true)
                {
                    bool number_detected =
                        event.text.unicode >= 48 && event.text.unicode <= 57;

                    //numbers 1 to 9

                    const bool letters_detected =
                       event.text.unicode >= 97 && event.text.unicode <= 122;

                    //alphabet

                    const bool math_symbol_detected =
                     event.text.unicode == 32 ||

                            // spacebar in order to handle sstream

                     event.text.unicode == 40 || event.text.unicode == 41 ||

                            // left / right parentheses

                     event.text.unicode == 42 || event.text.unicode == 43 ||

                            // * sign / + sign

                     event.text.unicode == 45 || event.text.unicode == 47 ||

                            // - sign / "/" sign

                     event.text.unicode == 94;

                            // ^ sign

                    if(number_detected || letters_detected ||
                            math_symbol_detected)
                    {
                        //strings have pushback function, using to store
                        //unicode to string

                        temp_input += static_cast<char>(event.text.unicode);

                        //temp_input.push_back(
                                    //static_cast<char>(event.text.unicode));
                    }
                }

                break;
            }

            case sf::Event::KeyPressed:
            {
                switch(event.key.code)
                {

                // Activate/De-activate user input

                    case sf::Keyboard::F:
                    {
                        if(entering_input == false)
                        {
                            window.pollEvent(event);    //clears stuff
                        }

                        entering_input = true;

                        break;
                    }

                    case sf::Keyboard::H:
                    {
                        if(viewing_help == false)
                        {
                            window.pollEvent(event);    //clears stuff
                        }

                        viewing_help = true;

                        break;
                    }

                    case sf::Keyboard :: Escape:
                    {
                        entering_input = false;

                        viewing_help = false;

                        temp_input.clear();

                        window.pollEvent(event);

                        break;
                    }
                    case sf::Keyboard::Enter:
                    {
                        entering_input = false;

                        if(validate_input(temp_input) == true)

                        //calls validate function to check if equation
                        //can be graphed
                        {
                            //cout << "\nEquation updated." << endl;

                            _info->_equation = temp_input;

                            sidebar.add_equation(temp_input);
                        }

                        temp_input.clear();

                        window.pollEvent(event);

                        break;
                    }

                    case sf::Keyboard::BackSpace:
                    {
                        if(entering_input == true)
                        {
                            if(temp_input.length() > 0)

                            //crashes if erase is called on empty string
                            {
                                temp_input.erase((temp_input.length() - 1));

                                //cute code that simulates delete, basically
                                //removes last char in an string
                            }
                        }

                        break;
                    }

                    case sf::Keyboard::C:
                    {
                        if(entering_input == false)
                        {
                            command = 4;    //clears grid of plotted points

                            break;
                        }
                    }

                    case sf::Keyboard::R:
                    {
                        if(entering_input == false)
                        {
                            command = 5;    //resets origin and domain
                                            //aka re-centers focus and zoom
                            break;
                        }
                    }

                    case sf::Keyboard::S:
                    {
                        if(entering_input == false)
                        {
                            sidebar.savefile(); //saves current history of
                                                //equations into file
                            break;
                        }
                    }

                    case sf::Keyboard::L:
                    {
                        if(entering_input == false)
                        {
                            sidebar.loadfile(); //loads file of equations

                            break;
                        }
                    }
                }

                break;
            }

            case sf::Event::MouseWheelScrolled:     //logic for zooming in
            {
                float domainlength =
                        _info->_domain.y - _info->_domain.x;

                //zooming is all about domain, so domain length should be
                //extracted from max - min AKA y - x

                float domainchange = domainlength / 50;

                //in order to "zoom" domain must change by reducing it
                //in size by dividing/subtracting whatever number

                //delta for mousewheel states that scrolling up/forward
                //results in positive increments

                if(event.mouseWheelScroll.delta > 0)
                {
                    //delta is the change in scroll wheel, so basically
                    //any positive increments result in an zoom

                    //zoom is simulated through domain increasing naturally
                    //while the y shrinks

                    _info->_domain.x += domainchange;

                    _info->_domain.y -= domainchange;
                }

                else
                {
                    _info->_domain.x -= domainchange;

                    _info->_domain.y += domainchange;
                }

                break;
            }
        }
    }

    // pan graph window

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
       sf::Mouse::getPosition(window).x <= _info->_window_dimensions.x)
    {
        //After adding sidebar functionality, mouse button location (x to x)
        //now is limited only to graph dimensions

        //OVERALL LOGIC: 2 different mouse states, click position and movement
        //position find offset between the 2, and shift everything accordingly.

        //2 variables needed to change in an graph, origin(x,y) and domain(x,y)

        //1. Get position of mouse click on the screen(AKA ORIGIN)

        //2. Get current location of mouse

        //3. Calculate Offset and use it to alter graph

        //NOTE: Vector2 series are X and Y coords

        //C++ LOGIC: be weary of graph to screen misunderstanding,
        //this part of the logic will be divided into steps

        //1. Grab screen coords of mouse

        //2. Grab new screen coords of mouse

        //3. subtract new by old for offset (x,y)

        //4. using domain(graph) to find the amount of pixels you would
        //  need to increment by to get to new from old

        //5. graph coords(NOT WINDOW COORDS) / DOMAIN Y - X

        //6. create an offset by dividing the screen coords (x, y) with
        //  increment values(graph) (x, y)

        //7. add into origin the new (graph) values


        //USE VECTOR2I 2F DOESN'T WORK??? Mouse coords are integer positions
        //while vector2f could be anything in graph coords? Pixels can't be
        //in decimals?

        sf::Vector2i current_position = sf::Mouse::getPosition(window);

        //wait for mouse drag, then record new position

        while(sf::Mouse::getPosition(window) == current_position)
        {
            //cout << "\nMouse has moved." << endl;

            //cout << "\nMouse X location is: " << event.mouseMove.x << endl;

            //cout << "Mouse Y location is: " << event.mouseMove.y << endl;
        }

        sf::Vector2i new_position = sf::Mouse::getPosition(window);

        // NEW COORDS AKA THE NEW ORIGIN

        sf::Vector2i position_diff = new_position - current_position;

        // calculate origin(x,y) offset

        float domainchange = _info->_domain.y - _info->_domain.x;

        //domain change required for recalculation of domain(x,y)

        float xincrease = _info->_window_dimensions.x / domainchange;

        float yincrease = _info->_window_dimensions.y / domainchange;

        //using current size of graph AKA window dimensions to find
        //the amount you need to increase by (accounting for domain change)

        //basically calculating pixel increments across graph screen x and y
        //with your current domain

        sf::Vector2f origin_offset = sf::Vector2f((0.0 + position_diff.x /
         xincrease), (0.0 + position_diff.y / yincrease));

        //to convert from int to float, just add an float

        //(offsetx / xincrease) (offserty / yincrease) for new offset


        // move origin to new coordinate

        _info->_origin.x -= origin_offset.x;

        _info->_origin.y += origin_offset.y;

        //graph origin origin is now subtracted by the offset to gain the new
        //coords

        //y is increased because when you drag down the graph moves down
        //instead of up so you account for the motion

        if(origin_offset.x != 0)    //if there was an offset aka mouse moved
        {
            //domain is an vector2f so calculation between both is allowed

            _info->_domain -= sf::Vector2f(origin_offset.x, origin_offset.x);
        }
    }

    else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
       sf::Mouse::getPosition(window).x >= _info->_window_dimensions.x)
    {
        //LOGIC: if mouse button is pressed (x value detected over a certain
        //x threshold (x dimensions from graph) then you get location of mouse
        //and pass in coords to a function

        // record current position

        sf::Vector2i current_position = sf::Mouse::getPosition(window);

        // wait for mouse button release

        while(sf::Mouse::getPosition(window) == current_position)
        {

        }

        //string will store whatever value the get equation will find

        string new_equation = sidebar.get_equation(
            sf::Vector2f(current_position.x, current_position.y));

        //if equation isn't default string, then graph info equation is updated

        if(!new_equation.empty())
        {
            _info->_equation = new_equation;
        }
    }
}
void animate::run()
{
   while (window.isOpen())
   {
       processEvents();

       update();

       render(); //clear/draw/display
   }
}

void animate::draw_input_box()
{
    // Box centered and hanging slightly from top of window that displays

    float box_width = 0.8 * _info->_window_dimensions.x;

    float box_height = 50;

    sf::RectangleShape input_box;

    input_box.setSize(sf::Vector2f(box_width, box_height));

    input_box.setOrigin(sf::Vector2f(box_width / 2, box_height / 2));

    //centers

    input_box.setPosition(sf::Vector2f(_info->_window_dimensions.x / 2,
    (box_height / 2) +  (0.1 * _info->_window_dimensions.y)));

    //middle of x value of graph, tenth of screen y with box height middle

    input_box.setFillColor(sf::Color::White);

    input_box.setOutlineColor(sf::Color::Cyan);

    input_box.setOutlineThickness(2);

    window.draw(input_box);


    // caret

//    const float caretwidth = 2;

//    const float caretheight = 20;

//    sf::RectangleShape caret;

//    caret.setSize(sf::Vector2f(caretwidth, caretheight));

//    caret.setOrigin(sf::Vector2f(caretwidth / 2, caretheight / 2));

//    caret.setPosition(sf::Vector2f((_info->_window_dimensions.x / 2) -
//                                   (box_width / 2) + 10,
//        box_height / 2 +  0.1 * _info->_window_dimensions.y));

//    caret.setFillColor(sf::Color::Black);

//    bool caretloop = true;

//    do
//    {

//        window.draw(caret);

//        caretloop = false;
//    }
//    while(caretloop == false);

//    window.draw(caret);


    // ...then draw text

    int text_size = 20;

    float left_margin = 10;

    myTextLabel.setFont(font);

    myTextLabel.setColor(sf::Color(119,136,153));

    //myTextLabel.setStyle(sf::Text::Bold);

    myTextLabel.setCharacterSize(text_size);

    myTextLabel.setOrigin(0, text_size / 2);

    myTextLabel.setPosition(
        input_box.getGlobalBounds().left + left_margin,
        input_box.getPosition().y);

    if(temp_input.empty())
    {
        myTextLabel.setString("f(x) = ");
    }

    else
    {
        myTextLabel.setString(temp_input);
    }

    window.draw(myTextLabel);
}

void animate::draw_help_box()
{
    // Box centered and hanging slightly from top of window that displays

    float box_width = 0.8 * _info->_window_dimensions.x;

    float box_height = 400;

    sf::RectangleShape help_box;

    help_box.setSize(sf::Vector2f(box_width, box_height));

    help_box.setOrigin(sf::Vector2f(box_width / 2, box_height / 2));

    //centers

    help_box.setPosition(sf::Vector2f(_info->_window_dimensions.x / 2,
    (box_height / 2) + (0.20 * _info->_window_dimensions.y)));

    //middle of x value of graph, tenth of screen y with box height middle

    help_box.setFillColor(sf::Color::White);

    help_box.setOutlineColor(sf::Color::Cyan);

    help_box.setOutlineThickness(2);

    window.draw(help_box);


    for(int i = 0; i < 6; i++)
    {
        //items[i].setColor(sf::Color::White);

        helptext[i].setColor(sf::Color(119,136,153));

        helptext[i].setStyle(sf::Text::Bold);

        helptext[i].setFont(font);

        helptext[i].setPosition((_info->_window_dimensions.x / 4),
        (box_height / 2) + i * (60));

        window.draw(helptext[i]);
    }
}

bool animate::validate_input(const string& input) const
{
    stringstream ss(input);

    int parentheses_counter = 0;

    //sstream will simulates char grabbing and evaluates them based on length
    //and determines if certain mathematical expressions are allowed

    string symbol;

    while(ss >> symbol)
    {
        if(symbol.length() == 1)
        {
            if(!isdigit(symbol[0]) &&
          (symbol != "+" && symbol != "-" && symbol != "*" && symbol != "/" &&
           symbol != "^" && symbol != "x" && symbol != "(" && symbol != ")"))
            {
                return false;
            }

            // check for matching parentheses

            if(symbol == "(")
            {
                parentheses_counter++;
            }

            else if(symbol == ")")
            {
                parentheses_counter--;
            }
        }

        else
        {
            bool only_numbers = true;

            for(int i = 0; i < symbol.length() && only_numbers; i++)
            {
                if(!isdigit(symbol[i]))
                {
                    only_numbers = false;   //since x is counted as a number
                                            //it will detect other chars
                }
            }
            if(!only_numbers && symbol != "sin" && symbol != "cos" &&
                symbol != "tan" && symbol != "exp" && symbol != "sqrt" &&
                symbol != "abs" && symbol != "log" && symbol != "ln" &&
                symbol != "pow" && symbol != "neg")
            {
                return false;
            }
        }
    }

    if(parentheses_counter != 0)
    {
        return false;   //uneven parentheses
    }

    if(symbol.find_first_not_of(' '))
    {
        return false;   //empty inputs
    }

    return true;
}
