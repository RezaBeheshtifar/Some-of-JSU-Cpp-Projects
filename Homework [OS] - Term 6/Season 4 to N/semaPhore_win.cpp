#include <windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

HANDLE Sem,S1,S2;
HANDLE FH,GH;

DWORD WINAPI F(LPVOID param)
{
    WaitForSingleObject(Sem,INFINITE); // WAIT
    for(int i=1 ; i<=1000 ; i++)
        cout << '+';
    ReleaseSemaphore(Sem,1/*RELEASE*/,NULL); // SIGNAL
    ReleaseSemaphore(S1,1,NULL);
    return 0;
}

DWORD WINAPI G(LPVOID param)
{
    WaitForSingleObject(Sem,INFINITE); // WAIT
    for(int i=1 ; i<=1000 ; i++)
        cout << '-';
    ReleaseSemaphore(Sem,1/*RELEASE*/,NULL); // SIGNAL
    ReleaseSemaphore(S2,1,NULL);
    return 0;
}

int main()
{
    Sem=CreateSemaphore(NULL,1/*COUNT*/,1/*MAX*/,NULL);
    S1 =CreateSemaphore(NULL,0/*COUNT*/,1/*MAX*/,NULL);
    S2 =CreateSemaphore(NULL,0/*COUNT*/,1/*MAX*/,NULL);

    FH=CreateThread(NULL,0,F,NULL,0,NULL);
    GH=CreateThread(NULL,0,G,NULL,0,NULL);

    WaitForSingleObject(S1,INFINITE); // WAIT
    WaitForSingleObject(S2,INFINITE); // WAIT

    //getchar();
    return 0;
}
