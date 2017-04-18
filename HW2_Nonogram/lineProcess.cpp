
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "lineProcess.h"
#include "filler.h"

using namespace std;

vector< vector<char> > Process::Line_process(vector< vector<char> >Picture ,char ROC,int tar_line,vector<int> clue,bool guess,bool& ExistButNosol)
{
	vector<char>::iterator iter;
	int Space = 0;//space
	if( ROC== 'C' )  Space = Picture.size();//length of Col    ROC= 1 >> Col process
	else  Space = Picture[0].size();//length of Row   ROC= 0 >> Row process

        int input_zone = clue.size();//input_zone
	int input_num = 0;           //input_num
	for(int i = 0;i < clue.size();i++)
	{
		input_num += clue[i];
	}
	int X_num = Space - input_num;//X_num
	
	vector< vector<char> >Fill_ans;//Container of possible answer
	Fill_ans.resize( Space );
	bool change = false;
	
        vector<char> tmp_row;//copy target row or col of Picture to tmp_row
	tmp_row.resize( Space );
	if(ROC == 'R')
	{
		for(int i = 0;i < Space; i++)
		{
			tmp_row[i] = Picture[tar_line][i];//copy Row
		}
	}
	else if(ROC == 'C')
	{
		for(int i = 0;i < Space;i++)
		{
			tmp_row[i] = Picture[i][tar_line];//copy Col
		}
	}

        //cout <<"start to use new filler_tool "<<endl;        
	Filler mechine;
	//mechine.filler_all( tmp_row, clue ,Space, Fill_ans, change);
	switch(input_zone)//Doing Line filling to fine all the possible
	{
		case 1:						
        		mechine.filler_1( tmp_row, clue ,Space, Fill_ans, change);
			break;
		/*case 2:
			mechine.filler_2( tmp_row, clue ,Space, Fill_ans, change);
			break;
		case 3:
			mechine.filler_3( tmp_row, clue ,Space, Fill_ans, change);
			break;*/
		default:
			mechine.filler_all( tmp_row, clue ,Space, Fill_ans, change);
			break;
	}

	

	vector< vector<char> >Fill_adv;//if there are ""existed ans"", Fill_ans be changed to Fill_adv
	Fill_adv.resize( Space );
	bool existAns = false;
	bool existButNosol = false;
	int inputFill_adv = 0;//how amny posiible Ans to this exist Ans
	vector<int> existline;//store the line have exist Ans
	int existNum = 0;
	for(int i = 0;i < Space; i++)
	{
		if(tmp_row[i] != '.')//there is existed ans
		{
			existAns = true;
			existline.push_back(i);
			existNum ++;					
		}
	}
	for(int i = 0;i < Fill_ans[0].size(); i++)
	{
		int filter = 0;
		for(int k = 0;k < existNum;k++)//examine whether the possible meet all existAns or not
		{
			if( Fill_ans[ existline[k] ][i] == tmp_row[ existline[k] ]) filter++;
		}
		if( filter == existNum )//if yes, store to Fill_adv
		{
			for(int j = 0;j < Space;j++) Fill_adv[j].push_back( Fill_ans[j][i] );
			inputFill_adv ++;
		}
	}
	if(inputFill_adv == 0 && existAns)
	{
		existButNosol = true;
		//cout << " NO exist Ans ~~~~~~!!!!"<< endl;
	}


	//debug output the Fill_ans and Fill_adv--------------------------------------------------------------
	/*if(!existAns)
	{
		cout << "The Fill_ans for :" << ROC <<"  "<< tar_line << " line"<<endl;
		for(int i = 0;i < Fill_ans[0].size(); i++)
		{
			for(int j =0;j < Space;j++)
			{
				cout << Fill_ans[j][i] << " ";
			}
			cout << endl;
		}
	}
	else if(existAns)
	{
		cout<< "The Fill_adv for :"<< ROC <<"  "<<tar_line<<" line"<<endl;
		for(int i=0;i < Fill_adv[0].size();i++)
		{
			for(int j=0;j < Space;j++)
			{
				cout << Fill_adv[j][i]<< " ";
			}
			cout << endl;
		}
	}*/
						
	
        if(!guess && change && !existAns && !existButNosol)// filting the Ans and fill in Picture
	{
		for(int Fill_col = 0;Fill_col < Space; Fill_col++)
		{
			char Ans = Fill_ans[Fill_col][0] ;
			int same = 0;
			for(iter = Fill_ans[Fill_col].begin(); iter != Fill_ans[Fill_col].end(); iter++)
			{
				if( Ans != *iter ) same++;
			}
			if(same == 0 && ROC=='R') Picture[tar_line][Fill_col] = Ans;//fill the absolute Ans to Picture
			else if(same ==0 && ROC=='C') Picture[Fill_col][tar_line] = Ans;
		}
	}
	else if(!guess && change && existAns && !existButNosol)//if Existed Ans, use Fill_adv
	{
		for(int Fill_col= 0;Fill_col < Space; Fill_col++)
		{
			char Ans = Fill_adv[Fill_col][0];
			int same = 0;
			for(iter = Fill_adv[Fill_col].begin(); iter != Fill_adv[Fill_col].end(); iter++)
			{
				if(Ans != *iter) same++;
			}
			if(same ==0 && ROC=='R') Picture[tar_line][Fill_col] =Ans;
			else if(same ==0 && ROC=='C') Picture[Fill_col][tar_line] =Ans;
		}
	}
	else if(existButNosol) ExistButNosol = existButNosol;
        
	//cout << endl;
	//cout << "The Picture after process  for :" << ROC <<"  "<< tar_line << " line"<<endl;
	/*for(int i = 0;i < Picture.size();i++)//debug output Picture----------------------------------------
	{
		for(int j = 0;j < Picture[0].size() ;j++)
		{
			cout<< Picture[i][j] << " ";
		}
		cout <<endl;
	}*/
			

	return Picture;
}

void Process::Result(vector< vector<char> >Picture, bool& result)
{
	bool over = true;
	for(int i = 0;i < Picture.size(); i++)
	{
		for(int j = 0;j < Picture[0].size(); j++)
		{
			if( Picture[i][j] == '.') over = false;
		}
	}

	result = over;
	//if(result == true)cout << "get the result"<< endl;
}


void Process::Guess( stack< vector<vector<char> > >& guess,vector<vector<char> >Picture,vector<vector<int> >RowClue,vector<vector<int> >ColClue)
{
	Filler mechine;
	vector<char> tmp_row;
	tmp_row.resize( 10);

	int Colsize = Picture.size();
	int Rowsize = Picture[0].size();

	vector< vector<char> >* rowguess = new vector<vector<char> >[Rowsize];
	for(int i = 0;i < Rowsize;i++) rowguess[i].resize( Rowsize );
	vector< vector<char> >* colguess = new vector<vector<char> >[Colsize];
	for(int j = 0;j < Colsize;j++) colguess[j].resize( Colsize );
	bool change = false;
	
	for(int i = 0;i < Rowsize;i++)
	{ 
		mechine.filler_all( tmp_row, RowClue[i] ,Rowsize, rowguess[i], change);
		int input_zone = RowClue[i].size();
		switch(input_zone)//Doing Line filling to fine all the possible
		{
			case 1:	
        			mechine.filler_1( tmp_row, RowClue[i] ,Rowsize, rowguess[i], change);
				break;
			case 2:			
				mechine.filler_2( tmp_row, RowClue[i] ,Rowsize, rowguess[i], change);				
				break;
			case 3:				
				mechine.filler_3( tmp_row, RowClue[i] ,Rowsize, rowguess[i], change);
				break;
			default:
				mechine.filler_all( tmp_row, RowClue[i] ,Rowsize, rowguess[i], change);
				break;
		}
	}
	for(int j = 0;j < Colsize;j++)
	{
		mechine.filler_all( tmp_row, ColClue[j] ,Colsize, colguess[j], change);
		int input_zone = ColClue[j].size();
		switch(input_zone)//Doing Line filling to fine all the possible
		{
			case 1:					
        			mechine.filler_1( tmp_row, ColClue[j] ,Colsize, colguess[j], change);
				break;
			case 2:				
				mechine.filler_2( tmp_row, ColClue[j] ,Colsize, colguess[j], change);
				break;
			case 3:				
				mechine.filler_3( tmp_row, ColClue[j] ,Colsize, colguess[j], change);
				break;
			default:
				mechine.filler_all( tmp_row, ColClue[j] ,Colsize, colguess[j], change);
				break;
		}
	}

	//Filting the guess by exist Ans
	for(int i = 0;i < Rowsize;i++)
	{
		mechine.Guess_filter( Picture , rowguess[i], 'R', i);
	}
	for(int j = 0;j < Colsize;j++)
	{
		mechine.Guess_filter( Picture, colguess[j], 'C', j);
	}
	


	//cout << "over filling the guess" << endl;//-------------------------------------------ˇ	
	/*for(int g = 0;g < rowguess[0][0].size();g++)
	{
		for(int f = 0; f < Rowsize;f++)
		{
			cout << rowguess[0][f][g]<< " ";
		}
		cout<<endl;
	}//------------------------------------------------------------------------------------^*/

	for(int i = 0;i < Rowsize; i++)
	{
		for(int j = 0; j < rowguess[i][0].size();j++)
		{
			//cout<< "Unit process title---------------------------------------------"<<endl;
			vector< vector<char> >tmp_Pic;
			tmp_Pic.resize(Colsize);
			for(int h = 0;h < Colsize;h++) tmp_Pic[h].resize(Rowsize);
			tmp_Pic = Picture;
			/*for(int a = 0;a < Colsize;a++)//--------------------------------------
			{
				for(int b = 0;b < Rowsize;b++)
				{
					cout << tmp_Pic[a][b] << " ";
				}
				cout<< endl;
			}
			//cout << "rowguess[i][0].size = "<< rowguess[i][0].size()<<endl;
			//cout << " deal with "<<i <<" row, "<<" num "<<j <<" guess ~"<<endl;//------------------*/
						
			for(int k = 0;k < Rowsize;k++)
			{
				tmp_Pic[i][k] = rowguess[i][k][j];
			}
			guess.push( tmp_Pic );

			/*cout << endl;
			for(int a = 0;a < Colsize;a++)//--------------------------------------
			{
				for(int b = 0;b < Rowsize;b++)
				{
					cout << guess.top()[a][b] << " ";
				}
				cout<< endl;
			}//--------------------------------------------------------------------*/
		}
	}
	for(int i = 0;i < Colsize; i++)
	{
		for(int j = 0;j < colguess[0][0].size();j++)
		{
			vector< vector<char> >tmp_Pic;
			tmp_Pic.resize(Colsize);
			for(int h = 0;h < Colsize;h++) tmp_Pic[h].resize(Rowsize);
			tmp_Pic = Picture;
			//cout<< "start to fill in c guess"<<endl;//--------------------------------
			
			for(int k = 0;k < Rowsize;k++)
			{
				tmp_Pic[k][i] = colguess[i][k][j];
			}
			guess.push( tmp_Pic );
		}
	}
}

	

		





