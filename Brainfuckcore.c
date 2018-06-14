#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

int bfexecute(char *code,char *input) {
	int *adr = (int *)malloc(strlen(code)* sizeof(int));
	int i, k, j;
	int n = 0;
	int ptr = 0;
	int illegalinput = 0;
	for (i = 0; i <strlen(code); i++)
		adr[i] = 0;
	for (i = 0; i < strlen(code); i++) {
		switch (code[i])
		{
		case '>':
			++ptr;
			break;
		case '<':
			--ptr;
			break;
		case '+':
			++adr[ptr];
			break;
		case '-':
			--adr[ptr];
			break;
		case '.':
			putchar(adr[ptr]);
			break;
		case ',':
			adr[ptr] = input[n++];
			break;
		case '[':
			k = 0, j = 0;
			if (adr[ptr] == 0) {
				k = 1, j = 0;
				i++;
				while (k != j) {
					if (code[i] == ']')
						k++;
					if (code[i] == '[')
						j++;
					i++;
				}
				i--;
			}
			break;
		case ']':
			if (adr[ptr] != 0) {
				k = 1, j = 0;
				i--;
				while (k != j) {
					if (code[i] == ']')
						k++;
					if (code[i] == '[')
						j++;
					i--;
				}
				i++;
			}
		break;
		default:
			illegalinput++;
			break;
		}
		Sleep(1);
	}
}

int comma(char *code) {
	int comma = 0;
	for (int i = 0; i < strlen(code); i++)
		if (code[i] == ',')
			comma++;
}

int check(char *code) {
	int i, result = 0;
	for (i = 0; i < strlen(code); i++) {
		if (code[i] == '[') {
			while (code[i] != ']') {
				if (code[i] == '[')
					result++;
			}
			while (code[i] == '['&&i<strlen(code)) {
				if (code[i] == ']')
					result--;
			}
			if (result != 0)
				return 0;
		}
	}
	return 1;
}

int iscode(char c) {
	if (c != ' ' || c != '\n')
		return 1;
	return 0;
}

int illegalcount(char *code) {
	int result = 0;
	for (int i = 0; i < strlen(code); i++) {
		if (!(code[i] == ',' || code[i] == '.' || code[i] == '<' || code[i] == '>' ||
			code[i] == ' ' || code[i] == '\n' || code[i] == '+' || code[i] == '-' || code[i] == '['
			|| code[i] == ']'))
			result++;
	}
	return result;
}

int boundry(char *code) {
	char memory[10] = { 0 };
	char *box = memory;
	for (int i = 0; i < strlen(code); i++) {
		if (code[i] == '[')
			box++;
		if (code[i] == ']')
			box--;
		if (box < memory)
			return 0;
	}
	return 1;
}

int onestep(char c,int ptr,char **adr,int i) {
	int k, j;
	switch (c)
	{
	case '>':
		++ptr;
		break;
	case '<':
		--ptr;
		break;
	case '+':
		++*adr[ptr];
		break;
	case '-':
		--*adr[ptr];
		break;
	case '.':
		putchar(*adr[ptr]);
		break;
	case ',':
		*adr[ptr] = getchar();
		break;
	case '[':
		k = 0, j = 0;
		if (*adr[ptr] == 0) {
			k = 1, j = 0;
			i++;
			while (k != j) {
				if (c == ']')
					k++;
				if (c == '[')
					j++;
				i++;
			}
			i--;
		}
		break;
	case ']':
		if (adr[ptr] != 0) {
			k = 1, j = 0;
			i--;
			while (k != j) {
				if (c == ']')
					k++;
				if (c == '[')
					j++;
				i--;
			}
			i++;
		}
		break;
	default:
		break;
	}
}

int main() {
	char *code = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
	char input[27] = { 0 };
	int i;
	for (i = 0; i < 26; i++) {
		input[i] = i + 'a';
	}
	input[1] = '\n';
	bfexecute(code, input);
}