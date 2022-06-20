#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cmath>
#include "NumberOfCores.h"
#include "myTextColor.h"
using namespace std;

#define maxDataPerLine 16

#define NumberOfData 64
#define maxNumberOfCores 16 //MAXIMUM -> FOR ARRAY SIZE

#define NOFLAG false
#define FLAG true //READY FOR USE

int myArray[NumberOfData];

int myMergeArray[maxNumberOfCores][NumberOfData];
int MAwidthOfsegments[maxNumberOfCores];
int MAnextEmptySegment[maxNumberOfCores];

const int NumberOfCores=getNumCores();
const int WidthOfSegments=NumberOfData/NumberOfCores;
const int NumberOfSemaphore=(int)log2(NumberOfCores)+1;

bool flags[2*maxNumberOfCores-2]={NOFLAG};

HANDLE SHandle[maxNumberOfCores]; //SEMAPHORE_HANDLE
HANDLE MutexHandle[maxNumberOfCores]; //MUTEX_HANDLE -> USE 2ND TRY
HANDLE updateMutex=CreateSemaphore(NULL,1/*INITIAL COUNT*/,1/*MAXIMUM COUNT*/,NULL); //MUTEX -> UPDATE MANEXTEMPTYSEGMENT[]
HANDLE flagsMutex=CreateSemaphore(NULL,1/*INITIAL COUNT*/,1/*MAXIMUM COUNT*/,NULL); //MUTEX -> UPDATE FLAGS[]
HANDLE printMutex=CreateSemaphore(NULL,1/*INITIAL COUNT*/,1/*MAXIMUM COUNT*/,NULL); //MUTEX -> PRINT MERGENUMBER

void intro();
void fillArray();
void show();
void showMerge();

DWORD WINAPI bubbleSort(LPVOID segment);
DWORD WINAPI merge(LPVOID semNumber);

void merge(int pLow,int pHigh,int qLow,int qHigh,int rLow,int currentSN);
void initMergeArray();
int flagsLowIndex(int SN); //SN: SEMAPHORE NUMBER
void MergeArrayLowHighIndex(int MN,int* LOW,int* HIGH); //MN: MERGE NUMBER
int flagsIndex(int SN,int SEG); //SN: SEMAPHORE NUMBER, SEG: SEGMENT NUMBER

bool isSuccessfulSort(int segment);
bool isSuccessfulMerge();
bool save();

//MAIN////////////////////////////////////////////////////////////////

int main()
{
    system("title R.Beheshtifar 911846105"); //PROGRAMMER NAME

    int UnitArray[NumberOfCores]; //SYNCHRONIZATION-PROBLEM SOLVE
    int SN=0,counter=NumberOfCores;
    register int i;

    clock_t s,e;
	float timediff;

	intro();

    initMergeArray();
    for(i=0;i<NumberOfCores;i++) //SYNCHRONIZATION-PROBLEM SOLVE
        UnitArray[i]=i;
    for(i=0;i<NumberOfSemaphore;i++) //BECAUSE BUBBLESORT THREAD USE SEMAPHORES
        SHandle[i]=CreateSemaphore(NULL,0/*INITIAL COUNT*/,NumberOfCores/*MAXIMUM COUNT*/,NULL); //MAXIMUM COUNT=NUMBER OF BUBBLESORT
    for(i=0;i<NumberOfSemaphore-1;i++)
        MutexHandle[i]=CreateSemaphore(NULL,1/*INITIAL COUNT*/,1/*MAXIMUM COUNT*/,NULL);
	textColor(YELLOW);
    cout << "\n 1st: RANDOM";
    textColor(WHITE);
    fillArray();
    show();

    textColor(YELLOW);
    cout << "\n 2nd: SORT & MERGE";
    textColor(WHITE);

    /*START*/s=clock();

    for(i=0;i<NumberOfCores;i++)
        CreateThread(NULL,0,bubbleSort,&UnitArray[i],0,NULL);

    while(counter/2)
    {
        counter/=2;
        for(i=0;i<counter;i++)
            CreateThread(NULL,0,merge,&UnitArray[SN],0,NULL);
        SN++;
    }

    WaitForSingleObject(SHandle[NumberOfSemaphore-1],INFINITE); //WAIT

    /*END*/e=clock();

    timediff=(float)(e-s)/CLOCKS_PER_SEC;

    textColor(YELLOW);
    cout << "\n\n 3rd: RESULT";
    textColor(LIGHTCYAN);
    showMerge();
    for(i=0;i<NumberOfCores;i++)
        if(isSuccessfulSort(i))
        {
        }
        else
        {
            textColor(LIGHTRED); //RED TEXT IN CONSOLE
            cout << "\n >>> Sort Segment " << i << " Failed\a" << endl;
        }
    if(isSuccessfulMerge())
    {
        textColor(LIGHTGREEN); //GREEN TEXT IN CONSOLE
        cout << "\n >>> Mission Completed in " << timediff*1000 << " ms with " << NumberOfCores << (NumberOfCores>1?" cores\n":" core\n");
        char c;
        do{
            cout << "\n >>> Do you want to save Data in File? (Y/N) ";
            cin >> c;
        }while(c!='y' && c!='n' && c!='Y' && c!='N');
        if(c=='y' || c=='Y')
        {
            cout << "     ";
            if(save())
            {
                cout << "Data Saved.";
            }
            else
            {
                textColor(LIGHTRED);
                cout << "Saving Failed.";
            }
        }
    }
    else
    {
        textColor(LIGHTRED); //RED TEXT IN CONSOLE
        cout << "\n >>> Mission Failed with " << NumberOfCores << (NumberOfCores>1?" cores\a":" core\a");
    }

    textColor(BLACK);
    getch();
    return 0;
}

//FUNCTION////////////////////////////////////////////////////////////

void intro()
{
    textColor(LIGHTRED);
    cout << "\n\n\n\t\t\t Operating System Final Project";
    textColor(GREEN);
    cout << "\n\n\n\t\t\t Multi-threaded BubbleSort";
    textColor(LIGHTBLUE);
    cout << "\n\n\n\t\t\t for Microsoft Windows";
    textColor(YELLOW);
    cout << "\n\n\n\t\t\t Reza Beheshtifar";
    textColor(WHITE);
    cout << "\n\n\n\t\t\t 911846105";
    textColor(LIGHTGREEN);
    cout << "\n\n\n\n\n\t\t\t Professor: Mousa Mousazadeh";
    getch();
    system("cls");
}

void fillArray()
{
    srand(time(NULL));
    for(int i=0;i<NumberOfData;i++)
        myArray[i]=rand()%90+10; //TWO-DIGIT NUMBERS
}

void show()
{
    for(int i=0;i<NumberOfData;i++)
    {
        if(i%maxDataPerLine==0)
            cout << '\n' << '\n';
        cout << ' ' << myArray[i];
    }
    cout << '\n';
}

void showMerge()
{
    int row=(int)log2(NumberOfCores)-1;
    for(int i=0;i<NumberOfData;i++)
    {
        if(i%maxDataPerLine==0)
            cout << '\n' << '\n';
        cout << ' ' << myMergeArray[row][i];
    }
    cout << '\n';
}

DWORD WINAPI bubbleSort(LPVOID segment)
{
    ///
    int seg=(*(int*)segment);
    int low=seg*WidthOfSegments;
    int high=low+WidthOfSegments-1;
    ///
    WaitForSingleObject(printMutex,INFINITE); //WAIT
    cout << "\n\n SORT " << seg << " -> START";
    ReleaseSemaphore(printMutex,1/*RELEASE*/,NULL); //SIGNAL
    ///
    for(int i=low;i<high;i++)
        for(int j=low;j<high;j++)
        if(myArray[j]>myArray[j+1])
        {
            int temp=myArray[j];
            myArray[j]=myArray[j+1];
            myArray[j+1]=temp;
        }
    ///
    WaitForSingleObject(printMutex,INFINITE); //WAIT
    cout << "\n\n SORT " << seg << " -> STOP";
    ReleaseSemaphore(printMutex,1/*RELEASE*/,NULL); //SIGNAL
    ///
    WaitForSingleObject(flagsMutex,INFINITE); //WAIT
    flags[seg]=FLAG;
    ReleaseSemaphore(flagsMutex,1/*RELEASE*/,NULL); //SIGNAL
    ///
    ReleaseSemaphore(SHandle[0],1/*RELEASE*/,NULL); //SIGNAL
}

DWORD WINAPI merge(LPVOID semNumber)
{
    int SN=(*(int*)semNumber),MN,SEG;
    int p,q,pLow,pHigh,qLow,qHigh; //MERGE NUMBER & INDEX
    int FLI=flagsLowIndex(SN),FHI=flagsLowIndex(SN+1)-1; //STUDY BOUND
    bool sel=false;
    ///
    /*MH*/WaitForSingleObject(MutexHandle[SN],INFINITE); //WAIT
    WaitForSingleObject(SHandle[SN],INFINITE); //WAIT
    WaitForSingleObject(SHandle[SN],INFINITE); //WAIT
    /*MH*/ReleaseSemaphore(MutexHandle[SN],1/*RELEASE*/,NULL); //SIGNAL
    ///
    /*UM*/WaitForSingleObject(updateMutex,INFINITE); //WAIT
    SEG=MAnextEmptySegment[SN];
    MAnextEmptySegment[SN]++;
    /*UM*/ReleaseSemaphore(updateMutex,1/*RELEASE*/,NULL); //SIGNAL
    MN=flagsIndex(SN,SEG);
    /*PM*/WaitForSingleObject(printMutex,INFINITE); //WAIT
    cout << "\n\n MERGE " << MN << " -> START";
    /*PM*/ReleaseSemaphore(printMutex,1/*RELEASE*/,NULL); //SIGNAL
    /*FM*/WaitForSingleObject(flagsMutex,INFINITE); //WAIT
    for(int i=FLI;i<=FHI;i++)
        if(flags[i]==FLAG)
            if(sel==false)
            { p=i; flags[i]=NOFLAG; sel=true; }
            else
            { q=i; flags[i]=NOFLAG; break; }
    /*FM*/ReleaseSemaphore(flagsMutex,1/*RELEASE*/,NULL); //SIGNAL
    MergeArrayLowHighIndex(p,&pLow,&pHigh);
    MergeArrayLowHighIndex(q,&qLow,&qHigh);
    merge(pLow,pHigh,qLow,qHigh,SEG*MAwidthOfsegments[SN],SN);
    ///
    /*PM*/WaitForSingleObject(printMutex,INFINITE); //WAIT
    cout << "\n\n MERGE " << MN << " -> STOP";
    /*PM*/ReleaseSemaphore(printMutex,1/*RELEASE*/,NULL); //SIGNAL
    /*FM*/WaitForSingleObject(flagsMutex,INFINITE); //WAIT
    flags[MN]=FLAG;
    /*FM*/ReleaseSemaphore(flagsMutex,1/*RELEASE*/,NULL); //SIGNAL
    ///
    ReleaseSemaphore(SHandle[SN+1],1/*RELEASE*/,NULL); //SIGNAL
}

/*
NUMBER_OF_CORES=8
SN=SEMAPHORE_NUMBER
MN=MERGE_NUMBER
SEG=SEGMENT_NUMBER
                              MY_ARRAY:
      ---------------------------------------------------------
      | MN=0 | MN=1 | MN=2 | MN=3 | MN=4 | MN=5 | MN=6 | MN=7 | WIDTH_OF_SEGMENTS=NUMBER_OF_DATA/NUMBER_OF_CORES
      ---------------------------------------------------------
                           MY_MERGE_ARRAY:
      ---------------------------------------------------------
 SN=0 | MN=08,SEG=0 | MN=09,SEG=1 | MN=10,SEG=2 | MN=11,SEG=3 | MA_WIDTH_OF_SEGMENTS[0]=2*NUMBER_OF_DATA/NUMBER_OF_CORES
      ---------------------------------------------------------
 SN=1 |        MN=12,SEG=0        |        MN=13,SEG=1        | MA_WIDTH_OF_SEGMENTS[1]=4*NUMBER_OF_DATA/NUMBER_OF_CORES
      ---------------------------------------------------------
 SN=2 |                      MN=14,SEG=0                      | MA_WIDTH_OF_SEGMENTS[2]=8*NUMBER_OF_DATA/NUMBER_OF_CORES
      ---------------------------------------------------------
*/

void merge(int pLow,int pHigh,int qLow,int qHigh,int rLow,int currentSN)
{
    int i=pLow,j=qLow,k=rLow;
    if(currentSN==0) //INPUT1,INPUT2: MYARRAY, OUTPUT: MYMERGEARRAY
    {
        while(i<=pHigh && j<=qHigh)
            if(myArray[i]<myArray[j])
                myMergeArray[currentSN][k++]=myArray[i++];
            else
                myMergeArray[currentSN][k++]=myArray[j++];
        if(i==pHigh+1)
            while(j<=qHigh)
                myMergeArray[currentSN][k++]=myArray[j++];
        else
            while(i<=pHigh)
                myMergeArray[currentSN][k++]=myArray[i++];
    }
    else //INPUT1,INPUT2,OUTPUT: MYMERGEARRAY
    {
        while(i<=pHigh && j<=qHigh)
            if(myMergeArray[currentSN-1][i]<myMergeArray[currentSN-1][j])
                myMergeArray[currentSN][k++]=myMergeArray[currentSN-1][i++];
            else
                myMergeArray[currentSN][k++]=myMergeArray[currentSN-1][j++];
        if(i==pHigh+1)
            while(j<=qHigh)
                myMergeArray[currentSN][k++]=myMergeArray[currentSN-1][j++];
        else
            while(i<=pHigh)
                myMergeArray[currentSN][k++]=myMergeArray[currentSN-1][i++];
    }
}

void initMergeArray()
{
    int step=NumberOfData/NumberOfCores;
    int counter=2;
    for(int i=0;i<maxNumberOfCores;i++)
    {
        MAwidthOfsegments[i]=counter*step;
        MAnextEmptySegment[i]=0;
        counter*=2;
    }
}

int flagsLowIndex(int SN)
{
    //THIS FUNCTION RETURN MERGENUMBER(MN)_LOW FOR FLAGS_STUDYBOUND
    /*
    NUMBER_OF_CORES=8
    SN=SEMAPHORE_NUMBER
                                    FLAGS:
    -----------------------------------------------------------------------
    | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 | 11 | 12 | 13 | SIZE=2*NUMBER_OF_CORES-2
    -----------------------------------------------------------------------
    SN=0 -> FLAGS_STUDYBOUND: 00 TO 07
    SN=1 -> FLAGS_STUDYBOUND: 08 TO 11
    SN=2 -> FLAGS_STUDYBOUND: 12 TO 13
    */
    int step=NumberOfCores, FLI=0;
    while(SN--)
    {
        FLI+=step;
        step/=2;
    }
    return FLI;
}

void MergeArrayLowHighIndex(int MN,int* LOW,int* HIGH)
{
    //THIS FUNCTION RETURN LOW & HIGH OF MERGENUMBER(MN) -> USE FOR -> STUDY BOUND
    if(MN<NumberOfCores) //MYARRAY
    {
        *LOW=MN*WidthOfSegments;
        *HIGH=*LOW+WidthOfSegments-1;
    }
    else //MYMERGEARRAY
    {
        int step=NumberOfCores/2, mn=NumberOfCores, sn=0;
        while(mn+step<=MN)
        {
            mn+=step;
            step/=2;
            sn++;
        }
        *LOW=(MN-mn)*MAwidthOfsegments[sn];
        *HIGH=*LOW+MAwidthOfsegments[sn]-1;
    }
}

int flagsIndex(int SN,int SEG)
{
    //THIS FUNCTION RETURN MERGENUMBER(MN)
    /*
    NUMBER_OF_CORES=8
    SN=SEMAPHORE_NUMBER
    MN=MERGE_NUMBER
    SEG=SEGMENT_NUMBER
                               MY_MERGE_ARRAY:
          ---------------------------------------------------------
     SN=0 | MN=08,SEG=0 | MN=09,SEG=1 | MN=10,SEG=2 | MN=11,SEG=3 |
          ---------------------------------------------------------
     SN=1 |        MN=12,SEG=0        |        MN=13,SEG=1        |
          ---------------------------------------------------------
     SN=2 |                      MN=14,SEG=0                      |
          ---------------------------------------------------------
    */
    int MN=NumberOfCores, step=NumberOfCores/2;
    while(SN--)
    {
        MN+=step;
        step/=2;
    }
    return MN+SEG;
}

bool isSuccessfulSort(int segment)
{
    int startIndex=segment*WidthOfSegments;
    int stopIndex=startIndex+WidthOfSegments;
    int temp=myArray[startIndex];
    for(int i=startIndex+1;i<stopIndex;i++)
        if(myArray[i]<temp)
            return false;
        else
            temp=myArray[i];
    return true;
}

bool isSuccessfulMerge()
{
    int row=(int)log2(NumberOfCores)-1;
    int temp=myMergeArray[row][0];
    for(int i=1;i<NumberOfData;i++)
        if(myMergeArray[row][i]<temp)
            return false;
        else
            temp=myMergeArray[row][i];
    return true;
}

bool save()
{
    ofstream fout;
    fout.open("sort.txt");
    if(!fout.is_open())
        return false;
    int row=(int)log2(NumberOfCores)-1;
    for(int i=0;i<NumberOfData;i++)
    {
        if(i && i%maxDataPerLine==0)
            fout << '\n';
        fout << myMergeArray[row][i] << ' ';
    }
    fout.close();
    return true;
}
