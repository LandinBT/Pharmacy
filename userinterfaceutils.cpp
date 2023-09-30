#include "userinterfaceutils.hpp"

using namespace std;

int UserInterfaceUtils::mainMenu(const  string& title,const   vector<string>& options,
                             const  int&    numOpt,const    int&    colorTxt) {
    int selecOpt=1; //select    option  1
    int key;
    bool    repeat=true;

    do {
        system("cls");

        setColorText(colorTxt);

        frame(1,1,118,25);
        frame(3,2,116,5);

        centerText(title,4);
        setColorText(TXT_WHITE);
        cout<<title;

        gotoxy(5,8+selecOpt);
        setColorText(TXT_WHITE);
        cout<<"==>";

        for(int i(0); i<numOpt; i++) {
            gotoxy(10,9+i);
            setColorText(TXT_GRAY);
            cout<<options[i];
            }

        do {
            key=getch();
            }
        while(key!=UP   and key!=DOWN   and key!=ENTER);

        switch(key) {
            case    UP:
                selecOpt--;

                if(selecOpt<1) {
                    selecOpt=numOpt;
                    }
                break;

            case    DOWN:
                selecOpt++;

                if(selecOpt>numOpt) {
                    selecOpt=1;
                    }
                break;

            case    ENTER:
                repeat=false;
                break;
            }

        }
    while(repeat);

    return  selecOpt;
    }

void    UserInterfaceUtils::frame(const int&    left,const  int&    top,
                                  const int&    right,const int&    bottom) {
    for(int i(left); i<right; i++) {
        gotoxy(i,top);
        cout<<"_";
        gotoxy(i,bottom);
        cout<<"_";
        }

    for(int i(top); i<bottom; i++) {
        gotoxy(left,i);
        cout<<"|";
        gotoxy(right,i);
        cout<<"|";
        }

    gotoxy(left,top);
    cout<<" ";
    gotoxy(left,bottom);
    cout<<"|";
    gotoxy(right,top);
    cout<<" ";
    gotoxy(right,bottom);
    cout<<"|";
    }

void    UserInterfaceUtils::gotoxy(const    int&    x,const int&    y) {
    HANDLE  hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD   dwPos;

    dwPos.X=x;
    dwPos.Y=y;

    SetConsoleCursorPosition(hConsole,dwPos);
    }

void    UserInterfaceUtils::centerText(const    string& text,const  int&    y) {
    int sizeText=text.length();

    gotoxy((SCREEN_WIDTH-sizeText)/2,y);
    }

void    UserInterfaceUtils::setColorText(const  int&    colorTxt) {
    HANDLE  hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    COLOR(hConsole,colorTxt);
    }

void    UserInterfaceUtils::enterToContinue() {
    cout<<"Presione ENTER para continuar.   .   ."<<endl;
    getchar();
    }
