#ifndef ITEM4_H_
#define ITEM4_H_
#include "PetriNet.h"
#include<vector>
#include<map>
#include <set> 
#include<queue> 
#include<stack>

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
void solve_greater1_enables(PetriNet N, vector<string>Trans, vector<string> transEnabled, vector<string> sequence, set<map<string,int>> &marking);

//solve if there is a transition can be enabled 
void solve_1_enable(PetriNet N,vector<string> Trans, string tranEnabled, vector<string>sequence, set<map<string, int>> &marking){
    N.firing(tranEnabled);  // firing transition enabled 
    printSequence(sequence); // In sequence đã firing để đạt trạng thái hiện tại 
    N.printMarking();    // In marking tại trạng thái hiện tại 
    sequence.push_back(tranEnabled); // Thêm label của transition đã kích hoạt vào sequence 

      
    // dùng phương thức insert của thư viện set sẽ đảm bảo các marking không trùng nhau, và những marking này chính là tập reachable markingmarking  
    marking.insert(N.getMarking());

    cout << endl;
    vector<string> transEnabled; 
    for (int i = 0; i < (int)Trans.size(); i++) {
        if (N.enabled(Trans[i])) {
            transEnabled.push_back(Trans[i]);
        }
    }
    if (transEnabled.size() == 1) {
        solve_1_enable(N, Trans, transEnabled[0], sequence, marking);
    }
    else if (transEnabled.size() > 1) {
        solve_greater1_enables(N, Trans, transEnabled, sequence, marking);
    } 
    else {
        return;
    }
}


void solve_greater1_enables(PetriNet N, vector<string>Trans, vector<string> transEnabled, vector<string> sequence, set<map<string, int>>& marking) 
{
    for (int i = 0; i < (int)transEnabled.size(); i++) {
        map<string, int> cur_state = N.getMarking();
        solve_1_enable(N, Trans, transEnabled[i], sequence, marking);
        N.setMarking(cur_state);
    }
}
void item4() {
    textcolor(15) ;
    //build petri net 
    PetriNet N;
    N.pushPlace("wait");
    N.pushPlace("free");
    N.pushPlace("inside");
    N.pushPlace("busy");
    N.pushPlace("docu");
    N.pushPlace("done");

    N.pushTransition("start");
    N.pushTransition("change");
    N.pushTransition("end");

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
    //===================
    vector<string>  sequence;  // contains sequence enabled transition
    set<map<string, int>> marking;  // contains list reachable marking 
    N.setMarking();    // set initial marking 
    marking.insert(N.getMarking()); // save initial marking to set of reachable marking 
    cout << endl;
    // initial marking is reachable marking when firing empty sequence 
    textcolor(11) ; cout<<"Firing sequence <>" <<endl; 
    N.printMarking() ;
    cout<<endl ;
    //===================
    vector<string> transEnabled ; // save list transitions can be enabled 
    vector<string> Trans{ "start", "change", "end" };  // save list transitions of Petri Net N 
    
    //push transitions can be enabled into transEnabled  
    for (int i = 0; i < Trans.size() ; i++) {
        if (N.enabled(Trans[i])) {   
            transEnabled.push_back(Trans[i]) ;
        }
    } 
    if (transEnabled.size() ==1) 
        solve_1_enable(N, Trans, transEnabled[0], sequence, marking);
    else 
        solve_greater1_enables(N, Trans, transEnabled, sequence, marking) ; 
    cout << "There are "<<marking.size()<<" reachable markings. "<<endl ; 
    cout<<endl ; 
    N.cleanUp(); 
}

#endif