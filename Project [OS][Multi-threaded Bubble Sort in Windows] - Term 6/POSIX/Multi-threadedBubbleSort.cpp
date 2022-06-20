#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

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

const int NumberOfCores=4;
const int WidthOfSegments=NumberOfData/NumberOfCores;
const int NumberOfSemaphore=(int)log2(NumberOfCores)+1;

bool flags[2*maxNumberOfCores-1]={NOFLAG};

sem_t SHandle[maxNumberOfCores]; //SEMAPHORE_HANDLE
pthread_mutex_t MutexHandle[maxNumberOfCores]; //MUTEX_HANDLE
pthread_mutex_t updateMutex; //MUTEX -> UPDATE MANEXTEMPTYSEGMENT[]
pthread_mutex_t flagsMutex; //MUTEX -> UPDATE FLAGS[]
pthread_mutex_t printMutex; //MUTEX -> PRINT MERGENUMBER

void fillArray();
void show();
void showMerge();

void* bubbleSort(void* segment);
void* merge(void* semNumber);

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
    //system("title R.Beheshtifar 911846105"); //PROGRAMMER NAME

    int UnitArray[NumberOfCores]; //SYNCHRONIZATION-PROBLEM SOLVE
    int SN=0,counter=NumberOfCores;
    register int i;

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    clock_t s,e;
	float timediff;

    initMergeArray();
    for(i=0;i<NumberOfCores;i++) //SYNCHRONIZATION-PROBLEM SOLVE
        UnitArray[i]=i;
    for(i=0;i<NumberOfSemaphore;i++) //BECAUSE BUBBLESORT THREAD USE SEMAPHORES
        sem_init(&SHandle[i],0,0/*INITIAL*/);
    for(i=0;i<NumberOfSemaphore-1;i++)
        pthread_mutex_init(&MutexHandle[i],NULL);
    pthread_mutex_init(&updateMutex,NULL);
    pthread_mutex_init(&flagsMutex,NULL);
    pthread_mutex_init(&printMutex,NULL);

    cout << "\n 1st: RANDOM";
    fillArray();
    show();

    cout << "\n 2nd: SORT & MERGE";

    /*START*/s=clock();

    for(i=0;i<NumberOfCores;i++)
        pthread_create(&tid,&attr,bubbleSort,&UnitArray[i]);

    while(counter/2)
    {
        counter/=2;
        for(i=0;i<counter;i++)
            pthread_create(&tid,&attr,merge,&UnitArray[SN]);
        SN++;
    }

    sem_wait(&SHandle[NumberOfSemaphore-1]); //WAIT

    /*END*/e=clock();

    timediff=(float)(e-s)/CLOCKS_PER_SEC;

    cout << "\n\n 3rd: RESULT";
    showMerge();
    cout << endl;

    for(i=0;i<NumberOfCores;i++)
        if(isSuccessfulSort(i))
        {
        }
        else
        {
            cout << "\n >>> Sort Segment " << i << " Failed\a" << endl;
        }
    if(isSuccessfulMerge())
    {
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
                cout << "Saving Failed.";
            }
        }
    }
    else
    {
        cout << "\n >>> Mission Failed with " << NumberOfCores << (NumberOfCores>1?" cores\a":" core\a");
    }

    getchar();
    return 0;
}

//FUNCTION////////////////////////////////////////////////////////////

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

void* bubbleSort(void* segment)
{
    ///
    int seg=(*(int*)segment);
    int low=seg*WidthOfSegments;
    int high=low+WidthOfSegments-1;
    ///
    pthread_mutex_lock(&printMutex); //WAIT
    cout << "\n\n SORT " << seg << " -> START";
    pthread_mutex_unlock(&printMutex); //SIGNAL
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
    pthread_mutex_lock(&printMutex); //WAIT
    cout << "\n\n SORT " << seg << " -> STOP";
    pthread_mutex_unlock(&printMutex); //SIGNAL
    ///
    pthread_mutex_lock(&flagsMutex); //WAIT
    flags[seg]=FLAG;
    pthread_mutex_unlock(&flagsMutex); //SIGNAL
    ///
    sem_post(&SHandle[0]); //SIGNAL

}

void* merge(void* semNumber)
{
    int SN=(*(int*)semNumber),MN,SEG;
    int p,q,pLow,pHigh,qLow,qHigh; //MERGE NUMBER & INDEX
    int FLI=flagsLowIndex(SN),FHI=flagsLowIndex(SN+1)-1; //STUDY BOUND
    bool sel=false;
    ///
    /*MH*/pthread_mutex_lock(&MutexHandle[SN]); //WAIT
    sem_wait(&SHandle[SN]); //WAIT
    sem_wait(&SHandle[SN]); //WAIT
    /*MH*/pthread_mutex_unlock(&MutexHandle[SN]); //SIGNAL
    ///
    /*UM*/pthread_mutex_lock(&updateMutex); //WAIT
    SEG=MAnextEmptySegment[SN];
    MAnextEmptySegment[SN]++;
    /*UM*/pthread_mutex_unlock(&updateMutex); //SIGNAL
    MN=flagsIndex(SN,SEG);
    /*PM*/pthread_mutex_lock(&printMutex); //WAIT
    cout << "\n\n MERGE " << MN << " -> START";
    /*PM*/pthread_mutex_unlock(&printMutex); //SIGNAL
    /*FM*/pthread_mutex_lock(&flagsMutex); //WAIT
    for(int i=FLI;i<=FHI;i++)
        if(flags[i]==FLAG)
            if(sel==false)
            { p=i; flags[i]=NOFLAG; sel=true; }
            else
            { q=i; flags[i]=NOFLAG; break; }
    /*FM*/pthread_mutex_unlock(&flagsMutex); //SIGNAL
    MergeArrayLowHighIndex(p,&pLow,&pHigh);
    MergeArrayLowHighIndex(q,&qLow,&qHigh);
    merge(pLow,pHigh,qLow,qHigh,SEG*MAwidthOfsegments[SN],SN);
    ///
    /*PM*/pthread_mutex_lock(&printMutex); //WAIT
    cout << "\n\n MERGE " << MN << " -> STOP";
    /*PM*/pthread_mutex_unlock(&printMutex); //SIGNAL
    /*FM*/pthread_mutex_lock(&flagsMutex); //WAIT
    flags[MN]=FLAG;
    /*FM*/pthread_mutex_unlock(&flagsMutex); //SIGNAL
    ///
    sem_post(&SHandle[SN+1]); //SIGNAL
}

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
