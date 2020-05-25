#include<iostream>
#include"mpi.h"
#include<ctime>
#include<cmath>
#include <iomanip>
using namespace std;


const int N = 1E9;
double start, finish;//�������ֹʱ��
int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);//MPI��ĳ�ʼ��
	int numprocs, myid;//����������������̱�ʶ
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);//��ý�����
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);//��õ�ǰ���̱�ʶ��0,1,2,3,....,numprocs - 1

	start = MPI_Wtime();//���ʱ��
	long double partSum = 0.0;//���岿�ֺ�
	
    long double x, y, z=0.0;
    long double num = 0;
	long double pi = 0.0;//����pi��ֵ

	for (int j = 0; j < 2000; j++)
	{
		int k = 0;
		srand((int)time(NULL));  // �����������  ��0����NULLҲ��
		for (int i = myid; i < N; i += numprocs)
		{
			x = rand() / long double(RAND_MAX);
			y = rand() / long double(RAND_MAX);
			z = x * x + y * y;
			if (z <= 1)
			{
				k++;
			}

			//partSum += sqrt(1.0 - (double)(i * i) / (N * N))/N; int�ͳ˷������������
		}
		num  = num + long double(k) / 1E8;
		partSum = num / long double(10* (j + 1));
		MPI_Reduce(&partSum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		//��Լ�������������̵�partSum���͵�0�Ž��̲����
		cout << "Ŀǰnum��ֵΪ��"<<num << endl;
		cout << "�ҵı�ʶ��" << myid << ",��õ�partSumֵΪ:" << setprecision(9) << partSum << endl;


		if (myid == 0)
		{
			pi *= 4.0;
			finish = MPI_Wtime();
			cout << "����" << j+1 << ",000,000,000 ��" << endl;
			cout << "��ý��Ƶ�piֵΪ:" << setprecision(9) << pi << endl;
			cout << "����" << numprocs << "�����̵ļ���ʱ��Ϊ:" << finish - start << " s" << endl;
			cout << '\n';
		}

		if (fabs(pi - 3.1415926 )< 1E-7)
			break;
	}

	MPI_Finalize();
	//system("pause");
	return 0;
}
