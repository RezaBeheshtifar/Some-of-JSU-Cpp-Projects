#include "myTextColor.h"
#include <conio.h>
#include <fstream>
#include <ctime>

using namespace std;

const short MAX_G=16; // GRAPH SIZE MAXIMUM
short G; // GRAPH SIZE

short MAXVALUE;

bool graph[MAX_G][MAX_G];
const char color[]={'R','G','B','Y'};
char current[MAX_G];
short current_FF;

void intro();
void input_graph();
void randomColoring();
short fitnessFunction(const char colors[MAX_G]);
short findBestNeighbor(char& bestNeighbor_i,char& bestNeighbor_j);
void assign_bestNeighbor2current(const char bestNeighbor_i,const char bestNeighbor_j);

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
	short bestNeighbor_FF;
	char bestNeighbor_i;
	char bestNeighbor_j;

    intro();
    srand(time(NULL));

    input_graph();
    print_graph();
    MAXVALUE=(G*G-G)/2;

    randomColoring();
    current_FF=fitnessFunction(current);
    print_colors(current,current_FF,-1);

    /*START*/s=clock();

    do
    {
        bestNeighbor_FF=findBestNeighbor(bestNeighbor_i,bestNeighbor_j);
        if(bestNeighbor_FF<=current_FF)
            break;
        ++step;
        assign_bestNeighbor2current(bestNeighbor_i,bestNeighbor_j);
        print_colors(current,current_FF,bestNeighbor_i);
	}while(1);

    /*END*/e=clock();

    timediff=(float)(e-s)/CLOCKS_PER_SEC;

    textColor(YELLOW);
    cout << "\n SOLUTION:\n \a";
    print_colors(current,current_FF,-1);
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
    cout << "\n\n\n\t\t\t Hill-Climbing Algorithm";
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

short findBestNeighbor(char& bestNeighbor_i,char& bestNeighbor_j)
{
    char neighbor[MAX_G];
    short neighbor_FF;
    short bestNeighbor_FF=-1;
    bestNeighbor_i=-1;
    bestNeighbor_j=-1;
    register char i,j;
    for(i=0;i<G;i++)
        neighbor[i]=current[i];
    for(i=0;i<G;i++)
    {
        for(j=0;j<4;j++) // NUMBER_OF_COLORS=4
            if(current[i]!=color[j])
            {
                neighbor[i]=color[j];
                neighbor_FF=fitnessFunction(neighbor);
                if(neighbor_FF>bestNeighbor_FF)
                {
                    bestNeighbor_FF=neighbor_FF; // FF
                    bestNeighbor_i=i; // INDEX
                    bestNeighbor_j=j; // COLOR
                }
            }
        neighbor[i]=current[i];
    }
    return bestNeighbor_FF;
}

void assign_bestNeighbor2current(const char bestNeighbor_i,const char bestNeighbor_j)
{
    current[bestNeighbor_i]=color[bestNeighbor_j];
    current_FF=fitnessFunction(current);
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
