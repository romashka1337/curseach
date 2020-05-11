#pragma once
#include "mt.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct BigChar {
	long int Zero[2];
	long int One[2];
	long int Two[2];
	long int Three[2];
	long int Four[2];
	long int Five[2];
	long int Six[2];
	long int Seven[2];
	long int Eight[2];
	long int Nine[2];
	long int Plus[2];
	long int Minus[2];
};

static struct BigChar BCH = {{2172748287,4286677377}, {2291179712,2155905152}, {270804024,1006896136}, {4286611711,4286611584}, {4286677377,2155905152}, {16843263,4286611711}, {16843263,4286677503}, {541098239,33818640}, {4286677503,4286677377}, {4286677503,4286611584}, {4279769112, 404232447}, {4278190080, 255}};

int bc_printA(char * str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(long int *, int x, int y, enum colors, enum colors);
int bc_setbigcharpos (int * big, int x, int y, int value);
int bc_getbigcharpos(int * big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int * big, int count);
int bc_bigcharread (int fd, int * big, int need_count, int * count);
int bc_setBCH(char, long int*);
