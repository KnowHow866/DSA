// stdafx.cpp : �ȥ]�t�з� Include �ɪ���l�{����
// ConsoleApplication16.pch �|��������sĶ���Y��
// stdafx.obj �|�]�t����sĶ������T

#include "stdafx.h"
#include <iostream>




// TODO:  �b STDAFX.H ���Ѧұz�ݭn�������L���Y�A
// �Ӥ��n�b�o���ɮפ��Ѧ�

double** Operater::Mutiply(double** Matrix1,double** Matrix2,int size)//�x�}���k�A��X�x�}>>�Υ��������б����A�_�h�|�y���������Ъ�memory leak
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

double Operater::MutiplyScalar(double** Matrix1, double** Matrix2, int size)//�x�}���k�A��X�¶q
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

double Operater::Sum(double** target,int size)//��X�x�}�¶q
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

void Operater::MutiplyRow(double** Matrix1, int row, double time,int size)//��Y�@��row���Htime�� 
{
	for (int j = 0;j < size;j++)
	{
		Matrix1[row][j] *= time;
	}
}

void Operater::InLineAdd(double** Matrix1, int size, int giver, int receiver,double time)//�x�}��C�ۥ[
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





