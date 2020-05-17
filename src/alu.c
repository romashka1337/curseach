#include "alu.h"

int alu_read(int adress) {
	int value = 0;
	scanf("%d", &value);
	int temp = 0;
	temp = sc_memorySet(adress, value);
	if (temp) return -1;
	return 0;
}

int alu_write(int adress) {
	int value = 0;
	int temp = 0;
	temp = sc_memoryGet(adress, &value);
	if (temp) return -1;
	printf("%.4X", value);
	return 0;
}

int alu_load(int adress) {
	int value = 0;
	int temp = 0;
	temp = sc_memoryGet(adress, &value);
	if (temp) return -1;
	sc_accumulatorSet(value);
	return 0;
}

int alu_store(int adress) {
	int value = 0;
	sc_accumulatorGet(&value);
	int temp = 0;
	temp = sc_memorySet(adress, value);
	if (temp) return -1;
	return 0;
}

int alu_add(int adress) {
	int value = 0, accum_value = 0;
	sc_memoryGet(adress, &value);
	sc_accumulatorGet(&accum_value);
	accum_value += value;
	if(accum_value <= 0x3FFF && accum_value >= -0x3FFF) {
		sc_regSet(MEMORY_OVERFLOW, 1);
		return -1;
	}
	sc_accumulatorSet(accum_value);
	return 0;
}

int alu_sub(int adress) {
	int value = 0, accum_value = 0;
	sc_memoryGet(adress, &value);
	sc_accumulatorGet(&accum_value);
	accum_value -= value;
	if(accum_value <= 0x3FFF && accum_value >= -0x3FFF) {
		sc_regSet(MEMORY_OVERFLOW, 1);
		return -1;
	}
	sc_accumulatorSet(accum_value);
	return 0;
}

int alu_divide(int adress) {
	int value = 0, accum_value = 0;
	sc_memoryGet(adress, &value);
	sc_accumulatorGet(&accum_value);
	if (value == 0) {
		sc_regSet(DIVISION_ERROR_BY_0, 1);
		return -1;
	}
	accum_value /= value;
	if(accum_value <= 0x3FFF && accum_value >= -0x3FFF) {
		sc_regSet(MEMORY_OVERFLOW, 1);
		return -1;
	}
	sc_accumulatorSet(accum_value);
	return 0;
}

int alu_multiply(int adress) {
	int value = 0, accum_value = 0;
	sc_memoryGet(adress, &value);
	sc_accumulatorGet(&accum_value);
	accum_value *= value;
	if(accum_value <= 0x3FFF && accum_value >= -0x3FFF) {
		sc_regSet(MEMORY_OVERFLOW, 1);
		return -1;
	}
	sc_accumulatorSet(accum_value);
	return 0;
}

int alu_jump(int adress) {
	sc_paintSet(adress);
	return 0;
}

int alu_jneg(int adress) {
	int value = 0;
	sc_accumulatorGet(&value);
	if (value < 0) sc_paintSet(adress);
	return 0;
}

int alu_jz(int adress) {
	int value = 0;
	sc_accumulatorGet(&value);
	if (value == 0) sc_paintSet(adress);
	return 0;
}

int alu_halt() {
	return 0;
}

int alu_rcr(int adress) {
	int value = 0, temp = 1;
	sc_memoryGet(adress, &value);
	temp = value | 1;
	temp = temp << 14;
	value = value >> 1;
	value = value | temp;
	sc_memorySet(adress, value);
	return 0;
}

int alu_alu(int command, int operand) {
	int temp = 0;
	switch (command) {
		case 0x30: temp = alu_add(operand); if (temp) return -1; break;
		case 0x31: temp = alu_sub(operand); if (temp) return -1; break;
		case 0x32: temp = alu_divide(operand); if (temp) return -1; break;
		case 0x33: temp = alu_multiply(operand); if (temp) return -1; break;
	}
	return 0;
}

int alu_cu() {
	int value = 0, command = 0, operand = 0, temp = 0, ram = 0;
	sc_instCounterGet(&value);
	sc_memoryGet(value, &ram);
	temp = sc_commandDecode(ram, &command, &operand);
	if (temp) return -1;
	switch (command) {
		case 0x10: temp = alu_read(operand); if (temp) return -1; break;
		case 0x11: temp = alu_write(operand); if (temp) return -1; break;
		case 0x20: temp = alu_load(operand); if (temp) return -1; break;
		case 0x21: temp = alu_store(operand); if (temp) return -1; break;
		case 0x30: temp = alu_alu(command, operand); if (temp) return -1; break;
		case 0x31: temp = alu_alu(command, operand); if (temp) return -1; break;
		case 0x32: temp = alu_alu(command, operand); if (temp) return -1; break;
		case 0x33: temp = alu_alu(command, operand); if (temp) return -1; break;
		case 0x40: temp = alu_jump(operand); if (temp) return -1; break;
		case 0x41: temp = alu_jneg(operand); if (temp) return -1; break;
		case 0x42: temp = alu_jz(operand); if (temp) return -1; break;
		case 0x43: temp = alu_halt(); if (temp) return -1; break;
		case 0x63: temp = alu_rcr(operand); if (temp) return -1; break;
	}
	switch (command) {
		case 0x40: temp = operand - value; break;
		case 0x41: temp = operand - value; break;
		case 0x42: temp = operand - value; break;
		default: temp = 1; break;
	}
	sc_instCounterGet(&value);
	sc_instCounterSet(value + temp);
	return 0;
}