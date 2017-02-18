#include <iostream>

#define _WIN32_WINNT 0x0500

#include <windows.h>
#include "console.ddt"
using namespace std;
using namespace ddt::console;

void ResizeConsole(int width, int height){
    //wymaga naglowka windows.h

    RECT rcClient, rcWindow;    // RECT to struktura opisujaca pozycje prostokata
    POINT ptDiff;                // POINT to pozycja opisujaca wspolrzedne punktu
    HWND hwnd;                    // HWND to uchwyt do okna

    hwnd = GetConsoleWindow();        //pobieramy uchwyt do konsoli
    GetClientRect(hwnd, &rcClient);    //pobieramy info o rozmiarze obszaru roboczego okna
    GetWindowRect(hwnd, &rcWindow);    //pobieramy info o rozmiarze calosci okna

    ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;        //roznica szerokosci obszarow
    ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;        //roznica wysokosci obszarow

    MoveWindow(hwnd, rcWindow.left, rcWindow.top, width + ptDiff.x, height + ptDiff.y, TRUE);        //zmiana pozycji i rozmiaru okna
}


main()
{
    COORD size;

    size.X = 80; // min 80
    size.Y = 40;  // min 25
     
    //cout << SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);
    //ResizeConsole(1024,768);
    resize(80,40);
    gotoxy(80,41);
    cout << "kasper";
    char b;
    cin >> b;
    clrscr();
    char c;
    cin >> c;
}
