#include "myTextColor.h"
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <climits>
#include <ctime>
#include <cmath>

using namespace std;

// FUNCTION(VAR1,VAR2,...,VAR8)=VAR1+VAR2-VAR3-VAR4+VAR5+VAR6-VAR7-VAR8

const short MAX_P=128; // POPULATION SIZE MAXIMUM
short P=64; // POPULATION SIZE

short OFFSET=37;
short MAXVALUE=5329;
short population[MAX_P][8];
short new_population[MAX_P][8];
short population_fitnessFunction[MAX_P];
short optimal_individual_index;
short bestIndividual[8];
short bestIndividualff=-1;

/*CROSSOVER_MUTATION::INDEX*/
// COLUMN 0 --> CROSSOVER, COLUMN 1 --> MUTATION
short CM[MAX_P][2];
/*CROSSOVER_MUTATION::INDEX*/

void intro();
void random_population();
short random_selection();
short fitnessFunction(short p);
void update_populationff();
short reproduce(short child[],short x,short y);
short mutation(short child[]);
void add2new_population(short a[],short p);
/*CROSSOVER_MUTATION::INDEX*/
void init_CM();
/*CROSSOVER_MUTATION::INDEX*/

// USER INTERFACE
void print_population();
void print_population_CM();

//MAIN////////////////////////////////////////////////////////////////

int main()
{
    system("title R.Beheshtifar 911846105"); //PROGRAMMER NAME

    clock_t s,e;
	float timediff;
	int timeOut=10000; // /1000 <SECOND>
	int populationCounter=0;

	register short i,j,k,X,Y;
	short child[8];

    intro();
    srand(time(NULL));

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
		    if((float)rand()/RAND_MAX<0.2)
                CM[i][1]=mutation(child);
            else
                CM[i][1]=-1;
		    add2new_population(child,i);
		}
		for(j=0;j<P;j++)
			for(k=0;k<8;k++)
				population[j][k]=new_population[j][k]; // COPY
        update_populationff(); // UPDATE
        cout << "\n POPULATION <" << populationCounter++ << ">\n\n";
        print_population_CM();
        //BEST
        if(population_fitnessFunction[optimal_individual_index]>bestIndividualff) // IF (CURRENT > BEST)
        {
            bestIndividualff=population_fitnessFunction[optimal_individual_index];
            for(i=0;i<8;i++)
                bestIndividual[i]=population[optimal_individual_index][i]; // COPY
        }
        //BEST
	}while(bestIndividualff!=MAXVALUE && (float)(clock()-s)/CLOCKS_PER_SEC*1000<timeOut);

    /*END*/e=clock();

    cout << "\n SOLUTION:\n\n \a";
    for(i=0;i<8;i++)
        cout << bestIndividual[i] << ' ';
    cout << "--> " << sqrt(bestIndividualff)-OFFSET;

    getch();
    return 0;
}

//FUNCTION////////////////////////////////////////////////////////////

void intro()
{
    textColor(LIGHTRED);
    cout << "\n\n\n\t\t\t Artificial Intelligence";
    textColor(GREEN);
    cout << "\n\n\n\t\t\t Optimal Value of Function";
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

void random_population()
{
	register short i,j;
	for(i=0;i<P;i++)
		for(j=0;j<8;j++)
			population[i][j]=rand()%10;
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
    short f=+population[p][0]+population[p][1]
            -population[p][2]-population[p][3]
            +population[p][4]+population[p][5]
            -population[p][6]-population[p][7];
    // [-36,+36]
    f+=OFFSET;
    // [1,73]
	return f*f; // [1,5329]
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

short reproduce(short child[],short x,short y)
{
    register short i=0;
    short crossOver=rand()%9;
    if(rand()%2)
    {
        for(;i<crossOver;i++)
            child[i]=population[x][i];
        for(;i<8;i++)
            child[i]=population[y][i];
    }
    else
    {
        for(;i<crossOver;i++)
            child[i]=population[y][i];
        for(;i<8;i++)
            child[i]=population[x][i];
    }
    return crossOver;
}
short mutation(short child[])
{
    short m=rand()%8;
    child[m]=rand()%10;
    return m;
}
void add2new_population(short a[],short p)
{
    register short i;
    for(i=0;i<8;i++)
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

void print_population()
{
	register short i,j;
	for(i=0;i<P;i++)
	{
		for(j=0;j<8;j++)
			cout << ' ' << population[i][j] << ' ';
		cout << "--> " << sqrt(population_fitnessFunction[i])-OFFSET << "\n\n";
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
        for(/*CROSSOVER*/;j<8/*END*/;j++)
        {
            if(j==CM[i][1]/*MUTATION*/)
                textColor(CYAN);
            else
                textColor(LIGHTGREEN);
            cout << ' ' << population[i][j] << ' ';
        }
        textColor(WHITE);
		cout << "--> " << sqrt(population_fitnessFunction[i])-OFFSET << "\n\n";
	}
}
