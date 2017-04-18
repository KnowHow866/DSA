#include <iostream>
#include <cstdlib>
#include <vector>
#include "possibleWord.h"

using namespace std;

void dicTool::possibleWord(string word, vector<string>& Pos)
{

	vector<char> letter;//store A to Z
	letter.resize(26);
	int size = 0;
	for(int i =97;size < 26;size++, i++)
	{
		letter[size] = static_cast<char>(i);
	}

	//INSERTION	
	vector<string> Pos1;//to store result of insertion
	int space =  word.length()+ 1;
		
	for(int numSpace = 0 ;numSpace < space; numSpace++)//choose the position to insert
	{
		for(int ABC = 0;ABC < 26; ABC++)//insert A to Z
		{
			string temp;
			
			for(int preSpace = 0; preSpace < numSpace; preSpace++) temp += word[preSpace];
			temp += letter[ABC]; 
			for(int postSpace = numSpace; postSpace < word.length() ;postSpace++) temp+= word[postSpace];
			
			Pos1.push_back(temp);
		}
	}
	
	//cout<< Pos1.size() <<" "<<Pos1.capacity()<<endl; //debug function//
	for(int i = 0; i <Pos1.size(); i++)
	{
		Pos.push_back( Pos1[i] );
	}
	
	//DELETION
	for(int deletePos = 0; deletePos < word.length(); deletePos++)
	{
		string temp;
		for(int record = 0; record < word.length(); record++ )
		{
			if(record != deletePos) temp += word[record];
		}
		Pos.push_back(temp);
	}

	//SUBSTITUTION
	for(int subPos = 0; subPos < word.length(); subPos++)
	{
		string* temp = new string[26];
		for(int record = 0;record < word.length(); record++)
		{
			if(record != subPos) for(int i = 0;i < 26;i++) temp[i] += word[record];
			if(record == subPos)
			{
				for(int ABC = 0;ABC < 26;ABC++)
				{
					temp[ABC] += letter[ABC];
				}
			}
		}

		for(int i = 0;i < 26;i++) Pos.push_back( temp[i] ); 
		delete[] temp;
	}

	//TRANSPOSE
	for(int i = 0;i < (word.length() -1); i++)
	{
		for(int j = i+1; j < word.length(); j++)
		{
			string temp;
			for(int record = 0; record < word.length(); record++)
			{
				if( record != i && record != j) temp += word[record];
				if(record == i) temp += word[j];
				if(record == j) temp += word[i];
			}

			Pos.push_back( temp );
		}		
	}
}

bool dicTool::prior(string word1,string word2)//judge if word1 has greater priorty than word2
{
	int compareTime = 0;
	if(word1.length() < word2.length() ) compareTime = word1.length(); //compareTime = minLength( word1,word2 )
	else compareTime = word2.length();

	for(int i = 0;i <compareTime; i++)
	{
		if( word1.at(i) < word2.at(i) ) return true;
		else if( word2.at(i) < word1.at(i) ) return false;
		else if( word1.at(i) == word2.at(i) ) continue;		
	}

	if( word1.length() < word2.length() ) return true;
	else if( word2.length() < word1.length() ) return false;
}

bool heap::prior(string word1,string word2)
{
	int compareTime = 0;
	if(word1.length() < word2.length() ) compareTime = word1.length(); //compareTime = minLength( word1,word2 )
	else compareTime = word2.length();

	for(int i = 0;i <compareTime; i++)
	{
		if( word1.at(i) < word2.at(i) ) return true;
		else if( word2.at(i) < word1.at(i) ) return false;
		else if( word1.at(i) == word2.at(i) ) continue;		
	}

	if( word1.length() < word2.length() ) return true;
	else if( word2.length() < word1.length() ) return false;
}
