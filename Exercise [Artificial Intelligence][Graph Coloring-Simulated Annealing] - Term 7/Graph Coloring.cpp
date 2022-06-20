#include "myTextColor.h"
#include <conio.h>
#include <fstream>
#include <climits>
#include <ctime>
#include <cmath>

using namespace std;

const short MAX_G=16; // GRAPH SIZE MAXIMUM
short G; // GRAPH SIZE

short MAXVALUE;

bool graph[MAX_G][MAX_G];
const char color[]={'R','G','B','Y'};

char current[MAX_G];
short current_FF;

char neighbor[MAX_G];
short neighbor_FF;

char bestSolution[MAX_G];
short bestSolution_FF;

void intro();
void input_graph();
void randomColoring();
short fitnessFunction(const char colors[MAX_G]);
int tempratureFunction(const unsigned int t);
char randomlyNeighbor();
void assign_neighbor2current();

// USER INTERFACE
void print_graph();
void print_colors(const char colors[MAX_G],const short ff,const char coloredIndex);

//MAIN////////////////////////////////////////////////////////////////

int main()
{
    system("title R.Beheshtifar 911846105"); //PROGRAMMER NAME

    clock_t s,e;
    float timediff;

	unsigned int step=0;
	bestSolution_FF=-1;
	int temprature;
	short diff_FF;
	char changedIndex;

    intro();
    srand(time(NULL));

    input_graph();
    print_graph();
    MAXVALUE=(G*G-G)/2;

    randomColoring();
    print_colors(current,current_FF,-1);

    /*START*/s=clock();

    while(++step)
    {
        temprature=tempratureFunction(step);
        if(temprature==0)
            break;
        changedIndex=randomlyNeighbor();
        print_colors(neighbor,neighbor_FF,changedIndex);
        diff_FF=neighbor_FF-current_FF;
        if(diff_FF>0 || exp((float)diff_FF/temprature)>0.4)
            assign_neighbor2current();
    }

    /*END*/e=clock();

    timediff=(float)(e-s)/CLOCKS_PER_SEC;

    textColor(YELLOW);
    cout << "\n SOLUTION:\n \a";
    print_colors(bestSolution,bestSolution_FF,-1);
    textColor(LIGHTGREEN);
    cout << "\n\n >>> Total Run Time: ";
    if(timediff<1)
        cout << timediff*1000 << " (ms)";
    else
        cout << timediff << " (sec)";
    cout << "\n\n >>> Number of Steps: " << step << " (step)";

    textColor(WHITE);
    getch();
    return 0;
}

//FUNCTION////////////////////////////////////////////////////////////

void intro()
{
    textColor(LIGHTRED);
    cout << "\n\n\n\t\t\t Artificial Intelligence";
    textColor(GREEN);
    cout << "\n\n\n\t\t\t Graph Coloring";
    textColor(CYAN);
    cout << "\n\n\n\t\t\t Simulated Annealing Algorithm";
    textColor(YELLOW);
    cout << "\n\n\n\t\t\t Reza Beheshtifar";
    textColor(WHITE);
    cout << "\n\n\n\t\t\t 911846105";
    textColor(LIGHTGREEN);
    cout << "\n\n\n\n\n\t\t\t Professor: Mousa Mousazadeh";
    getch();
    system("cls");
    textColor(WHITE);
}

void input_graph()
{
    ifstream fin("input.txt");
    if(!fin.is_open())
        exit(-1);
    fin >> G;
    for(int i=0;i<G;i++)
    {
        for(int j=0;j<G;j++)
            fin >> graph[i][j];
    }
    fin.close();
}

void randomColoring()
{
	for(int i=0;i<G;i++)
        current[i]=color[rand()%4];
    current_FF=fitnessFunction(current);
}

short fitnessFunction(const char colors[MAX_G])
{
	short cnt=0;
	register short i,j;
	for(i=0;i<G-1;i++)
		for(j=i+1;j<G;j++)
			if(graph[i][j] && colors[i]==colors[j])
				cnt++;
	return MAXVALUE-cnt;
}

int tempratureFunction(const unsigned int t)
{
    int ret=10000-t*t;
    if(ret<0)
        return 0;
    return ret;
}

char randomlyNeighbor()
{
    char changedIndex;
    for(int i=0;i<G;i++)
        neighbor[i]=current[i];
    changedIndex=rand()%G;
    neighbor[changedIndex]=color[rand()%4];
    neighbor_FF=fitnessFunction(neighbor);
    /*BEST_SOLUTION*/
    if(neighbor_FF>bestSolution_FF)
    {
        for(int i=0;i<G;i++)
            bestSolution[i]=neighbor[i];
        bestSolution_FF=neighbor_FF;
    }
    /*BEST_SOLUTION*/
    return changedIndex;
}

void assign_neighbor2current()
{
    for(int i=0;i<G;i++)
        current[i]=neighbor[i];
    current_FF=neighbor_FF;
}

// USER INTERFACE
void print_graph()
{
    for(int i=0;i<G;i++)
    {
        for(int j=0;j<G;j++)
            if(j>i)
            {
                textColor(WHITE);
                cout << ' ' << graph[i][j];
            }
            else if(j==i)
            {
                textColor(BROWN);
                cout << ' ' << graph[i][j];
            }
            else
                cout << ' ' << ' ';
        cout << endl;
    }
}

void print_colors(const char colors[MAX_G],const short ff,const char coloredIndex)
{
    textColor(WHITE);
    cout << '\n';
	for(int i=0;i<G;i++)
	{
	    if(i==coloredIndex)
            textColor(CYAN);
        else
            textColor(WHITE);
        cout << ' ' << colors[i];
	}
	textColor(LIGHTRED);
	cout << " --> ";
	textColor(YELLOW);
	cout << ff << '/' << MAXVALUE << '\n';
}
