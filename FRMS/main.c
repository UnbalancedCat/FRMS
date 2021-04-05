#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include"global.h"

int main(void)
{
	atexit(shut_down);
	init();
	//printf("%d/%d/%d ", (1900 + init_time->tm_year), (1 + init_time->tm_mon), init_time->tm_mday);
	//printf("%d %d:%d:%d\n", init_time->tm_wday, init_time->tm_hour + 8, init_time->tm_min, init_time->tm_sec);
	system("pause");
	menu();
	return 0;
}

