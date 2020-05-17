#include "graphics.h"

void signalhandler(int signo) {
	// int value = 0;
	// sc_regGet(3, &value);
	// if (!value) {
	// 	sc_instCounterGet(&value);
	// 	value++;
	// 	sc_instCounterSet(value);
	// }
	gr_printInstCounter();
	alarm(1);
}

void signalhandler1(int signo) {
	sc_regSet(3, 0);
}

int commandDecode(int value, int *command, int *operand) {
	int temp = value;
	if (((value >> 14) & (0x1)) != 0) {
		sc_regSet(IGNORING_TACT_PULSES, 1);
		sc_regSet(CODE_ERROR, 1);
		return 1;
	}
	value = temp;
	value = (value >> 7);
	*command = value >> 1;
	value = temp;
	value = value & ((1 << 6) - 1);
	*operand = value;
	return 0;
}

int main() {
	alarm(1);
	signal(SIGALRM, signalhandler);
	signal(SIGUSR1, signalhandler1);
	sc_memoryInit();
	rk_mytermsave();
	sc_memorySet(0, 0x2003);
	sc_memorySet(3, 0x3113);
	rk_mytermregime(0, 0, 0, 0, 0);
	gr_input();
	rk_mytermregime(0, 0, 1, 1, 1);
	printf("\n");
	return 0;
}