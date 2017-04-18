#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <cmath>
#include <functional>
#include <algorithm>
#include <stack>
#include "DP.h"

using namespace std;

int main()
{
	int pitchNum, noteNum;
	DP tool;

	cin>> pitchNum;
	vector<double> pitch;
	pitch.resize(pitchNum);
	for(int i = 0;i < pitch.size();i++) cin >> pitch[i]; 

	cin>> noteNum;
	vector<double> note;
	note.resize(noteNum);
	for(int i = 0;i < note.size();i++) cin >> note[i]; 
	//-------------------------------------------------------basic input
		
	/*double Amp =2;//find targetNote
	int targetNote;
	for(int h =noteNum-1;h >0;h--)
	{
		if( abs(pitch[pitchNum-1] - note[h]) < Amp)
		{
			targetNote = note[h];
			Amp = abs(pitch[pitchNum-1] - note[h]);
		}
	}
	cout<<"targetNote: "<<targetNote<<endl;
	
	vector<int> targetHight; targetHight.resize(3);//find 3 targetNote hight
	int putIn=0;
	for(int i= noteNum-1;i >0 && putIn <3;i--)
	{
		if(note[i] == targetNote)
		{
			cout <<"input hight "<<i<<endl;
			targetHight[putIn] = i;
			putIn++;
		}
	}
	cout<<"targetHight: "; 
	for(int i =0;i< putIn;i++) cout <<targetHight[i]<<" ";*/

	int testTime = 5;
	vector<double> min; min.resize(testTime);//build min by Num(targetHight)
	vector<double**> matrix; 
	matrix.resize(testTime);
	for(int k = 0;k < testTime;k++)
	{
		matrix[k] = new double*[pitchNum];
		for(int i = 0;i < pitchNum;i++) matrix[k][i] = new double[noteNum];

		for(int q =1; q< noteNum; q++) matrix[k][0][q] = 300.0;
	}
	vector<map<int,bool> > mark;
	mark.resize(testTime);
	vector<int> S; 

	for(int time = 0;time < testTime;time++)
	{
		min[time] = tool.D(pitch, note, pitchNum-1,noteNum-time-1, matrix[time],mark[time]);
	}
	
	/*min[0] = tool.D(pitch , note, pitchNum-1, noteNum-1,matrix[0], mark[0]);
	min[1] = tool.D(pitch , note, pitchNum-1, noteNum-2,matrix[1], mark[1]);
	min[2] = tool.D(pitch , note, pitchNum-1, noteNum-3,matrix[2], mark[2]);
	min[3] = tool.D(pitch , note, pitchNum-1, noteNum-4,matrix[3], mark[3]);
	min[4] = tool.D(pitch , note, pitchNum-1, noteNum-5,matrix[4], mark[4]);
	min[5] = tool.D(pitch , note, pitchNum-1, noteNum-6,matrix[5], mark[5]);*/

	double Ans;
	int select = 100;
	tool.Min(min, Ans,select);//select the min Ans
	cout << Ans<<endl;
	//cout << "the select Ans ---"<<select<<endl;
	tool.findS(matrix[select], pitchNum,noteNum-select,S);
	//cout <<"S : ";
	for(int j = 0;j< S.size(); j++) cout <<S[j]<<" "; cout<<endl;

	//cout <<min<< endl;

	/*for(int j = noteNum-1;j >= 0;j--)
	{
		cout << note[j] <<"	";
		for(int i = 0;i <pitchNum;i++)
		{
			cout << matrix[select][i][j] << "	";
		}
		cout <<endl;
	}
	cout<<" O "<<"	";
	for(int k = 0;k <pitchNum;k++) cout<< pitch[k]<<"	";
	cout<<endl;*/

	
}



