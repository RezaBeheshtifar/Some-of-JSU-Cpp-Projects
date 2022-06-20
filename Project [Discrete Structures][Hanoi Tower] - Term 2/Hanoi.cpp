#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

void hanoi(int, char, char, char);
void loading(void);

int main(int argc, char *argv[])
{   
    system("title * Reza Beheshtifar * Final Project - Hanoi Tower *");
    system("color 9F");
    loading();                                                               //   For Deley
    int n;
    char Start='A',Temp='B',Finish='C';
    while(1)
    {   
        cout << "\n\n Input the number of Disk: ";
        cin >> n;
        hanoi(n,Start,Temp,Finish);
    }
    return EXIT_SUCCESS;
}

//---------------------------------------------------------------------------------------

void hanoi (int Disk, char start, char temp, char finish)
{
    if (Disk==1)
       cout << setw(40) << start << " ---> " << finish << endl;              //   A >>> C
    else
    {
       hanoi (Disk-1, start, finish, temp);                                  //   A >>> B  ;A=n-1
       cout << setw(40) << start << " ---> " << finish << endl;              //   A >>> C
       hanoi (Disk-1, temp, start, finish);                                  //   B >>> C  ;B=n-1
    }
}
void loading(void)
{  
    int timeload = 1001;
    time_t t1;
    float t;
    t1 = time(NULL);
    double sum=0;
    cout << "\n\n\n\n\n\n\n\n\n\n";
    for (int i=0; i<timeload ;i++)
    {  
       for (int num=0; num<600000 ; num++)
   	      sum += num;
	   cout << "\t\t\t\tLOADING " << i/10 << "%\r";
    }
    system("cls");
}
