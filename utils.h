#ifndef UTILS_H
#define UTILS_H

#include "stacks.h"

void oper_replace(char *string);
void replacer(char *string, char *to_replace, char *replacer);
operands *get_operands(char *string, double x);
int is_end(char symbol);
int is_allowed(char *string);
int in_symbols(char symbol);
int is_operator(char c);
int is_geom_operator_or_l_parenthesis(char c);
int is_right_parenthesis(char c);
int is_digit(char c);
int get_order(char oper);
double calc(char oper, double operand1, double operand2);
double calc_geom(char oper, double res);

#endif