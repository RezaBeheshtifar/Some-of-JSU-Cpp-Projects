/* START: Family Tree Project With C++ */

using namespace std;
#include <cstdlib>
#include <iostream>
#include <iomanip>

void saving(short);

#include "familyTree.h"

void loading();
int menu();
familyTree testProject();

//end of prototype--------------------------------------------------------------

int main(int argc, char *argv[])
{  system("title Reza Beheshtifar AND Mohammad Zamani CREATED Family Tree Project");

   loading();      //2 sec delay
   familyTree FT;
   //FT=testProject(); //For test the Project
   string n,f,m;
   char c;
   unsigned s;
   myTime t;
   while(1)
      switch (menu())
      {
	     case 1: //Registration of Birth
	             cout << "\n <Birth>\n";
                 cout << "\n Name: ";
                 cin >> n;
                 cout << " Father: ";
                 cin >> f;
                 cout << " Mother: ";
                 cin >> m;
                 cout << " SSN: ";
                 cin >> s;
                 cout << " Sex: ";
                 cin >> c;
                 cout << " Date of Birth: ";
                 cin >> t.date;
                 if(c=='m')
                    c='M';
                 else if(c=='f')
                    c='F';
                 if(FT.birth(n,f,m,c,t,s)==false)
                    cout << "\n Error" << endl;
				 cout << "\n </Birth>\n";
				 saving(1000);
		         break;

	     case 2: //Registration of Marriage
	             cout << "\n <Marriage>\n";
                 cout << "\n Husband: ";
                 cin >> f;
                 cout << " Wife: ";
                 cin >> m;
                 cout << " Date of Marriage: ";
                 cin >> t.date;
                 if(FT.marriage(f,m,t)==false)
                    cout << "\n " << f << " / " << m << " Not Found.\n";
                 else
                    cout << "\n Saved.\n";
				 cout << "\n </Marriage>\n";
				 saving(1000);
				 break;

	     case 3: //Registration of death
	             cout << "\n <Death>\n";
                 cout << "\n Name: ";
                 cin >> n;
                 cout << " Date of Death: ";
                 cin >> t.date;
                 if(FT.death(n,t)==false)
                    cout << "\n Not Found.\n";
                 else
                    cout << "\n Saved.\n";
				 cout << "\n </Death>\n";
				 saving(1000);
				 break;

         case 4: //Registration of divorce
	             cout << "\n <Divorce>\n";
                 cout << "\n Husband: ";
                 cin >> f;
                 cout << " Wife: ";
                 cin >> m;
                 cout << " Date of Divorce: ";
                 cin >> t.date;
                 if(FT.divorce(f,m,t)==false)
                    cout << "\n Mission Failed.\n";
                 else
                    cout << "\n Saved.\n";
				 cout << "\n </Divorce>\n";
				 saving(1000);
				 break;

         case 5: //What is the relationship between A and B?
                 cout << "\n < Relationship between 'X' and 'Y' >\n";
                 cout << "\n Input 'X' name: ";
                 cin >> n;
                 cout << "\n Input 'Y' name: ";
                 cin >> m;
                 FT.Relation_betweenPeople(n,m);
                 break;

         case 6: //People who relationship with A
                 break;

         case 61://relationship Child
                 cout << "\n < Relationship :: Child >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_Child(n);
                 break;

         case 62://relationship Husband
                 cout << "\n < Relationship :: Husband >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_Husband(n);
                 break;

         case 63://relationship Wife
                 cout << "\n < Relationship :: Wife >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_Wife(n);

         case 64://relationship Brother
                 cout << "\n < Relationship :: Brother >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 cout << "\n Input Father's name: ";
                 cin >> f;
                 cout << "\n Input Mother's name: ";
                 cin >> m;
                 FT.Relation_brother(n,f,m);
                 break;

         case 65://relationship Sister
                 cout << "\n < Relationship :: Sister >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 cout << "\n Input Father's name: ";
                 cin >> f;
                 cout << "\n Input Mother's name: ";
                 cin >> m;
                 FT.Relation_sister(n,f,m);
                 break;

         case 66://relationship Grand Fhather
                 cout << "\n < Relationship :: Grand Fhather >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_GrandFather(n);
                 break;

         case 67://relationship Grand Mother
                 cout << "\n < Relationship :: Grand Mother >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_GrandMother(n);
                 break;

         case 68://relationship Ancestor
                 cout << "\n < Relationship :: Ancestor >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_Ancestor(n);
                 break;

         case 69://relationship Descendent
                 cout << "\n < Relationship :: Descendent >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_Descendent(n);
                 break;

         case 90://relationship Uncel [FB]
                 cout << "\n < Relationship :: Uncel [FB] >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_Uncel(n);
                 break;

         case 91://relationship Uncel [MB]
                 cout << "\n < Relationship :: Uncel [MB] >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_Uncel_momBrother(n);
                 break;

         case 92://relationship Aunt [FS]
                 cout << "\n < Relationship :: Aunt [FS] >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_Aunt(n);
                 break;

         case 93://relationship Aunt [MS]
                 cout << "\n < Relationship :: Aunt [MS] >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_Aunt_momSister(n);
                 break;

         case 94://relationship Father of Wife
                 cout << "\n < Relationship :: Father of Wife >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_FatherOfWife(n);
                 break;

         case 95://relationship Mother of Wife
                 cout << "\n < Relationship :: Mother of Wife >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_MotherOfWife(n);
                 break;

         case 96://relationship Father of Hus.
                 cout << "\n < Relationship :: Father of Hus. >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_FatherOfHus(n);
                 break;

         case 97://relationship Mother of Hus.
                 cout << "\n < Relationship :: Mother of Hus. >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_MotherOfHus(n);
                 break;

         case 98://relationship Brother-in-law
                 cout << "\n < Relationship :: Brother-in-law >\n";
                 cout << "\n Input Name: ";
                 cin >> n;
                 FT.Relation_Bajenagh(n);
                 break;

         case 7: //Option
                 break;

         case 71://Search by Name
                 cout << " Input Name: ";
                 cin >> n;
                 if(FT.isExistName(n)==false)
                 {
                    cout << " Not Found.\n";
                    saving(1000);
                 }
                 else
                    FT.printOne(FT.infoName(n));
                 break;

         case 72://Search by SSN
                 cout << " Input SSN: ";
                 cin >> s;
                 if(FT.isExistSSN(s)==false)
                 {
                    cout << " Not Found.\n";
                    saving(1000);
                 }
                 else
                    FT.printOne(FT.infoSSN(s));
                 break;

         case 73://Show All
                 if(FT.isEmpty()==true)
                 {
                     cout << "\n >>> Information:\n\n The Family Tree is Empty." << endl;
                     cin.get();
                 }
                 FT.printAll();
                 break;

         case 74://Show Special Informatiom about Tree
                 cout << "\n >>> Family Tree:"
                      << "\n\n Nodes:  " << FT.countNodes()
                      << "\n Height: " << FT.maxHeight()
                      << "\n Leaf:   " << FT.countLeaf()
                      << "\n\n " ;
                 system("pause");
                 break;

         case 8: //Setting
                 break;

         case 82://Save Files
                 break;

         case 84://Read Default Information
                 cout << "\n >>> Read Default Information: ";
                 FT=testProject();
                 cout << "\n\n Load is completed." << endl;
                 saving(1000);
                 break;

         case 0: //EXIT
                 cout << "\n\n\n\n\t\t\t\t<< Family Tree >>\n\n\n\n\t\t\t\tReza Beheshtifar\n\n\t\t\t\t Mohamad Zamani";
                 saving(1000);
                 return 0;

         default:
                 break;
      }
}

//end of call-------------------------------------------------------------------

void loading()
{  int sum=0,timeload=1010;
   cout << "\n\n\n\n\t\t\t\t<< Family Tree >>\n\n\n\n\t\t\t\tReza Beheshtifar\n\n\t\t\t\t Mohamad Zamani\n\n\n\n\n\n\n\n\n\n\n\n";
   for (int i=0; i<timeload ;i++)
   {  for (int num=0; num<600000 ; num++)
	    sum += num;
	  cout << "\tLOADING " << i/10 << "%\r";
   }
   system("cls");
   cout << "\n\n\n\n\t\t\t\t<< Family Tree >>\n\n\n\n\t\t\t\tReza Beheshtifar\n\n\t\t\t\t Mohamad Zamani\n\n\n\n\n\n\n\n\n\n\n\n";
   cout << "\tPress Enter to continue . . . ";
   cin.get();
   system(menuColor);
}

void saving(short delay)
{
    for (int i=0 ; i<1000 ; i++)
      for (int i=0 ; i<1000000 ; i++);
}

int menu()
{  short Choice;
   short ch;
   while(1)
   {   do { system("cls");
		    cout << " >>> MAIN MENU\n\n"
			     << " 1: Registration of Birth\n"
			     << "    ------------------------------------------\n"
		         << " 2: Registration of Marriage\n"
		         << "    ------------------------------------------\n"
		         << " 3: Registration of death\n"
		         << "    ------------------------------------------\n"
		         << " 4: Registration of divorce\n"
		         << "    ------------------------------------------\n"
		         << " 5: What is the relationship between A and B?\n"
		         << "    ------------------------------------------\n"
		         << " 6: People who relationship with A\n"
		         << "    ------------------------------------------\n"
		         << " 7: Option\n"
				 << "    ------------------------------------------\n"
				 << " 8: Setting\n"
				 << "    ------------------------------------------\n"
		         << " 0: EXIT\n"
		         << "\n _____________________________________________\n"
		         << " \n Please Select: ";
		    cin >> Choice;
	      } while(Choice<0 || Choice>8);
       if(Choice==6)
       {
           do {  system("cls");
	             cout << " >>> RELATIONSHIP WITH A\n\n"
                      << " 1: Child              10: Uncel [FB]\n"
                      << "    ---------------        ---------------\n"
	                  << " 2: Husband            11: Uncel [MB]\n"
	                  << "    ---------------        ---------------\n"
	                  << " 3: Wife               12: Aunt [FS]\n"
	                  << "    ---------------        ---------------\n"
	                  << " 4: Brother            13: Aunt [MS]\n"
	                  << "    ---------------        ---------------\n"
	                  << " 5: Sister             14: Father of Wife\n"
	                  << "    ---------------        ---------------\n"
	                  << " 6: Grand Fhather      15: Mother of Wife\n"
	                  << "    ---------------        ---------------\n"
	                  << " 7: Grand Mother       16: Father of Hus.\n"
	                  << "    ---------------        ---------------\n"
	                  << " 8: Ancestors          17: Mother of Hus.\n"
	                  << "    ---------------        ---------------\n"
                      << " 9: Descendents        18: Brother-in-law\n"
	                  << "\n _________________________________________\n"
	                  << " \n Please Select: ";
	             cin >> ch;
			  } while(ch<0 || ch>18);
            if(ch==1)
                Choice=61;
            else if(ch==2)
                Choice=62;
            else if(ch==3)
                Choice=63;
            else if(ch==4)
                Choice=64;
            else if(ch==5)
                Choice=65;
            else if(ch==6)
                Choice=66;
            else if(ch==7)
                Choice=67;
            else if(ch==8)
                Choice=68;
            else if(ch==9)
                Choice=69;
            else if(ch==10)
                Choice=90;
            else if(ch==11)
                Choice=91;
            else if(ch==12)
                Choice=92;
            else if(ch==13)
                Choice=93;
            else if(ch==14)
                Choice=94;
            else if(ch==15)
                Choice=95;
            else if(ch==16)
                Choice=96;
            else if(ch==17)
                Choice=97;
            else if(ch==18)
                Choice=98;
       }
       else if(Choice==7)
       {
           do {  system("cls");
	             cout << " >>> OPTION\n\n"
                      << " 1: Search by Name\n"
                      << "    ------------------------------------\n"
	                  << " 2: Search by SSN\n"
	                  << "    ------------------------------------\n"
	                  << " 3: Show All Information\n"
	                  << "    ------------------------------------\n"
	                  << " 4: Show Special Informatiom about Tree\n"
	                  << "    ------------------------------------\n"
                      << " 0: BACK\n"
	                  << "\n _______________________________________\n"
	                  << " \n Please Select: ";
	             cin >> ch;
			  } while(ch<0 || ch>4);
            if(ch==1)
                Choice=71;
            else if(ch==2)
                Choice=72;
            else if(ch==3)
                Choice=73;
            else if(ch==4)
                Choice=74;
       }
       else if(Choice==8)
       {
           do {  system("cls");
	             cout << " >>> SETTING\n\n"
				      << " 1: Change Color\n"
				      << "    -------------------------\n"
	                  << " 2: Save to File\n"
	                  << "    -------------------------\n"
				      << " 3: Read from File\n"
				      << "    -------------------------\n"
				      << " 4: Read Default File\n"
				      << "    -------------------------\n"
				      << " 0: BACK\n"
	                  << "\n ____________________________\n"
	                  << " \n Please Select: ";
	             cin >> ch;
			 } while(ch<0 || ch>4);
          if(ch==1)
	      {
	          do {   system("cls");
	                 cout << " >>> CHANGE COLOR\n\n"
                          << " 1: TEXT > White     BACKGROUND > Black\n"
	                      << "    ------------------------------------\n"
	                      << " 2: TEXT > Blue      BACKGROUND > White\n"
	                      << "    ------------------------------------\n"
	                      << " 3: TEXT > White     BACKGROUND > Blue\n"
                          << "    ------------------------------------\n"
	                      << " 0: BACK\n"
	                      << "\n _______________________________________\n"
	                      << " \n Please Select: ";
	                 cin >> ch;
			     } while(ch<0 || ch>3);
		      if(ch==1)
                 system("color 0F");
		      else if(ch==2)
                 system("color F9");
		      else if(ch==3)
                 system("color 9F");
		  }
		  else if(ch==2)
              Choice=82;
		  else if(ch==4)
              Choice=84;
       }
       system("cls");
       return Choice;
   }
}

familyTree testProject()
{
    #include "information.h"
}

//end of definition-------------------------------------------------------------
/* FINISH: Family Tree */
