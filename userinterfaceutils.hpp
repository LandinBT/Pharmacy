/*******************************************************************************
*   Filename:   userinterfaceutils.hpp  *
*   Author: Daniel  Basulto Del Toro    *
*   Date    Created:    September   23, 2023    *
*   Description:    This    file    provides    utilities
*   related to  the user    interface   *
*
*   Copyright   ©   DanyBT  2023    *
*******************************************************************************/
#ifndef USERINTERFACEUTILS_HPP_INCLUDED
#define USERINTERFACEUTILS_HPP_INCLUDED

#include<iostream>
#include<cstdlib>   //system()
#include<windows.h>
#include<conio.h>   //getch(),gotoxy()
#include<vector>

#define COLOR   SetConsoleTextAttribute
#define SCREEN_WIDTH    118

//COLOR TEXT
#define TXT_BLACK   0
#define TXT_BLUE    1
#define TXT_GREEN   2
#define TXT_CYAN    3
#define TXT_RED 4
#define TXT_VIOLET  5
#define TXT_YELLOW  6
#define TXT_WHITE   7
#define TXT_GRAY    8

#define UP  72
#define DOWN    80
#define ENTER   13

///DEFINITION
class   UserInterfaceUtils  {
    public:
        //UserInterfaceUtils();

        int mainMenu(const  std::string&,const  std::vector<std::string>&,
                 const  int&,const  int&);  //title,options,no. Options,color text

        void    frame(const int&,const  int&,const  int&,const  int&);  //Left,Top,Right,Bottom

        void    gotoxy(const    int&,const  int&);  //x,y

        void    centerText(const    std::string&,const  int&);  //text,y
        void    setColorText(const  int&);  //color

        void    enterToContinue();
    };

#endif // USERINTERFACEUTILS_HPP_INCLUDED
