// array.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
#define MAXSIZE 100
#define M 10
#define N 10
typedef int Elemtype;
/*ϡ�����һ�������ϴ�ľ����еķ���Ԫ�ظ���s����ھ���Ԫ�ص��ܸ���ʮ��Сʱ����s<<tʱ����þ���Ϊϡ�����
  ϡ������ѹ���洢������ֻ�洢����Ԫ�أ�ÿһ������Ԫ������һ����Ԫ��:(i,j,Aij)
  ��ϡ��������Ԫ�����Ա�˳��洢�ṹ�洢�����Ϊϡ��������Ԫ��˳���
*/

typedef struct  //��ŷ���Ԫ�صĽṹ��
{
	int r;      //�б�
	int c;      //�б�
	Elemtype d; //Ԫ��ֵ
}TopNode;       //��Ԫ�鶨��

typedef struct//�������ϡ�����Ľṹ��
{
	int rows;//����ֵ
	int cols;//����ֵ
	int nums;//����Ԫ�ظ���
	TopNode data[MAXSIZE];//��ŷ���Ԫ�ص���Ϣ
}TSMatrix;//��Ԫ��˳�����

//��һ����λ���鴴������Ԫ���ʾ��������ʽɨ���ά����A����������Ԫ�ز��뵽��Ԫ��t�ĺ���
void creatMat(TSMatrix &t,Elemtype A[M][N] )//������Ԫ��t,ϡ�����A
{
	int i, j;
	t.rows = M;  //M��
	t.cols = N;  //N��
	t.nums = 0;  //����Ԫ�ظ�����ʼֵΪ0
	for ( i = 0; i < M; i++)
		for (j = 0; j < N; j++)//ɨ��������ά����
		{
			if (A[i][j] != 0)
			{
				t.data[t.nums].r = i;//�кŸ�����Ԫ���б�
				t.data[t.nums].c = j;//�кŸ�����Ԫ���б�
				t.data[t.nums].d = A[i][j];//ֵ������Ԫ��Ԫ��ֵ
				t.nums++;//���������1
			}
		}
}

/*��Ԫ��Ԫ�ظ�ֵ�������������
1.��һ����0Ԫ���޸�Ϊ��һ����0ֵ����Ԫ��Ԫ��ֵ�޸ģ� 
2.��һ��0Ԫ���޸�Ϊ����ֵ����Ԫ��Ԫ��������
*/
bool value(TSMatrix &t, Elemtype x, int i, int j)//ϡ�����ij��λ�ø�ֵ   ��t[i][j]=x��
{
	int k = 0, k1;
	if (i >= t.rows || j >= t.cols)//������λ���Ƿ����
		return false;
	while (k<t.nums && i>t.data[k].r)
		k++;//�����У���ϡ�����Ԫ���в��ң������У�
	while (k<t.nums && i == t.data[k].r && j>t.data[k].c)
		k++;//������,�������ҵõ�Ҫ�����λ��,(��Ԫ���б�ʾ�ڼ���)
	if (t.data[k].r == i && t.data[k].c == j)//�����ʱ��λ���Ƿ��㣬���޸�ֵ����
		t.data[k].d = x;
	else//��λ����0��������Ԫ����Ҫ���룬�����Ԫ��ȫ������
	{
		for (k1 = t.nums - 1; k1 >= k; k1--)//�����һ��λ�����������ƶ���˳���
		{
			t.data[k1 + 1].r = t.data[k1].r;
			t.data[k1 + 1].c = t.data[k1].c;
			t.data[k1 + 1].d = t.data[k1].d;
		}
		t.data[k].r = i;
		t.data[k].c = j;
		t.data[k].d = x;//����x
		t.nums++;//�ܷ��������1
	}
	return true;
}

/*��ָ����Ԫ��ֵ��ֵ������  ��ִ��x=A[i][j]
����Ԫ�����ҵ�ָ�� ��λ�ã��ٽ��ô���Ԫ��ֵ����x
�Ҳ�����˵��Ϊ0
*/
bool assign(TSMatrix t, Elemtype &x, int i, int j)
{
	int k = 0;
	while (k<t.nums && i>t.data[k].r)
		k++;//������
	while (k<t.nums && i == t.data[k].r && j>t.data[k].c)
		k++;//������
	if (t.data[k].r == i && t.data[k].c == j)
		x = t.data[k].d;//�ҵ��ˣ���ֵ����x����
	else
		x = 0;//û�ҵ�˵��Ϊ0
	return true;
}


/*�����Ԫ��
��ͷ��βɨ����Ԫ��t,�������Ԫ��ֵ
*/
void dispMat(TSMatrix t)
{
	int i;
	if (t.nums <= 0) return;
	//cout << t.rows <<"\t "<< t.cols <<"\t"<< t.nums << endl;//\t�Ʊ��
	cout << "------------------" << endl;
	for (i = 0; i < t.nums; i++)
	   cout << t.data[i].r <<"\t"<< t.data[i].c <<"\t"<< t.data[i].d << endl;
}


/*�����ת�ã���Ԫ���Ȱ��в��ң�Ȼ��i,j����*/
void TranTat(TSMatrix t, TSMatrix &tb)
{
	int p, q = 0, v;  //qΪtb.data���±�,qΪt.data���±�
	tb.rows = t.cols; tb.cols = t.rows; tb.nums = t.nums;//ת��ǰ�����л���
	if (t.nums != 0)//�����ڷ���Ԫ��ʱִ��ת��
	{
		for ( v = 0; v < t.cols; v++)      //���п�ʼɨ��
			for ( p = 0; p < t.nums; p++)  //pΪt.data���±�
				if (t.data[p].c == v)//����Ŵ�0��ʼɨ�裬��Ⱦʹ����µ���Ԫ��
				{
					tb.data[q].r = t.data[p].c;//ԭ�����кŸ����к�
					tb.data[q].c = t.data[p].r;//ԭ�����кŸ����к�
					tb.data[q].d = t.data[p].d;
					q++;//tb���
			    }//����0��1�� 2��3...��n-1�н���ת��
	}
}

int main()
{
	int i;
	int a[10][10] = { {0,0,0,0,0,0,0,0,0,1},
	                  {1,0,0,0,0,0,0,0,0,0},
					  {0,1,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,1,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,1},
					  {0,0,0,0,0,0,0,1,0,0},
					  {0,0,0,0,0,0,0,0,0,0},
	};
	TSMatrix t;
	creatMat(t, a);//����ϡ��������Ԫ��
	dispMat(t);    //��ӡ��Ԫ��
	getchar();
	//while (1);
    return 0;
}

