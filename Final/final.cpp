#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <list>
#include "Edit.h"

using namespace std;

void ranking( list< point >& Rank, string target, int value);

int main()
{
	ifstream input2("/tmp2/dsa2016_project/2gm.small.txt");
	ifstream input3("/tmp2/dsa2016_project/3gm.small.txt");
	ifstream input4("/tmp2/dsa2016_project/4gm.small.txt");
	ifstream input5("/tmp2/dsa2016_project/5gm.small.txt");
	
	map<string, int> LDC;
	int gmCount = 2;
	int coutCount = 0;
	while(1)
	{
		string temp;
		if(gmCount ==2) getline(input2, temp,'\n');
		else if(gmCount ==3) getline(input3, temp,'\n');
		else if(gmCount ==4) getline(input4, temp,'\n');
		else if(gmCount ==5) getline(input5, temp,'\n');
		else break;

		istringstream in(temp);
		string item;

		if(temp[0] == '\0'){ gmCount++; /*cout<<"register a gm"<<endl;*/  continue; }
		if(gmCount == 6) break;
		//-------store procedure--------
		string sentance;
		int count;

		while(in >> item)
		{
			int ASCII = static_cast<int>(item[0]);
			if(ASCII > 47 && ASCII < 58){ stringstream convert(item); convert>> count; }
			else sentance += (item + " ");
		}
		//if(coutCount < 100){ cout <<"string:"<<sentance<<"||value: "<<count<<endl; coutCount++; }
		//if(coutCount == 100) break;

		LDC[sentance]= count;
	}
	
	string PrePo[20]= {"of","to","in","for","with","on","at","by",
		           "from","up","about","than","after","before",
			   "down","between","under","since","without","near"};
	map<string,bool>  prepoMap;
	for(int i=0;i<20; i++) prepoMap[ PrePo[i] ] = true;
	
	//cout <<"register  over"<<endl;

	//---------EDIT Process---------
	while(1)
	{
		EDIT Edit;
		string typeIn;
		map<string,int> Candidate;
		map<string,int> Candidate02;
		map<string,int>::iterator Map;

		getline(cin, typeIn, '\n');
		if(typeIn[0] == '\0') break;
		istringstream in(typeIn);  string item;
		list<string> wordList;  list<string>::iterator it;
		while(in >> item) wordList.push_back( item );
		
		//judge Preposition Exist or not
		bool prepoExist = false;
		for(it = wordList.begin(); it != wordList.end(); it++) if( prepoMap.find(*it) != prepoMap.end() ) prepoExist = true;

		//ED
		if(!prepoExist)
		{
			Edit.EditNonePre( typeIn, Candidate, prepoMap );
			for(Map = Candidate.begin(); Map != Candidate.end(); Map++)
				Edit.EditPre( Map->first, Candidate02, prepoMap, true,Candidate);
		}
		else if(prepoExist) Edit.EditPre( typeIn, Candidate, prepoMap ,false, Candidate);



		//Find Suggestion
		list< point > Rank;  list< point >::iterator R; 
		if(!prepoExist)
		{
			for(Map = Candidate.begin(); Map != Candidate.end(); Map++) 
			{
				if( LDC.find( Map->first) != LDC.end() ) ranking( Rank, Map->first, LDC[Map->first]);
				
			}
			for(Map = Candidate02.begin(); Map != Candidate02.end(); Map++)
			{
				if( LDC.find( Map->first) != LDC.end() ) ranking( Rank, Map->first, LDC[Map->first]);
			}
			if( LDC.find( typeIn+" " ) != LDC.end() )  ranking( Rank, typeIn, LDC[typeIn+" "]);
	        }
		else if(prepoExist)
		{
			for(Map = Candidate.begin(); Map != Candidate.end(); Map++)
			{
				//cout <<"rank	"<<Map->first<<endl;
				if( LDC.find( Map->first) != LDC.end() ) ranking( Rank, Map->first, LDC[Map->first]);
			}
			if( LDC.find( typeIn+" " ) != LDC.end() )  ranking( Rank, typeIn, LDC[typeIn+" "]);
		}
		
		int count = 0;
		cout << "query: "<<typeIn<<endl;
		cout << "output: "<<Rank.size()<<endl;
		for(R = Rank.begin(); R != Rank.end(); R++ )
		{
			cout << (*R).Str<<"	"<<(*R).value<<endl;
			count ++;
			if(count == 10) break;
		}	
	}	
}

void ranking( list< point >& Rank, string target, int value)
{
	list< point >::iterator R;
	//point* temp = new point(target, value);
	point temp(target, value);

	bool insert = false;
	if(Rank.empty()) Rank.push_back( temp );
	else 
	{
		for(R = Rank.begin(); R != Rank.end(); R++)
		{
			if(target == (*R).Str) { insert =true; break; }
			if(value == (*R).value) { insert = true; break;}
			if(value > (*R).value )
			{ Rank.insert(R, temp);  insert=true;   break; }
		}
		if(!insert)  Rank.push_back(temp);
	}

	if(Rank.size() > 10) Rank.pop_back();
}

