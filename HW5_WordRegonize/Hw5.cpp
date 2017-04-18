
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "possibleWord.h"

using namespace std;

int main()
{
	ifstream input("/tmp2/dsa2016_hw5/cmudict-0.7b");//("dictionary.txt");
	vector<string> dic;
	vector<string>::iterator iter;
	map<string, bool> Dic;
	map<string, bool>::iterator wordPos;

	int stop = 0;
	while(1) //read and build the dictionary
	{				
		string temp;
		getline(input, temp, '\n');

		istringstream in(temp);
		string item;

		//cout << temp <<endl;   //can see <temp> get a whole line ex. Apple e po
		if(temp[0] == '\0') break; //if get nothing >> break
		
		int extract = 0;
		while(in >> item && extract==0)//only want first string in the line !!!
		{
			int cap = item.size();
			bool over = false;
			for(int i = 0;i < cap;i++)
			{
				item[i] = tolower(item[i]);
				/*if(item[i] == '(') over = true; //Now we keep (1) in each data have it
				if(over)
				{ 
					item.erase(i,3);//delete (1)
					break;
				}*/
			}

			dic.push_back(item);//put word in dictionary
			Dic[item] = true;
			extract ++;
		}
		
	}
	
	
	dicTool tool;
	while(1) //input the word and judge
	{
		string temp;
		getline(cin, temp, '\n');
		istringstream in(temp);
		string aWord;
		if(temp[0] == '\0') break;
		int extract = 0;
		//string aWord;
		//cin >> aWord;
		while( in >> aWord && extract == 0)
		{
			if(aWord == "done_ok") break;

			bool exist = true;

			wordPos = Dic.find(aWord);//judge the word exist or not
			if( wordPos != Dic.end() ) cout << aWord<<" ==> "<< "OK"<<endl;
			else exist = false;

			//process to find possible
			vector<string> suggestion;
			if(!exist)
			{
				vector<string> Pos;
				if(!exist) tool.possibleWord(aWord,Pos);//DE1
				int stepOneNum = Pos.size(); 

				vector< vector<string> > Pos2;
				Pos2.resize( stepOneNum );
				for(int i =0; i<stepOneNum; i++)
				{
					tool.possibleWord( Pos[i], Pos2[i] );//for a result of DE1, to DE again and put into Pos2
				}

				//vector<string> suggestion;
				map<string, bool> same;
				for(int i = 0;i < stepOneNum; i++)//put the right word in the list of suggestion & delete the double
				{
					for(int j = 0; j < Pos2[i].size(); j++)
					{
						wordPos = Dic.find( Pos2[i][j] );
						if(wordPos != Dic.end() && same.find( Pos2[i][j]) == same.end() )
						{
							suggestion.push_back( Pos2[i][j] );
							same[ Pos2[i][j] ] = true;
						}
					}
				}
				//if(suggestion.size() == 0) cout <<aWord<<" ==> "<< "NONE"<<endl;
				if(suggestion.size() != 0) //output
				{
					for(int i =0;i < suggestion.size();i++) 
					{
						//cout << suggestion[i] << endl;
					}
				}
		

				//sorting to all the possible
				heap strHeap;
				for(int i = 0; i < suggestion.size(); i++)
				{	
					strHeap.addLast( suggestion[i] );
					strHeap.sortLast( strHeap.last() );
				}
		
				vector<string> result;
				for(int i =0;i < suggestion.size();i++) 
				{
					result.push_back( strHeap.V[1] );
					strHeap.swap(1, strHeap.last() );
					strHeap.removeLast();
					strHeap.sortFirst(1);
				}
				cout << aWord <<" ==> ";
				for(int i = 0;i < result.size(); i++)
				{
					cout << result[i] << " ";
				}
				if(suggestion.size() == 0) cout<<"NONE";
				cout <<endl;
			}
			extract ++;
		}

	}
	
}

		

