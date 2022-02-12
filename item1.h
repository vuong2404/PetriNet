#ifndef ITEM1_H_
#define ITEM1_H_ 
#include "PetriNet.h" 
#include "graphics.h" 
#include "PrintFunctions.h"
using namespace std;
// defines the coordinates of the rectangle containing PetriNet, used for item1, item2, item3
// L ->left ,  R ->right, T -> top ,  B ->bottom 
#define  L  5    
#define  R  105  
#define  T  5    
#define  B  25  
//=============================================================

//
void showMenuItem1() {
    int R1 = R - 45;  // Dùng R1 thay cho tọa độ R để thu nhỏ khung cho cân xứng với Petri Net của item 1 
    int marginTop = T + 8; // dùng để căn chỉnh menu  
    textcolor(10);
    printRectangle(R1 + 5, R1 + 55, marginTop - 5, marginTop - 1);
    textcolor(7);
    gotoxy(R1 + 6, marginTop - 4); cout << " This PetriNet describe the course of business";
    gotoxy(R1 + 6, marginTop - 3); cout << " around a specialist in this outpatient clinic ";
    gotoxy(R1 + 6, marginTop - 2); cout << " of hospital X. ";
    textcolor(3);
    printRectangle(R1 + 5, R1 + 55, marginTop, marginTop + 2);
    gotoxy(R1 + 6, marginTop + 1); cout << "Press 1 to set initial marking.";

    printRectangle(R1 + 5, R1 + 55, marginTop + 3, marginTop + 5);
    gotoxy(R1 + 6, marginTop + 4); cout << "Press 2 to set auto firing";

    printRectangle(R1 + 5, R1 + 55, marginTop + 6, marginTop + 8);
    gotoxy(R1 + 6, marginTop + 7); cout << "Press 3 quit";
}

//Hàm Vẽ Petri net lên mang hình console 
void drawPetriNetItem1(map<string, int> marking)
{   
    textcolor(5); // color of frame.  
    printRectangle(L, R - 45, T, B);
    gotoxy(L + 1 , T + 1) ; textcolor(11) ;
    cout<<"Item 1: Specialist network" ;

    //draw transision
    textcolor(12); // color of transition 
    printRectangle(L + 4, L + 10 , T + 9,T + 11);
    gotoxy(L + 5, T + 10);
    textcolor(6); cout << "start";

    textcolor(12);
    printRectangle(L + 23, L + 29, T + 4, T + 6);
    gotoxy(L + 25, T+ 5);
    textcolor(6);
    cout << "end";

    textcolor(12);
    printRectangle(T + 44, T + 51 , T + 9 , T + 11);
    gotoxy(L + 45, T + 10);
    textcolor(6);
    cout << "change";

    // draw places 
    textcolor(15);
    gotoxy(L + 5, T + 5);  cout << "free( )";
    gotoxy(L + 45,T + 5);  cout << "docu( )";
    gotoxy(L + 25, T + 10);  cout << "busy( )";
   
    // In dấu mũi tên nằm dọc  
    textcolor(8);
    indoc(L + 7, T + 5, T + 9);
    indoc(L + 47,T + 8, T + 5);
    
    //In các dấu mũi tên nằm ngang 
    inngang(L + 10, L + 25 , T + 10); 
    inngang(L + 32, L + 44 , T + 10);
    inngang(L + 45, L + 30 , T + 5);
    inngang(L + 23, L + 13 , T + 5);
 
    ///print the number of token in every place  
    printNumOftoken(marking, "free", L + 10, T + 5);
    printNumOftoken(marking, "docu", L + 50, T + 5);
    printNumOftoken(marking, "busy", L + 30, T + 10);

    
}

// Set firing transition automatically 
void auto_firingItem1(PetriNet &N) {
    bool terminal = false;  // kiểm tra trạng thái cuối cùng 
    map<string, int> marking = N.getMarking();
    drawPetriNetItem1(marking);
    while (!terminal) {   

        //enanbled transition start 
        while (!terminal) {  
            if (_kbhit()) {
                char ch = _getch();
                if (ch == '0') return;
            }
            terminal = true;
            if (N.firing("start")) {
                marking = N.getMarking();
                textcolor(9);
                indoc_Color(L + 7, T + 5, T + 9);
                inngang_Color(L + 10, L + 25, T + 10);
                Sleep(100);
                drawPetriNetItem1(marking);
                gotoxy(L +1, T + 14); 
                textcolor(15);
                cout << "Current state: ";  N.printMarking();
                terminal = false;
            }
        }
        terminal = false;

        //enables transition change 
        while (!terminal) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == '0') return;
            }
            terminal = true;
            if (N.firing("change")) {
                marking = N.getMarking();
                textcolor(9);
                inngang_Color(L + 32, L + 44, T + 10);
                indoc_Color(L + 47, T + 8, T + 5);
                Sleep(100);
                drawPetriNetItem1(marking);
                gotoxy(L + 1, T + 14);  textcolor(15);
                cout << "Current state: ";  N.printMarking();
                terminal = false;
            }
        }
        terminal = false;

        //enabled transition  end. 
        while (!terminal) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == '0') return;
            }
            terminal = true;
            if (N.firing("end")) {
                marking = N.getMarking();
                textcolor(9);
                inngang_Color(L + 44, L + 30, T + 5);
                inngang_Color(L + 22, L + 13, T + 5);
                Sleep(100);
                drawPetriNetItem1(marking);
                gotoxy(L + 1, T + 14);  textcolor(15);
                cout << "Current state: ";  N.printMarking();
                terminal = false;
            }
        }
    }
}

// main  
void item1()
{
    // build a petri Net 
    PetriNet N;
    // create 3 places 
    N.pushPlace("free");
    N.pushPlace("busy");
    N.pushPlace("docu");

    //create 3 transition 
    N.pushTransition("start");
    N.pushTransition("change");
    N.pushTransition("end");

    //arcs from place to trans
    N.arcPT("free", "start");
    N.arcPT("busy", "change");
    N.arcPT("docu", "end");
    //arcs from trans to place
    N.arcTP("start", "busy");
    N.arcTP("change", "docu");
    N.arcTP("end", "free"); 

    // print initial marking  
    map<string, int> marking = N.getMarking();
    textcolor(15);  cout << "\n   Initial Marking :"; N.printMarking();

    // print Petri Net 
    drawPetriNetItem1(marking);

    // printprint menu 
    showMenuItem1();

    // loop to control the prog
    bool quit = false;    // if quit == true, end loop.  
    while (!quit) {  
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
            case '1':        // press 1 to set initial marking
                gotoxy(L, B + 2);
                N.setMarking();
                system("cls");
                marking = N.getMarking();
                cout << "\nInitial Marking :"; N.printMarking();
                drawPetriNetItem1(marking);
                showMenuItem1();
                break;
            case '2':          // press 2 to set auto_firing 
                system("cls") ;
                marking = N.getMarking();
                cout << "\nInitial Marking :"; N.printMarking();

                drawPetriNetItem1(marking);
                printRectangle(R -40, R + 10, T + 11, T + 13);
                gotoxy(R - 39, T + 12); cout << "Press 0 to stop auto firing";
                auto_firingItem1(N);
                showMenuItem1() ;
                break ;
            case '3':           // press 3 to set quit = true ; 
                quit = true;
                break;
            default:
                break;
            }
        }
    }
    system("cls") ;
    N.cleanUp();            // free memory 
    printMainMenu();        // go to main menu 
}
#endif 