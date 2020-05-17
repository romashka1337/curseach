#pragma once

#include "sc.h"
#include "bc.h"
#include "mt.h"
#include "rk.h"
#include "alu.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

int gr_printMemory(int);
int gr_printRegFlag(void);
int gr_interface();
int gr_drawBCH(int);
int gr_printOperation(void);
int gr_printInstCounter(void);
int gr_printAccum(void);
int gr_input(void);
