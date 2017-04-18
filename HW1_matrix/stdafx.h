// stdafx.h : 可在此標頭檔中包含標準的系統 Include 檔，
// 或是經常使用卻很少變更的
// 專案專用 Include 檔案
//

#pragma onc


#include <stdio.h>
//
//#include <tchar.h>

class Operater
{
    public :
        double** Mutiply(double** Matrix1, double** Matrix2, int size);//矩陣相乘
		void MutiplyRow(double** Matrix1, int row, double time,int size);//把某一個row乘以n倍
		double MutiplyScalar(double** Matrix1, double** Matrix2, int size);//矩陣乘法，輸出純量
		double Sum(double** target, int size);//把矩陣化成純量
		void InLineAdd(double** Matrix1,int size,int giver,int receiver,double time);//矩陣內A行加到B行
		double Error(double** Matrix,int size);//The Error
};




