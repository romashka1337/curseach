#include "bc.h"

int bc_printA (char *str) {
	printf("\E(0%s\E(B", str);
	return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
	if (x1==0) x1=1;
	for (int CoordX = x1 + 1; CoordX < x2; CoordX++) {
		mt_gotoXY(CoordX, y1);
		bc_printA("r");   
	}
	for (int CoordY = y1 + 1; CoordY < y2; CoordY++) {
		mt_gotoXY(x1, CoordY);
		bc_printA("x");
	}
	for (int CoordX = x1 + 1; CoordX < x2; CoordX++) {
		mt_gotoXY(CoordX, y2);
		bc_printA("r");
	}
	for (int CoordY = y1 + 1; CoordY < y2; CoordY++) {
		mt_gotoXY(x2, CoordY);
		bc_printA("x");
	}
	mt_gotoXY(x1, y1);
	bc_printA("l");
	mt_gotoXY(x1, y2);
	bc_printA("m");
	mt_gotoXY(x2, y1);
	bc_printA("k");
	mt_gotoXY(x2, y2);
	bc_printA("j");
	return 0;
}

int bc_printbigchar(long int *a, int x, int y, enum colors colDig, enum colors colBG) {
	mt_setbgcolor(colDig);
	mt_setfgcolor(colBG);
	if (x < 0 || y < 0) {
		return -1;
	}
	mt_gotoXY(x, y);
	for (int i = 0; i < 2; i++) {
		for (int l = 0; l < 32;) {
			for (int j = 0; j < 8 && l < 32; j++, l++) {
				if ((a[i] >> (l)) & 0x1) {
					bc_printA("a");
				} else {
					bc_printA(" ");
				}
			}
			y++;
			mt_gotoXY(x,y);
		}
	}   
	mt_setbgcolor(reset);
	mt_setfgcolor(reset);
	return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int value) {
   if ((y >= 0 && y < 8) && (x >= 0 && x < 8)) {
		if (value == 1) {
			if (y < 4) {
				big[0] = big[0] | (1 << (8 * y + x));
			}
			if (y > 3) {
				y -= 4;
				big[1] = big[1] | (1 << (8 * y + x));
			}
		} else {
			if (value == 0) {
				if (y < 4) {
					big[0] = (~(1 << (8 * y + x))) & big[0];
				}
				if (y > 3) {
					y -= 4;
					big[1] = (~(1 << (8 * y + x))) & big[1];
				}
			}
		}
		return 0;
	} else {
		return -1;
	}
}

int bc_getbigcharpos(int *big, int x, int y, int *value) {
	if ((y >= 0 && y < 8) && (x >= 0 && x < 8)) {
			if (y < 4) {
				(*value) = (big[0] >> (y * 8 + x)) & 0x1;
			}
			if (y > 3) {
				y -= 4;
				(*value) = (big[1] >> (y * 8 + x)) & 0x1;
			}
		return 0;
	} else {
		return -1;
	}
}

int bc_bigcharwrite(int fd, int *big, int count) {
	int result;
	for (int i = 0; i < count; i++) {
		if ((result = write(fd, big, sizeof(int) * 2)) == -1)
			return -1;
	}
	return 0;
}
int bc_bigcharread(int fd, int *big, int need_count, int *count) {
	for (int i = 0; i < need_count; i++, *count++) {
		int result;
		if ((result = read(fd, big, sizeof(int) * 2)) == -1)
			return -1;
	}
	return 0;
}

int bc_setBCH(char s, long int *digit) {
	switch (s) {
		case '0': digit[0] = BCH.Zero[0]; digit[1] = BCH.Zero[1]; break;
		case '1': digit[0] = BCH.One[0]; digit[1] = BCH.One[1]; break;
		case '2': digit[0] = BCH.Two[0]; digit[1] = BCH.Two[1]; break;
		case '3': digit[0] = BCH.Three[0]; digit[1] = BCH.Three[1]; break;
		case '4': digit[0] = BCH.Four[0]; digit[1] = BCH.Four[1]; break;
		case '5': digit[0] = BCH.Five[0]; digit[1] = BCH.Five[1]; break;
		case '6': digit[0] = BCH.Six[0]; digit[1] = BCH.Six[1]; break;
		case '7': digit[0] = BCH.Seven[0]; digit[1] = BCH.Seven[1]; break;
		case '8': digit[0] = BCH.Eight[0]; digit[1] = BCH.Eight[1]; break;
		case '9': digit[0] = BCH.Nine[0]; digit[1] = BCH.Nine[1]; break;
		case '+': digit[0] = BCH.Plus[0]; digit[1] = BCH.Plus[1]; break;
		case '-': digit[0] = BCH.Minus[0]; digit[1] = BCH.Minus[1]; break;
		default: break;
	}
	return 0;
}