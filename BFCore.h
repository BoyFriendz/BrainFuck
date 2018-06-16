#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

char result[100] = { "" };

void bfexecute(char *code, char *input) {
        strcpy(result,"");
	char *adr = (char *)malloc(strlen(code) * sizeof(char));
	char temp[2] = { "" };
	int i, k, j;
	int n = 0;
	int ptr = 0;
	int illegalinput = 0;
	for (i = 0; i <(int)strlen(code); i++)
		adr[i] = 0;
	for (i = 0; i < (int)strlen(code); i++) {
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
			temp[0] = adr[ptr];
			strcat(result, temp);
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
		//Sleep(1);
	}
}

int comma(char *code) {
	int comma = 0;
        for (int i = 0; i <(int)strlen(code); i++)
		if (code[i] == ',')
			comma++;
	return comma;
}

int check(char *code) {
	int i, result = 0;
        for (i = 0; i < (int)strlen(code); i++) {
		if (code[i] == '[') {
			while (code[i] != ']') {
				if (code[i] == '[')
					result++;
                                i++;
			}
                        while (code[i] == '['&&i < (int)strlen(code)) {
				if (code[i] == ']')
					result--;
                                i++;
			}
			if (result != 0)
				return 0;
		}
	}
	return 1;
}

int illegalcount(char *code) {
	int result = 0;
	for (int i = 0; i < (int)strlen(code); i++) {
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
	for (int i = 0; i < (int)strlen(code); i++) {
		if (code[i] == '[')
			box++;
		if (code[i] == ']')
			box--;
		if (box < memory)
			return 0;
	}
	return 1;
}
