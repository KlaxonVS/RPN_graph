#include "stacks.h"

#include <stdio.h>
#include <stdlib.h>

operators *init_operator(char oper) {
    operators *new_node = malloc(sizeof(operators));
    if (new_node == NULL) {
        printf("Memory ERR");
        exit(1);
    }
    new_node->oper = oper;
    new_node->prev = NULL;

    return new_node;
}

operators *push_operator(operators *head, char oper) {
    operators *new_node = init_operator(oper);
    new_node->prev = head;
    return new_node;
}

operators *pop_operator(operators *head) {
    operators *temp = head->prev;
    free(head);
    return temp;
}

void destroy_operator(operators *head) {
    while (head->prev) {
        operators *temp = head->prev;
        free(head);
        head = temp;
    }
    free(head);
}

operands *init_operand(double operand) {
    operands *new_node = malloc(sizeof(operands));
    if (new_node == NULL) {
        printf("Memory ERR");
        exit(1);
    }
    new_node->operand = operand;
    new_node->prev = NULL;

    return new_node;
}
operands *push_operand(operands *head, double integer) {
    operands *new_node = init_operand(integer);
    new_node->prev = head;
    return new_node;
}

operands *pop_operand(operands *head) {
    operands *temp = head->prev;
    free(head);
    return temp;
}

void destroy_operand(operands *head) {
    while (head->prev) {
        operands *temp = head->prev;
        free(head);
        head = temp;
    }
    free(head);
}