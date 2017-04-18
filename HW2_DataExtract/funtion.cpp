
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <map>
#include "funtion.h"
#include <vector>

using namespace std;

void function::accept(int** Data,int Data_size)
{
	int user,item,result,time;
	cin >> user >> item >> time;
	
        int limit = 100;
	int* target = new int[limit ];
	int index = 0; 
	for(int i = 0;i < Data_size;i++)
	{
		if(Data[i][0] == user && Data[i][1] == item && Data[i][3] == time)
		{
			target[index] = i;
			index++;
		}
		if(index == limit) break;
	}

	for(int j = 0; j < index;j++)
	{
		cout << Data[ target[index] ][2] << "    ";
	}
	cout << "\n" << "over" << endl;
}

void function::items(int** Data,int Data_size)
{
	int user01,user02;
	cin >> user01 >> user02;                                                                                               

        int* target = new int[1000];//a row to register item
	int index = 0;//position the target
	int count = 0;//count items
	int* check01 = new int[1000];
	int* check02 = new int[1000];
	
	for(int i = 0;i < Data_size;i++)//See all the data
	{
		if(Data[i][0] == user01 )//find items for the spcefied user
		{
		      int  same = 0;
		      int Num = -1;
		      for(int k = 0;k < index; k++)//see the item have registered,if the item is rgistered,then skip it
		      {
			      if(Data[i][1] == Data[target[k]][1])
			      {
				      same = 1;
                                      Num = k;
			      }
		      }
		      if(same == 0) 
		      {
			      target[index] = i;//register Item 
			      check01[index] = 1;
			      check02[index] = 0;
			      index ++;
			      //count ++;
		      }
		      if(same == 1)
		      {
			      check01[Num] = 1;
		      }
		    
		}
		if(Data[i][0] == user02)
		{
			int same = 0;
			int Num = -1;
			for(int k = 0;k < index; k++)
			{
				if(Data[i][1] == Data[ target[k] ][1])
				{
					same = 1;
					Num = k;
				}
			}
			if(same == 0)
			{
				target[index] = i;
				check01[index] = 0;
				check02[index] = 1;
				index ++;
			}
			if(same == 1)
			{
				check02[Num] = 1;
			}
		}
		//cout << "index: " << index << "  "<<  i <<endl;

		if(index == 1000)//if there are too many items,drop
		{
			cout << "items are toomany !!!" << endl;
			break;
		}
	}

	/*cout << "item & check01 & check02" << endl;
	for(int i = 0;i < index; i++)
	{
		cout << Data[ target[i] ][1] << " " << check01[i] <<" " << check02[i] <<endl;
	}*/
        
        int* trueitem = new int[1000];
	int trueindex = 0;
	for(int i = 0;i < index; i++)
	{
		if(check01[i] == 1 && check02[i] == 1)
		{
                      trueitem[trueindex] = Data[ target[i] ][1];
		      trueindex ++;
		}
	}

        //sort
	int* items = new int[1000];
	for(int i = 0;i < trueindex ;i++) items[i] = trueitem[i];
	for(int u = 0;u < (trueindex-1); u++)
	{
		for(int v = (u+1);v < (trueindex);v++)
		{
			if(items[u] > items[v])
			{
				int c = items[u];
				items[u] = items[v];
				items[v] = c;
			}
		}
	}
	for(int k = 0;k < (trueindex);k++)
	{
		cout << items[k] << endl;
	}

       /* for(int j = index;j > (0);j--)//print out
	{
		cout << Data[ target[j] ][1] << "\n";
	}

	for(int j = index;j > (0);j--)
	{
		cout << target[j] << " target row " << endl;
	}*/

        /*cout << "index & target(item)" <<endl;
	for(int i = 0; i < (trueindex);i++)
	{
		cout << i << "  " << trueitem[i] << endl;
	}*/
	//cout << "There are " << count << " items" << endl;

}


void function::users(int** Data,int Data_size)
{
	int item01,item02,time01,time02;
	cin >> item01 >> item02 >> time01 >> time02;

	int* pretarget = new int[50000];
	int preindex = 0;
	int* check01 = new int[50000];
	int* check02 = new int[50000];
	int* target = new int[50000];
	int index = 0;

	for(int i = 0;i <Data_size;i++)
	{
		if(Data[i][3] > time01 && Data[i][3] < time02)//extract by time
		{
			
		        if(Data[i][1] == item01)//find the user be asked the item01
		        {
				int same = 0;
				int Num = -1;
				for(int j = 0;j < preindex;j++)//exclude users that have registered
				{
                                         if(Data[i][0] == Data[pretarget[j] ][0]) 
					 {
						 same = 1;
                                                 Num = j;//the preindex of registered item
					 }
				}
				if(same == 0 && Num == -1)//register a user
				{
			                 pretarget[preindex] = i;//the userindex
			                 check01[preindex] = 1;//user was asked by item01			
		                         preindex ++;
				}
				if(same == 1)//registered user, check item01
				{
					check01[Num] = 1;
				}
		        }

			else  if(Data[i][1] == item02)//find the user be asked th item02
			{
				int same = 0;
				int Num = -1;
				for(int j = 0;j < preindex;j++)
				{
					if(Data[i][0] == Data[ pretarget[j] ][0])
					{
						same = 1;
						Num = j;
					}
				}
				if(same == 0 && Num == -1)
				{
					pretarget[preindex] = i;
					check02[preindex] = 1;
					preindex ++;
				}
				if(same == 1)
				{
					check02[Num] = 1;
				}
			}

			if(preindex == 50000)
			{
				cout << "too many users !"<<endl;
				break;
			}
			
		}//end of extrac of time
	}


	        //cout << "there are " << preindex << " pre-users " << endl;
		for(int i = 0;i< preindex;i++) //add the double-checked user's row  to target
		{
			if(check01[i] == 1 && check02[i] == 1)
			{
				target[index] = pretarget[i];
				index++;	
			}
		}

		//sort
		int* finaluser = new int[index];
		for(int i = 0;i < index;i++) finaluser[i] = Data[ target[i] ][0];
		for(int i = 0;i < (index-1); i++)
		{
			for(int j = (i+1);j <index ;j++)
			{
				if(finaluser[i] > finaluser[j])
				{ 
					int tmp;
					tmp = finaluser[i];
					finaluser[i] = finaluser[j];
					finaluser[j] = tmp;
				}
			}
		}

		for(int i = 0;i < index;i++)//output the users
		{
			cout << finaluser[i]  << endl;
		}
		//if(index == 0) cout << "No user !" << endl;

	
}


void function::ratio(int** Data,int Data_size)
{
	int item,threshold;
	cin >> item >> threshold;

	int limit = 1000;//limit of array and index
        int preindex = 0;//store users be recommmanded the CM
	int* user = new int[limit];
	int* time = new int[limit];
	int* accept = new int[limit];
	int index = 0;//store users accept the CM
	int* target = new int[limit];
	int Numaccept = 0;

        for(int i = 0;i < Data_size;i++)//scan DAta & build recording structure
	{
		int same = 0;
		int Pos = -1;
		for(int j = 0;j < preindex;j++)//judge user recorded or not
		{ 
			if(Data[i][0] == Data[ user[j]][0] )//if yes,remember it's origin position
			{
				same = 1;
				Pos = j;
			}
		}
		if(Data[i][1] == item && same == 0)//new user
		{
                        user[preindex] = i;//record PosRow in user
			time[preindex] = 1;//set recommand time
			if(Data[i][2] == -1) accept[preindex] = 0;
			else if(Data[i][2] == 1) accept[preindex] = 1;
			preindex++;//go to next index
		}
		else if(Data[i][1] == item && same ==  1)//old user
		{

                        time[Pos] ++;//add recommand time
			if(Data[i][2] == -1) ;
			else if(Data[i][2] == 1 &&  accept[Pos] > 0 ) accept[Pos] = 1;
		}
		//default function
		if(preindex == limit)
		{ 
			cout << "too many users be recommanded!" << endl;
			break;
		}
	}//end of scaning all data and build the structure

	for(int i = 0;i < preindex;i++)
	{
                 if(time[i] > threshold || time[i] == threshold)
		 {
			 target[index] = user[i];
			 index++;
			 if(accept[i] > 0) Numaccept++;
		 }
		/* if(accept[i] > 0)
		 {
			 Numaccept ++;
		 }*/
	}

	cout << Numaccept << " / " << (index -1) << endl;
}


void function::findtime_item(int** Data,int Data_size)
{
        int item;
	int userNum = 1000;
	int tmp;
	int tmpindex =0;
	int* user = new int[userNum];
        cin >> item;
	while( scanf("%d", &tmp) == 1 && tmpindex != 1000)
	{
		user[tmpindex] = tmp;
		tmpindex ++;
	}              

        int limit = 1000;
	int* target = new int[limit];
	int index = 0;

	for(int i = 0;i < Data_size;i++)//scan all Data
	{
		if(Data[i][1] == item)//the user recommand the item
		{
		  //	if(Data[i][0] == user[0] || Data[i][0] == user[1] || Data[i][0] == user[2])//the user is in the list
		   for(int h = 0;h < tmpindex; h++)
		   {
		        if( Data[i][0] == user[h] )
			{
				int same = 0;
				for(int j = 0;j < index;j++)//exclude time that have been registered
				{
					if(Data[i][3] == Data[ target[j] ][3]) same = 1;
				}
				if(same == 0)//register time
				{
					target[index] = i;
					index++;
				}
				if(index == limit)//default function
				{
					cout << "There are too many timeset ! " <<endl;
					break;
				}
				break;
			}
		   }
		}
	}//end of scaning all Data
	/*for(int i = 0;i < index;i++)
	{
		cout << Data[ target[i] ][3] << endl;//output extracted time
	}*/
        
	//sort
	int* value = new int[index];
	for(int i = 0;i < index;i++) value[i] = Data[ target[i] ][3];
	for(int i = 0;i < (index-1);i++)
	{
		for(int j = (i+1);j < index;j++)
		{
			if(value[i] > value[j])
			{
				int tmp;
				tmp = value[i];
				value[i] = value[j];
				value[j] = tmp;
			}
		}
	}

	for(int i =0;i< index;i++)//output the time
	{
		cout << value[i] << endl;
	}
}


void function::ratio_02(int** Data,int Data_size)
{
	int item,threshold;
	cin >> item >> threshold;

	map<int,int> mapUser;
	map<int,int> mapAccept;
	map<int,int>::iterator iter;

	for(int i = 0;i < Data_size;i++)//scan all Data
	{
	  if( Data[i][1] == item)//find who be recommended
	  {
		int same = 0 ;
		if( mapUser.find(Data[i][0]) != mapUser.end() ) same = 1;
                if(same == 0)
		{
			mapUser[ Data[i][0] ] = 1;
			if( Data[i][2] == 1) mapAccept[ Data[i][0] ] =1;
			else mapAccept[ Data[i][0] ] = 0;
		}
		if(same == 1)
		{
			mapUser[ Data[i][0] ] ++;
			if( Data[i][2] == 1) mapAccept[ Data[i][0] ] = 1;
		}
	  }
	}
	//cout << "total recommended people: " << mapUser.size() <<endl;

	for(iter = mapUser.begin(); iter != mapUser.end(); iter++)
	{
		//cout << iter->first << " his recommend time is " << iter->second  << endl;
		if( (*iter).second < threshold)
		{
                        mapAccept.erase( iter->first );
			mapUser.erase(iter);
		}
	}
	//cout << "rest people: " << mapUser.size() << endl;
	for(iter = mapAccept.begin(); iter != mapAccept.end(); iter++)
	{
		if( (*iter).second != 1) mapAccept.erase(iter);
        }

        cout << mapAccept.size() << " / " << mapUser.size() << endl;
}


void function::findtime_item02(int** Data,int Data_size)
{
       int item;
       vector<int> users;
       vector<int> usersRow;
       int tmp;
       map<int , int> time;
       map<int , int>::iterator iter;

       cin >> item ;
       while( scanf("%d", &tmp) == 1 )//input target-users
       {
	      users.push_back(tmp);
       }


       for(int i = 0;i < Data_size; i++)//Find Users be recommended
       {
	   for(int j = 0; j < users.size() ; j++)
	   {
		if( Data[i][0] == users[j]) 
		{
				usersRow.push_back(i);
			}
		}
		//if( Data[i][1] == item ) time[ Data[i][3] ] = Data[i][0];//Map : time >> user
	   }
	//debug output
	/*for(iter = time.begin() ; iter != time.end() ; iter++)
	{
		cout << iter->first << "  " << iter->second << endl;
	}*/
	for(int i = 0; i < usersRow.size() ; i++)
	{
		if( Data[ usersRow[i] ][1] == item) time[ Data[usersRow[i]][3] ] = Data[ usersRow[i] ][0] ;
	}
        
	/*for(iter = time.begin() ; iter != time.end() ; iter++)
	{
		
		int recommend = 0;//the Map[time] >> user is in state not be recommended
		for(int i = 0; i < users.size() ; i++)
		{
			if( iter->second == users[i] ) recommend = 1;
		}
		if(recommend != 1) time.erase(iter);//erase un-recommend users's time in Map
	}*/

	for(iter = time.begin() ; iter != time.end() ; iter++)//output the time
	{
		cout << iter->first << endl;
	}
}


void function::users02(int** Data,int Data_size)
{

	int item01,item02,time01,time02;
	cin >> item01 >> item02 >> time01 >> time02;

	map<int , int>item_1;
	map<int , int>item_2;
	map<int , int>::iterator iter1;
	map<int , int>::iterator iter2;
	map<int , int>users;

	for(int i = 0; i < Data_size;i++)
	{
		if( Data[i][3] > time01 && Data[i][3] < time02)
		{
			if( Data[i][1] == item01) item_1[ Data[i][0] ] = 1;
			else if( Data[i][1] == item02) item_2[ Data[i][0] ] = 1;
		}
	}

	for(iter1 = item_1.begin() ; iter1 != item_1.end() ;iter1++)
	{
		iter2 = item_2.find( iter1->first );
		if( iter1->second == 1 && iter2->second == 1) users[ iter1->first ] = 1;
	}

	for(iter1 = users.begin() ; iter1 != users.end() ; iter1++)
	{
		cout << iter1->first << endl;
	}
}

void function::items02(int** Data,int Data_size)
{
	int user01,user02;
	cin >> user01 >> user02;

	map<int , int> item1;
	map<int , int> item2;
	map<int , int>::iterator iter1;
	map<int , int>::iterator iter2;
	map<int , int> items;

	for(int i = 0;i <Data_size; i++)
	{
		if( Data[i][0] == user01) item1[ Data[i][1] ] = 1;
		else if(Data[i][0] == user02) item2[ Data[i][1] ] = 1;
	}

	for(iter1 = item1.begin() ; iter1 != item1.end() ; iter1++)
	{
		iter2 = item2.find( iter1->first );
		if( iter1->second == 1 && iter2->second == 1) items[ iter1->first ] = 1;
	}

	for(iter1 = items.begin() ; iter1 != items.end() ; iter1 ++)
	{
		cout << iter1->first << endl;
	}
}
		
				



	


		       
		    

 
                






