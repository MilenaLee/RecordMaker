#include <stdio.h>      
#include <stdlib.h>     
#include <iostream>		
#include <time.h>       
#include "WELL1024a.h"	// WELL Random number generator  http://www.iro.umontreal.ca/~panneton/WELLRNG.html

#define MAX 99999


int * rdNum() { // 랜덤으로 사원번호를 생성하는 함수
	int * ran;
	ran = (int*)calloc(MAX, sizeof(int));
	int i;

	srand((unsigned)time(NULL));
	unsigned int init[32];
	for (int i = 0; i<32; i++) {
		init[i] = rand() << 16 | rand();
		// WELL Random 을 초기화 하기 위해, C 표준 rand() 함수를 이용하여 init 값을 생성합니다
		// WELL Random 을 사용하는 이유 1. 사원번호 최대값이 99999이기 때문에 2. 표준 함수보다 속도가 빠르기 때문에
	}
	InitWELLRNG1024a(init); // WELL Random 초기화
				// 기본 사용법 - min ~ max 범위의 난수
				//double x = (double)WELLRNG1024a() * (max-min+1) + min; 

	//사원번호의 중복을 방지하기 위해 MAX크기의 배열에 1부터 99999까지의 숫자를 차례대로 넣은 후 카드 섞기 방식으로 난수 배열 생성.
	for (i = 0; i<MAX; i++)
	{
		ran[i] = i+1;
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
