// stdafx.h : �i�b�����Y�ɤ��]�t�зǪ��t�� Include �ɡA
// �άO�g�`�ϥΫo�ܤ��ܧ�
// �M�ױM�� Include �ɮ�
//

#pragma onc


#include <stdio.h>
//
//#include <tchar.h>

class Operater
{
    public :
        double** Mutiply(double** Matrix1, double** Matrix2, int size);//�x�}�ۭ�
		void MutiplyRow(double** Matrix1, int row, double time,int size);//��Y�@��row���Hn��
		double MutiplyScalar(double** Matrix1, double** Matrix2, int size);//�x�}���k�A��X�¶q
		double Sum(double** target, int size);//��x�}�Ʀ��¶q
		void InLineAdd(double** Matrix1,int size,int giver,int receiver,double time);//�x�}��A��[��B��
		double Error(double** Matrix,int size);//The Error
};




