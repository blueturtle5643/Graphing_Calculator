#ifndef Z_WORK_REPORT_H
#define Z_WORK_REPORT_H
/*
    Features:
        -Not Implemented: Did not implement axis tick marks, axis
        numbers, grid lines, equation text as buttons, tab, ctrl v, ctrl c,
        longer list of equations, caret, rectangles instead of circles

        -Implemented: Relationship between classes have mostly been established
        Heavy work for most of the functions have been written. Shunting yard
        postfix queue can now communicate with RPN and RPN can pass an number
        to the plot. Input queue can now communicate with animate, sstream
        in both tokenize and validate

        -Partly implemented: Plotting is still buggy, large gaps in
        y axis for graphing

    Bugs: Y axis needs to be re examined

    Reflections:

    WEEK 1: Project was very interesting I suppose. Had fun taking
    detailed notes of the lecture, compiling into stickies, having a bunch
    of stickes on my board. Also created a bunch of workflow charts of how
    the program runs with every function. Working on a list of every function
    and capability of every class. Logic shouldn't be hard, just need examples
    to work off of like online graphing calculators and how their displays
    work. Not too worried about design of calulcator.

    WEEK 2: Project is cancer. Haven't taken linear algrebra but linear
    transformation isn't too bad. What was bad/difficult was figuring out
    how many damn relationships and logic for graph coordinates to be
    translated properly to the screen using an changing origin. Watched
    a few videos on coordinate translation and spent hours looking for
    things to account for. What was REALLY BAD was learning about SFML.
    I hate reading documentation and the example projects given weren't too
    much help. My assumptions going in for SFML documentation were that
    I would be in the classes section looking at window and vectors and mouse

    NOTE: relationship between several classes AKA mouse (using ints) and
    vectors need to be matched

    mouse scrolling was an decent read, don't know the limits on it, should
    test it. Panning was an can of worms mostly due to my idea of how to handle
    mouse events. Now that I sorta understand panning I'm really impressed
    at how fast the whole process is. My understanding is that the program is
    Constantly calling draw and re-ordering/re-organizing both the graph and
    all the points where the human eye discerns it as an seemless transition.

    zooming is changing the domain, but the relationship of the x and y and
    how they should be effected (- or +) threw me off, forgot about how SFML
    treats origin.

    WEEK 3: WHEW FINALLY FINISHED :) Input was pretty bad to be honest. I chose
    the easy way with the spaces between every symbol. Sidebar logic was
    pretty interesting. Spent hours just making things pretty, had some dumb
    bugs on loading files in and I thought it was spacing haha. Worked on unary
    operator negative, realized the - operator worked in some cases. I think
    the hardest part was the sidebar detection in animate. Fstream wasn't bad
    at all, had code from last semester and it was just an matter of copy and
    pasting. Had some weird bug with instream unable to pick up so I used
    getline from c string I believe. Couldn't be too creative with the
    validation, could also add more functions. Overall, pretty happy, I really
    wanted to add more design like grid lines or ticks but I was strapped
    for time. I also want to redo my input method (without spaces) but that
    would take a lot of time and thinking. I guess I could work on it over
    the summer since there's nothing else to do.

*/
#endif // Z_WORK_REPORT_H
