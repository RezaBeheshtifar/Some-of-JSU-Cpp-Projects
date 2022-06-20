#include <windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int s=0;
int p=1;

DWORD WINAPI sum(LPVOID param)
{
    int N=*(int*)param;
    for(int i=1 ; i<=N ; i++)
        s+=i;
    return 0;
}

DWORD WINAPI mul(LPVOID param)
{
    int N=*(int*)param;
    for(int i=1 ; i<=N ; i++)
        p*=i;
    return 0;
}

int main()
{
    DWORD Tid1,Tid2;
    HANDLE THandle[2];
    int param=5;
    THandle[0]=CreateThread(NULL,0,sum,&param,0,&Tid1);
    THandle[1]=CreateThread(NULL,0,mul,&param,0,&Tid2);
    WaitForSingleObject(THandle[0],INFINITE);
    WaitForSingleObject(THandle[1],INFINITE);
    CloseHandle(THandle[0]);
    CloseHandle(THandle[1]);
    cout << "sum=" << s << endl;
    cout << "mul=" << p << endl;
    system("pause");
    return 0;
}
