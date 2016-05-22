#include <stdio.h>      
#include <stdlib.h>     
#include <iostream>		
#include <time.h>       
#include "WELL1024a.h"	// WELL Random number generator  http://www.iro.umontreal.ca/~panneton/WELLRNG.html

#define MAX 99999


int * rdNum() { // �������� �����ȣ�� �����ϴ� �Լ�
	int * ran;
	ran = (int*)calloc(MAX, sizeof(int));
	int i;

	srand((unsigned)time(NULL));
	unsigned int init[32];
	for (int i = 0; i<32; i++) {
		init[i] = rand() << 16 | rand();
		// WELL Random �� �ʱ�ȭ �ϱ� ����, C ǥ�� rand() �Լ��� �̿��Ͽ� init ���� �����մϴ�
		// WELL Random �� ����ϴ� ���� 1. �����ȣ �ִ밪�� 99999�̱� ������ 2. ǥ�� �Լ����� �ӵ��� ������ ������
	}
	InitWELLRNG1024a(init); // WELL Random �ʱ�ȭ

							// �⺻ ���� - min ~ max ������ ����
							//	double x = (double)WELLRNG1024a() * (max-min+1) + min; 

	for (i = 0; i<MAX; i++)
	{
		ran[i] = i;
	}

	srand((unsigned)time(NULL));

	int rana;

	for (i = 0; i<MAX; i++)
	{
		rana = (int)((double)WELLRNG1024a() * (MAX-i+1)) + i;
		int prev;

		prev = ran[i];
		ran[i] = ran[rana];
		ran[rana] = prev;

	}

	return ran;

}
int main(void)
{
	int i, count, *ran;
	char temp_record[6] = { 0 };
	ran = rdNum();

	scanf("%d", &count);

	for (i = 0; i<count; i++)
	{
		itoa(ran[i], temp_record, 10);

		printf("NT%05s %3d\n", temp_record,(int)((double)WELLRNG1024a() * 101));

	}

	return 0;
}