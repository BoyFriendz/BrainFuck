#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

extern char result[8000] ={""};//全局变量，用于保存结果

//核心代码，结果输出
int BFexecute(char *code, char* input) {
    strcpy(result,"");//将全局变量result清零
    char *adr = (char *)malloc(strlen(code) * sizeof(char));//初始化数组
    //char Result[100] = { "" };
    char temp[2] = { "" };//临时保存一个字符
    int i, k, j;
    int n = 0;
    int ptr = 0;
    for (i = 0; i <(int)strlen(code); i++)
        adr[i] = 0;//数组元素清零
    //输入处理
    for (i = 0; i < (int)strlen(code); i++) {
        switch (code[i])
        {
        case '>':
            ++ptr;
            break;
        case '<':
            --ptr;
            if (ptr < 0)
                return 0;
            break;
        case '+':
            ++adr[ptr];
            break;
        case '-':
            --adr[ptr];
            break;
        case '.':
            //将结果加入result
            temp[0] = adr[ptr];
            strcat(result, temp);
            break;
        case ',':
            //取得输入
            adr[ptr] = input[n++];
            break;
        case '[':
            //括号匹配
            if (adr[ptr] == 0) {
                k = 1, j = 0;
                i++;
                while (k != j) {
                    if (code[i] == ']')
                        j++;
                    if (code[i] == '[')
                        k++;
                    i++;
                }
                i--;
            }
            break;
        case ']':
                    //括号匹配
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
        }
    }
    return 1;
}

//检查是否有逗号
int comma(char *code) {
    int comma = 0;
    for (int i = 0; i <(int) strlen(code); i++)
        if (code[i] == ',')
            comma++;
    return comma;
}

//检查括号是否匹配
int check(char *code) {
    int i, count = 0;
    for (i = 0; i < (int)strlen(code); i++) {
        if (code[i] == '[')
            count++;
        if (code[i] == ']')
            count--;
        if (count < 0)
            return 0;
    }
    if (count == 0)
        return 1;
    else
        return 0;
}


//判断输入是否错误
int illegalcount(char *code) {
    int Result = 0;
    for (int i = 0; i < (int)strlen(code); i++) {
        if (!(code[i] == ',' || code[i] == '.' || code[i] == '<' || code[i] == '>' ||
            code[i] == ' ' || code[i] == '\n' || code[i] == '+' || code[i] == '-' || code[i] == '['
            || code[i] == ']'))
            Result++;
    }
    return Result;
}
