#ifndef STACKS_H
#define STACKS_H

typedef struct operators {
    char oper;
    struct operators *prev;
} operators;

typedef struct operands {
    double operand;
    struct operands *prev;
} operands;

operators *init_operator(char oper);
operators *push_operator(operators *head, char oper);
operators *pop_operator(operators *head);
void destroy_operator(operators *head);

operands *init_operand(double integers);
operands *push_operand(operands *head, double integer);
operands *pop_operand(operands *head);
void destroy_operand(operands *head);

#endif