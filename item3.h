#ifndef ITEM3_H_
#define ITEM3_H_
#include "main.h"
// L, R , T , B is defined in item1.h  

// print menu to control the program 
void showMenuItem3() { 
    textcolor(10);
    printRectangle(R + 5, R + 55, T + 3, T + 7); 
    textcolor(7);
    gotoxy(R + 6, T + 4); cout << " This PetriNet describe the course of business";
    gotoxy(R + 6, T + 5); cout << " around a specialist in this outpatient clinic "; 
    gotoxy(R + 6, T + 6); cout<< " of hospital X. " ; 
    textcolor(3);
    printRectangle(R + 5, R + 55, T + 8, T + 10);
    gotoxy(R + 6, T + 9); cout << "Press 1 to set initial marking.";
   
    printRectangle(R + 5,R + 55, T + 11 , T + 13);
    gotoxy(R + 6, T + 12); cout << "Press 2 to set auto firing";

    printRectangle(R + 5, R + 55, T + 14, T +16); 
    gotoxy(R + 6, T + 15); cout << "Press 3 to quit";
}

// draw Petri Net on console 
void drawPetriNetItem3(map<string, int> marking) {
    //print frame 
    textcolor(5);
    printRectangle(L, R, T, B);
    gotoxy(L + 1, T + 1) ; textcolor(11) ;
    cout<< "Item 3: Superimposed network" ;

    //draw transisions 
    textcolor(12);
    printRectangle(L + 20, L + 28, T + 8, T + 12);
    gotoxy(L + 21, T + 10);  cout << "start";
    printRectangle(L + 40, L + 54 - 9, T + 3, T + 7);
    gotoxy(L + 41, T + 5);  cout << "end";
    printRectangle(L + 60, L + 68, T + 8, T + 12);
    gotoxy(L + 61, T + 10);  cout << "change";
 
    //// draw places 
    textcolor(15);
    gotoxy(L +41, T + 10);  cout << "busy( )";
    gotoxy(L + 6, T + 10);  cout << "wait( )";
    gotoxy(L + 61, T + 5);  cout << "docu( )";
    gotoxy(L + 21, T + 5);  cout << "free( )";
    gotoxy(L + 41, T + 15);  cout << "inside( )";
    gotoxy(L + 81, T + 10); cout << "done( )";
    //====================================

    //// In các dấu mũi tên nối places  và transitions theo chiều ngang 
    textcolor(8);
    inngang(L + 13, L + 20, T + 10);
    inngang(L + 28, L + 41, T + 10);
    inngang(L + 48, L + 60, T + 10);
    inngang(L + 61, L + 46, T + 5);
    inngang(L + 40, L + 29, T + 5);
    inngang(L + 50, L + 63, T + 15);
    inngang(L + 23, L + 41, T + 15);
    inngang(L + 68, L + 81, T + 10);
    
    // In các mũi tên nối places và transitions theo chiều dọc 
    indoc(L + 23, T + 5, T + 8);
    indoc(L + 63, T + 15, T + 12);
    indoc(L + 63, T + 7, T + 5);
    indoc(L + 23, T + 12, T + 16); 
    gotoxy(L + 23, T + 15); cout << char(468);
    gotoxy(L + 62, T + 15);  cout << char(196)<<char(473);
    gotoxy(L + 61, T + 20);
    //============================

    // print the number of  token in every place 
    printNumOftoken(marking, "wait", L + 11, T + 10); 
    printNumOftoken(marking, "busy", L + 46, T + 10);
    printNumOftoken(marking, "docu", L + 66, T + 5);
    printNumOftoken(marking, "free", L + 26, T + 5);
    printNumOftoken(marking, "inside", L + 48, T + 15);
    printNumOftoken(marking, "done", L + 86, T + 10);
}

// Dùng Sleep() để tạo hiệu ứng động 
void showItem3(map<string, int> marking) {
    Sleep(400);
    drawPetriNetItem3(marking);
}

// Set auto firing automatically 
void auto_firingItem3(PetriNet N) { 
    bool terminal = false;  // Kiểm tra Petri net đi tới trạng thái cuối cùng 
    
    //draw Petri Net of Item3 
    map<string, int> marking = N.getMarking(); 
    showItem3(marking); 

    while (!terminal) {  // if terminal == true, end loop 
        //press 0 to stop auto firing 
        if (_kbhit()) {  
                char c = _getch();
                if (c == '0') return;
        }

        terminal = true; 

        //enabeld transition start 
        while (N.firing("start")) {
            if (_kbhit()) {
                char c = _getch();
                if (c == '0') return ;
            }
            marking = N.getMarking();
            inngang_Color(L + 13, L + 20, T + 10);
            indoc_Color(L + 32 - 9, T + 5, T + 8);
            showItem3(marking);

            ToMau(L + 30 - 9, T + 10, "start", 7);
            inngang(L + 28, L + 41, T + 10);
            indoc(L + 23, T + 12, T + 16) ;
            gotoxy(L + 23, T + 15); cout << char(468);
            inngang(L + 23, L + 41, T + 15);

            showItem3(marking);
            gotoxy(L + 4, T + 18); textcolor(14);
            cout << "Current state: ";  N.printMarking();
            terminal = false;
        }

        //enabeld transition change 
        while (N.firing("change")) {
            if (_kbhit()) {
                char c = _getch();
                if (c == '0') return;
            }
            marking = N.getMarking();
            inngang_Color(L + 48, L + 60, T + 10);
            inngang_Color(L + 50, L + 63, T + 15);
            indoc_Color(L + 63, T + 15, T + 12);
            showItem3(marking);
            
            ToMau(L + 61, T + 10, "change", 7);
            inngang(L + 68, L + 81, T + 10);
            indoc(L + 63, T + 7, T + 5);

            showItem3(marking);
            gotoxy(L + 4, T + 18); textcolor(14);
            cout << "Current state: ";  N.printMarking();
            terminal = false;
        }

        //enabeld transition end  
        while (N.firing("end")) {
            if (_kbhit()) {
                char c = _getch();
                if (c == '0') return;
            }
            marking = N.getMarking();
            inngang_Color(L + 60, L + 46, T + 5);
            showItem3(marking);

            ToMau(L + 41, T + 5, "end", 7);
            inngang_Color(L + 39, L + 29, T + 5);

            showItem3(marking);
            gotoxy(L + 4, T + 18); textcolor(14);
            cout << "Current state: ";  N.printMarking();
            terminal = false;
        } 
    }
}

void item3() {
    //build a Petri Net
    PetriNet N;
    // create 6 places 
    N.pushPlace("wait");
    N.pushPlace("free");
    N.pushPlace("inside");
    N.pushPlace("busy");
    N.pushPlace("docu");
    N.pushPlace("done");

    //create 3 transtion 
    N.pushTransition("start");
    N.pushTransition("change");
    N.pushTransition("end"); 

    //create arcs from trans to place and place to trans 
    N.arcPT("wait", "start");
    N.arcPT("free", "start");
    N.arcTP("start", "inside");
    N.arcTP("start", "busy");
    N.arcPT("inside", "change");
    N.arcPT("busy", "change");
    N.arcTP("change", "done");
    N.arcTP("change", "docu");
    N.arcPT("docu", "end");
    N.arcTP("end", "free");
    //========================== 
    
    //print initila marking, petri Net  and menu 
    map<string, int> marking = N.getMarking();
    cout << "\n   Initial Marking :"; N.printMarking();
    drawPetriNetItem3(marking);
    showMenuItem3(); 

    bool quit = false;   // quit == true, end loop 
    while (!quit) {
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
            case '1' :  // press 1 to set initial marking 
               // set marking 
                gotoxy(L, B + 1);
                N.setMarking();  

                /// clear screen 
                system("cls");  

                // print petri Net in new states 
                marking = N.getMarking(); 
                cout << "\nInitial Marking :"; N.printMarking();
                drawPetriNetItem3(marking); 
                showMenuItem3();
                break;
            case '2': // press 2 to set auto firing  
                // clear screen 
                system("cls"); 

                //print Petri Net without menu 
                marking = N.getMarking();
                cout << "\nInitial Marking :"; N.printMarking();
                drawPetriNetItem3(marking); 
                printRectangle(R + 5,R + 55, T + 11 , T + 13);
                gotoxy(R + 6, T + 12); cout << "Press 0 to stop auto firing";

                //set auto firing 
                auto_firingItem3(N);
                showMenuItem3() ;
                break;
            case '3' : // press 3 to set quit = true 
                quit = true;
                break;
            default:
                break;
            }
        }
    }
    N.cleanUp();     // free memory 
    printMainMenu(); // go to main menu 
}
#endif // ITEM1_H_

