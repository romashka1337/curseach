#include <stdio.h>
#include <string.h>

int ram[100];

int commandEncode(int command, int operand, int *value) {
	if ((command >= 0x10 && command <= 0x11) || (command >= 0x20 && command <= 0x21) || (command >= 0x30 && command <= 0x33) || (command >= 0x40 && command <= 0x43) || (command >= 0x63 && command <= 0x63)) {
		*value = (command << 7) + operand;
		*value = *value & (~(1 << 14));
		return 0;
	} else {
		return 1;
	};
}

int main(int argc, char **argv) {
	for (int it = 0; it < 100; ++it) ram[it] = 0;
	FILE *in;
	char* iFileName = argv[1];
	in = fopen(iFileName, "r");
	char line[256];
	while (fgets(line, sizeof(line), in)) {
		int a = 0, c = 0;
		char b[8];
		sscanf(line, "%d %s %d", &a, b, &c);
		int command = 0, operand = c, value = 0;
		if (strcmp(b, "READ") == 0) {
			command = 0x10;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "WRITE") == 0)  {
			command = 0x11;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "LOAD") == 0) {
			command = 0x20;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "STORE") == 0)  {
			command = 0x21;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "ADD") == 0) {
			command = 0x30;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "SUB") == 0) {
			command = 0x31;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "DIVIDE") == 0)  {
			command = 0x32;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "MUL") == 0) {
			command = 0x33;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "JUMP") == 0) {
			command = 0x40;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "JNEG") == 0) {
			command = 0x41;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "JZ") == 0){
			command = 0x42;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "HALT") == 0) {
			command = 0x43;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "RCR") == 0) {
			command = 0x63;
			commandEncode(command, operand, &value);
			ram[a] = value;
		}
		if (strcmp(b, "=") == 0) {
			ram[a] = c;
		}
		printf("%d %s %d %04X\n", a, b, c, value);
	}
	fclose(in);
	FILE *out;
	char* oFileName = argv[2];
	out = fopen(oFileName, "w+b");
	if (out == NULL) {
		return 1;
	}
	fwrite(&ram, sizeof(int), 100, out);
	fclose(out);
	return 0;
}

