

#include <iostream>
#include <cstdlib>
#include <vector>
#include "filler.h"

using namespace std;

void Filler::Guess_filter( vector<vector<char> >Picture, vector<vector<char> >& guess, char ROC, int line)
{
	int space = 0;
	if( ROC == 'C') space = Picture.size();
	else space = Picture[0].size();

	vector<vector<char> > Container;
	Container.resize( space );

	vector<char> tmp_row;
	tmp_row.resize( space );
	
	if(ROC == 'R')
	{
		for(int i = 0;i <space;i++)
		{
			tmp_row[i] = Picture[line][i];
		}
	}
	else if(ROC =='C')
	{
		for(int i = 0;i < space;i++)
		{
			tmp_row[i] = Picture[i][line];
		}
	}

	//cout << "the target "<< ROC<< " "<< line <<" is "<<endl;//debug---------------------------------<
	//for(int i = 0;i < space;i++) cout << tmp_row[i] <<" ";
	//cout<< endl;//----------------------------------------------------------------------------------->

	bool existAns = false;
	bool existButNosol = false;
	int input_Fill = 0;
	vector<int> existline;
	int existNum = 0;
	for(int i = 0;i < space;i++)
	{
		if( tmp_row[i] != '.') 
		{
			existAns == true;
			existline.push_back( i );
			existNum ++;
		}
	}
	if(existNum != space)
	{
	for(int i = 0;i < guess[0].size();i++)
	{
		int filter = 0;
		for(int k = 0;k < existNum; k++)
		{
			if( guess[ existline[k] ][i] == tmp_row[ existline[k] ] ) filter ++;
		}
		if( filter == existNum )
		{
			for(int j = 0;j < space;j++) Container[j].push_back( guess[j][i] );
			input_Fill ++;
			//cout << " Container get input_Fill "<< input_Fill<<endl;//-----------------------------------
		}
	}
	}

	//if(input_Fill == 0 && existAns) cout << "nothing"<<endl;

	//if(input_Fill > 0 && existAns)//change guess if Container have somethine
	//{
		//cout<< "clear guess "<<ROC <<" "<<line <<" and put Container "<<endl;//-------------------
		for(int i = 0;i < space;i++)//clear guess to push Container to it
		{
			guess[i].clear();
		}
		for(int j = 0;j < Container[0].size() ;j++)
		{
			for(int i = 0;i < space;i++)
			{
				guess[i].push_back( Container[i][j]);
			}
			//cout << ROC <<" "<<line <<" been new guess "<<j<<endl;//---------------------
		}
	//}


}

void Filler::filler_1( vector<char>line, vector<int> clue, int space,vector< vector<char> >& Fill_ans ,bool& change)
{
	int input_zone = clue.size();//process input_zone = 1
	int input_num = 0;
	for(int i = 0;i < clue.size() ;i++)
	{
        	input_num += clue[i];
	}
	int X_num = (space - input_num);

        change = true;

	if( X_num == 0)//situation A
	{
		int Fill_col = 0;
		for(int firstA = 0;firstA < space; firstA ++)
		{
			Fill_ans[Fill_col].push_back('#');
			Fill_col ++;
		}
	}
	if( X_num > 0)//X_zone = 1   XA
	{
		int Fill_col = 0;
		for(int firstX = 0;firstX < X_num; firstX ++)
		{
			Fill_ans[Fill_col].push_back('X');
			Fill_col ++;
		}
		for(int firstA = 0;firstA < clue[0] ; firstA ++)
		{
			Fill_ans[Fill_col].push_back('#');
			Fill_col ++;
		}
	}
	if( X_num > 0)//X_zone = 1 AX
	{
		int Fill_col = 0;
		for(int firstA = 0;firstA < clue[0] ;firstA ++)
		{
			Fill_ans[Fill_col].push_back('#');
			Fill_col ++;
		}
		for(int firstX = 0;firstX < X_num; firstX ++)
		{
			Fill_ans[Fill_col].push_back('X');
			Fill_col ++;
		}
	}
	if( X_num > 1 )//X_zone = 2 XAX
	{
		int X_zone = 2;
		for(int oneXnum=1; oneXnum < (X_num-X_zone+2);oneXnum++)
		{
			for(int twoXnum=( X_num- oneXnum); twoXnum< (X_num-X_zone-oneXnum+3) ;twoXnum ++)
			{
				int Fill_col = 0;
				for(int oneX = 0; oneX < oneXnum; oneX ++)
				{
					Fill_ans[Fill_col].push_back('X');
					Fill_col ++;
				}
				for(int oneA = 0;oneA < clue[0];oneA ++)
				{
					Fill_ans[Fill_col].push_back('#');
					Fill_col ++;
				}
				for(int twoX = 0;twoX < twoXnum; twoX ++)
				{
					Fill_ans[Fill_col].push_back('X');
					Fill_col ++;
				}
			}
		}
	} 	
}

void Filler::filler_2( vector<char>line, vector<int> clue, int space,vector< vector<char> >& Fill_ans ,bool& change)
{
        int input_zone = clue.size();//process input_zone = 2
	int input_num = 0;
	for(int i = 0;i < clue.size() ;i++)
	{
        	input_num += clue[i];
	}
	int X_num = (space - input_num);
        change = true;

        if( X_num > 0)//X_zone = 1 AXA
	{
		int Fill_col = 0;
		for(int oneA = 0; oneA < clue[0]; oneA++)
		{
			Fill_ans[Fill_col].push_back('#');
			Fill_col ++;
		}
		for(int oneX = 0;oneX < X_num; oneX ++)
		{
			Fill_ans[Fill_col].push_back('X');
			Fill_col ++;		
		}
		for(int twoA = 0;twoA < clue[1] ;twoA++)
		{

			Fill_ans[Fill_col].push_back('#');
			Fill_col ++;
		}
	}

	if( X_num >1)//X_zone = 2 XAXA
	{
		int X_zone = 2;
		for(int oneXnum=1; oneXnum < (X_num-X_zone+2);oneXnum++)
		{
			for(int twoXnum=( X_num- oneXnum); twoXnum< (X_num-X_zone-oneXnum+3) ;twoXnum ++)
			{
				int Fill_col = 0;
				for(int oneX = 0; oneX < oneXnum; oneX ++)
				{
					Fill_ans[Fill_col].push_back('X');
					Fill_col ++;
				}
				for(int oneA = 0;oneA < clue[0];oneA ++)
				{
					Fill_ans[Fill_col].push_back('#');
					Fill_col ++;
				}
				for(int twoX = 0;twoX < twoXnum; twoX ++)
				{
					Fill_ans[Fill_col].push_back('X');
					Fill_col ++;
				}
				for(int twoA = 0;twoA < clue[1]; twoA++)
				{
					Fill_ans[Fill_col].push_back('#');
					Fill_col ++;
				}
			}
		}
	}

	if( X_num >1)//X_zone = 2 AXAX
	{
		int X_zone = 2;
		for(int oneXnum=1; oneXnum < (X_num-X_zone+2);oneXnum++)
		{
			for(int twoXnum=( X_num- oneXnum); twoXnum< (X_num-X_zone-oneXnum+3) ;twoXnum ++)
			{
				int Fill_col = 0;
				for(int oneA = 0;oneA < clue[0];oneA ++)
				{
					Fill_ans[Fill_col].push_back('#');
					Fill_col ++;
				}
				for(int oneX = 0;oneX < oneXnum; oneX ++)
				{
					Fill_ans[Fill_col].push_back('X');
					Fill_col ++;
				}
				for(int twoA = 0;twoA < clue[1]; twoA++)
				{
					Fill_ans[Fill_col].push_back('#');
					Fill_col ++;
				}
				for(int twoX = 0;twoX < twoXnum; twoX ++)
				{
					Fill_ans[Fill_col].push_back('X');
					Fill_col ++;
				}

			}
		}
	}

	if( X_num > 2)//X_zone = 3 XAXAX
	{
		int X_zone = 3;
		for(int oneXnum = 1; oneXnum < (X_num-X_zone+2); oneXnum++)
		{
			for(int twoXnum = 1;twoXnum < (X_num-X_zone-oneXnum+3) ;twoXnum++)
			{
				for(int threeXnum=(X_num-oneXnum-twoXnum); threeXnum< (X_num-X_zone-oneXnum-twoXnum+4) ;threeXnum++)
				{
					int Fill_col = 0;
					for(int oneX = 0; oneX < oneXnum; oneX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}
					for(int oneA = 0;oneA < clue[0];oneA ++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
					for(int twoX = 0;twoX < twoXnum; twoX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}
					for(int twoA = 0;twoA < clue[1]; twoA++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
					for(int threeX= 0;threeX < threeXnum; threeX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}
				}
			}
		}
	}

}


void Filler::filler_3( vector<char>line, vector<int> clue, int space,vector< vector<char> >& Fill_ans ,bool& change)
{
        int input_zone = clue.size();//process input_zone = 3
	int input_num = 0;
	for(int i = 0;i < clue.size() ;i++)
	{
        	input_num += clue[i];
	}
	int X_num = (space - input_num);

        change = true;
	/*cout<< " r3 just start to fill "<<endl;//--------------------------------
	cout<< "intput_ zone & input_num & X_num"<<endl;
	cout << input_zone<<"  "<<input_num<<"  "<<X_num<<endl;//----------------------*/

        if( X_num > 1)//X_zone = 2 AXAXA
	{
		int X_zone = 2;
		for(int oneXnum=1; oneXnum < (X_num-X_zone+2);oneXnum++)
		{
			for(int twoXnum= (X_num-oneXnum); twoXnum< (X_num-X_zone-oneXnum+3) ;twoXnum ++)
			{				
					int Fill_col = 0;
					for(int oneA = 0;oneA < clue[0];oneA ++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
					for(int oneX = 0;oneX < oneXnum; oneX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}
					for(int twoA = 0;twoA < clue[1]; twoA++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
					for(int twoX = 0;twoX < twoXnum; twoX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}
					for(int threeA = 0;threeA < clue[2];threeA++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
			}
		}
	}

	if( X_num>2)//X-zone = 3  XAXAXA
	{
		int X_zone = 3;
		for(int oneXnum = 1; oneXnum < (X_num-X_zone+2); oneXnum++)
		{
			for(int twoXnum = 1;twoXnum < (X_num-X_zone-oneXnum+3) ;twoXnum++)
			{
				for(int threeXnum=(X_num-oneXnum-twoXnum); threeXnum< (X_num-X_zone-oneXnum-twoXnum+4) ;threeXnum++)
				{
					int Fill_col = 0;
					for(int oneX = 0; oneX < oneXnum; oneX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}
					for(int oneA = 0;oneA < clue[0];oneA ++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
					for(int twoX = 0;twoX < twoXnum; twoX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}
					for(int twoA = 0;twoA < clue[1]; twoA++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
					for(int threeX= 0;threeX < threeXnum; threeX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}
					for(int threeA = 0;threeA < clue[2]; threeA ++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
				}
			}
		}
	}

	if( X_num > 2)//X_zone = 3  AXAXAX
	{
		int X_zone = 3;
		for(int oneXnum=1; oneXnum < (X_num-X_zone+2);oneXnum++)
		{
			for(int twoXnum= 1; twoXnum< (X_num-X_zone-oneXnum+3) ;twoXnum ++)
			{
				for(int threeXnum=(X_num-oneXnum-twoXnum);threeXnum< (X_num-X_zone-oneXnum-twoXnum+4);threeXnum++)
				{
					int Fill_col = 0;
					for(int oneA = 0;oneA < clue[0];oneA ++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
					for(int oneX = 0;oneX < oneXnum; oneX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}
					for(int twoA = 0;twoA < clue[1]; twoA++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
					for(int twoX = 0;twoX < twoXnum; twoX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}
					for(int threeA = 0;threeA < clue[2];threeA++)
					{
						Fill_ans[Fill_col].push_back('#');
						Fill_col ++;
					}
					for(int threeX = 0;threeX < threeXnum; threeX ++)
					{
						Fill_ans[Fill_col].push_back('X');
						Fill_col ++;
					}

				}
			}
		}
	}

	if(X_num > 3)//X_zone = 4   XAXAXAX
	{
		int X_zone = 4;
		for(int oneXnum = 1; oneXnum < (X_num-X_zone+2); oneXnum++)
		{
			for(int twoXnum = 1;twoXnum < (X_num-X_zone-oneXnum+3) ;twoXnum++)
			{
				for(int threeXnum=1; threeXnum< (X_num-X_zone-oneXnum-twoXnum+4) ;threeXnum++)
				{
					for(int fourXnum=(X_num-oneXnum-twoXnum-threeXnum);
							fourXnum< (X_num-X_zone-oneXnum-twoXnum-threeXnum+5);
							fourXnum++)
					{
						int Fill_col = 0;
						for(int oneX = 0; oneX < oneXnum; oneX ++)
						{
							Fill_ans[Fill_col].push_back('X');
							Fill_col ++;
						}
						for(int oneA = 0;oneA < clue[0];oneA ++)
						{
							Fill_ans[Fill_col].push_back('#');
							Fill_col ++;
						}
						for(int twoX = 0;twoX < twoXnum; twoX ++)
						{
							Fill_ans[Fill_col].push_back('X');
							Fill_col ++;
						}
						for(int twoA = 0;twoA < clue[1]; twoA++)
						{
							Fill_ans[Fill_col].push_back('#');
							Fill_col ++;
						}
						for(int threeX= 0;threeX < threeXnum; threeX ++)
						{
							Fill_ans[Fill_col].push_back('X');
							Fill_col ++;
						}
						for(int threeA = 0;threeA < clue[2]; threeA ++)
						{
							Fill_ans[Fill_col].push_back('#');
							Fill_col ++;
						}
						for(int fourX= 0;fourX < fourXnum; fourX ++)
						{
							Fill_ans[Fill_col].push_back('X');
							Fill_col ++;
						}
					}
				}
			}
		}
	}

}

void Filler::Distribute(vector<int>& X, int X_value, vector< vector<int> >& Pos,int countX,int value)
{
	//cout<<" just at door"<<endl;//---------------------------------------------
	for(  X[countX]= 0; X[countX]< (X_value+1 ); X[countX] ++)
	{
		//cout << countX +1 <<" level "<<endl;
		if(countX < (X.size()-1))
		{
			//cout << "num "<<countX+1 <<" level of recursive"<<endl;//------------------
			Distribute(X ,(X_value - X[countX]) ,Pos,( countX + 1), value);
		}
	
		else if( countX == ( X.size()- 1))
		{
			//cout <<"least level of recursive"<<endl;//---------------------
			X[countX] =X_value;
			for( int i = 0; i < X.size() ;i++)
			{
				Pos[i].push_back( X[i] );
			}
		}
	}
}

void Filler::filler_all( vector<char>line, vector<int> clue, int space,vector< vector<char> >& Fill_ans ,bool& change)
{
        int input_zone = clue.size();
	int input_num = 0;
	for(int i = 0;i < clue.size() ;i++)
	{
        	input_num += clue[i];
	}
	int X_num = (space - input_num);

        change = true;

	//cout << "fill XAX"<<endl;//-------------------------------------------------------------------------
	
	if(X_num > (input_zone - 2) && input_zone != 1)//XAX
	{
		int X_zone = (input_zone - 1);// AXA
		int X_value =( X_num - X_zone);//make any X_zone at least 1 X

		vector<int> X;
		X.resize( X_zone );
		vector< vector<int> >Pos;
		Pos.resize( X_zone);
		int countX = 0;

		//cout<<"start recursive"<<endl;//--------------------------------------
		Distribute(X, X_value ,Pos, countX, X_value);
		//cout<<"end recursive"<<endl;//-------------------------------------------------------

		for(int line = 0;line < Pos[0].size() ;line++)
		{
			int Fill_col = 0;
			for(int i = 0;i < X_zone;i++)
			{
				for(int oneA = 0;oneA < clue[i];oneA ++)
				{
					Fill_ans[Fill_col].push_back('#');
					Fill_col ++;
				}
				for(int oneX = 0;oneX < (Pos[i][line]+1); oneX ++)
				{
					Fill_ans[Fill_col].push_back('X');
					Fill_col ++;
				}
			}
			for(int endA = 0;endA < clue[ input_zone- 1];endA ++)
				{
					Fill_ans[Fill_col].push_back('#');
					Fill_col ++;
				}
		}
	}

	
	if( X_num > (input_zone - 1) )
	{ 
		int X_zone = input_zone ;// XAXA and AXAX
		int X_value =( X_num - X_zone);//make any X_zone at least 1 X

		vector<int> X;
		X.resize( X_zone );
		vector< vector<int> >Pos;
		Pos.resize( X_zone);
		int countX = 0;

		Distribute(X, X_value ,Pos, countX, X_value);

		for(int line = 0;line < Pos[0].size() ;line++)
		{
			int Fill_col = 0;
			for(int i = 0;i < X_zone;i++)
			{
				for(int oneX = 0; oneX < (Pos[i][line]+1); oneX ++)
				{
					Fill_ans[Fill_col].push_back('X');
					Fill_col ++;
				}
				for(int oneA = 0;oneA < clue[i];oneA ++)
				{
					Fill_ans[Fill_col].push_back('#');
					Fill_col ++;
				}
			}
		}
		for(int line = 0;line < Pos[0].size() ;line++)
		{
			int Fill_col = 0;
			for(int i = 0;i < X_zone;i++)
			{
				for(int oneA = 0;oneA < clue[i];oneA ++)
				{
					Fill_ans[Fill_col].push_back('#');
					Fill_col ++;
				}
				for(int oneX = 0; oneX < (Pos[i][line]+1); oneX ++)
				{
					Fill_ans[Fill_col].push_back('X');
					Fill_col ++;
				}											
			}
		}
	}

	//cout << "fill_XAXAX "<<endl;
	if( X_num > input_zone )
	{
		int X_zone = (input_zone + 1) ;// XAXAX
		int X_value =( X_num - X_zone);//make any X_zone at least 1 X

		vector<int> X;
		X.resize( X_zone );
		vector< vector<int> >Pos;
		Pos.resize( X_zone);
		int countX = 0;

		Distribute(X, X_value ,Pos, countX, X_value);

		for(int line = 0;line < Pos[0].size() ;line++)
		{
			int Fill_col = 0;
			for(int i = 0;i < (X_zone-1);i++)
			{
				for(int oneX = 0; oneX < (Pos[i][line]+1); oneX ++)
				{
					Fill_ans[Fill_col].push_back('X');
					Fill_col ++;
				}
				for(int oneA = 0;oneA < clue[i];oneA ++)
				{
					Fill_ans[Fill_col].push_back('#');
					Fill_col ++;
				}
			}
			for(int endX = 0; endX < (Pos[ (X_zone-1) ][line]+1); endX ++)
			{
				Fill_ans[Fill_col].push_back('X');
				Fill_col ++;
			}
		}
	}
}





				
	



