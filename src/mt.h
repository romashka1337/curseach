#pragma once
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

enum colors {
	black = 30,
	red = 31,
	green = 32,
	yellow = 33,
	blue = 34,
	magenta = 35,
	cyan = 36,
	white = 37,
	reset = 0
};

int mt_clrscr (void);
int mt_gotoXY (int, int);
int mt_getscreensize (int * rows, int * cols);
int mt_setfgcolor (enum colors);
int mt_setbgcolor (enum colors);
