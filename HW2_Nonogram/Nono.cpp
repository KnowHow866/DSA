
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <stack>
#include <fstream>
#include <sstream>
#include "lineProcess.h"

using namespace std;

//include C++ source file LineProcess.h filler.h

int main()
{
	bool result = false;//does we get the answer Picture
	bool ExistButNosol = false;
	int Col,Row;
	cin >> Row >> Col;//input Row and Col number
	vector< vector<char> > Picture;//storing Picture
	Picture.resize(Row);
	for(int i = 0;i< Row;i++) Picture[i].resize( Col);

        for( int i= 0;i < Row;i++)
	{
		for(int j = 0;j < Col; j++)
		{
			Picture[i][j] = '.';
			//cout << Picture[i][j] << " ";
		}
		//cout << endl;
	}
	//cout<<endl;
        
	string defaulter;
	getline(cin , defaulter);

	vector< vector<int> > Clue;
	Clue.resize( Row );
	for(int m = 0;m < Row; m++)//store Row-Clue
	{
		string line;
	        getline(cin , line);
	
	        istringstream in(line);
	        int item;
		
	        while( in >> item)
                {
                        Clue[m].push_back(item);
	        }			
	}

	vector< vector<int> > ColClue;//store Col-Clue
	ColClue.resize( Col );
	for(int l = 0;l < Col;l++)
	{
		string line;
		getline(cin , line);

		istringstream in(line);
		int item;

		while( in >> item )
		{
			ColClue[l].push_back(item);
		}
	}

	Process Pro;
	for(int time = 0;time < 10;time ++)//Do line_process for N circles
	{
		for(int row= 0;row < Row; row++)
		{
			Picture = Pro.Line_process( Picture, 'R', row, Clue[row], 0,ExistButNosol);
			Pro.Result( Picture, result);
		}
		for(int col= 0;col < Col; col++)
		{
			Picture = Pro.Line_process( Picture, 'C', col, ColClue[col], 0,ExistButNosol);
			Pro.Result( Picture, result);
		}

		if(result == true) break;
	}

	stack< vector<vector<char> > > Process;
	stack< vector<vector<char> > >guess;
	Process.push(Picture);
	int count = 0;
	while(result == false)//start DFS looping
	{
		
		for(int time = 0;time < 4;time ++)//Do line_process for N circles
		{	
			for(int row= 0;row < Row; row++)
			{
				Process.top() = Pro.Line_process( Process.top(), 'R', row, Clue[row], 0, ExistButNosol);
				Pro.Result( Process.top(), result);
				if( ExistButNosol) break;
			}
			for(int col= 0;col < Col; col++)
			{
				if( ExistButNosol) break;
				Process.top() = Pro.Line_process( Process.top(), 'C', col, ColClue[col], 0, ExistButNosol);
				Pro.Result( Process.top(), result);
				if( ExistButNosol) break;

			}

			if(result)
			{
				Picture = Process.top();
				break;
			}
			if( ExistButNosol && Process.size() > 0)//if impossible, pop and lineprocess another 
			{
				Process.pop();
				ExistButNosol = false;
				//cout << "stack pop"<<endl;//------------------
				//cout << "there are "<< Process.size() <<" element in stack"<<endl;
				time = 0;
				continue;
			}
		}


		if(!ExistButNosol)
		{
			Pro.Guess( guess, Process.top() , Clue, ColClue);
			Process.pop();
			//cout << "Do a guess---------------------------------------------------"<< endl;
			while( guess.size() > 0)
			{
				Process.push( guess.top() );
				guess.pop();
			}
			//cout << "there are "<<Process.size() <<" guess"<<endl;
		}
		ExistButNosol = false;
		count ++;
		
	}

	if(1)//result == true)
	{
		for(int i = 0;i < Row;i ++)
		{
			for(int j = 0; j< Col;j++)
			{
				if(Picture[i][j] =='X') Picture[i][j] = '.';
			}
		}
	}





	for(int i = 0;i < Row;i++)//output Picture
	{
		for(int j = 0;j < Col; j++)
		{
			cout << Picture[i][j] ;
		}
		cout << endl;
	}
	


	
}





















































		
	

















