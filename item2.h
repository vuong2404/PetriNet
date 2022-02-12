#ifndef ITEM2_H_
#define ITEM2_H_ 
#include "main.h"
#include "graphics.h" 
#include "PrintFunctions.h" 
using namespace std; 
// L, R , T , B is defined in item1.h 

//Draw the petri net of item2 
void drawPetriNetItem2(map<string, int> marking) {
    //print frame 
    textcolor(5);
    printRectangle(L, R, T, B);
    gotoxy (L + 1, T + 1) ; textcolor(11) ;
    cout<<"Item 2: Specialist network" ;

    //print transitions
    textcolor(12);
    printRectangle(L + 24, L + 30, T + 9, T + 11); 
    gotoxy(L + 25, T + 10); cout << "start";      
    printRectangle(L + 65, L + 72, T + 9, T + 11);
    gotoxy(L + 66 ,T + 10); cout << "change"; 

    ///print places
    textcolor(15);
    gotoxy(L + 5, T + 10); cout << "wait( )";
    gotoxy(L + 45,T + 10); cout << "inside( ) ";
    gotoxy(L + 85,T + 10); cout << "done( ) ";

    //print the number of token in every place 
    printNumOftoken(marking, "wait", L + 10, T + 10);
    printNumOftoken(marking, "inside", L + 52, T + 10);
    printNumOftoken(marking, "done", L + 90, T + 10);

    // In các dấu mũi tên nằm ngang  
    textcolor(8);
    inngang(L + 12, L + 24, T + 10);
    inngang(L + 30, L + 45, T + 10);
    inngang(L + 54, L + 65, T + 10);
    inngang(L + 72, L + 85, T + 10);
    //==============

}


//Set Firing transition automatically 
void auto_firingItem2(PetriNet N) {
    bool terminal = false; // kiểm tra trạng thái cuối cùng  của Petri Net 
    map<string, int> marking = N.getMarking(); 

    while (!terminal) { // if terminal == true ,end loop  
       //press 0 to turn off auto_firing 
        if (_kbhit()) { 
            char c = _getch();
            if (c == '0') return;
        }

        terminal = true;
        // enabled transition start 
        if (N.firing("start")) {
            marking = N.getMarking();
            textcolor(9);
            inngang_Color(L + 12,L + 24 , T + 10);
            inngang_Color(L + 30, L + 45, T+ 10);
            drawPetriNetItem2(marking);
            gotoxy(L +2, T + 15);
            textcolor(15);
            cout << "Current state: ";  N.printMarking();
            terminal = false;
        } 
        //enable transition change 
        else if (N.firing("change")) {
            marking = N.getMarking();
            textcolor(9);
            inngang_Color(L + 54, L + 65, T + 10);
            inngang_Color(L + 72, L + 85, T + 10);
            drawPetriNetItem2(marking);
            gotoxy(L + 2, T + 15); textcolor(15);
            cout << "Current state: ";  N.printMarking();
            terminal = false;
        }

    }
}


// print menu 
void showMenuItem2() {
    int marginTop = T + 8;  // Dùng để căn chinh vị trí in menu 
    textcolor(10);
    printRectangle(R + 5, R + 55, marginTop - 5, marginTop - 1);
    textcolor(7);
    gotoxy(R + 6, marginTop - 4); cout << " This PetriNet describe the course of business";
    gotoxy(R + 6, marginTop - 3); cout << " around a specialist in this outpatient clinic ";
    gotoxy(R + 6, marginTop - 2); cout << " of hospital X. ";
    textcolor(3);
    printRectangle(R + 5, R + 55, marginTop, marginTop + 2);
    gotoxy(R + 6, marginTop + 1); cout << "Press 1 to set initial marking.";

    printRectangle(R + 5, R + 55, marginTop + 3, marginTop + 5);
    gotoxy(R + 6, marginTop + 4); cout << "Press 2 to set auto firing";

    printRectangle(R + 5, R + 55, marginTop + 6, marginTop + 8);
    gotoxy(R + 6, marginTop + 7); cout << "Press 3 to quit";
}

// main 
void item2() {
    //build the petri net 
    PetriNet N;
    //create 3 places  
    N.pushPlace("wait");
    N.pushPlace("inside");
    N.pushPlace("done");
    //create 3 transitions
    N.pushTransition("start");
    N.pushTransition("change");
    // Init arcs between place and transition  
    N.arcPT("wait", "start");
    N.arcTP("start", "inside");
    N.arcPT("inside", "change");
    N.arcTP("change", "done");
    //==========================

    //print initial marking 
    textcolor(7);
    map<string, int> marking = N.getMarking();     // get marking from petri net
    cout << "\n   Initial Marking :"; N.printMarking();
    
    // vẽ petri net lên màn hình, in menu 
    drawPetriNetItem2(marking); 
    showMenuItem2();

    bool quit = false;  // Dùng để thoát khỏi vòng lặp 
    while (!quit) {
        if (_kbhit()) {  
            char ch = _getch();
            switch (ch) {
            case '1':  // press 1 to set initial marking 
                gotoxy(L, B + 1);
                N.setMarking();
                system("cls");
                marking = N.getMarking();
                cout << "\nInitial Marking :"; N.printMarking();
                drawPetriNetItem2(marking);
                showMenuItem2();
                break;
            case '2':   // press 2 to set auto firing 
                system("cls") ;
                marking = N.getMarking();
                cout << "\nInitial Marking :"; N.printMarking();
                drawPetriNetItem2(marking);
                printRectangle(R + 5, R + 55, T + 11, T + 13);
                gotoxy(R + 6, T + 12); cout << "Press 0 to stop auto firing";
                auto_firingItem2(N);
                showMenuItem2() ;
                break;
            case '3':  // press 3 to set quit =true ;
                quit = true;
                break;
            default:
                break;
            }
        }
    }
    N.cleanUp(); // free memory 
    printMainMenu(); // goto main menu 
}
#endif // !ITEM2_H_

