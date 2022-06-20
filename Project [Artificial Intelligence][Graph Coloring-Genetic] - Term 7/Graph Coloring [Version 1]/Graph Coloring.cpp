#include "myTextColor.h"
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <climits>
#include <ctime>
#include <cmath>

using namespace std;

const short MAX_G=16; // GRAPH SIZE MAXIMUM
const short MAX_P=16; // POPULATION SIZE MAXIMUM
short G; // GRAPH SIZE
short P; // POPULATION SIZE

bool graph[MAX_G][MAX_G];
const char color[]={'R','G','B','Y'};
char population[MAX_P][MAX_G];
char new_population[MAX_P][MAX_G];
short population_fitnessFunction[MAX_P];
short optimal_individual_index;
/*BEST*/
char bestIndividual[MAX_G];
short bestIndividualff=-1;
/*BEST*/

void intro();
void input_graph();
void random_graph();
void random_population();
short random_selection();
short fitnessFunction(short p);
void update_populationff();
void reproduce(char child[],short x,short y);
void mutation(char child[]);
void add2new_population(char a[],short p);

// USER INTERFACE
void print_graph();
void print_population();

//MAIN////////////////////////////////////////////////////////////////

int main()
{
    system("title R.Beheshtifar 911846105"); //PROGRAMMER NAME

    clock_t s,e;
	float timediff;
	int timeOut=3000; // /1000 <SECOND>
	int populationCounter=0;

	register short i,j,k,X,Y;
	char child[G];

    intro();
    srand(time(NULL));
    input_graph();

    /*START*/s=clock();

    random_population();
    update_populationff(); // UPDATE
    cout << "\n POPULATION <" << populationCounter++ << ">\n\n";
    print_population();

    do
    {
		for(i=0;i<P;i++)
		{
		    X=random_selection();
		    Y=random_selection();
		    reproduce(child,X,Y);
		    if((float)rand()/RAND_MAX<0.5)
                mutation(child);
		    add2new_population(child,i);
		}
		for(j=0;j<P;j++)
			for(k=0;k<G;k++)
				population[j][k]=new_population[j][k]; // COPY
        update_populationff(); // UPDATE
        cout << "\n POPULATION <" << populationCounter++ << ">\n\n";
        print_population();
        /*BEST*/
        if(population_fitnessFunction[optimal_individual_index]>bestIndividualff) // IF (CURRENT > BEST)
        {
            bestIndividualff=population_fitnessFunction[optimal_individual_index];
            for(i=0;i<G;i++)
                bestIndividual[i]=population[optimal_individual_index][i]; // COPY
        }
        /*BEST*/
	}while(bestIndividualff!=G*G/2 && (float)(clock()-s)/CLOCKS_PER_SEC*1000<timeOut);

    /*END*/e=clock();

    cout << "\n SOLUTION:\n\n";
    textColor(CYAN);
    for(i=0;i<G;i++)
        cout << bestIndividual[i] << ' ';
    cout << "--> " << bestIndividualff;

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
    cout << "\n\n\n\t\t\t Genetic Algorithm";
    textColor(YELLOW);
    cout << "\n\n\n\t\t\t Reza Beheshtifar";
    textColor(WHITE);
    cout << "\n\n\n\t\t\t 911846105";
    textColor(LIGHTGREEN);
    cout << "\n\n\n\n\n\t\t\t Professor: Mousa Mousazadeh";
    getch();
    system("cls");
    system("color 1F");
}

void input_graph()
{
    ifstream fin("input.txt");
    if(!fin.is_open())
        exit(-1);
    fin >> G;
    fin >> P;
    for(int i=0;i<G;i++)
    {
        for(int j=0;j<G;j++)
            fin >> graph[i][j];
    }
    for(int i=0;i<G;i++)
    {
        for(int j=0;j<G;j++)
            cout << graph[i][j] << ' ';
        cout << endl;
    }
    fin.close();
}

void random_graph()
{
	register short i,j;
	for(i=0;i<G;i++)
		for(j=i+1;j<G;j++)
			graph[i][j]=rand()%2;
}

void random_population()
{
	register short i,j;
	for(i=0;i<P;i++)
		for(j=0;j<G;j++)
			population[i][j]=color[rand()%4];
}

short random_selection()
{
	int s=0;
	register short i;
	for(i=0;i<P;i++)
		s+=population_fitnessFunction[i];
	float r=(float)rand()/RAND_MAX;
	float t=0;
	for(i=0;i<P;i++)
	{
		t=t+(float)population_fitnessFunction[i]/s;
		if(r<=t)
        {
            return i;
        }
	}
}

short fitnessFunction(short p)
{
	short cnt=0;
	register short i,j;
	for(i=0;i<G-1;i++)
		for(j=i+1;j<G;j++)
			if(graph[i][j] && population[p][i]==population[p][j])
				cnt++;
	return G*G/2-cnt;
}

void update_populationff()
{
	register short i;
	optimal_individual_index=0;
	for(i=0;i<P;i++)
    {
        population_fitnessFunction[i]=fitnessFunction(i);
        if(population_fitnessFunction[i]>population_fitnessFunction[optimal_individual_index])
            optimal_individual_index=i;
    }
}

void reproduce(char child[],short x,short y)
{
    register short i=0;
    short crossOver=rand()%(G+1);
    if(rand()%2)
    {
        for(;i<crossOver;i++)
            child[i]=population[x][i];
        for(;i<G;i++)
            child[i]=population[y][i];
    }
    else
    {
        for(;i<crossOver;i++)
            child[i]=population[y][i];
        for(;i<G;i++)
            child[i]=population[x][i];
    }
}
void mutation(char child[])
{
    child[rand()%G]=color[rand()%4];
}
void add2new_population(char a[],short p)
{
    register short i;
    for(i=0;i<G;i++)
        new_population[p][i]=a[i];
}

// USER INTERFACE

void print_graph()
{
	register short i,j;
	for(i=0;i<P;i++)
	{
		for(j=0;j<G;j++)
			cout << graph[i][j] << ' ';
		cout << endl;
	}
}

void print_population()
{
	register short i,j;
	for(i=0;i<P;i++)
	{
		for(j=0;j<G;j++)
			cout << population[i][j] << ' ';
		cout << "--> " << population_fitnessFunction[i] << endl;
	}
}
