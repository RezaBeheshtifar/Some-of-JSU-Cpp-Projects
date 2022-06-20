#include <iostream>
#include <ctime>
#include <windows.h>
#include "NumberOfCores.h"
using namespace std;

#define Max 64

int myArray[Max];
const int NumberOfCores=getNumCores();
const int WidthOfSegments=Max/NumberOfCores;

void fillArray();
void show();
DWORD WINAPI bubbleSort(LPVOID segment);
void myMerge();
void myMergeFunction(int low,int mid,int high);
bool isSuccessful();

//MAIN////////////////////////////////////////////////////////////////

int main()
{
    system("title R.Beheshtifar 911846105"); //PROGRAMMER NAME

    DWORD Tid[NumberOfCores];
    HANDLE THandle[NumberOfCores];
    int ThreadTempArray[NumberOfCores]; //SYNCHRONIZATION-PROBLEM SOLVE
    register int i;

    clock_t s,e;
	double timediff;

	s=clock();

    fillArray();
    cout << "\n 1st: RANDOM\n";
    show();
    for(i=0;i<NumberOfCores;i++)
        ThreadTempArray[i]=i;
    for(i=0;i<NumberOfCores;i++)
        THandle[i]=CreateThread(NULL,0,bubbleSort,&ThreadTempArray[i],0,&Tid[i]);
    for(i=0;i<NumberOfCores;i++)
        WaitForSingleObject(THandle[i],INFINITE);
    for(i=0;i<NumberOfCores;i++)
        CloseHandle(THandle[i]);
    cout << "\n 2nd: SORT\n";
    show();
    cout << "\n 3rd: MERGE\n";
    myMerge();
    show();

    e=clock();

    timediff=(e-s)/(double)CLOCKS_PER_SEC;
    if(isSuccessful())
    {
        system("color 0A"); //GREEN TEXT IN CONSOLE
        cout << "\n\n >>> Mission Completed in " << timediff << " sec with " << NumberOfCores << " cores";
    }
    else
    {
        system("color 0C"); //RED TEXT IN CONSOLE
        cout << "\n\n >>> Mission Failed!\b";
    }
    cout << "\n\n ";
    system("pause");
    return 0;
}

//FUNCTION////////////////////////////////////////////////////////////

void fillArray()
{
    srand(time(NULL));
    for(int i=0;i<Max;i++)
        myArray[i]=rand()%90+10; //TWO-DIGIT NUMBERS
}

void show()
{
    for(int i=0;i<Max;i++)
    {
        if((float)i/WidthOfSegments==i/WidthOfSegments)
            cout << endl;
        cout << myArray[i] << ',';
    }
    cout << "\b\b";
    cout << endl;
}

DWORD WINAPI bubbleSort(LPVOID segment)
{
    int seg=(*(int*)segment);
    int low=seg*WidthOfSegments;
    int high=low+WidthOfSegments;
    for(int i=low;i<high-1;i++)
        for(int j=low;j<high-1;j++)
        if(myArray[j]>myArray[j+1])
        {
            int temp=myArray[j];
            myArray[j]=myArray[j+1];
            myArray[j+1]=temp;
        }
}

void myMerge()
{
    if(NumberOfCores==1)
        return;
    // COMPUTE
    int merge_counter=NumberOfCores;
    int MergeTempArraySize=0, arr_counter=0;
    while(merge_counter/2)
    {
        merge_counter/=2;
        MergeTempArraySize+=merge_counter;
    }
    int MergeTempArray[3][MergeTempArraySize];
    merge_counter=NumberOfCores;
    while(merge_counter/2)
    {
        merge_counter/=2;
        int temp=Max/merge_counter;
        for(int i=0;i<merge_counter;i++)
        {
            /*LOW */MergeTempArray[0][arr_counter]=i*temp;
            /*HIGH*/MergeTempArray[2][arr_counter]=MergeTempArray[0][arr_counter]+temp-1;
            /*MID */MergeTempArray[1][arr_counter]=(MergeTempArray[2][arr_counter]-MergeTempArray[0][arr_counter]+1)/2-1+MergeTempArray[0][arr_counter];
            arr_counter++;
        }
    }
    // CALL
    for(int i=0;i<arr_counter;i++)
        myMergeFunction(MergeTempArray[0][i],MergeTempArray[1][i],MergeTempArray[2][i]);
}

void myMergeFunction(int low,int mid,int high)
{
    register int i,j,k,t;
    j=low;
    for(i=mid+1;i<=high;i++)
    {
        while(myArray[j]<=myArray[i] && j<i)
            j++;
        if(j==i)
            break;
        t=myArray[i];
        for(k=i;k>j;k--)
            myArray[k]=myArray[k-1];
        myArray[j]=t;
    }
}

bool isSuccessful()
{
    int temp=myArray[0];
    for(int i=1;i<Max;i++)
        if(myArray[i]<temp)
            return 0;
        else
            temp=myArray[i];
    return 1;
}
