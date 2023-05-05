#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stacks.h"
#include "utils.h"

double calc_expression(char *expression, double x) {
    operators *oper_stack = init_operator('$');
    operands *operand_stack = init_operand(0.0);

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '-' &&
            (i == 0 || (i > 1 && (is_operator(expression[i - 1]) ||
                                  is_geom_operator_or_l_parenthesis(expression[i - 1]))))) {
            if (expression[i + 1] == 'x') {
                operand_stack = push_operand(operand_stack, x * -1);
                i += 1;
            }
            if (is_digit(expression[i + 1])) {
                char num_s[strlen(expression)];
                int j = 0;
                num_s[j] = expression[i];
                j += 1;
                i += 1;
                while (!is_end(expression[i]) && i != (int)strlen(expression)) {
                    num_s[j++] = expression[i++];
                }
                double num;
                sscanf(num_s, "%lf", &num);
                operand_stack = push_operand(operand_stack, num * -1);
            }
        } else if (is_digit(expression[i])) {
            char num_s[strlen(expression)];
            int j = 0;
            num_s[j] = expression[i];
            j += 1;
            i += 1;
            while (!is_end(expression[i]) && i != (int)strlen(expression)) {
                num_s[j++] = expression[i++];
            }
            double num;
            sscanf(num_s, "%lf", &num);
            operand_stack = push_operand(operand_stack, num);
        } else if (expression[i] == 'x') {
            operand_stack = push_operand(operand_stack, x);
        } else if (is_operator(expression[i])) {
            if (oper_stack->oper == '$') {
                oper_stack = push_operator(oper_stack, expression[i]);
            } else if (get_order(expression[i]) <= get_order(oper_stack->oper)) {
                double operand2 = operand_stack->operand;
                operand_stack = pop_operand(operand_stack);
                double operand1 = operand_stack->operand;
                operand_stack = pop_operand(operand_stack);
                char operator= oper_stack->oper;
                double res = calc(operator, operand1, operand2);
                oper_stack = pop_operator(oper_stack);
                oper_stack = push_operator(oper_stack, expression[i]);
                operand_stack = push_operand(operand_stack, res);
            } else {
                oper_stack = push_operator(oper_stack, expression[i]);
            }
        }
        if (is_geom_operator_or_l_parenthesis(expression[i])) {
            oper_stack = push_operator(oper_stack, expression[i]);
        }
        if (is_right_parenthesis(expression[i])) {
            while (!is_geom_operator_or_l_parenthesis(oper_stack->oper)) {
                double operand2 = operand_stack->operand;
                operand_stack = pop_operand(operand_stack);
                double operand1 = operand_stack->operand;
                operand_stack = pop_operand(operand_stack);
                char operator= oper_stack->oper;
                oper_stack = pop_operator(oper_stack);
                double res = calc(operator, operand1, operand2);
                operand_stack = push_operand(operand_stack, res);
            }
            if (is_geom_operator_or_l_parenthesis(oper_stack->oper)) {
                double operand = operand_stack->operand;
                double result = calc_geom(oper_stack->oper, operand);
                operand_stack = pop_operand(operand_stack);
                operand_stack = push_operand(operand_stack, result);
                oper_stack = pop_operator(oper_stack);
            }
        }
    }
    while (oper_stack->oper != '$') {
        double operand2 = operand_stack->operand;
        operand_stack = pop_operand(operand_stack);
        double operand1 = operand_stack->operand;
        operand_stack = pop_operand(operand_stack);
        char operator= oper_stack->oper;
        oper_stack = pop_operator(oper_stack);
        double res = calc(operator, operand1, operand2);
        operand_stack = push_operand(operand_stack, res);
    }
    double result = operand_stack->operand;
    destroy_operand(operand_stack);
    destroy_operator(oper_stack);
    return result;
}
