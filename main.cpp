#include "main.h"
//set console screen 
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 1200;
int main() {
    bool quit = false;
    textcolor(14);
    printMainMenu();  
    while (!quit) { 
         if (_kbhit()) { 
             char ch = _getch();
             switch (ch) {

                case '1':   // press 1 to show item1 
                    system("cls");
                    resizeConsole(SCREEN_HEIGHT - 200, SCREEN_WIDTH);
                    item1();
                    break;

                case '2':   // press 2 to show item2 
                    system("cls");
                    resizeConsole(SCREEN_HEIGHT, SCREEN_WIDTH);
                    
                    item2();
                    break;  // press 4 to show item3 

                case '3':
                    system("cls");
                    resizeConsole(SCREEN_HEIGHT, SCREEN_WIDTH);
                    item3();
                    break;
        
                case '4':  // press 4 to show item4 
                    system("cls");
                    resizeConsole(SCREEN_HEIGHT, SCREEN_WIDTH);
                    item4();
                    break;
                default:   // press other key to quit 
                    quit = true;
                    break;
                }
         } 
    }
    system("cls");
    return 0; 
}
