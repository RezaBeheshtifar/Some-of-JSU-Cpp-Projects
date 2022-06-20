/* 
 * START: Align Text Left Project With C++
 * Using Dynamic Programming
 * R.Beheshtifar 911846105
 * Professor M.EnayatZare
 */

using namespace std;
#include <cstdlib>
#include <iostream>
#include <fstream>
#define color "color 1F"
#define path_input "input.txt"
#define path_output "output.txt"
#define path_words "words.txt"
#define path_paragraph "paragraph.txt"
#define max 100
#define INFINITE 2147483647
// 2^32/2-1

int loading(int &n, int &M, int L[]); // Read Data from 'path_input' & Clear 'path_output' & Clear 'path_paragraph'
int loadingWords(string W[], int n);  // Read words from 'path_words'
int const lineCost(int n, int M, int L[], int i, int j);
void computeLcArray(int n, int M, int L[], int LC[][max]);
void computeSolution(int n, int M, int LC[][max], int C[], int P[]);
int displayPrint_Solution(int P[], int n);
void displayPrint_AlignTextLeft(int P[], string W[], int n);

//end of prototype--------------------------------------------------------------

int main(int argc, char *argv[])
{
	system("title Reza Beheshtifar  911846105");
	system(color);
	
	int n, M;
	int L[max], LC[max][max], C[max], P[max];
	string W[max];
	
	cout << "\n Align Text Left Project:\n\n";
	
	if(loading(n,M,L)) // loading(n,M,L)==1 --> The Information in File is Correct.
	{
		cout << " n = " << n << " , M = " << M << "\n";
		computeLcArray(n,M,L,LC);
		computeSolution(n,M,LC,C,P);
		
		cout << "\n <Solution>\n\n";
		ofstream fout(path_output, ios::app);
		fout << C[n] << endl;
		fout.close();
		displayPrint_Solution(P,n);
		cout << "\n </Solution>\n\n";
		
		if(loadingWords(W,n))
		{
			cout << "\n <Paragraph>\n\n";
			displayPrint_AlignTextLeft(P,W,n);
			cout << "\n </Paragraph>\n\n";
		}
	}
	
	cout << "\n ";
	system("pause");
	return 0;
}

//end of call-------------------------------------------------------------------

int loading(int &n, int &M, int L[])
{
    string fileNotFound=" Mission Failed, File Not Found.";
    string infoNotCorrect=" The Information in File, Not Correct.";
    
    ifstream fin(path_input);
    ofstream fout;
	fout.open(path_output);
    fout.close(); // clear output file
    fout.open(path_paragraph);
    fout.close(); // clear paragraph file
    
    if(!fin.is_open())
    {
		cout << fileNotFound << " [" << path_input << "]" << endl;
		fin.close();
		return 0;
    }
    	
    if(!fin.eof())
    	fin >> n;
    else
    {
		cout << infoNotCorrect << " [" << path_input << "]" << endl;
		fin.close();
		return 0;
    }      
    if(!fin.eof())
    	fin >> M;
    else
    {
		cout << infoNotCorrect << " [" << path_input << "]" << endl;
		fin.close();
		return 0;
    }  
    int i=1;
    while(!fin.eof() && i<=n)
    	fin >> L[i++];
    if(i<=n) // size(L) < n ; Data aren't complete.
    {
		cout << infoNotCorrect << " [" << path_input << "]" << endl;
		fin.close();
		return 0;
    }
    fin.close();
    return 1;
}

int loadingWords(string W[], int n)
{
    string fileNotFound=" Mission Failed, File Not Found.";
    string infoNotCorrect=" The Information in File, Not Correct.";
    
    ifstream fin(path_words);
    
    if(!fin.is_open())
    {
		cout << fileNotFound << " [" << path_words << "]" << endl;
		fin.close();
		return 0;
    }
    int i=1;
    while(!fin.eof() && i<=n)
    	fin >> W[i++];
    if(i<=n) // size(W) < n ; Data aren't complete.
    {
		cout << infoNotCorrect << " [" << path_words << "]" << endl;
		fin.close();
		return 0;
    }
    fin.close();
    return 1;
}

int const lineCost(int n, int M, int L[], int i, int j)
{
	int tempL=0;
	for(int k=i;k<=j;k++)
		tempL+=L[k];
	int temp=M-j+i-tempL;
	// temp=number of space in end of line
	if(temp<0)
		return INFINITE;
	// temp<0 --> lineCost=INFINITE
	return temp*temp*temp;
}

void computeLcArray(int n, int M, int L[], int LC[][max])
{
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			if(i==j)
				LC[i][j]=M-L[i]; // main diameter
			else if(LC[i][j-1]==INFINITE || LC[i][j-1]-1-L[j]<0)
				LC[i][j]=INFINITE;
			else
				LC[i][j]=LC[i][j-1]-1-L[j];
		}
	
	register int R;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			R=LC[i][j];
			if(R!=INFINITE)
				LC[i][j]=R*R*R;
		}
}

void computeSolution(int n, int M, int LC[][max], int C[], int P[])
{
	C[0]=0;
	for(int j=1 ; j<=n ; j++)
    {
        C[j]=INFINITE;
        for(int i=1 ; i<=j ; i++)
            if(C[i-1]!=INFINITE && LC[i][j]!=INFINITE && (C[i-1]+LC[i][j]-1<C[j]))
            {
                C[j]=C[i-1]+LC[i][j]-1;
                P[j]=i;
            }
    }
}

int displayPrint_Solution(int P[], int n)
{
	ofstream fout(path_output, ios::app);
    int k; // k=Line_number
    if(P[n]==1)
        k=1;
    else
        k=displayPrint_Solution(P,P[n]-1)+1;
    cout << "Line " << k << ": From "<< P[n] << " To " << n << endl;
    fout << k << ": " << P[n] << ',' << n << endl;
    fout.close();
    return k;
}

void displayPrint_AlignTextLeft(int P[], string W[], int n)
{
	ofstream fout(path_paragraph, ios::app);
    if(P[n]==1)
    {
    	for(int k=1 ; k<=n ; k++)
    	{
    		cout << W[k] << ' ';
    		fout << W[k] << ' ';
    	}	
    	cout << endl;
    	fout << endl;
    	fout.close();
    	return;
    }
    displayPrint_AlignTextLeft(P,W,P[n]-1);
    for(int k=P[n] ; k<=n ; k++)
    {
		cout << W[k] << ' ';
		fout << W[k] << ' ';
    }
    cout << endl;
    fout << endl;
    fout.close();
}

//end of definition-------------------------------------------------------------
/* FINISH: Align Text Left Project */
