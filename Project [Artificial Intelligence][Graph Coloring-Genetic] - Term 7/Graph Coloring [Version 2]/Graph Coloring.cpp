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

short MAXVALUE;

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

/*CROSSOVER_MUTATION::INDEX*/
// COLUMN 0 --> CROSSOVER, COLUMN 1 --> MUTATION
short CM[MAX_P][2];
/*CROSSOVER_MUTATION::INDEX*/

void intro();
void input_graph();
void random_graph();
void random_population();
short random_selection();
short fitnessFunction(short p);
void update_populationff();
short reproduce(char child[],short x,short y);
short mutation(char child[]);
void add2new_population(char a[],short p);
/*CROSSOVER_MUTATION::INDEX*/
void init_CM();
/*CROSSOVER_MUTATION::INDEX*/

// USER INTERFACE
void print_graph();
void print_population();
void print_population_CM();

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
    MAXVALUE=(G*G-G)/2;

    /*START*/s=clock();

    random_population();
    update_populationff(); // UPDATE
    init_CM();
    cout << "\n POPULATION <" << populationCounter++ << ">\n\n";
    print_population();

    do
    {
		for(i=0;i<P;i++)
		{
		    X=random_selection();
		    Y=random_selection();
		    CM[i][0]=reproduce(child,X,Y);
		    if((float)rand()/RAND_MAX<0.5)
                CM[i][1]=mutation(child);
            else
                CM[i][1]=-1;
		    add2new_population(child,i);
		}
		for(j=0;j<P;j++)
			for(k=0;k<G;k++)
				population[j][k]=new_population[j][k]; // COPY
        update_populationff(); // UPDATE
        cout << "\n POPULATION <" << populationCounter++ << ">\n\n";
        print_population_CM();
        /*BEST*/
        if(population_fitnessFunction[optimal_individual_index]>bestIndividualff) // IF (CURRENT > BEST)
        {
            bestIndividualff=population_fitnessFunction[optimal_individual_index];
            for(i=0;i<G;i++)
                bestIndividual[i]=population[optimal_individual_index][i]; // COPY
        }
        /*BEST*/
	}while(bestIndividualff!=MAXVALUE && (float)(clock()-s)/CLOCKS_PER_SEC*1000<timeOut);

    /*END*/e=clock();

    cout << "\n SOLUTION:\n\n \a";
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
    textColor(WHITE);
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
            return i;
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
	return MAXVALUE-cnt;
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

short reproduce(char child[],short x,short y)
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
    return crossOver;
}

short mutation(char child[])
{
    short m=rand()%G;
    child[m]=color[rand()%4];
    return m;
}

void add2new_population(char a[],short p)
{
    register short i;
    for(i=0;i<G;i++)
        new_population[p][i]=a[i];
}

void init_CM()
{
	register short i,j;
	for(i=0;i<P;i++)
	{
	    CM[i][0]=-1;
	    CM[i][1]=-1;
	}
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
			cout << ' ' << population[i][j] << ' ';
		cout << "--> " << population_fitnessFunction[i] << "\n\n";
	}
}

void print_population_CM()
{
	register short i,j;
	for(i=0;i<P;i++)
	{
		for(j=0/*START*/;j<CM[i][0]/*CROSSOVER*/;j++)
        {
            if(j==CM[i][1]/*MUTATION*/)
                textColor(CYAN);
            else
                textColor(YELLOW);
            cout << ' ' << population[i][j] << ' ';
        }
        for(/*CROSSOVER*/;j<G/*END*/;j++)
        {
            if(j==CM[i][1]/*MUTATION*/)
                textColor(CYAN);
            else
                textColor(LIGHTGREEN);
            cout << ' ' << population[i][j] << ' ';
        }
        textColor(WHITE);
		cout << "--> " << population_fitnessFunction[i] << "\n\n";
	}
}
