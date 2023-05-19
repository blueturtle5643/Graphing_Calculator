TEMPLATE = app
CONFIG += console
#CONFIG -= app_bundle
#CONFIG -= qt
CONFIG += c++11

#------------------------------------------
##Add these lines for SFML:


#WINDOWS

LIBS += -L"C:\Qt\SFML-2.5.1\lib"
LIBS += -L"C:\Qt\SFML-2.5.1\bin"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

#WINDOWS

INCLUDEPATH += "C:\Qt\SFML-2.5.1\include"
DEPENDPATH += "C:\Qt\SFML-2.5.1\include"


#-----------------------------------------
SOURCES += \
        Coordinate_Translator.cpp \
        Graph.cpp \
        Plot.cpp \
        RPN.cpp \
        animate.cpp \
        sidebar.cpp \
        system.cpp \
        ShuntingYard.cpp \
        Token.cpp \
        RightParentheses.cpp \
        LeftParentheses.cpp \
        Numbers.cpp \
        Operators.cpp \
        Variables.cpp \
        Negatives.cpp \
        Functions.cpp \
        main.cpp


HEADERS += \
    Coordinate_Translator.h \
    Graph.h \
    Graph_Info.h \
    Plot.h \
    RPN.h \
    animate.h \
    constants.h \
    sidebar.h \
    system.h \
    ShuntingYard.h \
    Token.h \
    RightParentheses.h \
    LeftParentheses.h \
    Numbers.h \
    Operators.h \
    Variables.h \
    Negatives.h \
    Functions.h \
    Queue.h \
    Stack.h \
    IteratedLists.h \
    Node.h \
    AddEntry.h \
    MyVector.h \
    z_output.h \
    z_output.h \
    z_work_report.h \
    z_work_report.h
