#include "graphics.h"
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void signalhandler(int signo) {
	int value = 0;
	sc_regGet(3, &value);
	if (!value) {
		sc_instCounterGet(&value);
		value++;
		sc_instCounterSet(value);
	}
	gr_printInstCounter();
	alarm(1);
}

void signalhandler1(int signo) {
	sc_regSet(3, 0);
}

int main() {
	alarm(1);
	signal(SIGALRM, signalhandler);
	signal(SIGUSR1, signalhandler1);
	rk_mytermsave();
	enum keys Key = Default;
	int paintCount = 0;
	int regime = 0;
	rk_mytermregime(regime, 0, 0, 0, 0);
	while (Key != Quit) {
		mt_clrscr();
		gr_printMemory(paintCount);
		int m = 0;
		sc_memoryGet(paintCount, &m);
		gr_drawBCH(m);
		gr_printInstCounter();
		gr_printRegFlag();
		gr_interface();
		rk_readkey(&Key);
		int value = 0;
		sc_regGet(3, &value);
		if (!value) {
			switch (Key) {
				case Load:
					rk_mytermrestore();
					break;
				case Save:
					rk_mytermsave();
					break;
				case Right:
					if (paintCount < 100) {
						paintCount++;
					} else {
						paintCount = 0;
					}
					break;
				case Left:
					if (paintCount >= 0) {
						paintCount--;
					} else {
						paintCount = 100;
					}
					break;
				case PlusValue: {
					int ValuePLusRAM = 0;
					sc_memoryGet(paintCount, &ValuePLusRAM);
					ValuePLusRAM++;
					sc_memorySet(paintCount, ValuePLusRAM);
					break;
				}
				case MinusValue: {
					int ValueMinusRAM = 0;
					sc_memoryGet(paintCount, &ValueMinusRAM);
					if (ValueMinusRAM - 1 >= 0) {
						ValueMinusRAM--;
						sc_memorySet(paintCount, ValueMinusRAM);
					}
					break;
				}
				case Register0: {
					int ValueReg = 0;
					sc_regGet(0, &ValueReg);
					if (ValueReg) {
						sc_regSet(0, 0);
					} else {
						sc_regSet(0, 1);
					}
					break;
				}
				case Register1: {
					int ValueReg = 0;
					sc_regGet(1, &ValueReg);
					if (ValueReg) {
						sc_regSet(1, 0);
					} else {
						sc_regSet(1, 1);
					}
					break;
				}
				case Register2: {
					int ValueReg = 0;
					sc_regGet(2, &ValueReg);
					if (ValueReg) {
						sc_regSet(2, 0);
					} else {
						sc_regSet(2, 1);
					}
					break;
				}
				case Register3: {
					int ValueReg = 0;
					sc_regGet(3, &ValueReg);
					if (ValueReg) {
						sc_regSet(3, 0);
					} else {
						sc_regSet(3, 1);
					}
					break;
				}
				case Register4: {
					int ValueReg = 0;
					sc_regGet(4, &ValueReg);
					if (ValueReg) {
						sc_regSet(4, 0);
					} else {
						sc_regSet(4, 1);
					}
					break;
				}
				case Regime: {
					if (regime == 0) {
						rk_mytermregime(1, 0, 1, 0, 1);
						regime = 1;				
					} else {
						rk_mytermregime(0, 0, 1, 0, 1);
						regime = 0;
					}
					break;
				}
				default: break;
			}
		} else {
			if (Key == Restore) {
				raise(SIGUSR1);
			}
		}
	}	
	rk_mytermregime(0, 0, 1, 1, 1);
	printf("\n");
	return 0;
}