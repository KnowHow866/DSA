
// ConsoleApplication16.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main()
{
	int size;
	int Error=0;
	Operater tool;

	cin >> size;
	double** matrix = new double*[size];//�t�m���а}�C
	for (int i = 0;i < size;i++) matrix[i] = new double[size];//�t�m�G���}�C

	double** I = new double*[size];//�ب���x�}
	for (int i = 0;i < size;i++) I[i] = new double[size];
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			if (i == j) I[i][j] = 1;
			else I[i][j] = 0;
		}
	}

	double** I2 = new double*[size];//�ب���x�}�A�ƥ�
	for (int i = 0;i < size;i++) I2[i] = new double[size];
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			if (i == j) I2[i][j] = 1;
			else I2[i][j] = 0;
		}
	}

	double** substitude = new double*[size];//�غc�ůx�}�A�Ψӽƻs��J�x�}
	for (int i = 0;i < size;i++) substitude[i] = new double[size];

	double** result;//�������СA�����p�⵲�G
	
	for (int i = 0;i < size;i++)//��J�ؼЯx�},�ýƻs�@����ůx�}
	{
		for (int j = 0;j < size;j++)
		{
			cin >> matrix[i][j];
			substitude[i][j] = matrix[i][j];
		}
	}
	

	for (int i = 0;i < size;i++)//�������h�D�ϯx�}
	{
		double RowTime = 1 / matrix[i][i];
		tool.MutiplyRow(matrix, i, RowTime, size);
		tool.MutiplyRow(I, i, RowTime, size);
		for (int b = 0;b < size; b++)
		{
			if (b == i);
			else
			{
				double time =(-1)* matrix[b][i];
				tool.InLineAdd(matrix, size, i, b, time);
				tool.InLineAdd(I, size, i, b, time);
			}
		}
	}

	result = tool.Mutiply(substitude , I , size);//���ϯx�}�ۭ�
	//sum = tool.MutiplyScalar(substitude, I, size) - tool.Sum(I2,size);//�D�~�t
        Error = tool.Error(result,size);


	cout << "��X��\n";  //��X�~�t�ΥؼЯx�}
	cout << Error  << endl;
	for (int i = 0;i < size;i++) 
	{
		for (int j = 0;j < size;j++) 
		{
			cout << I[i][j] << " ";
		}
		cout << endl;
	}
	

	//system("PAUSE");
	delete[] matrix, I, substitude, result, I2;

    return 0;
}

