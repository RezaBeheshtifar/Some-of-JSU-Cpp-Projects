#include <windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

HANDLE FH,GH;

DWORD WINAPI F(LPVOID param)
{
    //WaitForSingleObject(GH,INFINITE);
    for(int i=1 ; i<=1000 ; i++)
        cout << '+';
    return 0;
}

DWORD WINAPI G(LPVOID param)
{
    WaitForSingleObject(FH,INFINITE);
    for(int i=1 ; i<=1000 ; i++)
        cout << '-';
    return 0;
}

int main()
{
    FH=CreateThread(NULL,0,F,NULL,0,NULL);
    GH=CreateThread(NULL,0,G,NULL,0,NULL);
    getchar();
    return 0;
}
