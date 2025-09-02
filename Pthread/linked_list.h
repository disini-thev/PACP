#ifndef SERIAL_H
#define SERIAL_H

typedef struct list_node {
    int data;
    struct list_node *next;
} list_node;

//linked list function signatures member, insert, delete, destructor, print
// _p for pointer to head - for reading files, _pp for pointer to pointer to head
int Member(int value, list_node *head_p);
int Insert(int value, list_node **head_pp);
int Delete(int value, list_node **head_pp);

void Destructor(list_node *head_pp);
void PrintList(list_node *head_p);

#endif