/* START: DC_Multiply Project With C++ */

using namespace std;
#include <cstdlib>
#include <iostream>
#define MenuColor "color 1F"
#define SubMenuColor "color 3F"
#define myDelay 1800

#include "DC_Multiply.h"

void delay(int);
void loading();
int menu();

//end of prototype--------------------------------------------------------------

int main(int argc, char *argv[])
{
   system("title Reza Beheshtifar");
   loading();

   string bs1, bs2;
   int n;

   while(1)
      switch (menu())
      {
	     case 1:
	             cout << "\n <Add>\n";
	             do{
                    cout << "\n Enter the 'first'  binary number: ";
                    cin >> bs1;
	             }while(!isBinary(bs1));
	             do{
                    cout << "\n Enter the 'second' binary number: ";
                    cin >> bs2;
	             }while(!isBinary(bs2));
	             cout << "\n Result = " << addString(bs1,bs2);
				 cout << "\n\n </Add>";
				 delay(myDelay);
		         break;

	     case 2:
	             cout << "\n <Multiply>\n";
	             do{
                    cout << "\n Enter the 'first'  binary number: ";
                    cin >> bs1;
	             }while(!isBinary(bs1));
	             do{
                    cout << "\n Enter the 'second' binary number: ";
                    cin >> bs2;
	             }while(!isBinary(bs2));
	             cout << "\n Result = " << multiply(bs1,bs2);
				 cout << "\n\n </Multiply>\n";
				 delay(myDelay);
		         break;

	     case 3:
	             cout << "\n <Convert>\n";
                 cout << "\n Enter the 'power' of decimal number: ";
                 cin >> n;
	             cout << "\n Result = " << power2bin_first(n);
				 cout << "\n\n </Convert>\n";
				 delay(myDelay);
		         break;

	     case 4:
	             cout << "\n <Convert>\n";
	             do{
	                cout << "\n Enter the decimal number: ";
	                cin >> bs1;
                 }while(!isDecimal(bs1));
	             cout << "\n Result = " << decimal2bin(bs1);
				 cout << "\n\n </Convert>\n";
				 delay(myDelay);
		         break;

	     case 5:
	             cout << "\n <Test>\n";
	             #include "test.h"
				 cout << "\n\n </Test>\n\n ";
                 system("pause");
		         break;

         case 0: //EXIT
                 cout << "\n\n\n\n\t\t\t\t<< DC_Multiply >>\n\n\n\n\t\t\t\tReza Beheshtifar";
                 delay(myDelay);
                 return 0;

         default:
                 break;
      }
}

//end of call-------------------------------------------------------------------

void delay(int d)
{
    for (int i=0 ; i<d ; i++)
      for (int i=0 ; i<1000000 ; i++);
}

void loading()
{  int sum=0,timeload=1010;
   cout << "\n\n\n\n\t\t\t\t<< DC_Multiply >>\n\n\n\n\t\t\t\tReza Beheshtifar\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
   for (int i=0; i<timeload ;i++)
   {  for (int num=0; num<600000 ; num++)
	    sum += num;
	  cout << "\tLOADING " << i/10 << "%\r";
   }
   system("cls");
   cout << "\n\n\n\n\t\t\t\t<< DC_Multiply >>\n\n\n\n\t\t\t\tReza Beheshtifar\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
   cout << "\tPress Enter to continue . . . ";
   cin.get();
}

int menu()
{
   system(MenuColor);
   short Choice;
   while(1)
   {   do { system("cls");
		    cout << " >>> MAIN MENU\n\n\n"
                 << " 1: Add          ; binary + binary\n"
			     << "    ----------------------------------\n"
			     << " 2: Multiply     ; binary * binary\n"
			     << "    ----------------------------------\n"
		         << " 3: Convert      ; 10^n to binary\n"
		         << "    ----------------------------------\n"
		         << " 4: Convert      ; decimal to binary\n"
				 << "    ----------------------------------\n"
		         << " 5: Program Test ; test\n"
				 << "    ----------------------------------\n"
		         << " 0: EXIT\n"
		         << "\n\n _____________________________________\n"
		         << " \n Please Select: ";
		    cin >> Choice;
	      } while(Choice<0 || Choice>5);
       system("cls");
       system(SubMenuColor);
       return Choice;
   }
}

//end of definition-------------------------------------------------------------
/* FINISH: DC_Multiply */
