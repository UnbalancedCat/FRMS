#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include"global.h"

int main(void)
{
	atexit(shut_down);
	init();
	menu();
	return 0;
}

