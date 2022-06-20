#include <conio.h>
#include <iomanip>
#include <fstream>
#include <climits>
#include <ctime>
#include <cmath>

#include "myLibrary.h"
#include "myTextColor.h"

#define solutionAddress "solution.txt" // OUTPUT
#define sodukoProblemsAddress "sodukoProblems.txt" // INPUT

#define numberOfProblemsInFile 1 // RANGE: {1,2,3,...}
#define MAX_STEPS 100000 // RANGE: {1,2,3,...,UNSIGNED_INT_MAX}
#define PATH_PRINT 1 // RANGE: {0,1} OR {FALSE,TRUE}

using namespace std;

struct soduko
{
    short TABLE[9][9];
    bool SET[9][9]; // SET=0 --> VARIABLE, SET=1 --> CONST
};

soduko SODUKO;

void intro();

/*FUNCTIONS*/
char randomTable();
bool validTable();
void scanTable();
void printTable(const short table[9][9]);
void printSolution();
void randomCompleteAssignment();
bool solutionTest();
bool isConflictedVariable(const char row,const char column);
char minimumConflict(const char row,const char column);

/*CONTROLERS*/
void pathPrint(const char row,const char column);

/*CONVERTERS*/
void Comp2baseRowCol(const char component,char* row,char* column);
char RowCol2Comp(const char row,const char column);

/*SAVING*/
bool readyFile();
void save();

//MAIN////////////////////////////////////////////////////////////////

int main()
{
    system("title R.Beheshtifar 911846105"); //PROGRAMMER NAME

    clock_t s,e;
	float timediff;

    bool isSuccessful;
    unsigned int step;
    char rand_row,rand_col;
    char prg_continue='y',q;
    char randTable;

    intro();
    srand(time(NULL));

    while(prg_continue=='y' || prg_continue=='Y')
    {
        isSuccessful=false;
        step=0;
        textColor(LIGHTGREEN);
        cout << "\n >>> Do you want a random Table? [Y/N] ";
        cin >> q;
        if(q=='y' || q=='Y')
        {
            randTable=randomTable();
            if(randTable==-1)
                exit(-1);
            else if(randTable==-2)
                exit(-2);
            else
            {
                cout << "\n     table number = " << (short)randTable << endl;
            }
            if(!validTable())
                exit(-3);
            cout << endl;
            printTable(SODUKO.TABLE);
        }
        else
        {
            do{
                textColor(LIGHTGREEN);
                cout << "\n Enter the Soduko Table: [0 for Blank]\n\n";
                textColor(WHITE);
                scanTable();
                cout << "\n\n";
            }while(!validTable());
        }

        /*START*/s=clock();

        // MIN_CONFLICTS
        randomCompleteAssignment();
        do
        {
            // SOFT-RESTART TECHNIC
            if(step%200==0)
                randomCompleteAssignment();
            if(solutionTest())
            {
                isSuccessful=true;
                break;
            }
            do
            {
                rand_row=rand()%9;
                rand_col=rand()%9;
            }while(SODUKO.SET[rand_row][rand_col] || !isConflictedVariable(rand_row,rand_col));
            SODUKO.TABLE[rand_row][rand_col]=minimumConflict(rand_row,rand_col);
            if(PATH_PRINT)
            {
                cout << endl;
                pathPrint(rand_row,rand_col);
                textColor(WHITE);
                system("pause");
            }
        }while(++step<=MAX_STEPS);
        // MIN_CONFLICTS

        /*END*/e=clock();

        timediff=(float)(e-s)/CLOCKS_PER_SEC*1000;

        if(isSuccessful)
        {
            // RESULT
            printSolution();
            textColor(LIGHTGREEN);
            cout << "\n\n >>> Total Run Time: " << timediff << " (ms)"
                 << "\n\n     Number of Steps: " << step-1 << " (step)";
            cout << "\n\n >>> Do you want to save Solution in \"" << solutionAddress << "\" file? [Y/N] ";
            cin >> q;
            cout << endl;
            if(q=='y' || q=='Y')
            {
                if(readyFile())
                {
                    save();
                }
                else
                {
                    textColor(LIGHTRED);
                    cout << "     ERROR!\n\n";
                }
            }
        }
        else
        {
            // FAILURE
            textColor(LIGHTRED);
            cout << "\n\n >>> Solution not Found!";
            textColor(WHITE);
            cout << "\n\n >>> Total Run Time: " << timediff << " (ms)"
                 << "\n\n     Number of Steps: " << step-1 << " (step)"
                 << "\n\n";
        }

        textColor(CYAN);
        cout << " >>> Do you want to continue? [Y/N] ";
        cin >> prg_continue;
        system("cls");
    }

    textColor(WHITE);
    return 0;
}

//FUNCTION////////////////////////////////////////////////////////////

void intro()
{
    textColor(LIGHTRED);
    cout << "\n\n\n\t\t\t Artificial Intelligence";
    textColor(GREEN);
    cout << "\n\n\n\t\t\t Soduko Puzzle";
    textColor(CYAN);
    cout << "\n\n\n\t\t\t min_conflicts Algorithm";
    textColor(YELLOW);
    cout << "\n\n\n\t\t\t Reza Beheshtifar";
    textColor(WHITE);
    cout << "\n\n\n\t\t\t 911846105";
    textColor(LIGHTGREEN);
    cout << "\n\n\n\n\n\t\t\t Professor: Mousa Mousazadeh";
    getch();
    system("cls");
}

/*FUNCTIONS*/
char randomTable()
{
    ifstream fin(sodukoProblemsAddress);
    if(!fin.is_open())
        return -1;
    char i,j,f,r,ret;
    r=ret=rand()%numberOfProblemsInFile;
    while(r--)
    {
        i=0;
        while(i++!=9)
        {
            j=0;
            while(j++!=9)
            {
                do{ fin >> f; if(fin.eof()){ return -2; } }while(f=='-');
                //
            }
        }
    }
    i=0;
    while(i!=9)
    {
        j=0;
        while(j!=9)
        {
            do{ fin >> f; if(fin.eof()){ return -2; } }while(f=='-');
            if(f=='?'){ SODUKO.SET[i][j]=0; }
            else{ f-='0'; if(f<1 || f>9){ return -2; } SODUKO.SET[i][j]=1; SODUKO.TABLE[i][j]=f; }
            j++;
        }
        i++;
    }
    fin.close();
    return ret;
}

bool validTable()
{
    register char row,column,component;
    register char rowMax,columnMax;
    repeatDetection r;
    // STEP 1 --> ROW CHECK
    for(row=0;row<9;row++)
    {
        for(column=0;column<9;column++)
            if(SODUKO.SET[row][column])
                r.set(SODUKO.TABLE[row][column]);
        if(r.isRepeated())
            return false;
        r.reset();
    }
    // STEP 2 --> COLUMN CHECK
    for(column=0;column<9;column++)
    {
        for(row=0;row<9;row++)
            if(SODUKO.SET[row][column])
                r.set(SODUKO.TABLE[row][column]);
        if(r.isRepeated())
            return false;
        r.reset();
    }
    // STEP 3 --> COMPONENT CHECK
    for(component=0;component<9;component++)
    {
        Comp2baseRowCol(component,&row,&column);
        rowMax=row+3;
        columnMax=column+3;
        for(;row<rowMax;row++)
        {
            for(;column<columnMax;column++)
                if(SODUKO.SET[row][column])
                    r.set(SODUKO.TABLE[row][column]);
            column=columnMax-3;
        }
        if(r.isRepeated())
            return false;
        r.reset();
    }
    return true;
}

void scanTable()
{
    char i,j;
    short c;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            while(1)
            {
                cin >> c;
                if(c==0)
                {
                    SODUKO.SET[i][j]=0;
                    break;
                }
                else if(c>0 && c<10)
                {
                    SODUKO.TABLE[i][j]=c;
                    SODUKO.SET[i][j]=1;
                    break;
                }
            }
        }
}

void printTable(const short table[9][9])
{
    char i,j;
    textColor(WHITE);
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(SODUKO.SET[i][j]==1)
                cout << table[i][j];
            else
                cout << ' ';
            cout << ' ';
            if(j%3==2)
                cout << ' ';
        }
        cout << '\n';
        if(i%3==2)
            cout << '\n';
    }
}

void printSolution()
{
    char i,j;
    textColor(YELLOW);
    cout << " >>> Solution:\n\n";
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(SODUKO.SET[i][j]==1)
                textColor(WHITE);
            else
                textColor(YELLOW);
            cout << SODUKO.TABLE[i][j];
            cout << ' ';
            if(j%3==2)
                cout << ' ';
        }
        cout << '\n';
        if(i%3==2)
            cout << '\n';
    }
}

void randomCompleteAssignment()
{
    char i,j;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            if(SODUKO.SET[i][j]==0)
                SODUKO.TABLE[i][j]=rand()%9+1;
}

bool solutionTest()
{
    register char row,column,component;
    register char rowMax,columnMax;
    repeatDetection r;
    // STEP 1 --> ROW CHECK
    for(row=0;row<9;row++)
    {
        for(column=0;column<9;column++)
            r.set(SODUKO.TABLE[row][column]);
        if(r.isRepeated())
            return false;
        r.reset();
    }
    // STEP 2 --> COLUMN CHECK
    for(column=0;column<9;column++)
    {
        for(row=0;row<9;row++)
            r.set(SODUKO.TABLE[row][column]);
        if(r.isRepeated())
            return false;
        r.reset();
    }
    // STEP 3 --> COMPONENT CHECK
    for(component=0;component<9;component++)
    {
        Comp2baseRowCol(component,&row,&column);
        rowMax=row+3;
        columnMax=column+3;
        for(;row<rowMax;row++)
        {
            for(;column<columnMax;column++)
                r.set(SODUKO.TABLE[row][column]);
            column=columnMax-3;
        }
        if(r.isRepeated())
            return false;
        r.reset();
    }
    return true;
}

bool isConflictedVariable(const char row,const char column)
{
    register char r,c;
    register char rMax,cMax;
    repeatCounter v;

    char value=SODUKO.TABLE[row][column];

    // STEP 1 --> ROW CHECK
    for(c=0;c<9;c++)
        v.inc(SODUKO.TABLE[row][c]);
    if(v.get(value)>1)
        return true;
    v.reset();
    // STEP 2 --> COLUMN CHECK
    for(r=0;r<9;r++)
        v.inc(SODUKO.TABLE[r][column]);
    if(v.get(value)>1)
        return true;
    v.reset();
    // STEP 3 --> COMPONENT CHECK
    Comp2baseRowCol(RowCol2Comp(row,column),&r,&c);
    rMax=r+3;
    cMax=c+3;
    for(;r<rMax;r++)
    {
        for(;c<cMax;c++)
            v.inc(SODUKO.TABLE[r][c]);
        c=cMax-3;
    }
    if(v.get(value)>1)
        return true;

    return false;
}

char minimumConflict(const char row,const char column)
{
    register char r,c;
    register char rMax,cMax;
    repeatCounter cnt;

    SODUKO.TABLE[row][column]=0;

    // STEP 1 --> ROW
    for(c=0;c<9;c++)
        cnt.inc(SODUKO.TABLE[row][c]);
    // STEP 2 --> COLUMN
    for(r=0;r<9;r++)
        cnt.inc(SODUKO.TABLE[r][column]);
    // STEP 3 --> COMPONENT
    Comp2baseRowCol(RowCol2Comp(row,column),&r,&c);
    rMax=r+3;
    cMax=c+3;
    for(;r<rMax;r++)
    {
        for(;c<cMax;c++)
            if(r!=row && c!=column)
                cnt.inc(SODUKO.TABLE[r][c]);
        c=cMax-3;
    }

    if(PATH_PRINT)
    {
        cout << endl;
        for(char h=1;h<10;h++)
            cout << (short)cnt.get(h) << ' ';
        cout << ":: Value: " << (short)cnt.minimum() << endl;
    }

    return cnt.minimum();
}

/*CONTROLERS*/
void pathPrint(const char row,const char column)
{
    char i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(SODUKO.SET[i][j]==1)
                textColor(WHITE);
            else if(i==row && j==column)
                textColor(GREEN);
            else
                textColor(BROWN);
            cout << SODUKO.TABLE[i][j];
            cout << ' ';
            if(j%3==2)
                cout << ' ';
        }
        cout << '\n';
        if(i%3==2)
            cout << '\n';
    }
}

/*CONVERTERS*/
void Comp2baseRowCol(const char component,char* row,char* column)
{
    *row=(component/3)*3;
    *column=(component%3)*3;
    /*
                   COLUMN
        |        |        |        |
        | COMP=0 | COMP=1 | COMP=2 |
        |        |        |        |

        |        |        |        |
    ROW | COMP=3 | COMP=4 | COMP=5 |
        |        |        |        |

        |        |        |        |
        | COMP=6 | COMP=7 | COMP=8 |
        |        |        |        |

    ROW=[0,8]
    COLUMN=[0,8]
    COMP=[0,8]
    */
}

char RowCol2Comp(const char row,const char column)
{
    return 3*(row/3)+(column/3);
}

/*SAVING*/
bool readyFile()
{
    ofstream fout;
    fout.open(solutionAddress);
    return fout.is_open();
}

void save()
{
    ofstream fout;
    fout.open(solutionAddress);
    fout << "Solution :: Soduko :: min_conflicts Algorithm\n\n";
    char i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            fout << SODUKO.TABLE[i][j];
            if(j==2 || j==5)
                fout << ' ' << ' ';
            else if(j!=8)
                fout << ' ';
        }
        if(i==2 || i==5)
            fout << '\n' << '\n';
        else if(i!=8)
            fout << '\n';
    }
    fout.close();
}
