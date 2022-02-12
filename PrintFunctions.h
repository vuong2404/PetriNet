#ifndef PRINTFUNCTIONS_H_
#define PRINTFUNCTIONS_H_ 
#include "graphics.h"
// in mũi tên theo chiều ngang 
void inngang(int x1, int x2, int y) { 
    if (x1 < x2) {
        for (int i = x1 + 1; i < x2 - 1; i++) {
            gotoxy(i, y);  cout << char(196);
        }
        cout << ">";
    }
    else if (x1 > x2) {
        gotoxy(x2, y); cout << "<";
        for (int i = x2 + 1; i < x1; i++) {
            gotoxy(i, y); cout << char(196);
        }
    }
}

// in mũi tên theo chiều dọc 
void indoc(int x, int y1, int y2) {     
    if (y1 < y2) {                     
        for (int i = y1 + 1; i < y2 - 1; i++) {
            gotoxy(x, i); cout << char(179);
        }
        gotoxy(x, y2 - 1);  cout << char(281);
    }
    else if (y1 > y2) {
        gotoxy(x, y2 + 1); cout << char(280);
        for (int i = y2 + 2; i <= y1; i++) {
            gotoxy(x, i); cout << char(179);
        }
    }
}

// print rectangle 
void printRectangle(int x1, int x2, int y1, int y2) {
    gotoxy(x1, y1); cout << char(474);
    gotoxy(x2, y1); cout << char(439);
    gotoxy(x1, y2); cout << char(468);
    gotoxy(x2, y2); cout << char(473);
    for (int i = x1+1; i <= x2-1; i++) {
        gotoxy(i, y1); cout << char(196);
        gotoxy(i, y2); cout << char(196);
    }
    for (int i = y1 + 1; i <= y2-1; i++) {
        gotoxy(x1, i); cout << char(179);
        gotoxy(x2, i); cout << char(179);
    }
}

// In mũi tên theo chiều ngang  khi firing 
void inngang_Color(int x1, int x2, int y) {
    if (x1 < x2) {
        for (int i = x1 + 1; i < x2 - 1; i++) {
            gotoxy(i, y);
            Sleep(50);
            cout << char(249);
        }
        Sleep(50);
        cout << ">";
    }
    else if (x1 > x2) {
        for (int i = x1; i >= x2 + 1; i--) {
            gotoxy(i, y);
            Sleep(50);
            cout << char(249);
        }
        gotoxy(x2, y); cout << "<";
    }
}

//in mũi tên theo chiều dọc khi firing 
void indoc_Color(int x, int y1, int y2) {
    if (y1 < y2) {
        for (int i = y1 + 1; i < y2 - 1; i++) {
            gotoxy(x, i); Sleep(50); cout << char(!49);
        }
        gotoxy(x, y2 - 1); Sleep(50); cout << "v";
    }
    else if (y1 > y2) {
        for (int i = y1; i >= y2 + 2; i--) {
            gotoxy(x, i); Sleep(50); cout << char(249);
        }
        gotoxy(x, y2 + 1); Sleep(50); cout << "^";
    }
}

// Print main menu 
void printMainMenu() {
    //Thu nhỏ màn hình consolo  and clear screen 
    resizeConsole(300, 400);
    textcolor(7);;
    system("cls");

    //print rectangle frames
    printRectangle(4, 35, 4, 6);
    printRectangle(4, 35, 7, 9);
    printRectangle(4, 35, 10, 12);
    printRectangle(4, 35, 13, 15);
    printRectangle(4, 35, 16, 18);
    printRectangle(4, 35, 19, 21);
    
    //print conntent   
    textcolor(11) ; 
    gotoxy(5, 5);  cout << "Please enter your choice!";
    gotoxy(5, 8);  cout << "1 to show ITEM1";
    gotoxy(5, 11); cout << "2 to show ITEM2";
    gotoxy(5, 14); cout << "3 to show ITEM3";
    gotoxy(5, 17); cout << "4 to show ITEM4";
    gotoxy(5, 20); cout << "Other to quit";
}


// print the number of token in every place 
void printNumOftoken(map<string, int> marking, string nameOFplace, int x, int y) {
    gotoxy(x, y); 
    textcolor(3);
    if (marking[nameOFplace] > 9) {
        cout << marking[nameOFplace];
        textcolor(15);
        cout << ")";
        textcolor(15);
    }
    else {
        cout << marking[nameOFplace];
    }
}

#endif // !PRINTFUNCTIONS_H_

