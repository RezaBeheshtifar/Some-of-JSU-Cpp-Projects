#include <stdio.h>
#include <windows.h>

using namespace std;

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si,sizeof(si));
    si.cb=sizeof(si);
    ZeroMemory(&pi,sizeof(pi));
    int a;
    a=CreateProcess(NULL,"c:\\windows\\system32\\mspaint.exe",NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
    if(a==0)
    {
        printf("Create Process failed!\n");
        return -1;
    }
    WaitForSingleObject(pi.hProcess,INFINITE);
    printf("Child Complete.\n");
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    system("pause");
    return 0;
}
