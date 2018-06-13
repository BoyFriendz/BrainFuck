#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int bfcore(char *code,char *input) {
	int *adr = (int *)malloc(strlen(code)* sizeof(int));
	int i, k, j;
	int n = 0;
	int ptr = 0;
	int illegalinput = 0;
	for (i = 0; i <1000; i++)
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