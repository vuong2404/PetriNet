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
        count ++ ;
    if (marking.count(N.getMarking()) == 0) {
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
    N.pushPlace("a") ;
    N.pushPlace("b") ;
    N.pushPlace("c") ;
    N.pushPlace("d") ;
    N.pushPlace("out") ;

    N.pushTransition("t1") ;
    N.pushTransition("t2") ;
    N.pushTransition("t3") ;
    N.pushTransition("t4") ; 

    N.arcPT("a", "t1") ;
    N.arcPT("b", "t2") ;
    N.arcPT("c", "t3") ;
    N.arcPT("d", "t4") ;

    N.arcTP("t1", "out") ;
    N.arcTP("t2", "out") ;
    N.arcTP("t3", "out") ;
    N.arcTP("t4", "out") ; 
    
    vector<string>  sequence;  // contains sequence enabled transition
    set<map<string, int>> marking;  // contains list reachable marking 
    N.setMarking();    // set initial marking 
    marking.insert(N.getMarking()); // save initial marking to set of reachable marking 
    cout << endl;
    
    // initial marking is reachable marking when firing empty sequence 
    textcolor(11) ; cout<<"Firing sequence <>" <<endl; 
    N.printMarking() ;
    //===================
    vector<string> transEnabled ; // save list transitions can be enabled 
    vector<string> Trans{ "t1", "t2", "t3", "t4", "out" };  // save list transitions of Petri Net N 
    for (int i = 0; i < 5 ; i++) {
        //push transitions can be enabled into transEnabled  
        if (N.enabled(Trans[i])) {   
            transEnabled.push_back(Trans[i]) ;
        }
    } 
    solve_greater1_enables(N, Trans, transEnabled, sequence, marking);
    cout << "There are "<<marking.size()<<" reachable markings. "<<endl ; 
    cout<<endl ; 
    N.cleanUp(); 
    cout<<"\n"<<count ; 
    system ("pause") ;

}