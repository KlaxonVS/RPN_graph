#include "utils.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stacks.h"

void oper_replace(char *string) {
    replacer(string, "ln(", "L");
    replacer(string, "cos(", "C");
    replacer(string, "sin(", "S");
    replacer(string, "tan(", "T");
    replacer(string, "ctg(", "H");
    replacer(string, "sqrt(", "R");
}

void replacer(char *string, char *to_replace, char *replacer) {
    char *pointer;
    while ((pointer = strstr(string, to_replace))) {
        strcpy(pointer, replacer);
        strcpy(pointer + 1, pointer + strlen(to_replace));
    }
}

int is_end(char symbol) {
    char symbols[] = {'(', ')', 'C', 'S', 'T', 'H', 'L', 'R', '*', '/', '+', '-', '\0'};
    for (int i = 0; symbols[i] != '\0'; i++) {
        if (symbols[i] == symbol) return 1;
    }
    return 0;
}

int in_symbols(char symbol) {
    int check = 0;
    char symbols[] = {'x', '(', ')', 'C', 'S', 'T', 'H', 'L', 'R', '*', '/', '+', '-', '.', '\0'};
    for (int j = 0; symbols[j] != '\0'; j++) {
        if (symbols[j] == symbol) check += 1;
    }
    return check;
}

int is_allowed(char *string) {
    int check = 0;
    for (int i = 0; i < (int)strlen(string); i++) {
        if (isdigit(string[i])) continue;
        if (in_symbols(string[i]) == 1) continue;
        check += 1;
    }
    return check;
}

int is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
int is_geom_operator_or_l_parenthesis(char c) {
    return c == 'S' || c == 'C' || c == 'T' || c == 'G' || c == 'R' || c == 'L' || c == '(';
}

int is_right_parenthesis(char c) { return c == ')'; }

int is_digit(char c) { return c >= '0' && c <= '9'; }

int get_order(char oper) {
    if (oper == '*' || oper == '/') {
        return 2;
    } else if (oper == '+' || oper == '-') {
        return 1;
    } else {
        return 0;
    }
}

double calc(char oper, double operand1, double operand2) {
    switch (oper) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        default:
            return 0;
    }
}

double calc_geom(char oper, double res) {
    switch (oper) {
        case 'S':
            return sin(res);
        case 'C':
            return cos(res);
        case 'T':
            return tan(res);
        case 'H':
            return 1 / tan(res);
        case 'R':
            return sqrt(res);
        case 'L':
            return log(res);
        default:
            return res;
    }
}
