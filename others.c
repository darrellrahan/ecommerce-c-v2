#include <stdio.h>
#include <stdlib.h>
#include "others.h"

void clearScreen()
{
	#ifdef _WIN32
	    system("cls");
	#else
	    system("clear");
	#endif
}

void exitProgram()
{
    clearScreen();
    puts("Keluar dari aplikasi.");
    exit(0);
}
