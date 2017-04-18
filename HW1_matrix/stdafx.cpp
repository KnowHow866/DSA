// stdafx.cpp : 僅包含標準 Include 檔的原始程式檔
// ConsoleApplication16.pch 會成為先行編譯標頭檔
// stdafx.obj 會包含先行編譯類型資訊

#include "stdafx.h"
#include <iostream>




// TODO:  在 STDAFX.H 中參考您需要的任何其他標頭，
// 而不要在這個檔案中參考

double** Operater::Mutiply(double** Matrix1,double** Matrix2,int size)//矩陣乘法，輸出矩陣>>用未指派指標接收，否則會造成接收指標的memory leak
{
	double** result = new double*[size];
	for (int i = 0;i < size;i++) result[i] =new double[size];

	for (int i = 0;i < size;i++) 
	{
		for (int j = 0;j < size;j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < size;k++)
			{
				result[i][j] += Matrix1[i][k] * Matrix2[k][j];
			}		
		}

	}
	return result;
}

double Operater::MutiplyScalar(double** Matrix1, double** Matrix2, int size)//矩陣乘法，輸出純量
{
	double sum = 0;

	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			for (int k = 0; k < size;k++)
			{
				sum += Matrix1[i][k] * Matrix2[k][j];
			}
		}

	}
	return sum;
}

double Operater::Sum(double** target,int size)//輸出矩陣純量
{
	double sum = 0;
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++) 
		{
			sum += target[i][j];
		}
	}
	return sum;
}

void Operater::MutiplyRow(double** Matrix1, int row, double time,int size)//把某一個row乘以time倍 
{
	for (int j = 0;j < size;j++)
	{
		Matrix1[row][j] *= time;
	}
}

void Operater::InLineAdd(double** Matrix1, int size, int giver, int receiver,double time)//矩陣兩列相加
{
	if (giver < size && receiver < size) 
	{
		double** result = new double*[size];
		for (int i = 0;i < size;i++) result[i] = new double[size];

		for (int j = 0;j < size; j++)
		{
			Matrix1[receiver][j] += Matrix1[giver][j]*time;
		}
	}
	else
	{
		std::cout << "Wrong ! Please recode.";
	}
}

double Operater::Error(double** Matrix,int size)
{
	double** testM = new double*[size];
	for(int i = 0;i < size;i++){ testM[i] = new double[size]; }//Build a Unit Matrx
        for(int i = 0;i < size;i++)
	{
                 for(int j = 0;j < size;j++)
		 {
                      if(i == j) testM[i][j] = 1;
		      else testM[i][j] = 0;
		 }

	}


	double Error = 0;
	double Giver;
        for(int i = 0;i < size;i++)
	{
		for(int j = 0;j < size;j++)
		{
                     if( (Matrix[i][i] - testM[i][i]) < 0) Giver = ((Matrix[i][i] - testM[i][i])*(-1));
		     else{ Giver = (Matrix[i][i] - testM[i][i]); }

		     if(Giver > Error) Error = Giver;
		     else;
		 }
	}

	return Error;									
}





