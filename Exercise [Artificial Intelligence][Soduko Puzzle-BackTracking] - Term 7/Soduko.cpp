#include <conio.h>
#include <iomanip>
#include <fstream>
#include <climits>
#include <ctime>
#include <cmath>

using namespace std;

#include "myLibrary.h"
#include "myTextColor.h"

#define sodukoProblemsAddress "problems.txt" // INPUT
#define solutionAddress "solution.txt" // OUTPUT
#define numberOfProblemsInFile 6 // RANGE: {1,2,3,...}
#define ALGORITHM_SELECTOR 3 // 1: BT+FC  2: BT+FC+MRV  3: AC3+BT+FC+MRV

struct soduko
{
    short TABLE[9][9];
    bool SET[9][9]; // SET=0 --> VARIABLE, SET=1 --> CONST
    bool DOM[9][9][10]; // DOMAIN(VAR)={DOM[VARI][VARJ][1 TO 9]}
}SODUKO;

unsigned int step;

void intro();

/*FUNCTIONS*/
char randomTable();
bool validTable();
void scanTable();
void printTable(const short table[9][9]);
void printTable_TST();
void printSolution();
bool solutionTest();

bool Backtrack_FC(const bool domain[9][9][10]);
bool Backtrack_FC_MRV(const bool domain[9][9][10]);
bool isCompleteAssignment();
bool selectAnUnassignmentVariable(char& row,char& column);
char minimumRemainingValue(const bool domain[9][9][10],char& row,char& column);
bool isConsistentWithAssignment(const char row,const char column);
void forwardChecking(const bool domain[9][9][10],bool fc_domain[9][9][10],const char row,const char col,const char d);
void arc_consistency();

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

        switch(ALGORITHM_SELECTOR)
        {
            case 1:
                {
                    if(Backtrack_FC(SODUKO.DOM))
                        isSuccessful=true;
                    else
                        isSuccessful=false;
                    break;
                }

            case 2:
                {
                    if(Backtrack_FC_MRV(SODUKO.DOM))
                        isSuccessful=true;
                    else
                        isSuccessful=false;
                    break;
                }

            case 3:
                {
                    arc_consistency();
                    if(Backtrack_FC_MRV(SODUKO.DOM))
                        isSuccessful=true;
                    else
                        isSuccessful=false;
                    break;
                }

            default:
                {
                    exit(0);
                    break;
                }
        }

        /*END*/e=clock();

        timediff=(float)(e-s)/CLOCKS_PER_SEC*1000;

        if(isSuccessful)
        {
            // RESULT
            printSolution();
            textColor(LIGHTGREEN);
            cout << "\n\n >>> Total Run Time: " << timediff << " (ms)"
                 << "\n\n     Number of Steps: " << step << " (step)";
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
                 << "\n\n     Number of Steps: " << step << " (step)"
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
    cout << "\n\n\n\t\t\t BackTracking Algorithm";
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
            if(f=='?'){ SODUKO.SET[i][j]=0; SODUKO.TABLE[i][j]=0; }
            else{ f-='0'; if(f<1 || f>9){ return -2; } SODUKO.SET[i][j]=1; SODUKO.TABLE[i][j]=f; }
            j++;
        }
        i++;
    }
    fin.close();
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            for(f=1;f<10;f++)
                SODUKO.DOM[i][j][f]=true;
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
                    SODUKO.TABLE[i][j]=0;
                    SODUKO.SET[i][j]=0;
                    //
                    for(char f=1;f<10;f++)
                        SODUKO.DOM[i][j][f]=true;
                    //
                    break;
                }
                else if(c>0 && c<10)
                {
                    SODUKO.TABLE[i][j]=c;
                    SODUKO.SET[i][j]=1;
                    for(char f=1;f<10;f++)
                        SODUKO.DOM[i][j][f]=true;
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

void printTable_TST()
{
    char i,j;
    textColor(WHITE);
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(SODUKO.SET[i][j]==1)
                textColor(WHITE);
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

bool Backtrack_FC(const bool domain[9][9][10])
{
    char var_i,var_j;
    bool result;
    bool domain_fc[9][9][10];
    ++step;
    if(!selectAnUnassignmentVariable(var_i,var_j))
        return true; // SUCCESSFUL
    for(char d=1;d<=9;d++)
        if(domain[var_i][var_j][d])
        {
            SODUKO.TABLE[var_i][var_j]=d;
            if(isConsistentWithAssignment(var_i,var_j))
            {
                forwardChecking(domain,domain_fc,var_i,var_j,d);
                result=Backtrack_FC(domain_fc);
                if(result)
                    return true;
            }
            SODUKO.TABLE[var_i][var_j]=0;
        }
    return false;
}

bool Backtrack_FC_MRV(const bool domain[9][9][10])
{
    char var_i,var_j;
    bool result;
    bool domain_fc[9][9][10];
    ++step;
    char r=minimumRemainingValue(domain,var_i,var_j);
    if(r==-1)
        return false; // UNSUCCESSFUL
    else if(r==1)
        return solutionTest();
    for(char d=1;d<=9;d++)
        if(domain[var_i][var_j][d])
        {
            SODUKO.TABLE[var_i][var_j]=d;
            if(isConsistentWithAssignment(var_i,var_j))
            {
                forwardChecking(domain,domain_fc,var_i,var_j,d);
                result=Backtrack_FC_MRV(domain_fc);
                if(result)
                    return true;
            }
            SODUKO.TABLE[var_i][var_j]=0;
        }
    return false;
}

bool isCompleteAssignment()
{
    char i,j;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            if(SODUKO.TABLE[i][j]==0)
                return false;
    return true;
}

bool selectAnUnassignmentVariable(char& row,char& column)
{
    for(row=0;row<9;row++)
        for(column=0;column<9;column++)
            if(SODUKO.TABLE[row][column]==0)
                return true;
    return false;
}

char minimumRemainingValue(const bool domain[9][9][10],char& row,char& column)
{
    register char r,c,f;
    char cnt=0,min_domain=10;
    for(r=0;r<9;r++)
        for(c=0;c<9;c++)
            if(SODUKO.SET[r][c]==0 && SODUKO.TABLE[r][c]==0)
            {
                for(f=1;f<10;f++)
                    if(domain[r][c][f])
                        ++cnt;
                if(cnt<min_domain)
                {
                    min_domain=cnt;
                    row=r;
                    column=c;
                    if(min_domain==0)
                        return -1; // FAILURE
                }
                cnt=0;
            }
    if(min_domain==10)
        return 1;
    return 0;
}

bool isConsistentWithAssignment(const char row,const char column)
{
    register char r,c;
    register char rMax,cMax;
    repeatDetection d;

    // STEP 1 --> ROW CHECK
    for(c=0;c<9;c++)
        if(SODUKO.TABLE[row][c]!=0)
            d.set(SODUKO.TABLE[row][c]);
    if(d.isRepeated())
        return false;
    d.reset();
    // STEP 2 --> COLUMN CHECK
    for(r=0;r<9;r++)
        if(SODUKO.TABLE[r][column]!=0)
            d.set(SODUKO.TABLE[r][column]);
    if(d.isRepeated())
        return false;
    d.reset();
    // STEP 3 --> COMPONENT CHECK
    Comp2baseRowCol(RowCol2Comp(row,column),&r,&c);
    rMax=r+3;
    cMax=c+3;
    for(;r<rMax;r++)
    {
        for(;c<cMax;c++)
            if(SODUKO.TABLE[r][c]!=0)
                d.set(SODUKO.TABLE[r][c]);
        c=cMax-3;
    }
    if(d.isRepeated())
        return false;

    return true;
}

void forwardChecking(const bool domain[9][9][10],bool fc_domain[9][9][10],const char row,const char col,const char d)
{
    register char r,c,f;
    register char rMax,cMax;
    for(r=0;r<9;r++)
        for(c=0;c<9;c++)
            for(f=1;f<10;f++)
                fc_domain[r][c][f]=domain[r][c][f];
    // STEP 1 --> ROW CHECK
    for(c=0;c<9;c++)
        fc_domain[row][c][d]=false; // REMOVE FROM FC_DOMAIN[ROW][]
    // STEP 2 --> COLUMN CHECK
    for(r=0;r<9;r++)
        fc_domain[r][col][d]=false; // REMOVE FROM FC_DOMAIN[][COL]
    // STEP 3 --> COMPONENT CHECK
    Comp2baseRowCol(RowCol2Comp(row,col),&r,&c);
    rMax=r+3;
    cMax=c+3;
    for(;r<rMax;r++)
    {
        for(;c<cMax;c++)
            fc_domain[r][c][d]=false; // REMOVE FROM FC_DOMAIN[COMP]
        c=cMax-3;
    }
}

void arc_consistency()
{
    register char row,col;
    register char r,c,rMax,cMax;
    char x;
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
            if(SODUKO.SET[row][col]==1)
            {
                x=SODUKO.TABLE[row][col];
                // STEP 1 --> ROW CHECK
                for(c=0;c<9;c++)
                    SODUKO.DOM[row][c][x]=false;
                // STEP 2 --> COLUMN CHECK
                for(r=0;r<9;r++)
                    SODUKO.DOM[r][col][x]=false;
                // STEP 3 --> COMPONENT CHECK
                Comp2baseRowCol(RowCol2Comp(row,col),&r,&c);
                rMax=r+3;
                cMax=c+3;
                for(;r<rMax;r++)
                {
                    for(;c<cMax;c++)
                        SODUKO.DOM[r][c][x]=false;
                    c=cMax-3;
                }
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
    fout << "Solution :: Soduko :: BackTracking Algorithm\n\n";
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
