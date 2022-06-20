/* START: Note */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#define MAXTITLE 41
#define MAXTEXT 101
#define MAXNOTE 200
#define MAXADDRESS 100
using namespace std;

//end of include----------------------------------------------------------------

struct Note
{  char Title[MAXTITLE];
   char Text[MAXTEXT];
   char Modified[20];   //format: <YYYY/MM/DD><HH:MM>
   char Reminder[20];   //format: <YYYY/MM/DD><HH:MM>
};

//end of struct-----------------------------------------------------------------

void loading(int);
void saving(int);

int menu();
short Searchmenu();

void Read(Note &);
void ReadDate(char[]);
void Print(Note,int);

void Insert(Note[],int &,Note);
void Delete(Note[],int &,int);
void Edit(Note[],int,int);

void ReportToday(Note[],int);
void ReportAll(Note[],int);

int SearchTitle(Note[],int,char[]);
int SearchText(Note[],int,char[]);
int SearchModified(Note[],int,char[]);
int SearchReminder(Note[],int,char[]);

void SortReminder(Note[],int);

void Save(Note[],int,char[]);
void Readfiles(Note[],int &,char[]);

void TimeToStr(char[]);

//end of prototype--------------------------------------------------------------

int main(int argc, char *argv[])
{  system("title * Novinsoft * Reza Beheshtifar * Final Project");
   system("color 9F");
   Note Array[MAXNOTE];
   int Elemnum=0;
   char Address[MAXADDRESS]="NOTE BOOK.txt";
   loading(1001);      //2-3 sec delay
   while(1)
      switch (menu())
      {  	
	     case 1: Note A;
	             cout << "\n <Insert>\n";
				 Read(A);
				 Insert(Array,Elemnum,A);
				 cout << "\n </Insert>\n";
				 saving(700);
		         break;
			
	     case 2: int index;
	             cout << "\n <Delete>\n";
	             if(Elemnum!=0)
	             {  do{ cout << " Input index: ";
				        cin >> index; } while(index<0 || index>Elemnum-1);
				    Delete(Array,Elemnum,index);
				 }
				 else
				    cout << "\a There aren't Notes." << endl;
				 cout << "\n </Delete>\n";
				 saving(700);
				 break;
			
	     case 3: int edit;
		         cout << "\n <Edit>\n";
		         if(Elemnum!=0)
		         {  do{ cout << " Input index: ";
				        cin >> edit; } while(edit<0 || edit>Elemnum-1);
				    Edit(Array,Elemnum,edit);
				 }
				 else
				    cout << "\a There aren't Notes." << endl;
				 cout << "\n </Edit>\n";
				 saving(700);
				 break;
			
	     case 4: cout << "\n <Print>\n";
	             if(Elemnum!=0)
                    ReportToday(Array,Elemnum);
				 else
				    cout << "\a There aren't Notes." << endl;
				 cout << "\n </Print>\n\n";
				 cout << " Goto \"MAIN MENU\" >>> ";
				 system("pause");
				 break;
			
	     case 5: cout << "\n <Print>\n";
	             if(Elemnum!=0)
                    ReportAll(Array,Elemnum);
				 else
				    cout << "\a There aren't Notes." << endl;
				 cout << "\n </Print>\n\n";
				 cout << " Goto \"MAIN MENU\" >>> ";
				 system("pause");
				 break;
			
	     case 6: cout << "\n <SEARCHING>\n";
	             if(Elemnum!=0)
                    {   char Key[MAXTITLE];
						cout << " Input title: ";
                        cin >> Key;
                        int search=SearchTitle(Array,Elemnum,Key);
					    if(search!=-1)
					    {  Print(Array[search],search);
					       cout << "\n I want Goto \"SEARCH MENU\" >>> ";
						   system("pause");
						   int Exit=0;
						   while(1)
					       {   switch(Searchmenu())
					             {  case 1: for(int i=search+1 ; i<Elemnum ; i++)
									        {  Print(Array[i],i);
									           if(i!=Elemnum-1)
									           {  cout << " Next Note >>> ";
									              system("pause");
											   }
											   else
											   {  cout << "\n\a Finish.Goto \"SEARCH MENU\" >>> ";
									              system("pause");
											   }
										    }
									        break;
									        
								    case 0: Exit=1;
										    break;
								 
								    case 2: for(int i=search ; i>=0 ; i--)
									        {  Print(Array[i],i);
									           if(i!=0)
											   {  cout << " Before Note >>> ";
									              system("pause");
											   }
											   else
											   {  cout << "\n\a Finish.Goto \"SEARCH MENU\" >>> ";
									              system("pause");
											   }
										    }
										    break;
										
							     }
							   if(Exit==1)
							   { Exit=0; break;}
							}	
						}  
					    else
					       cout << "\a Not found.";
				    }
				 else
				    cout << "\a There aren't Notes." << endl;
				 cout << "\n </SEARCHING>\n ";
				 saving(700);
				 break;
			
         case 7: cout << "\n <SEARCHING>\n";
	             if(Elemnum!=0)
                    {   char Key[MAXTEXT];
						cout << " Input text: ";
                        cin >> Key;
                        int search=SearchText(Array,Elemnum,Key);
					    if(search!=-1)
					    {  Print(Array[search],search);
					       cout << "\n I want Goto \"SEARCH MENU\" >>> ";
						   system("pause");
						   int Exit=0;
						   while(1)
					       {   switch(Searchmenu())
					             {  case 1: for(int i=search+1 ; i<Elemnum ; i++)
									        {  Print(Array[i],i);
									           if(i!=Elemnum-1)
									           {  cout << " Next Note >>> ";
									              system("pause");
											   }
											   else
											   {  cout << "\n\a Finish.Goto \"SEARCH MENU\" >>> ";
									              system("pause");
											   }
										    }
									        break;
									        
								    case 0: Exit=1;
										    break;
								 
								    case 2: for(int i=search ; i>=0 ; i--)
									        {  Print(Array[i],i);
									           if(i!=0)
											   {  cout << " Before Note >>> ";
									              system("pause");
											   }
											   else
											   {  cout << "\n\a Finish.Goto \"SEARCH MENU\" >>> ";
									              system("pause");
											   }
										    }
										    break;
										
							     }
							   if(Exit==1)
							   { Exit=0; break;}
							}	
					    }
					    else
					       cout << "\a Not found.";
				    }
				 else
				    cout << "\a There aren't Notes." << endl;
				 cout << "\n </SEARCHED>\n ";
				 saving(700);
				 break;
			
	     case 8: cout << "\n <SEARCHING>\n";
	             if(Elemnum!=0)
                    {   char Key[20];
						cout << " Input Date and Time:\n\n";
                        ReadDate(Key);
                        int search=SearchModified(Array,Elemnum,Key);
					    if(search!=-1)
					       Print(Array[search],search);
					    else
					       cout << "\a Not found.";
				    }
				 else
				    cout << "\a There aren't Notes." << endl;
				 cout << "\n </SEARCHING>\n ";
				 saving(700);
				 break;
			
	     case 9: cout << "\n <SEARCHING>\n";
	             if(Elemnum!=0)
                    {   char Key[20];
						cout << " Input Date and Time:\n\n";
                        ReadDate(Key);
                        int search=SearchReminder(Array,Elemnum,Key);
					    if(search!=-1)
					    {  Print(Array[search],search);
					       cout << "\n I want Goto \"SEARCH MENU\" >>> ";
						   system("pause");
						   int Exit=0;
						   while(1)
					       {   switch(Searchmenu())
					             {  case 1: for(int i=search+1 ; i<Elemnum ; i++)
									        {  Print(Array[i],i);
									           if(i!=Elemnum-1)
									           {  cout << " Next Note >>> ";
									              system("pause");
											   }
											   else
											   {  cout << "\n\a Finish.Goto \"SEARCH MENU\" >>> ";
									              system("pause");
											   }
										    }
									        break;
									        
								    case 0: Exit=1;
										    break;
								 
								    case 2: for(int i=search ; i>=0 ; i--)
									        {  Print(Array[i],i);
									           if(i!=0)
											   {  cout << " Before Note >>> ";
									              system("pause");
											   }
											   else
											   {  cout << "\n\a Finish.Goto \"SEARCH MENU\" >>> ";
									              system("pause");
											   }
										    }
										    break;
										
							     }
							   if(Exit==1)
							   { Exit=0; break;}
							}	
					    }
					    else
					       cout << "\a Not found.";
				    }
				 else
				    cout << "\a There aren't Notes." << endl;
				 cout << "\n </SEARCHING>\n ";
				 saving(700);
				 break;
	     
	     case 10:cout << "\n <SAVING>\n";
				 Save(Array,Elemnum,Address);
				 cout << "\n </SAVED>\n";
				 saving(700);
	             break;
	             
	     case 11:cout << "\n <READING>\n";
				 Readfiles(Array,Elemnum,Address);
				 cout << "\n </READ>\n";
				 saving(700);
	             break;
				
		 case 12:cout << "\n <ADDRESS>\n";
		         cout << " Input Address:\n >>> ";
		         cin >> Address;
				 cout << "\n </ADDRESS>\n";
				 saving(700);
	             break;
	             
      }

   system("pause");
   return 0;
}

//end of call-------------------------------------------------------------------

void loading(int timeload)
{  time_t t1;
   float t;
   t1 = time(NULL);
   double sum=0;
   cout << "\n\n\n\n\n\n\n\n\n\n";
   for (int i=0; i<timeload ;i++)
   {  for (int num=0; num<600000 ; num++)
	    sum += num;
	  cout << "\t\t\t\tLOADING " << i/10 << "%\r";
   }
   cout << "\n\n";
   sum=0;
   float Done=time(NULL)-t1;
   for (int i=0; i<200 ;i++)
   {  for (int num=0; num<1000000 ; num++)
	    sum += num;
	  cout << "\t\t\t\tDone in " << Done << " Sec" << "\r";
   }
}
void saving(int delay)
{  double sum=0;
   for (int i=0 ; i<delay ; i++)
     for (int i=0 ; i<600000 ; i++)
	    sum+=i;
}

int menu()
{  short BaseChoice,BranchChoice;
   short SETTING=0;
   while(1)
   {   do { system("cls");
		    cout << " >>> MAIN MENU\n\n"
			     << " 1: Insert a Note\n"                    //BaseChoice=1
			     << "    -------------------------\n"
		         << " 2: Delete a Note\n"                    //BaseChoice=2
		         << "    -------------------------\n"
		         << " 3: Edit a Note\n"                      //BaseChoice=3
		         << "    -------------------------\n"
		         << " 4: View today's Notes\n"               //BaseChoice=4
		         << "    -------------------------\n"
		         << " 5: View all of Notes\n"                //BaseChoice=5
		         << "    -------------------------\n"
		         << " 6: Find a Special Note\n"    
				 << "    -------------------------\n"       
		         << " 0: SETTING\n"
		         << "\n ____________________________\n"
		         << " \n Please Select: ";
		    cin >> BaseChoice;
	      } while(BaseChoice<0 || BaseChoice>6);
	  
	   if(BaseChoice==6)
	      {   do { system("cls");
		           cout << " >>> FINDER\n\n"
				        << " 1: Find a Title\n"              //BaseChoice=6
				        << "    -------------------------\n"
		                << " 2: Find a Text\n"               //BaseChoice=7
		                << "    -------------------------\n"
		                << " 3: Search by Modified\n"        //BaseChoice=8
		                << "    -------------------------\n"
		                << " 4: Search by Reminder\n"        //BaseChoice=9
		                << "    -------------------------\n"
		                << " 5: Back to Main Menu\n"
		                << "\n ____________________________\n"
		                << " \n Please Select: ";
		           cin >> BranchChoice;
	             } while(BranchChoice<1 || BranchChoice>5);
	          BaseChoice=BaseChoice+BranchChoice-1;
	      }
	   
	   if(BaseChoice!=10 && BaseChoice!=0)
	      return BaseChoice;
	   
	   if(BaseChoice==0)
	      do {   system("cls");
	             cout << " >>> SETTING\n\n"
				      << " 1: Change Color\n"
				      << "    -------------------------\n"
	                  << " 2: Save Changes\n"
	                  << "    -------------------------\n"
				      << " 3: Read Files\n"
				      << "    -------------------------\n"
				      << " 4: Change Address\n"
	                  << "\n ____________________________\n"
	                  << " \n Please Select: ";
	             cin >> SETTING;
			 } while(SETTING<1 || SETTING>4);
			 
	    if(SETTING==1)
	      {   do {   system("cls");
	                 cout << " 1: TEXT > White     BACKGROUND > Black\n"
	                      << "    ------------------------------------\n"
	                      << " 2: TEXT > Blue      BACKGROUND > White\n"
	                      << "    ------------------------------------\n"
	                      << " 3: TEXT > White     BACKGROUND > Blue\n"
	                      << "\n _______________________________________\n"
	                      << " \n Please Select: ";
	                 cin >> SETTING;
			     } while(SETTING<1 || SETTING>3);
		      if(SETTING==1)
		         { system("color 0F");
		           SETTING=0;
				 }
		      if(SETTING==2)
		         { system("color F9");
		           SETTING=0;
				 }
		      if(SETTING==3)
		         { system("color 9F");
		           SETTING=0;
				 }
		  }
	    if(SETTING==2)
	       {  SETTING=0;
	          return 10;                                      //Setting=10
		   }
		if(SETTING==3)
		   {  SETTING=0;
		      return 11;                                      //Setting=11
		   }
		if(SETTING==4)
		   {  SETTING=0;
		      return 12;                                      //Setting=12
		   }
   }
}
short Searchmenu()
{   short searchchoice;
    do {   system("cls");
	       cout << " >>> SEARCH MENU\n\n"
				<< " 1: Next Notes\n"
				<< "    -------------------------\n"
	            << " 2: Before Notes\n"
	            << "    -------------------------\n"
				<< " 0: Back to Main Menu\n"
	            << "\n ____________________________\n"
	            << " \n Please Select: ";
	       cin >> searchchoice;
	   } while(searchchoice<0 || searchchoice>2);
	return searchchoice;
}

void Read(Note &R)
{   cout << "\n Input the title of Note [" << MAXTITLE-1 << "] :\n -";
    cin >> R.Title;
    cout << "\n Input the text of Note [" << MAXTEXT-1 << "] :\n -";
    cin >> R.Text;
    cout << "\n Input Date & Time for Alarm :\n\n";
    ReadDate(R.Reminder);
	TimeToStr(R.Modified);
}
void ReadDate(char R[])
{   char Year[5],Month[3],Day[3],Hour[3],Minute[3];
	cout << " -Input year [4 Digit]:   ";
	cin >> Year;
	cout << " -Input month [2 Digit]:  ";
	cin >> Month;
	cout << " -Input day [2 Digit]:    ";
	cin >> Day;
	cout << " -Input hour [2 Digit]:   ";
	cin >> Hour;
	cout << " -Input minute [2 Digit]: ";
	cin >> Minute;
	R[0]='<';
	R[1]=Year[0];
	R[2]=Year[1];
	R[3]=Year[2];
	R[4]=Year[3];
	R[5]='/';
	R[6]=Month[0];
	R[7]=Month[1];
	R[8]='/';
	R[9]=Day[0];
	R[10]=Day[1];
	R[11]='>';
	R[12]='<';
	R[13]=Hour[0];
	R[14]=Hour[1];
	R[15]=':';
	R[16]=Minute[0];
	R[17]=Minute[1];
	R[18]='>';
	R[19]='\0';
}
void Print(Note P,int Number)
{   cout << "\n\t\t (TITLE)    >>> " << P.Title << endl;
    cout << "\t\t (TEXT)     >>> " << P.Text << endl;
    cout << "\t\t (CREATED)  >>> " << P.Modified << endl;
    cout << "\t\t (REMINDER) >>> " << P.Reminder << endl;
    cout << "\t\t (NUMBER)   >>> " << Number << endl;
    cout << endl;
}

void Insert(Note Array[],int &Elemnum,Note I)
{   if(Elemnum==MAXNOTE)
       cout << "\a Memory is full." << endl;
    else
       {  Array[Elemnum]=I;
          Elemnum++;
          SortReminder(Array,Elemnum);
	   }
}
void Delete(Note Array[],int &Elemnum,int D)
{   for(int i=D ; D<Elemnum-1 ; i++)
       Array[i]=Array[i+1];
    Elemnum--;
}
void Edit(Note Array[],int Elemnum,int E)
{   Note A;
	Read(A);
	Array[E]=A;
	SortReminder(Array,Elemnum);
}

void ReportToday(Note Array[],int Elemnum)
{   char Nulltime[20],Temp[20];
    TimeToStr(Nulltime);
    Nulltime[12]='\0';
	for(int i=0 ; i<Elemnum ; i++)
    {  strcpy(Temp,Array[i].Reminder);
       Temp[12]='\0';
	   if(strcmp(Temp,Nulltime)==0)
	      Print(Array[i],i);
	}
}
void ReportAll(Note Array[],int Elemnum)
{   char Nulltime[20];
    TimeToStr(Nulltime);
	for(int i=0 ; i<Elemnum ; i++)
       if(strcmp(Array[i].Reminder,Nulltime)!=-1)
	      Print(Array[i],i);
}

int SearchTitle(Note Array[],int Elemnum,char Key[])
{   int i;
	for(i=0 ; i<Elemnum ; i++)
       if(strcmp(Key,Array[i].Title)==0)
          return i;
    return -1;
}
int SearchText(Note Array[],int Elemnum,char Key[])
{   int i;
	for(i=0 ; i<Elemnum ; i++)
       if(strcmp(Key,Array[i].Text)==0)
          return i;
    return -1;
}
int SearchModified(Note Array[],int Elemnum,char Key[])
{   int i;
	for(i=0 ; i<Elemnum ; i++)
       if(strcmp(Key,Array[i].Modified)==0)
          return i;
    return -1;
}
int SearchReminder(Note Array[],int Elemnum,char Key[])
{   int i;
	for(i=0 ; i<Elemnum ; i++)
       if(strcmp(Key,Array[i].Reminder)==0)
          return i;
    return -1;
}

void Readfiles(Note Array[],int &Elemnum,char Address[])
{  ifstream read(Address);
   if(!read)
   { cout << "\n\a Warning: File Not Found.\n ";
     system("pause");
   }
   int i=Elemnum;
   while(!read.eof())
   {  read >> Array[i].Title
           >> Array[i].Text
		   >> Array[i].Modified
		   >> Array[i].Reminder;
      i++;
	  Elemnum++;
	  if(Elemnum==MAXNOTE)
	     break;
   }
   Elemnum--;
   SortReminder(Array,Elemnum);
}

void SortReminder(Note Array[],int Elemnum)
{  Note temp;
   for(int i=0 ; i<Elemnum-1 ; i++)
      for(int j=0 ; j<Elemnum-1 ; j++)
         if(strcmp(Array[j].Reminder,Array[j+1].Reminder)==1)
         {  temp=Array[j];
            Array[j]=Array[j+1];
            Array[j+1]=temp;
		 }
}

void Save(Note Array[],int Elemnum,char Address[])
{  ofstream save(Address);
   if(!save)
   { cout << "\n\a Warning: File Not Opened.\n ";
     system("pause");
   }
   for(int i=0 ; i<Elemnum ; i++)
   {  save << Array[i].Title << ' ';
      save << Array[i].Text << ' ';
      save << Array[i].Modified << ' ';
      save << Array[i].Reminder << ' ';
   }
}

void TimeToStr(char t[])    // format: <YYYY/MM/DD><HH:MM>
{  // current date-time based on current system
   time_t now = time(0);
   // convert now to string form
   char* dt = ctime(&now);
   ofstream wtime("~time~");
   wtime << dt << endl;
   // format: Sat Jan DD HH:MM:SS YYYY
   wtime.close();
   ifstream rtime("~time~");
   char time[26];
   rtime.get(time,25);
   rtime.close();
   t[0]='<';
   t[1]=time[20];
   t[2]=time[21];
   t[3]=time[22];
   t[4]=time[23];
   t[5]='/';
   if(time[4]=='J')
   {  if(time[5]=='a')
      { t[6]='0'; t[7]='1'; }
      else
      {  if(time[6]=='n')
         { t[6]='0'; t[7]='6'; }
         if(time[6]=='l')
         { t[6]='0'; t[7]='7'; }
      }
   }
   else if(time[4]=='F')
        { t[6]='0'; t[7]='2'; }
   else if(time[4]=='M')
   {  if(time[6]=='r')
      { t[6]='0'; t[7]='3'; }
      if(time[6]=='y')
      { t[6]='0'; t[7]='5'; }
   }
   else if(time[4]=='A')
   {  if(time[5]=='p')
      { t[6]='0'; t[7]='4'; }
      if(time[5]=='u')
      { t[6]='0'; t[7]='8'; }
   }
   else if(time[4]=='S')
        { t[6]='0'; t[7]='9'; }
   else if(time[4]=='O')
        { t[6]='1'; t[7]='0'; }
   else if(time[4]=='N')
        { t[6]='1'; t[7]='1'; }
   else if(time[4]=='D')
        { t[6]='1'; t[7]='2'; }
   t[8]='/';
   t[9]=time[8];
   t[10]=time[9];
   t[11]='>';
   t[12]='<';
   t[13]=time[11];
   t[14]=time[12];
   t[15]=':';
   t[16]=time[14];
   t[17]=time[15];
   t[18]='>';
   t[19]='\0';
   // format: <YYYY/MM/DD><HH:MM>
}
//end of definition-------------------------------------------------------------
/* FINISH: Note */
