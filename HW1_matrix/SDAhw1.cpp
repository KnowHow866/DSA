
// ConsoleApplication16.cpp : 定義主控台應用程式的進入點。
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
	double** matrix = new double*[size];//配置指標陣列
	for (int i = 0;i < size;i++) matrix[i] = new double[size];//配置二維陣列

	double** I = new double*[size];//建制單位矩陣
	for (int i = 0;i < size;i++) I[i] = new double[size];
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			if (i == j) I[i][j] = 1;
			else I[i][j] = 0;
		}
	}

	double** I2 = new double*[size];//建制單位矩陣，備用
	for (int i = 0;i < size;i++) I2[i] = new double[size];
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			if (i == j) I2[i][j] = 1;
			else I2[i][j] = 0;
		}
	}

	double** substitude = new double*[size];//建構空矩陣，用來複製輸入矩陣
	for (int i = 0;i < size;i++) substitude[i] = new double[size];

	double** result;//接收指標，接收計算結果
	
	for (int i = 0;i < size;i++)//輸入目標矩陣,並複製一分到空矩陣
	{
		for (int j = 0;j < size;j++)
		{
			cin >> matrix[i][j];
			substitude[i][j] = matrix[i][j];
		}
	}
	

	for (int i = 0;i < size;i++)//高斯消去求反矩陣
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

	result = tool.Mutiply(substitude , I , size);//正反矩陣相乘
	//sum = tool.MutiplyScalar(substitude, I, size) - tool.Sum(I2,size);//求誤差
        Error = tool.Error(result,size);


	cout << "輸出值\n";  //輸出誤差及目標矩陣
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

