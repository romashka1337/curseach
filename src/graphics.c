#include "graphics.h"

int gr_printMemory(int number) {
	for (int it = 0, row = 2; it < 100;) {
		mt_gotoXY(2, row);
		for (int jt = 0; jt < 10; jt++, it++) {
			int Memory = 0;
			sc_memoryGet(it, &Memory);
			int command = 0, operand = 0;
			sc_commandDecode(Memory, &command, &operand);
			if (it == number) {
				mt_setbgcolor(yellow);
				if(Memory <= 0x3FFF && Memory >= -0x3FFF) printf("+%.2X%.2X", command, operand);
				else printf("%.2X%.2X", command, operand);
				mt_setbgcolor(reset);
				printf(" ");
			} else {
				mt_setbgcolor(reset);
				if(Memory <= 0x3FFF && Memory >= -0x3FFF) printf("+%.2X%.2X", command, operand);
				else printf("%.2X%.2X", command, operand);
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
	int CheckBitRegister = 0;
	sc_regGet(0, &CheckBitRegister);
	if (CheckBitRegister == 1) {
		mt_setfgcolor(yellow);
		printf("M ");
		mt_setfgcolor(reset);
	} else {
		mt_setfgcolor(reset);
		printf("M ");
		mt_setfgcolor(reset);
	}
	sc_regGet(1, &CheckBitRegister);
	if (CheckBitRegister == 1) {
		mt_setfgcolor(yellow);
		printf("0 ");
		mt_setfgcolor(reset);
	} else {
		mt_setfgcolor(reset);
		printf("0 ");
		mt_setfgcolor(reset);
	}
	sc_regGet(2, &CheckBitRegister);
	if (CheckBitRegister == 1) {
		mt_setfgcolor(yellow);
		printf("B ");
		mt_setfgcolor(reset);
	} else {
		mt_setfgcolor(reset);
		printf("B ");
		mt_setfgcolor(reset);
	}
	sc_regGet(3, &CheckBitRegister);
	if (CheckBitRegister == 1) {
		mt_setfgcolor(yellow);
		printf("I ");
		mt_setfgcolor(reset);
	} else {
		mt_setfgcolor(reset);
		printf("I ");
		mt_setfgcolor(reset);
	}
	sc_regGet(4, &CheckBitRegister);
	if (CheckBitRegister == 1) {
		mt_setfgcolor(yellow);
		printf("C ");
		mt_setfgcolor(reset);
	} else {
		mt_setfgcolor(reset);
		printf("C ");
		mt_setfgcolor(reset);
	}
	return 0;
}

int gr_interface() {
	mt_clrscr();
	int temp = 0;
	sc_instCounterGet(&temp);
	gr_printMemory(temp);
	int m = 0;
	sc_memoryGet(temp, &m);
	gr_drawBCH(m);
	gr_printAccum();
	gr_printInstCounter();
	gr_printOperation();
	gr_printRegFlag();
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
	printf("F6 - instrictionCounter\n");
	mt_gotoXY(50, 24);
	printf("\n");
	mt_gotoXY(1, 23);
	printf("\nInput/Output:\n");
	return 0;
}

int gr_drawBCH(int digit) {
	char str[2] = {0}, str1[2] = {0}, str2[2] = {0};
	long int BigDigit[2] = {0};
	if(digit <= 0x3FFF && digit >= -0x3FFF) {
		bc_setBCH('+', BigDigit);
		bc_printbigchar(BigDigit, 2, 14, magenta, magenta);
		int command = 0, operand = 0;
		sc_commandDecode(digit, &command, &operand);
		sprintf(str1, "%.2X", command);
		sprintf(str2, "%.2X", operand);
		for(int it = 0, x = 11; it < 2; ++it, x += 9) {
			bc_setBCH(str1[it], BigDigit);
			bc_printbigchar(BigDigit, x, 14, magenta, magenta);
		}
		for(int it = 0, x = 29; it < 2; ++it, x += 9) {
			bc_setBCH(str2[it], BigDigit);
			bc_printbigchar(BigDigit, x, 14, magenta, magenta);
		}
	} else {
		sprintf(str, "%.4X", digit);
		for(int it = 0, x = 11; it < 4; ++it, x += 9) {
			bc_setBCH(str[it], BigDigit);
			bc_printbigchar(BigDigit, x, 14, magenta, magenta);
		}
	}
	return 0;
}

int gr_printOperation(void) {
	mt_gotoXY(71, 8);
	int value = 0, command = 0, operand = 0, temp = 0;
	sc_instCounterGet(&value);
	sc_memoryGet(value, &temp);
	sc_commandDecode(temp, &command, &operand);
	mt_setfgcolor(reset);
	printf("+%02X:%02X", command, operand);
	mt_gotoXY(1, 25);
	return 0;
}

int gr_printInstCounter(void) {
	mt_gotoXY(73, 5);
	mt_setfgcolor(reset);
	int value = 0;
	sc_instCounterGet(&value);
	printf("%.2d", value);
	mt_gotoXY(1, 25);
	return 0;
}

int gr_printAccum(void) {
	mt_gotoXY(71, 2);
	mt_setfgcolor(reset);
	int value = 0;
	sc_accumulatorGet(&value);
	if(value <= 0x3FFF && value >= -0x3FFF) printf("+%04X", value);
	else printf("%04X", value);
	mt_gotoXY(1, 25);
	return 0;
}

int gr_input() {
	int regime = 0;
	enum keys Key = Default;
	while (Key != Quit) {
		gr_interface();
		rk_readkey(&Key);
		int value = 0;
		sc_regGet(3, &value);
		if (value == 1) {
			switch (Key) {
				case Right: {
					int temp = 0;
					sc_paintGet(&temp);
					if (temp < 99) {
						temp++;
					} else {
						temp = 0;
					}
					sc_paintSet(temp);
					sc_instCounterSet(temp);
					break;
				}
				case Left: {
					int temp = 0;
					sc_paintGet(&temp);
					if (temp > 0) {
						temp--;
					} else {
						temp = 99;
					}
					sc_paintSet(temp);
					sc_instCounterSet(temp);
					break;
				}
				case Up: {
					int temp = 0;
					sc_paintGet(&temp);
					if (temp < 10) {
						temp += 90;
					} else {
						temp -= 10;
					}
					sc_paintSet(temp);
					sc_instCounterSet(temp);
					break;
				}
				case Down: {
					int temp = 0;
					sc_paintGet(&temp);
					if (temp > 89) {
						temp -= 90;
					} else {
						temp += 10;
					}
					sc_paintSet(temp);
					sc_instCounterSet(temp);
					break;
				}
				case Step: {
					alu_cu();
					break;
				}
				case Run: {
					sc_regSet(3, 0);
					alarm(1);
					break;
				}
				case PlusValue: {
					int ValuePLusRAM = 0;
					int temp = 0;
					sc_paintGet(&temp);
					sc_memoryGet(temp, &ValuePLusRAM);
					ValuePLusRAM++;
					sc_memorySet(temp, ValuePLusRAM);
					break;
				}
				case MinusValue: {
					int ValueMinusRAM = 0;
					int temp = 0;
					sc_paintGet(&temp);
					sc_memoryGet(temp, &ValueMinusRAM);
					if (ValueMinusRAM - 1 >= 0) {
						ValueMinusRAM--;
						sc_memorySet(temp, ValueMinusRAM);
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
				case Accumulator: {
					char acc[10];
					printf("\nEnter Accumulator: ");
					fgets(acc, 10, stdin);
					int acc_copy = 0;
					acc[strlen(acc) - 1] = '\0';
					if(strlen(acc) <= 5 && acc[0] == '+') {
						sscanf(acc + 1, "%04X", &acc_copy);
						sc_accumulatorSet(acc_copy);
					} else {
						printf("\nError");
						getchar();
					}
					break;
				}
				case InstructionCounter: {
					char ic[10];
					printf("\nEnter InstructionCounter: ");
					fgets(ic, 10, stdin);
					//getchar();
					int ic_copy = 0;
					ic[strlen(ic) - 1] = '\0';
					if(strlen(ic) <= 2) {
						sscanf(ic, "%02d", &ic_copy);
						sc_instCounterSet(ic_copy);
						sc_paintSet(ic_copy);
					} else {
						printf("\nError");
						getchar();
					}
					break;
				}
				case Load: {
					char in[5];
					printf("\nEnter filename:");
					fgets(in, 5, stdin);
					getchar();
					int value = 0;
					value = sc_memoryLoad(in);
					if (value) printf("\nError");
					break;
				}
				case Save: {
					char out[5];
					printf("\nEnter filename:");
					fgets(out, 5, stdin);
					getchar();
					int value = 0;
					value = sc_memorySave(out);
					if (value) printf("\nError");
					break;
				}
				case Reset: {
					sc_memoryInit();
					sc_accumulatorSet(0);
					sc_instCounterSet(0);
					sc_regSet(0, 0);
					sc_regSet(1, 0);
					sc_regSet(2, 0);
					sc_regSet(3, 1);
					sc_regSet(4, 0);
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
	return 0;
}
