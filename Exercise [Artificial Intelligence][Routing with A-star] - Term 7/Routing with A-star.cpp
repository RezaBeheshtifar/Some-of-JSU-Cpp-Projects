#include <conio.h>
#include <iomanip>
#include <fstream>
#include <climits>
#include <ctime>
#include <cmath>

using namespace std;

#include "myTextColor.h"
#define MAXSIZE 8
#define U 0 // UP
#define D 1 // DOWN
#define L 2 // LEFT
#define R 3 // RIGHT

struct position{
    char i;
    char j;
};

struct environment{
    char SIZE;
    char ENV[MAXSIZE][MAXSIZE];
    bool VALIDMOVE[MAXSIZE][MAXSIZE][4];
    // VALIDMOVE[][][0]=TRUE --> UP, VALIDMOVE[][][1]=TRUE --> DOWN, VALIDMOVE[][][2]=TRUE --> LEFT, VALIDMOVE[][][3]=TRUE --> RIGHT
    position START;
    position GOAL;
}ENVIRONMENT;

void intro();
void input_env();
void print_env();
bool isGoal(const position p);
short heuristic(const position p); // MANHATTEN DISTANCE
void print_pos(const position p);
void validMove(const position p,bool &up,bool &down,bool &left,bool &right);
position Move(const position src,const char action);

void showOnScreen(const position p,const char action);

bool readyFile();
void infoFile();
bool saveToFile(const position p,const char action);

#include "myLinkedList.h"

//MAIN////////////////////////////////////////////////////////////////

int main()
{
    system("title R.Beheshtifar 911846105"); //PROGRAMMER NAME

    clock_t s,e;
	float timediff;

    linkedList frontier;
    stateNode* exp;
    position destination_pos={0,0};
    bool up,down,left,right;
    bool isSuccessful;
    char prg_continue='y',q;

    intro();

    while(prg_continue=='y' || prg_continue=='Y')
    {
        input_env();
        cout << endl;
        print_env();

        textColor(YELLOW);
        cout << "\n Searching...\n\n";

        frontier.delete_All();
        frontier.add_graphSearch(ENVIRONMENT.START,'S',ENVIRONMENT.ENV[ENVIRONMENT.START.i][ENVIRONMENT.START.j],heuristic(ENVIRONMENT.START),NULL);

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
            exp=frontier.removeAndReturnAddress();
            cout << " ACTION: " << exp->action << endl;
            // GOAL TEST
            if(isGoal(exp->pos))
            {
                isSuccessful=true;
                break;
            }
            // EXPAND
            validMove(exp->pos,up,down,left,right);
            if(up==true)
            {
                destination_pos=Move(exp->pos,'U');
                frontier.add_graphSearch(destination_pos,'U',ENVIRONMENT.ENV[destination_pos.i][destination_pos.j],heuristic(destination_pos),exp);
            }
            if(down==true)
            {
                destination_pos=Move(exp->pos,'D');
                frontier.add_graphSearch(destination_pos,'D',ENVIRONMENT.ENV[destination_pos.i][destination_pos.j],heuristic(destination_pos),exp);
            }
            if(left==true)
            {
                destination_pos=Move(exp->pos,'L');
                frontier.add_graphSearch(destination_pos,'L',ENVIRONMENT.ENV[destination_pos.i][destination_pos.j],heuristic(destination_pos),exp);
            }
            if(right==true)
            {
                destination_pos=Move(exp->pos,'R');
                frontier.add_graphSearch(destination_pos,'R',ENVIRONMENT.ENV[destination_pos.i][destination_pos.j],heuristic(destination_pos),exp);
            }
        }

        /*END*/e=clock();

        if(isSuccessful)
        {
            // RETURN SOLUTION
            textColor(LIGHTGREEN);
            cout << "\n START POSITION: ";
            print_pos(ENVIRONMENT.START);
            textColor(LIGHTGREEN);
            cout << "\n\n GOAL POSITION: ";
            print_pos(ENVIRONMENT.GOAL);
            textColor(LIGHTGREEN);
            cout << "\n\n PATH: ";
            frontier.printSolution1(exp);
            timediff=(float)(e-s)/CLOCKS_PER_SEC*1000;
            textColor(LIGHTGREEN);
            cout << "\n\n >>> Total Run Time: " << timediff << " (ms)"
                 << "\n\n     Total Used Memory: " << frontier.size_Frontier() << '+' << frontier.size_Explored() << " (nodes)"
                 << "\n\n     Path-cost of Solution: " << exp->f << " (cost)";
            cout << "\n\n >>> Do you want to save Solution in \"routing.txt\" file? ";
            cin >> q;
            cout << endl;
            if(q=='y' || q=='Y')
            {
                if(readyFile())
                {
                    infoFile();
                    frontier.printSolution2(exp);
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
        cout << " >>> Do you want to continue 'Routing with A*'? [Y/N] ";
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
    cout << "\n\n\n\t\t\t Routing";
    textColor(CYAN);
    cout << "\n\n\n\t\t\t A* Graph Search";
    textColor(YELLOW);
    cout << "\n\n\n\t\t\t Reza Beheshtifar";
    textColor(WHITE);
    cout << "\n\n\n\t\t\t 911846105";
    textColor(LIGHTGREEN);
    cout << "\n\n\n\n\n\t\t\t Professor: Mousa Mousazadeh";
    getch();
    system("cls");
}

void input_env()
{
    #include "input.env"
}

void print_env()
{
    textColor(WHITE);
    for(char i=0;i<ENVIRONMENT.SIZE;i++)
    {
        for(char j=0;j<ENVIRONMENT.SIZE;j++)
            if(i==ENVIRONMENT.START.i && j==ENVIRONMENT.START.j)
            {
                textColor(CYAN);
                cout << ' ' << 'S' << ' ';
                textColor(WHITE);
            }
            else if(i==ENVIRONMENT.GOAL.i && j==ENVIRONMENT.GOAL.j)
            {
                textColor(LIGHTRED);
                cout << ' ' << 'G' << ' ';
                textColor(WHITE);
            }
            else
                cout << ' ' << (short)ENVIRONMENT.ENV[i][j] << ' ';
        cout << '\n' << '\n';
    }
}

bool isGoal(const position p)
{
    return (p.i==ENVIRONMENT.GOAL.i)&&(p.j==ENVIRONMENT.GOAL.j);
}

short heuristic(const position p) // MANHATTEN DISTANCE
{
    return abs(p.i-ENVIRONMENT.GOAL.i)+abs(p.j-ENVIRONMENT.GOAL.j);
}

void print_pos(const position p)
{
    textColor(WHITE);
    cout << '<' << (short)p.i << ':' << (short)p.j << '>';
}

void validMove(const position p,bool &up,bool &down,bool &left,bool &right)
{
    if(p.i>0 && ENVIRONMENT.VALIDMOVE[p.i][p.j][U])
        up=true;
    else
        up=false;

    if(p.i<ENVIRONMENT.SIZE-1 && ENVIRONMENT.VALIDMOVE[p.i][p.j][D])
        down=true;
    else
        down=false;

    if(p.j>0 && ENVIRONMENT.VALIDMOVE[p.i][p.j][L])
        left=true;
    else
        left=false;

    if(p.j<ENVIRONMENT.SIZE-1 && ENVIRONMENT.VALIDMOVE[p.i][p.j][R])
        right=true;
    else
        right=false;
}

position Move(const position src,const char action)
{
    position des=src;
    switch(action)
    {
        case 'U':
            --des.i;
            break;
        case 'D':
            ++des.i;
            break;
        case 'L':
            --des.j;
            break;
        case 'R':
            ++des.j;
            break;
    }
    return des;
}

void showOnScreen(const position p,const char action)
{
    textColor(WHITE);
    cout << '\n' << '\t';
    switch(action)
    {
        case 'U':
            cout << "UP   ";
            break;
        case 'D':
            cout << "DOWN ";
            break;
        case 'L':
            cout << "LEFT ";
            break;
        case 'R':
            cout << "RIGHT";
            break;
        case 'S':
            cout << "START";
            break;
    }
    cout << " / ";
    print_pos(p);
}

bool readyFile()
{
    ofstream fout;
    fout.open("routing.txt");
    return fout.is_open();
}

void infoFile()
{
    ofstream fout;
    fout.open("routing.txt",ios::app);
    fout << "ROUTING :: A* GRAPH SEARCH :: REZA BEHESHTIFAR\n";
    fout.close();
}

bool saveToFile(const position p,const char action)
{
    ofstream fout;
    fout.open("routing.txt",ios::app);
    if(!fout.is_open())
        return false;
    fout << '\n';
    switch(action)
    {
        case 'U':
            fout << "UP   ";
            break;
        case 'D':
            fout << "DOWN ";
            break;
        case 'L':
            fout << "LEFT ";
            break;
        case 'R':
            fout << "RIGHT";
            break;
        case 'S':
            fout << "START";
            break;
    }
    fout << " / " << '(' << (short)p.i << ',' << (short)p.j << ')';
    fout.close();
    return true;
}
