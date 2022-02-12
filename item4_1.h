#ifndef ITEM4_H_
#define ITEM4_H_
#include "PetriNet.h"
#include<vector>
#include<map>
#include <set> 
#include<queue> 
#include<stack>
using namespace std ;

 // Store all making of Petri Net   
  // Store all sequence transition enabled 


// show menu 
void showMenuItem4() { 
    textcolor(3);
    printRectangle(R + 5, R + 55, T + 8, T + 10);
    gotoxy(R + 6, T + 9); cout << "Press 1 to set initial marking.";
   
    printRectangle(R + 5,R + 55, T + 11 , T + 13);
    gotoxy(R + 6, T + 12); cout << "Press 2 count markings";

    printRectangle(R + 5, R + 55, T + 14, T +16); 
    gotoxy(R + 6, T + 15); cout << "Press 3 to find sequence"; 

    printRectangle(R + 5, R + 55, T + 17, T +19); 
    gotoxy(R + 6, T + 18); cout << "Press 4 to quit";

}

//print sequence 
void printSequence(vector<string> sq) {
    textcolor(11) ;
    cout << "Firing sequence <";
    for (int i = 0; i < (int)sq.size(); i++) {
        if (i == (int)sq.size() - 1) {
            cout << sq[i];
        }
        else cout << sq[i] << ", ";
    }
    cout<<">\n" ;
    textcolor(15);
}  

//solve if many transition canbe enabled 
void solve_greater1_enables(PetriNet N, vector<string>Trans, vector<string> transEnabled,
             vector<string> sequence, vector<map<string, int>>&marking, vector<vector<string>> &listSequence);

//solve if there is a transition can be enabled 
void solve_1_enable(PetriNet N,vector<string> Trans, string tranEnabled, vector<string>sequence, 
                            vector<map<string, int>>&marking, vector<vector<string>> &listSequence)
    {
        N.firing(tranEnabled); 
        listSequence.push_back(sequence) ;
        marking.push_back(N.getMarking());

        sequence.push_back(tranEnabled);
        vector<string> transEnabled; 
        for (int i = 0; i < 3; i++) {
            if (N.enabled(Trans[i])) {
                transEnabled.push_back(Trans[i]);
            }
        }

        if (transEnabled.size() == 1) {
            solve_1_enable(N, Trans, transEnabled[0], sequence, marking, listSequence );
        }
        else if (transEnabled.size() > 1) {
            solve_greater1_enables(N, Trans, transEnabled, sequence, marking, listSequence);
        } 
        else {
            return;
        }
    }


void solve_greater1_enables(PetriNet N, vector<string>Trans, vector<string> transEnabled, vector<string> sequence,
                                    vector<map<string, int>>&marking, vector<vector<string>> &listSequence) 
{
    for (int i = 0; i < (int)transEnabled.size(); i++) {
        map<string, int> cur_state = N.getMarking();
        solve_1_enable(N, Trans, transEnabled[i], sequence, marking, listSequence);
        N.setMarking(cur_state);
    }
}

void item4() {
    textcolor(15) ;
    //build petri net 
    PetriNet N ;
    // create 6 place 
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
    vector<string> transEnabled ; // save list transitions can be enabled 
    vector<string> Trans{ "start", "change", "end" };  // save list transitions of Petri Net N 
    vector<string>  sequence;  // contains sequence enabled transition 
    vector<map<string, int>> marking;  // Dùng để lưu tất cả marking của petri net 
    vector<vector<string>> listSequence ; // Dùng để lưu tất cả các sequence transition enabled 
    

    // draw Petri Net on console 
    drawPetriNetItem3(N.getMarking()) ; 
    showMenuItem4() ;
    
    bool quit = false ;
    while (!quit) {
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
                case '1' :  // press 1 to set initial marking 
                // set marking 
                    gotoxy(L, B + 1);
                    N.setMarking();  
                    marking.push_back(N.getMarking()); // store initial marking to set of reachable marking  

                    system("cls") ; 
                    drawPetriNetItem3(N.getMarking()) ;
                    showMenuItem4() ;

                    //push transitions can be enabled into transEnabled  
                    for (int i = 0; i < 3 ; i++) {
                        if (N.enabled(Trans[i])) {   
                            transEnabled.push_back(Trans[i]) ;
                        }
                    } 
                    // caculate 
                    if (transEnabled.size() == 1)
                        solve_1_enable(N, Trans, transEnabled[0], sequence, marking, listSequence);
                    else 
                        solve_greater1_enables(N,Trans,transEnabled,sequence, marking, listSequence) ; 

                    break;
                case  '2': 
                    // clear screen 
                    system("cls"); 
                    cout<<"There are "<< marking.size() << " reachable marking"<<endl ;

                    printRectangle(L, L + 30, T , T + 2) ; textcolor(11) ;
                    gotoxy(L + 1, T + 1); cout << "Press 2 to continue!" ;  

                    printRectangle(L, L + 30, T + 4 , T + 6) ; textcolor(11) ;
                    gotoxy(L + 1, T + 5); cout << "Press other to end program!" ; 

                    
                    while(1) {
                        if (_kbhit()) {
                            char _ch = _getch() ; 
                            if (_ch == '2') {
                                system("cls") ; 
                                drawPetriNetItem3(N.getMarking()) ;
                                showMenuItem4() ;
                                return ; 
                            }
                        }
                    }   
                    break ; 
                case '3': // press 3 to set quit = true 
                    system("cls") ; 
                    for (int i = 0 ; i < listSequence.size() ; i++) {
                        printSequence(listSequence[i]) ; cout<<endl ;
                        N.printMarking(marking[i]) ; 
                    } 

                    cout<<"\nPress 0 to exits!" ;
                    while (1) {
                        if (_kbhit()) {
                            if (_getch() == '0') {
                                system("cls") ;  
                                drawPetriNetItem3(N.getMarking()) ;
                                showMenuItem4() ;
                                return ; 
                            }
                        }
                        else return ; 
                    }
                    break;
                default:
                    break;
            }
        }
    }
    N.cleanUp() ;
    cout << endl;
    
    // initial marking is reachable marking when firing empty sequence 
    textcolor(11) ; cout<<"Firing sequence <>" <<endl; 
    N.printMarking() ;
    //===================
    
    
    cout << "There are "<<marking.size()<<" reachable markings. "<<endl ; 
    cout<<endl ; 
    N.cleanUp(); 
}

#endif