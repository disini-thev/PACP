#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "linked_list.h"
#include "serial.h"
#include "global.h"

unsigned long serialExecution(int total_operations, int mMember, int mInsert, int mDelete) {

    //initialize the linked list

    list_node *head = NULL;

    int n = 1000;
    int count = 0;

    while ( count < n) {
        Insert(rand()%MAX, &head);
        count++;

    }

    //get the start time    
    struct timeval start, end;

    int totalOp_count = 0, memberOp_count = 0, insertOp_count = 0, deleteOp_count = 0;

    gettimeofday(&start, NULL);

    while (totalOp_count < total_operations){

        int rand_value = rand() % MAX;
        int operation_number = rand() % 3; // generate a random number between 0 and 2  ex:{0,1,2}

        if (operation_number == 0 && insertOp_count < mInsert){
            Insert(rand_value, &head);
            insertOp_count++;
            totalOp_count++;
        }
        else if(operation_number == 1 && memberOp_count < mMember){
            Member(rand_value, head);
            memberOp_count++;
            totalOp_count++;
        }
        else if(deleteOp_count < mDelete){
            Delete(rand_value, &head);
            deleteOp_count++;
            totalOp_count++;
        }
    }

    gettimeofday(&end, NULL);

    unsigned long exec_time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec; 

    Destructor(head);
    printf("Serial run complete\n");
    return exec_time;

}