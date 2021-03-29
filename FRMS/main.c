#define _CRT_SECURE_NO_WARNINGS  
#include "global.h"

int main(void)
{
	atexit(shut_down);
	init();
	menu();
	//play_music();
	return 0;
}

