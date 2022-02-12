#ifndef ITEM4_H_
#define ITEM4_H_
#include "PetriNet.h"
#include<vector>
#include<map>
#include <set> 
#include<queue> 
#include<stack>
vector<map<string, int>> marking;  // Dùng để lưu tất cả marking của petri net 
vector<vector<string>> listSequence ; // Dùng để lưu tất cả các sequence transition enabled 
void printSequence(vector<string> sq) {
    cout << "(";
    for (int i = 0; i < (int)sq.size(); i++) {
        if (i == (int)sq.size() - 1) {
            cout << sq[i] << ")\n";
        }
        else cout << sq[i] << ", ";
    }
}
// 
void solve_2_enables(PetriNet N, vector<string>Trans, vector<string> transEnabled, vector<string> sequence);
void solve_1_enable(PetriNet N,vector<string> Trans, string tranEnabled, vector<string>sequence){
    N.firing(tranEnabled); 
    listSequence.push_back(sequence) ; 
    sequence.push_back(tranEnabled);
    printSequence(sequence);
    N.printMarking(); 
    marking.push_back(N.getMarking());
    cout << endl;

    vector<string> transEnabled; 
    for (int i = 0; i < 3; i++) {
        if (N.enabled(Trans[i])) {
            transEnabled.push_back(Trans[i]);
        }
    }
    if (transEnabled.size() == 1) {
        solve_1_enable(N, Trans, transEnabled[0], sequence);
    }
    else if (transEnabled.size() > 1) {
        solve_2_enables(N, Trans, transEnabled, sequence);
    } 
    else {
        return;
    }
}
void solve_2_enables(PetriNet N, vector<string>Trans, vector<string> transEnabled, vector<string> sequence, vector<map<string, int>>& marking) 
{
    for (int i = 0; i < (int)transEnabled.size(); i++) {
        map<string, int> cur_state = N.getMarking();
        solve_1_enable(N, Trans, transEnabled[i], sequence);
        N.setMarking(cur_state);
    }
}
void item4() {
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
    vector<string>  sequence;
    N.setMarking(); 
    marking.push_back(N.getMarking());
    cout << endl;
    vector<string> Trans{ "start", "change", "end" }; 
    solve_1_enable(N, Trans, "start", sequence);
    cout << marking.size();
    N.cleanUp(); 
}

#endif