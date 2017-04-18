#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
#include <list>
#include "Edit.h"
using namespace std;

void EDIT::EditNonePre(string typeIn, map<string, int>& Candidate, map<string,bool> prepoMap)
{
	map<string, bool>::iterator pre;

	string item;
	stringstream in(typeIn);
	list<string> wordList;  list<string>::iterator it;
	while(in >> item) wordList.push_back(item);  
	int InsertNum = wordList.size();

	int processNum = 0;
	while(1)
	{
		if(processNum == InsertNum+1) break;
		for(pre = prepoMap.begin(); pre != prepoMap.end(); pre++)
		{
			list<string> tempList = wordList;
			it = tempList.begin(); for(int i = 0;i< processNum;i++) it++; 
			tempList.insert( it, pre->first ); //Insert Preposition
			
			string editStr;
			for(it = tempList.begin(); it != tempList.end(); it++) editStr += (*it + " ");

			Candidate[editStr] = 1;
			//cout << editStr<<endl;
		}
	
		processNum ++;
	}

}

void EDIT::EditPre(string typeIn, map<string,int>& Candidate, map<string,bool> prepoMap, bool ED2, map<string,int> Compare)
{
	map<string,bool>::iterator pre;
	//debug infro
	int ED1count = 0;

	vector<bool> buildList;
	vector<string> theStr;
	vector<string > Varity;  int VarityIdx = 0;
	vector<string> verb; int verbIdx = 0;

	string item;  stringstream in(typeIn);
	while(in >> item) theStr.push_back(item);//use theStr to bulid buildList & Varity_set , verb_set

	bool status = false; 
	string tempStr;
	for(int i = 0;i < theStr.size(); i++)
	{
		if(i == 0)
		{
			if( prepoMap.find(theStr[i])==prepoMap.end() ) { status=false;  buildList.push_back(false);  }
			else { status=true;  buildList.push_back(true); }
			tempStr += (theStr[i]+" ");
			continue;
		}
		

		bool pre; 
		if(prepoMap.find(theStr[i]) == prepoMap.end()) pre = false;
		else pre = true;

		if(pre)
		{
			if(status == pre) tempStr += (theStr[i]+" ");
			else if(status != pre)
			{
				status = true;  buildList.push_back(true);
				verb.push_back(tempStr);  verbIdx++;
				tempStr = "";
				tempStr += (theStr[i] +" ");
			}
		}
		else if(!pre)
		{
			if(status == pre) tempStr +=(theStr[i]+" ");
			else if(status != pre)
			{
				status = false; buildList.push_back(false);
				Varity.push_back(tempStr); VarityIdx++;
				tempStr = "";
				tempStr += (theStr[i]+" ");
			}
		}

		if(i == (theStr.size()-1) )
		{
			if(status){ Varity.push_back(tempStr); VarityIdx++; }
			else if(!status){ verb.push_back(tempStr); verbIdx++; }
		}
	}

	vector< vector<string> > prepoSet;
	prepoSet.resize(Varity.size() );
	//cout<<"Build List:~~~~~~~~ "<<endl;  for(int i = 0;i< buildList.size(); i++) cout<<buildList[i]<<" "; cout<<endl;
	//cout<<"Verb set:~~~~~~ "<<endl;      for(int i = 0;i < verb.size();i++) cout<<"set "<<i<<"	"<<verb[i]<<endl;
	//cout<<"Varity set:~~~~~ "<<endl;     for(int i = 0;i < Varity.size(); i++) cout<<"set "<<i<<"	"<<Varity[i]<<endl;


	vector< map<string,int> > possibleSet;  possibleSet.resize( Varity.size() );
	vector< list<string> > wordList;  wordList.resize( Varity.size() ); 
	list<string>::iterator it,it2;
	for(int i = 0;i < Varity.size(); i++) 
	{
		stringstream in(Varity[i]);
		string item;
		while(in >> item) wordList[i].push_back(item);
	}

	int setProcess = 0;
	while(1)
	{
		if(setProcess == Varity.size() ) break;

		//INSERTION
		int insertNum = 0;
		while(1)
		{
			if(insertNum == (wordList[setProcess].size()+1) ) break;
			for(pre = prepoMap.begin(); pre != prepoMap.end(); pre++)
			{
				list<string> tempList = wordList[setProcess]; 
				it = tempList.begin(); for(int i = 0;i < insertNum;i++) it++;
				tempList.insert(it , pre->first);

				string tempStr;
				for(it = tempList.begin(); it != tempList.end(); it++) tempStr += (*it+" ");

				if(!ED2) prepoSet[setProcess].push_back(tempStr);  
				else if(ED2) if(Compare.find(tempStr) == Compare.end() ) prepoSet[setProcess].push_back(tempStr);
				//cout << tempStr<<endl;
			}
			insertNum ++;
		}
		
		//DELETION
		int targetPos = 0;
		while(1)
		{
			if(targetPos == wordList[setProcess].size() ) break;

			list<string> tempList = wordList[setProcess];
			it = tempList.begin(); for(int i = 0;i < targetPos; i++) it++;
			tempList.erase(it);

			string tempStr;
			for(it = tempList.begin(); it != tempList.end(); it++) tempStr += (*it+" ");

			if(!ED2) prepoSet[setProcess].push_back(tempStr);  
			else if(ED2) if(Compare.find(tempStr) == Compare.end() ) prepoSet[setProcess].push_back(tempStr);
			//cout << tempStr<<"~"<<endl;

			targetPos++;
		}

		//SUBSTITUTION
		if(1)
		{	
			for(int i = 0;i < wordList[setProcess].size(); i++)
			{
				for(pre = prepoMap.begin(); pre != prepoMap.end(); pre++)
				{
					list<string> tempList = wordList[setProcess];
					it = tempList.begin(); for(int k = 0; k < i;k++) it++;

					*it = pre->first;

					string tempStr;
					for(it = tempList.begin(); it != tempList.end(); it++) tempStr += (*it+" ");

					if(!ED2) prepoSet[setProcess].push_back(tempStr);
					else if(ED2) if(Compare.find(tempStr) == Compare.end() ) prepoSet[setProcess].push_back(tempStr);
				}
			}
		}

		setProcess++;
	}
	vector<string> tempPre;  tempPre.resize( Varity.size() );

	reBuild(buildList, verb, prepoSet, Candidate, 0, tempPre , ED1count);
}

void EDIT::reBuild(vector<bool> buildList, vector<string> verb,vector< vector<string> >prepoSet, 
		map<string,int>& Candidate, int index, vector<string>& tempPre, int& EDcount)
{
	if(index != prepoSet.size() )
	{
		for(int i = 0; i< prepoSet[index].size(); i++)
		{
			tempPre[index] = prepoSet[index][i];
			reBuild(buildList, verb, prepoSet, Candidate, (index+1), tempPre, EDcount);
		}
	}
	else// if(index == prepoSet.size() )
	{
		string tempStr;
		int verbNum = 0;
		int preNum = 0;
		for(int b = 0;b < buildList.size(); b++)
		{
			if(!buildList[b]) 
			{
				tempStr += verb[verbNum];
				verbNum++;
			}
			else if(buildList[b])
			{
				tempStr += tempPre[preNum];
				preNum++;
			}
		}

		if(Candidate.find(tempStr)==Candidate.end() ) Candidate[tempStr] = 1;   
		EDcount++;
		//cout << tempStr<<endl;
	}
}

/*void ranking( list< point >& Rank, string Str, int value)
{
	list< point >::iterator R;
	point temp(Str, value);

	bool insert = false;
	if(Rank.empty() ) Rank.push_back(temp);
	else 
	{
		for(R = Rank.begin(); R != Rank.end(); R++)
		{
			if(value >= (*R).value )
			{ Rank.insert(R, temp);  insert = true;  break;}
			if(!insert) Rank.push_back(temp);
		}
	}

	if(Rank.size() > 10 ) Rank.pop_back();
}*/



