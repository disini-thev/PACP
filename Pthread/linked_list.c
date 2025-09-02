#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

// expects sorted linked list, returns 1 if value is found, 0 otherwise
int Member(int value, list_node* head_p){
    list_node* curr_p = head_p;
    while (curr_p != NULL && curr_p->data < value){
        curr_p = curr_p->next;
    }
    if (curr_p == NULL || curr_p->data > value){
        return 0;
    }
    return 1;
}

//inserts a node with the given value - if already doesn't exist
int Insert(int value, list_node** head_pp){
    list_node * curr_p = *head_pp; //dereference to get the pointer to head
    list_node * prev_p = NULL;
    list_node * temp_p;

    //loop until the correct place
    while (curr_p !=NULL && curr_p->data < value){
        prev_p = curr_p;
        curr_p = curr_p->next;
    }
    //insert or skip(if exists)
    if (curr_p == NULL || curr_p->data > value){
        temp_p = malloc(sizeof(list_node));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (prev_p != NULL){
            prev_p->next = temp_p;
        }
        else{
            *head_pp = temp_p; //change the pointer to the head to the new one
        }
        return 1;
    }else{
        return 0; // value exists
    }
}

//deletes a node having a given value
int Delete(int value, list_node** head_pp){
    list_node* curr_p = *head_pp;
    list_node* prev_p = NULL;

    //loop until data is less than the value
    while (curr_p != NULL && curr_p->data < value){
        prev_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p==NULL || curr_p->data != value){
        return 0; // value is not in the list
    }
    else{ //if curr_p not null and data == value
        if (prev_p == NULL){ //curr_p is the first node, it will be deleted
            *head_pp = curr_p->next;
        }
        else{
            prev_p->next = curr_p->next;
        }
        free(curr_p);
        return 1;
    }
}

//destroys the linkedlist
void Destructor(list_node* head_p){
    list_node * curr_p = head_p;
    list_node * temp_p = NULL; //used to free the space

    while(curr_p!= NULL){
        temp_p = curr_p;
        curr_p = curr_p->next;
        free(temp_p);
    }
}

void PrintList(list_node * head_p){
    list_node * curr_p = head_p;
    while(curr_p!=NULL){
        printf("Node : %d \n",curr_p->data);
        curr_p = curr_p->next;
    }
}