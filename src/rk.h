#pragma once
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>

enum keys {
	Load,//l
	Save,//s
	Run,//r
	Step,//t
	Reset,//i
	Accumulator,//f5
	InstructionCounter,//f6
	Quit,//q 
	Right,//>
	Left,//<
	Down,//v
	Up,//^
	PlusValue,//+
	MinusValue,//-
	Register0,//0
	Register1,//1
	Register2,//2
	Register3,//3
	Register4,//4
	Regime,//*
	Restore,//`
	Default
};

int rk_readkey (enum keys *);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
