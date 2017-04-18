
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "funtion.h"
#include <map>

using namespace std;

int main()
{
       int Data_size =7500*10000;
       function tool;



       int** Data = new int*[Data_size];
       for(int i = 0;i < Data_size;i ++) Data[i] = new int[4];
       map<int ,map<int, map<int, int> > > Map;
       map<int, map<int, map<int, int> > >::iterator iter;

       ifstream input("/tmp2/KDDCUP2012/track1/rec_log_train.txt");
       //ifstream input("testdata.txt");

       for(int i = 0;i < Data_size;i++)
       {
	       for(int j = 0;j < 4;j++)
	       {
		       input  >> Data[i][j]; //UserID / ItemID / Result / Unix-timestamp
	       }
	       Map[ Data[i][0] ][Data[i][1] ][ Data[i][3] ] = Data[i][2];
       } 
       cout << "Now Please Input query time " << endl;
       int time;
       cin >> time;
       
       for(int i = 0;i <time; i++)
       {
         //cout << "query ";
         string command;
         int choose;
         cin >> command;

         if(command == "accept") choose = 1;
         else if(command == "items") choose = 2;
	 else if(command == "users") choose = 3;
	 else if(command == "ratio") choose = 4;
	 else if(command == "findtime_item") choose = 5;
         else if(command == "end") choose = 10;
         else choose= 0;

         switch(choose)
         {
	         case 0:
		         cout << "Wrong query !" << endl;
		         break;
	         case 1:
			 int user,item,times;
			 cin >> user >> item >> times;
			 cout << Map[user][item][times] << endl;
		         //tool.accept(Data,Data_size);
		         break;
	         case 2:
		         tool.items02(Data,Data_size);
		         break;
	         case 3:
			 tool.users02(Data,Data_size);
			 break;
	         case 4:
			 tool.ratio_02(Data,Data_size);
			 break;
		 case 5:
			 tool.findtime_item02(Data,Data_size);
			 break;
	         case 10:
		         break;

	 }
         if(command == "end") break;


       }



       
}
