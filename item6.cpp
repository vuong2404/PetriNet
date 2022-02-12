#include "PetriNet.h" 
#include "graphics.h" 
#include "PrintFunctions.h" 
#include<vector>
#include<map>
#include <set> 
#include<queue> 
#include<stack>
using namespace std ; 
static int count = 0 ;
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
    N.firing(tranEnabled); 
    if (marking.count(N.getMarking()) == 0) {
        count ++ ;
        sequence.push_back(tranEnabled);
        printSequence(sequence);
        N.printMarking(); 
        marking.insert(N.getMarking());
        cout << endl;
    }
    vector<string> transEnabled; 
    for (int i = 0; i <(int) Trans.size(); i++) {
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
int main() {
    PetriNet N ; 
    N.pushPlace("start") ;
    N.pushPlace("c1") ;
    N.pushPlace("c2") ;
    N.pushPlace("c3") ;
    N.pushPlace("c4") ;
    N.pushPlace("c5") ;
    N.pushPlace("end") ;
   

    N.pushTransition("a") ;
    N.pushTransition("b") ;
    N.pushTransition("c") ;
    N.pushTransition("d") ;
    N.pushTransition("e") ;
    N.pushTransition("f") ;
    N.pushTransition("g") ;
    N.pushTransition("h") ;

    

    N.arcPT("start", "a") ;
    N.arcPT("c1", "b") ;
    N.arcPT("c1", "c") ;
    N.arcPT("c2", "d") ;
    N.arcPT("c3", "e") ;
    N.arcPT("c4", "e") ;
    N.arcPT("c5", "f") ;
    N.arcPT("c5", "g") ;
    N.arcPT("c5", "h") ;

    N.arcTP("a", "c1") ;
    N.arcTP("a", "c2") ;
    N.arcTP("b", "c3") ;
    N.arcTP("c", "c3") ;
    N.arcTP("d", "c4") ;
    N.arcTP("e", "c5") ;
    N.arcTP("g", "end") ;
    N.arcTP("h", "end") ;
    N.arcTP("f", "c1") ;
    N.arcTP("f", "c2") ;
    
    vector<string>  sequence;  // contains sequence enabled transition
    set<map<string, int>> marking;  // contains list reachable marking 
    N.setMarking();    // set initial marking 
    marking.insert(N.getMarking()); // save initial marking to set of reachable marking 
    cout << endl;
    
    // initial marking is reachable marking when firing empty sequence 
    textcolor(11) ; cout<<"Firing sequence <>" <<endl; 
    N.printMarking() ;
    //===================
    vector<string> transEnabled  ; // save list transitions can be enabled 
    vector<string> Trans{ "a", "b", "c", "d", "e", "h", "g" };  // save list transitions of Petri Net N 
    for (int i = 0; i < (int)Trans.size() ; i++) {
        //push transitions can be enabled into transEnabled  
        if (N.enabled(Trans[i])) {   
            transEnabled.push_back(Trans[i]) ;
        }
    } 
    if (transEnabled.size() > 1)
    solve_greater1_enables(N, Trans, transEnabled, sequence, marking); 
    else solve_1_enable (N, Trans, transEnabled[0], sequence, marking) ;
    cout << "There are "<<marking.size()<<" reachable markings. "<<endl ; 
    cout<<endl ; 
    N.cleanUp(); 
    cout<<"\n"<<count ; 

    system ("pause") ;

}