#pragma once
#include <stdio.h>

static int register_flag = 0;
static int RAM[100];
static int instCounter = 0;

#define MEMORY_OVERFLOW 0 
#define DIVISION_ERROR_BY_0 1 
#define BORDER_OVERLOAD_ERROR 2 
#define IGNORING_TACT_PULSES 3 
#define CODE_ERROR 4 

int sc_regInit(void); 
int sc_regSet(int, int); 
int sc_regGet(int, int*); 
int sc_memoryInit();
int sc_memorySet(int, int);
int sc_memoryGet(int, int*);
int sc_memorySave(char*);
int sc_memoryLoad(char*);
int sc_commandEncode(int, int, int*); 
int sc_commandDecode(int, int*, int*);
int sc_instCounterGet(int*);
int sc_instCounterSet(int);
