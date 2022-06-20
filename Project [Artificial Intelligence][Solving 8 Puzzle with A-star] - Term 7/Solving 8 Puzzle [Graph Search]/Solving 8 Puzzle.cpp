#include <conio.h>
#include <iomanip>
#include <fstream>
#include <climits>
#include <ctime>
#include <cmath>

#include "myTextColor.h"

#define B 0; // 0 FOR BLANK

using namespace std;

short init_Tiles[9];
short goal_Tiles[9];
short heuristic_number;
/*
INIT_TILES[0] INIT_TILES[1] INIT_TILES[2]        GOAL_TILES[0] GOAL_TILES[1] GOAL_TILES[2]
INIT_TILES[3] INIT_TILES[4] INIT_TILES[5]        GOAL_TILES[3] GOAL_TILES[4] GOAL_TILES[5]
INIT_TILES[6] INIT_TILES[7] INIT_TILES[8]        GOAL_TILES[6] GOAL_TILES[7] GOAL_TILES[8]
*/

void intro();

void randomPuzzle(short output_Tiles[]);
bool validPuzzle(const short input_Tiles[]);
void stdGoalPuzzle(short output_Tiles[]);
void scanPuzzle(short output_Tiles[]);
void printPuzzle(const short input_Tiles[]);
bool isGoal(const short input_Tiles[]);
short heuristic_1(const short input_Tiles[]); // NUMBER OF MISPLACED TILES
short heuristic_2(const short input_Tiles[]); // MANHATTEN DISTANCE
short heuristic_3(const short input_Tiles[]); // HOMEWORK

short blankIndex(const short input_Tiles[]);
void validBlankMove(const short input_Tiles[],const short blankIndex,bool &up,bool &down,bool &left,bool &right);
void blankMove(const short input_Tiles[],const short blankIndex,short output_Tiles[],const char action);

bool readyFile();
void infoFile();
bool saveToFile(const short input_Tiles[]);

#include "myLinkedList.h"

//MAIN////////////////////////////////////////////////////////////////

int main()
{
    system("title R.Beheshtifar 911846105"); //PROGRAMMER NAME

    clock_t s,e;
	float timediff;

    linkedList frontier;
    stateNode* L;
    short expand_Tiles[9];
    short BI;
    bool up,down,left,right;
    bool isSuccessful;
    char prg_continue='y',q;
    short cur_depth;

    intro();

    while(prg_continue=='y' || prg_continue=='Y')
    {
        textColor(LIGHTGREEN);
        cout << "\n >>> Do you want a random initial state? [Y/N] ";
        cin >> q;
        if(q=='y' || q=='Y')
        {
            randomPuzzle(init_Tiles);
            cout << endl;
            printPuzzle(init_Tiles);
            cout << endl;
        }
        else
            do{
                textColor(LIGHTGREEN);
                cout << "\n Enter the initial state: [0 for Blank]\n\n";
                textColor(WHITE);
                scanPuzzle(init_Tiles);
            }while(!validPuzzle(init_Tiles));

        textColor(LIGHTGREEN);
        cout << "\n >>> Do you want the goal state to be standard? [Y/N] ";
        cin >> q;
        if(q=='y' || q=='Y')
        {
            stdGoalPuzzle(goal_Tiles);
            cout << endl;
            printPuzzle(goal_Tiles);
            cout << endl;
        }
        else
            do{
                textColor(LIGHTGREEN);
                cout << "\n Enter the goal state: [0 for Blank]\n\n";
                textColor(WHITE);
                scanPuzzle(goal_Tiles);
            }while(!validPuzzle(goal_Tiles));

        do{
            textColor(CYAN);
            cout << "\n 0: DO NOT USE"
                 << "\n 1: NUMBER OF MISPLACED TILES"
                 << "\n 2: MANHATTEN DISTANCE"
                 << "\n 3: HOMEWORK";
            textColor(LIGHTGREEN);
            cout << "\n\n >>> Choose Heuristic Function: ";
            cin >> heuristic_number;
        }while(heuristic_number<0 || heuristic_number>3);

        textColor(YELLOW);
        cout << "\n Current Depth:\n\n";

        frontier.delete_All();
        frontier.hSelect(heuristic_number);
        frontier.add_graphSearch(init_Tiles,'I',0,NULL);
        cur_depth=-1;

        /*START*/s=clock();

        while(1)
        {
            // EXIST?
            if(frontier.isEmpty())
            {
                isSuccessful=false;
                break;
            }
            // CHOOSE
            L=frontier.removeAndReturnAddress();
            if(L->depth>cur_depth)
            {
                cur_depth=L->depth;
                cout << ' ' << cur_depth << endl;
            }
            // GOAL TEST
            if(isGoal(L->tiles))
            {
                isSuccessful=true;
                break;
            }
            // EXPAND
            BI=blankIndex(L->tiles);
            validBlankMove(L->tiles,BI,up,down,left,right);
            if(up==true)
            {
                blankMove(L->tiles,BI,expand_Tiles,'U');
                frontier.add_graphSearch(expand_Tiles,'U',L->depth+1,L);
            }
            if(down==true)
            {
                blankMove(L->tiles,BI,expand_Tiles,'D');
                frontier.add_graphSearch(expand_Tiles,'D',L->depth+1,L);
            }
            if(left==true)
            {
                blankMove(L->tiles,BI,expand_Tiles,'L');
                frontier.add_graphSearch(expand_Tiles,'L',L->depth+1,L);
            }
            if(right==true)
            {
                blankMove(L->tiles,BI,expand_Tiles,'R');
                frontier.add_graphSearch(expand_Tiles,'R',L->depth+1,L);
            }
        }

        /*END*/e=clock();

        if(isSuccessful)
        {
            // RETURN SOLUTION
            textColor(LIGHTGREEN);
            cout << "\n START:\n\n";
            printPuzzle(init_Tiles);
            textColor(LIGHTGREEN);
            cout << "\n\n GOAL:\n\n";
            printPuzzle(L->tiles);
            timediff=(float)(e-s)/CLOCKS_PER_SEC*1000;
            textColor(LIGHTGREEN);
            cout << "\n\n >>> Total Run Time: " << timediff << " (ms)"
                 << "\n\n     Total Used Memory: " << frontier.size_Frontier() << '+' << frontier.size_Explored() << " (nodes)"
                 << "\n\n     Path-cost of Solution: " << L->depth << " (depth)";
            cout << "\n\n >>> Do you want to save Solution in \"solution.txt\" file? ";
            cin >> q;
            cout << endl;
            if(q=='y' || q=='Y')
            {
                if(readyFile())
                {
                    infoFile();
                    frontier.printSolution(L);
                }
                else
                {
                    textColor(LIGHTRED);
                    cout << " >>> ERROR!\n\n";
                }
            }

        }
        else
        {
            // FAILURE
            textColor(LIGHTRED);
            cout << "\n >>> SOLUTION NOT FOUND!\n\n";
        }

        textColor(CYAN);
        cout << " >>> Do you want to continue 'Solving 8 Puzzle'? [Y/N] ";
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
    cout << "\n\n\n\t\t\t Solving 8 Puzzle";
    textColor(CYAN);
    cout << "\n\n\n\t\t\t A* Search";
    textColor(YELLOW);
    cout << "\n\n\n\t\t\t Reza Beheshtifar";
    textColor(WHITE);
    cout << "\n\n\n\t\t\t 911846105";
    textColor(LIGHTGREEN);
    cout << "\n\n\n\n\n\t\t\t Professor: Mousa Mousazadeh";
    getch();
    system("cls");
}

void randomPuzzle(short output_Tiles[])
{
    bool flag[9]={false};
    short r;
    srand(time(NULL));
    for(short i=0;i<9;i++)
    {
        do{
            r=rand()%9;
        }while(flag[r]);
        output_Tiles[i]=r;
        flag[r]=true;
    }
}

bool validPuzzle(const short input_Tiles[])
{
    for(short i=0;i<9;i++)
    {
        short i_counter=0;
        for(short j=0;j<9;j++)
            if(input_Tiles[j]==i)
                i_counter++;
        if(i_counter!=1)
            return false;
    }
    return true;
}

void stdGoalPuzzle(short output_Tiles[])
{
    goal_Tiles[0]=1; goal_Tiles[1]=2; goal_Tiles[2]=3;
    goal_Tiles[3]=4; goal_Tiles[4]=5; goal_Tiles[5]=6;
    goal_Tiles[6]=7; goal_Tiles[7]=8; goal_Tiles[8]=B;
}

void scanPuzzle(short output_Tiles[])
{
    for(short i=0;i<9;i++)
    {
        cout << " Tile[" << i+1 << "]: ";
        cin >> output_Tiles[i];
    }
}

void printPuzzle(const short input_Tiles[])
{
    textColor(WHITE);
    for(short i=0;i<9;i++)
    {
        if(i && i%3==0)
            cout << '\n' << '\n';
        if(input_Tiles[i])
            cout << ' ' << input_Tiles[i];
        else
        {
            textColor(YELLOW);
            cout << ' ' << 'B';
            textColor(WHITE);
        }
        cout << ' ';
    }
}

bool isGoal(const short input_Tiles[])
{
    for(short i=0;i<9;i++)
        if(input_Tiles[i]!=goal_Tiles[i])
            return false;
    return true;
}

short heuristic_1(const short input_Tiles[])
{
    short r=0;
    for(short i=0;i<9;i++)
        if(input_Tiles[i]!=goal_Tiles[i] && input_Tiles[i]/*!=0*/) // 0 FOR BLANK
            r++;
    return r;
}

short heuristic_2(const short input_Tiles[])
{
    short manhatten=0;
    short cnt,in_row,in_col,goal_row,goal_col;
    for(short i=1;i<=8;i++) // 0 FOR BLANK
    {
        cnt=0;
        for(;cnt<9;cnt++)
            if(input_Tiles[cnt]==i)
                break;
        in_row=cnt/3;
        in_col=cnt%3;
        cnt=0;
        for(;cnt<9;cnt++)
            if(goal_Tiles[cnt]==i)
                break;
        goal_row=cnt/3;
        goal_col=cnt%3;
        manhatten+=(abs(in_row-goal_row)+abs(in_col-goal_col));
    }
    return manhatten;
}

short heuristic_3(const short input_Tiles[])
{
    return 0;
}

short blankIndex(const short input_Tiles[])
{
    for(short i=0;i<9;i++)
        if(input_Tiles[i]==0)
            return i;
    return -1;
}

void validBlankMove(const short input_Tiles[],const short blankIndex,bool &up,bool &down,bool &left,bool &right)
{
    if(blankIndex>=3 && blankIndex<=8)
        up=true;
    else
        up=false;
    if(blankIndex>=0 && blankIndex<=5)
        down=true;
    else
        down=false;
    if(blankIndex%3!=0)
        left=true;
    else
        left=false;
    if(blankIndex%3!=2)
        right=true;
    else
        right=false;
}

void blankMove(const short input_Tiles[],const short blankIndex,short output_Tiles[],const char action)
{
    short temp;
    for(short i=0;i<9;i++)
        output_Tiles[i]=input_Tiles[i];
    switch(action)
    {
        case 'U':
            // TILE[BLANK_INDEX] <---> TILE[BLANK_INDEX-3]
            temp=output_Tiles[blankIndex];
            output_Tiles[blankIndex]=output_Tiles[blankIndex-3];
            output_Tiles[blankIndex-3]=temp;
            break;
        case 'D':
            // TILE[BLANK_INDEX] <---> TILE[BLANK_INDEX+3]
            temp=output_Tiles[blankIndex];
            output_Tiles[blankIndex]=output_Tiles[blankIndex+3];
            output_Tiles[blankIndex+3]=temp;
            break;
        case 'L':
            // TILE[BLANK_INDEX] <---> TILE[BLANK_INDEX-1]
            temp=output_Tiles[blankIndex];
            output_Tiles[blankIndex]=output_Tiles[blankIndex-1];
            output_Tiles[blankIndex-1]=temp;
            break;
        case 'R':
            // TILE[BLANK_INDEX] <---> TILE[BLANK_INDEX+1]
            temp=output_Tiles[blankIndex];
            output_Tiles[blankIndex]=output_Tiles[blankIndex+1];
            output_Tiles[blankIndex+1]=temp;
            break;
    }

}

bool readyFile()
{
    ofstream fout;
    fout.open("solution.txt");
    return fout.is_open();
}

void infoFile()
{
    ofstream fout;
    fout.open("solution.txt",ios::app);
    fout << "SOLUTION :: 8 PUZZLE :: REZA BEHESHTIFAR";
    fout << "\n\n START:";
    fout.close();
    saveToFile(init_Tiles);
    fout.open("solution.txt",ios::app);
    fout << "\n\n GOAL:";
    fout.close();
    saveToFile(goal_Tiles);
    fout.open("solution.txt",ios::app);
    fout << "\n\n SOLUTION:";
    fout.close();
}

bool saveToFile(const short input_Tiles[])
{
    ofstream fout;
    fout.open("solution.txt",ios::app);
    if(!fout.is_open())
        return false;

    fout << '\n' << '\n';
    for(short i=0;i<9;i++)
    {
        if(i && i%3==0)
            fout << '\n';
        if(input_Tiles[i])
            fout << input_Tiles[i];
        else
            fout << ' ';
        if(i%3!=2)
            fout << ' ';
    }

    fout.close();
    return true;
}
