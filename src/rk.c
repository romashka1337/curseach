#include "rk.h"

struct termios savetty;


int rk_readkey(enum keys *Key) {
	char str[8] = {0};
	read(0, str, 8);
	if (str[0] == 'q')
		(*Key) = Quit;
	else if (str[0] == 'l')
		(*Key) = Load;
	else if (str[0] == 's')
		(*Key) = Save;
	else if (str[0] == 'r')
		(*Key) = Run;
	else if (str[0] == 't')
		(*Key) = Step;
	else if (str[0] == 'i')
		(*Key) = Reset;
	else if (strcmp(str, "\033[15~") == 0)
		(*Key) = Accumulator;
	else if (strcmp(str, "\033[17~") == 0)
		(*Key) = InstructionComputer;
	else if (str[0] == 'd')
		(*Key) = Right;
	else if (str[0] == 'a')
		(*Key) = Left;
	else if (str[0] == '+')
		(*Key) = PlusValue;
	else if (str[0] == '-')
		(*Key) = MinusValue;
	else if (str[0] == '0')
		(*Key) = Register0;
	else if (str[0] == '1')
		(*Key) = Register1;
	else if (str[0] == '2')
		(*Key) = Register2;
	else if (str[0] == '3')
		(*Key) = Register3;
	else if (str[0] == '4')
		(*Key) = Register4;
	else if (str[0] == '*')
		(*Key) = Regime;
	else if (str[0] == '`')
		(*Key) = Restore;
	return 0;
}

int rk_mytermsave(void) {
	struct termios tty;
	if (tcgetattr(0, &tty) == -1) {
		return 1;
	} else {
		savetty = tty;
		return 0;
	} 
}

int rk_mytermrestore(void) {
	if (tcsetattr(0, TCSANOW, &savetty) == -1) {
		return 1;
	} else {
		return 0;
	}
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint) {
	struct termios Settings;
	rk_mytermsave();
	Settings = savetty;
	if (regime == 1) {
		Settings.c_lflag &= (~ICANON);
		if (sigint == 1) {
			Settings.c_lflag &= (~ISIG);
		} else if (sigint == 0) {
			Settings.c_lflag |= ISIG;
		}
		if (echo == 1) {
			Settings.c_lflag &= (~ECHO);
		} else if (echo == 0) {
			Settings.c_lflag |= ECHO;
		}
		Settings.c_cc[VMIN] = vmin;
		Settings.c_cc[VTIME] = vtime;
	} else if (regime == 0) {
		Settings.c_lflag |= (ICANON | ECHO);
	}
	tcsetattr(0, TCSANOW, &Settings);
	return 0;
}