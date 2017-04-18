nclude <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>
#include <map>
#include "DP.h"

using namespace std;

double DP::D(vector<double> pitch,vector<double> note, int P, int N, double**& matrix, map<int,bool>& mark)
{
		map<int, map<int, double> > value;

			double aAli = abs( (pitch[P] - note[N] ) );
				int point = P+N*pitch.size();

					if( mark.find(point) != mark.end()) return matrix[P][N];
						
						if(P == 0)
								{
											if( N == 0)
														{ 
																		matrix[0][0] = pitch[0]-note[0]; 
																					mark[0] = true;
																								return matrix[0][0]; 
																										}
													else if( N != 0) 
																{
																				mark[point] = true; 
																							return matrix[0][N]; 
																									}
														}
							else if (N>0 && P> 0 && D(pitch,note,P-1,N-1,matrix,mark) < D(pitch,note,P-1,N,matrix,mark) )
									{
												matrix[P][N]= (aAli + D(pitch,note,P-1,N-1,matrix,mark));
														mark[point ] = true; 
																return matrix[P][N];
																	}
								else if(N==0 || D(pitch,note,P-1,N,matrix,mark) <= D(pitch,note,P-1,N-1,matrix,mark))
										{
													matrix[P][N] =(aAli + D(pitch,note,P-1,N,matrix,mark));
															mark[point ] = true; 
																	return matrix[P][N];
																		}
									
}

void DP::extract(vector<double> note, vector<double>& extract)
{
		extract.clear();

			double* temp = new double[note.size()];
				for(int i = 0;i< note.size();i++) temp[i] = note[i];
					sort(temp, temp+note.size());
						for(int i = 0;i < note.size();i++) cout<< temp[i]<<" "; cout<<endl;
							for(int i  = 0;i< note.size();i++)
									{
												bool exist = false;
														for(int j = 0;j< i;j++) if(temp[i] == temp[j]) exist = true; 
																if(!exist) extract.push_back(temp[i]);
																	}
								for(int i = 0;i < extract.size();i++) cout<< extract[i]<<" ";
									cout<<endl;
}

void DP::Min(vector<double> num,double& Min,int& select)
{
		Min = 3000;
			for(int i = 0;i < num.size();i++)
					{
								if(num[i] < Min)
											{
															Min = num[i];
																		select = i;
																				}
									}
				

}

void DP::findS(double** matrix,int pitchNum,int noteNum, vector<int>& S)
{
		double point = matrix[0][0];
			int noteHight = 0;
				S.push_back(0);
					for(int i = 1;i < pitchNum;i++)
							{
										if(noteHight == (noteNum-1) ) point = matrix[i][noteHight];	
												else if(matrix[i][noteHight] < matrix[i][noteHight+1]) point = matrix[i][noteHight];
														else if(matrix[i][noteHight] >= matrix[i][noteHight+1]) 
																	{
																					noteHight++;
																								point = matrix[i][noteHight];
																											S.push_back(i);
																													}
															}
}

