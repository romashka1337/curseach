#pragma once

#include "sc.h"
#include <stdio.h>

int alu_read(int);
int alu_write(int);
int alu_load(int);
int alu_store(int);
int alu_add(int);
int alu_sub(int);
int alu_divide(int);
int alu_multiply(int);
int alu_jump(int);
int alu_jneg(int);
int alu_jz(int);
int alu_halt(void);
int alu_rcr(int);
int alu_alu(int, int);
int alu_cu(void);
