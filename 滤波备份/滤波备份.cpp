// 滤波.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//生成一个随机数矩阵（可以设置的大一些），随机数的范围是0 - 255.
//程序可以进行滤波操作，其中滤波核大小和值由用户进行设置。
#include<iostream>
#include<iomanip>
#include<random>
using namespace std;
float** ARRAY(int row, int column,int Cube);
float** Array2(int row, int column,int Cube);
float** Filter(int Cube);
void Print(float** Matrix1, int row,int column,int Cube);
int main() {
	int row, column,Cube;
	cout << "ROW COLUMN" << "\n";
	cin >> row >> column;
	cout << "Length of Filter(n=2k-1)" << "\n";
	cin>>Cube;
	float** Matrix1 = ARRAY(row, column, Cube);
	float** Matrix2 = Array2(row, column, Cube);
	float** Fil = Filter(Cube);
	//进行滤波操作
	float num1 = 0;
	float num2 = 0;
	for (int n = ((Cube - 1) / 2)-1; n < row + Cube - 1; n++)
	{
		for (int m = ((Cube - 1) / 2)-1; m < column + Cube -1; m++)
		{
			float sum = 0;
			for (int i = 0; i <Cube; i++)
			{
				for (int j = 0; j <Cube; j++)
				{
					num1 = Matrix2[n + i][m + j];
					num2 = Fil[i][j];
					sum += num1 * num2;
				}
			}
			Matrix1[n+((Cube- 1)/2)][m+((Cube - 1)/2)] = sum / (Cube * Cube);//求均值并替换核心值
		}

	}
	
	Print(Matrix1, row,column,Cube);
	return 0;

}

float** ARRAY(int row, int column,int Cube) {//row为数组行数，column为数组列数，Cube为滤波邻域直径
	random_device rd;//随机数生成器
	mt19937 Random(rd());
	int i = 0, j = 0;
	float** Matrix1;//双指针
	Matrix1 = new float* [row +(Cube-1)];
	for (int a = 0; a < row + (Cube - 1); a++)
		Matrix1[a] = new float[column + (Cube - 1)];//指针数组的每个元素指向每个int型数组的第一个元素地址，实现了二维数组的创建，在这里往外扩张了(Cube-1)/2圈
	for (i = 0; i < row + Cube - 1; i++)
	{
		for (j = 0; j < column + Cube - 1; j++)
		{
			if (i <= ((Cube - 1) / 2) - 1 || j <= ((Cube - 1) / 2) - 1 || i >= row + ((Cube - 1) / 2) - 1 || j >= column + ((Cube - 1) / 2) - 1) {//外界填0元素
				Matrix1[i][j] = 0;
			}
			else { Matrix1[i][j] = (float)(rd() % 255 + 1); }//rand函数填充内界值，rand的范围在[0,255]内
		}
	}
	return Matrix1;
}//创建二维数组，并用随机数初始化每个元素的值，扩展了最外圈且元素值为0
float** Array2(int row, int column,int Cube) {//创建数组2，作为数组1的备份
	float** Matrix2;
	Matrix2 = new float* [row + (Cube - 1)];
	float** Matrix1 = ARRAY(row, column,Cube);
	for (int a = 0; a < row + Cube - 1; a++)
		Matrix2[a] = new float[column + (Cube - 1)];
	for (int i = 0; i < row + Cube-1 ; i++)
	{
		for (int j = 0; j < column + Cube-1 ; j++) {
			Matrix2[i][j] = Matrix1[i][j];
		}
	}
	return Matrix2;
}
float** Filter(int Cube) {//Fil是一个Cube*Cube大小的滤波器(核)
	float** Fil;
	Fil = new float* [Cube];
	for (int a = 0; a < Cube; a++)
		Fil[a] = new float[Cube];
	for (int i = 0; i < Cube ; i++)
	{
		for (int j = 0; j < Cube ; j++) {
			Fil[i][j] = 1.0;
		}
	}
	return Fil;
}
void Print(float** Matrix1, int row,int column,int Cube) {//打印一次滤波结果
	for (int i = ((Cube - 1) / 2)-1; i <row + ((Cube - 1) / 2) - 1; i++) {
		for (int j = ((Cube - 1) / 2)-1; j <column + ((Cube - 1) / 2) - 1; j++)
		{
			cout << setw(7) << fixed << setprecision(2) << Matrix1[i][j];
		}
		cout << "\n";
	}
}