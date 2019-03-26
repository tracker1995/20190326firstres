// array.cpp : 定义控制台应用程序的入口点。
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
/*稀疏矩阵：一个阶数较大的矩阵中的非零元素个数s相对于矩阵元素的总个数十分小时，即s<<t时，则该矩阵为稀疏矩阵
  稀疏矩阵的压缩存储方法是只存储非零元素，每一个非零元素需有一个三元组:(i,j,Aij)
  把稀疏矩阵的三元组线性表按顺序存储结构存储，则称为稀疏矩阵的三元组顺序表
*/

typedef struct  //存放非零元素的结构体
{
	int r;      //行标
	int c;      //列标
	Elemtype d; //元素值
}TopNode;       //三元组定义

typedef struct//存放整个稀疏矩阵的结构体
{
	int rows;//行数值
	int cols;//列数值
	int nums;//非零元素个数
	TopNode data[MAXSIZE];//存放非零元素的信息
}TSMatrix;//三元组顺序表定义

//从一个二位数组创建其三元组表示：以行序方式扫描二维数组A，将其非零的元素插入到三元组t的后面
void creatMat(TSMatrix &t,Elemtype A[M][N] )//传入三元组t,稀疏矩阵A
{
	int i, j;
	t.rows = M;  //M行
	t.cols = N;  //N行
	t.nums = 0;  //非零元素个数初始值为0
	for ( i = 0; i < M; i++)
		for (j = 0; j < N; j++)//扫描整个二维数组
		{
			if (A[i][j] != 0)
			{
				t.data[t.nums].r = i;//行号赋给三元组行标
				t.data[t.nums].c = j;//列号赋给三元组列标
				t.data[t.nums].d = A[i][j];//值赋给三元组元素值
				t.nums++;//非零个数加1
			}
		}
}

/*三元组元素赋值，分两种情况：
1.将一个非0元素修改为另一个非0值（三元组元素值修改） 
2.将一个0元素修改为非零值（三元组元素新增）
*/
bool value(TSMatrix &t, Elemtype x, int i, int j)//稀疏矩阵ij的位置赋值   （t[i][j]=x）
{
	int k = 0, k1;
	if (i >= t.rows || j >= t.cols)//检查插入位置是否合理
		return false;
	while (k<t.nums && i>t.data[k].r)
		k++;//查找行（在稀疏表三元组中查找，先找行）
	while (k<t.nums && i == t.data[k].r && j>t.data[k].c)
		k++;//查找列,两个查找得到要插入的位置,(三元组中表示第几个)
	if (t.data[k].r == i && t.data[k].c == j)//如果此时该位置是非零，则修改值即可
		t.data[k].d = x;
	else//该位置是0，则在三元表中要插入，后面的元素全部后移
	{
		for (k1 = t.nums - 1; k1 >= k; k1--)//从最后一个位置依次往后移动（顺序表）
		{
			t.data[k1 + 1].r = t.data[k1].r;
			t.data[k1 + 1].c = t.data[k1].c;
			t.data[k1 + 1].d = t.data[k1].d;
		}
		t.data[k].r = i;
		t.data[k].c = j;
		t.data[k].d = x;//插入x
		t.nums++;//总非零个数加1
	}
	return true;
}

/*将指定的元素值赋值给变量  即执行x=A[i][j]
在三元组中找到指定 的位置，再将该处的元素值赋给x
找不到则说明为0
*/
bool assign(TSMatrix t, Elemtype &x, int i, int j)
{
	int k = 0;
	while (k<t.nums && i>t.data[k].r)
		k++;//先找行
	while (k<t.nums && i == t.data[k].r && j>t.data[k].c)
		k++;//再找列
	if (t.data[k].r == i && t.data[k].c == j)
		x = t.data[k].d;//找到了，将值赋给x即可
	else
		x = 0;//没找到说明为0
	return true;
}


/*输出三元组
从头到尾扫描三元组t,依次输出元素值
*/
void dispMat(TSMatrix t)
{
	int i;
	if (t.nums <= 0) return;
	//cout << t.rows <<"\t "<< t.cols <<"\t"<< t.nums << endl;//\t制表符
	cout << "------------------" << endl;
	for (i = 0; i < t.nums; i++)
	   cout << t.data[i].r <<"\t"<< t.data[i].c <<"\t"<< t.data[i].d << endl;
}


/*矩阵的转置，三元组先按列查找，然后i,j互换*/
void TranTat(TSMatrix t, TSMatrix &tb)
{
	int p, q = 0, v;  //q为tb.data的下标,q为t.data的下标
	tb.rows = t.cols; tb.cols = t.rows; tb.nums = t.nums;//转置前后行列互换
	if (t.nums != 0)//当存在非零元素时执行转置
	{
		for ( v = 0; v < t.cols; v++)      //从列开始扫描
			for ( p = 0; p < t.nums; p++)  //p为t.data的下标
				if (t.data[p].c == v)//列序号从0开始扫描，相等就存入新的三元表
				{
					tb.data[q].r = t.data[p].c;//原来的列号给到行号
					tb.data[q].c = t.data[p].r;//原来的行号给到列号
					tb.data[q].d = t.data[p].d;
					q++;//tb序号
			    }//按第0、1、 2、3...、n-1列进行转换
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
	creatMat(t, a);//创建稀疏矩阵的三元组
	dispMat(t);    //打印三元组
	getchar();
	//while (1);
    return 0;
}

