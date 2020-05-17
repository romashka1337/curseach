#include "sc.h"

int sc_regInit(void) {
	register_flag = 0;
	return 0;
}

int sc_regSet(int reg, int value) {
	if ((reg <= CODE_ERROR) && (reg >= MEMORY_OVERFLOW)) {
		if (value == 1) {
			register_flag = register_flag | (value << reg);
			return 0;
		} else if (value == 0) {
			register_flag = register_flag & (~(1 << reg));
			return 0;
		}
	}
	return 1;
}

int sc_regGet(int reg, int *value) {
	if ((reg <= CODE_ERROR) && (reg >= MEMORY_OVERFLOW)) {
		(*value) = (register_flag >> reg) & 1;
		return 0;
	}
	return 1;
}

int sc_memoryInit() {
	if (RAM != NULL) {
		for (int it = 0; it < 100; ++it) {
			RAM[it] = 0;
	   }
	   return 0;
	} else {
		return 1;
	}
}

int sc_memorySet(int address, int value) {
	if (RAM != NULL) {
		if (address >= 0 && address <= 99) {
			RAM[address] = value;
			return 0;
		} else {
			sc_regSet(BORDER_OVERLOAD_ERROR, 1);
			return 1;
		}
	} else {
		return 1;
	}
}

int sc_memoryGet(int address, int *value) {
	if (RAM != NULL) {
		if (address >= 0 && address <= 99) {
			 (*value) = RAM[address];
			 return 0;
		} else {
			sc_regSet(BORDER_OVERLOAD_ERROR, 1);
			return 1;
		}
	} else {
		return 1;
	}
}

int sc_memorySave(char *filename) {
	FILE *save = NULL;
	save = fopen(filename, "wb");
	if (save == NULL) {
		return 1;
	}
	fwrite(&RAM, sizeof(int), 100, save);
	fclose(save);
	return 0;
}

int sc_memoryLoad(char *filename){
	if (RAM != NULL) {
		FILE *load = NULL;
		load = fopen(filename, "rb");
		if (load == NULL) {
			return 1;
		}
		int loadRam[100];
		fread(loadRam, sizeof(int), 100, load);
		fclose(load);
		for (int it = 0; it < 100; ++it) {
			RAM[it] = loadRam[it];
		}
		return 0;
	} else {
	   return 1;
	}
}


int sc_commandEncode(int command, int operand, int *value) {
	if ((command <= 128) && (command >= 0) && (operand <= 128) && (operand >= 0)) {
		if ((command >= 0x10 && command <= 0x11) || (command >= 0x20 && command <= 0x21) || (command >= 0x30 && command <= 0x33) || (command >= 0x40 && command <= 0x43) || (command >= 0x63 && command <= 0x63)) {
			*value = (command << 7) + operand;
			*value = *value & (~(1 << 14));
			return 0;
		} else {
			sc_regSet(CODE_ERROR, 1);
			return 1;
		}
	}
	sc_regSet(BORDER_OVERLOAD_ERROR, 1);
	return 1;
}

int sc_commandDecode(int value, int *command, int *operand) {
	int temp = value;
	if (((value >> 14) & (0x1)) != 0) {
		sc_regSet(IGNORING_TACT_PULSES, 1);
		sc_regSet(CODE_ERROR, 1);
		return 1;
	}
	value = temp;
	value = (value >> 7);
	*command = value;
	value = temp;
	value = value & ((1 << 6) - 1);
	*operand = value;
	return 0;
}

int sc_instCounterGet(int* value) {
	*value = instCounter;
	return 0;
}

int sc_instCounterSet(int value) {
	if (value >= 100 || value <= -1) {
		sc_regSet(MEMORY_OVERFLOW, 1);
		return -1;
	}
	instCounter = value;
	return 0;
}

int sc_accumulatorGet(int* value) {
	*value = accumulator;
	return 0;
}

int sc_accumulatorSet(int value) {
	if (value >= 0xFFFF || value <= -0xFFFF) {
		sc_regSet(MEMORY_OVERFLOW, 1);
		return -1;
	}
	accumulator = value;
	return 0;
}

int sc_paintGet(int* value) {
	*value = paintCount;
	return 0;
}

int sc_paintSet(int value) {
	if (value >= 0xFFFF || value <= -0xFFFF) {
		sc_regSet(MEMORY_OVERFLOW, 1);
		return -1;
	}
	paintCount = value;
	return 0;
}