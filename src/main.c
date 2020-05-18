#include "graphics.h"

void signalhandler(int signo) {
	int temp = 0;
	temp = alu_cu();
	if (temp == -1) {
		printf("\nprogram error");
		getchar();
	}
	if (temp == 1) {
		printf("End");
		getchar();
		alarm(0);
	} else alarm(1);
	gr_interface();
}

void signalhandler1(int signo) {
	sc_regSet(3, 0);
}

int main() {
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