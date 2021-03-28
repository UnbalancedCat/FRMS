#define _CRT_SECURE_NO_WARNINGS  
#include "global.h"

int main(void)
{
	atexit(backup_files);
	init();
	menu();
	//play_music();
	return 0;
}

