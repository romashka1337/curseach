#include "graphics.h"

int gr_printMemory(int number) {
	for (int it = 0, row = 2; it < 100;) {
		mt_gotoXY(2, row);
		for (int jt = 0; jt < 10; jt++, it++) {
			int Memory = 0;
			sc_memoryGet(it, &Memory);
			if (it == number) {
				mt_setbgcolor(yellow);
				printf("+%.4X", Memory);
				mt_setbgcolor(reset);
				printf(" ");
			} else {
				mt_setbgcolor(reset);
				printf("+%.4X", Memory);
				mt_setbgcolor(reset);
				printf(" ");
			}
		}
		row++;
	}
	return 0;
}

int gr_printRegFlag(void) {
	mt_gotoXY(69, 11);
	for (int it = 0; it < 5; ++it) {
		int CheckBitRegister = 0;
		sc_regGet(it, &CheckBitRegister);
		if (CheckBitRegister == 1) {
			mt_setfgcolor(yellow);
			printf("%d ", it);
			mt_setfgcolor(reset);
		} else {
			mt_setfgcolor(reset);
			printf("%d ", it);
			mt_setfgcolor(reset);
		}
	}
	return 0;
}

int gr_interface() {
	bc_box(1, 1, 61, 12);
	bc_box(62, 1, 83, 3);
	bc_box(62, 4, 83, 6);
	bc_box(62, 7, 83, 9);
	bc_box(62, 10, 83, 12);
	bc_box(1, 13, 47, 22);
	bc_box(48, 13, 83, 22);
	mt_gotoXY(27, 1);
	printf(" Memory ");
	mt_gotoXY(67, 1);
	printf(" Accumulator ");
	mt_gotoXY(63, 4);
	printf(" InstructionCounter ");
	mt_gotoXY(68, 7);
	printf(" Operation ");
	mt_gotoXY(70, 10);
	printf(" Flags ");
	mt_gotoXY(51, 13);
	printf(" Keys: ");
	mt_gotoXY(49, 14);
	printf("l - load");
	mt_gotoXY(49, 15);
	printf("s - save");
	mt_gotoXY(49, 16);
	printf("r - run");
	mt_gotoXY(49, 17);
	printf("t - step");
	mt_gotoXY(49, 18);
	printf("i - DEFAULT");
	mt_gotoXY(49, 19);
	printf("F5 - accumulator");
	mt_gotoXY(49, 20);
	printf("F6 - instrictionComputer\n");
	mt_gotoXY(50, 24);
	printf("\n");
	mt_gotoXY(1, 23);
	printf("\nInput/Output:\n");
	return 0;
}

int gr_drawBCH(int digit) {
	char str[4] = {0};
	long int BigDigit[2] = {0};
	bc_setBCH('+', BigDigit);
	bc_printbigchar(BigDigit, 2, 14, magenta, magenta);
	sprintf(str, "%.4X", digit);
	for(int it = 0, x = 11; it < 4; ++it, x += 9) {
		bc_setBCH(str[it], BigDigit);
		bc_printbigchar(BigDigit, x, 14, magenta, magenta);
	}
	return 0;
}

int gr_printInstCounter(void) {
	mt_gotoXY(71, 5);
	mt_setfgcolor(reset);
	int value = 0;
	sc_instCounterGet(&value);
	printf("%.4u", value);
	mt_gotoXY(1, 25);
	return 0;
}