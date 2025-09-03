#ifndef MUTEX_H
#define MUTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "global.h"

void *threadFuncMutex(void* rank);

typedef struct mutex_data{

    // Mutex data structure
    pthread_mutex_t mutex;       // Mutex protecting the entire linked list
    list_node *head;           // Pointer to linked list head

    int total_operations;        // Total number of operations

    int mMember;             // Number of Member operations to perform
    int mInsert;             // Number of Insert operations to perform
    int mDelete;             // Number of Delete operations to perform

    int memberOp_count; // Progress counter for performed Member ops
    int insertOp_count; // Progress counter for performed Insert ops
    int deleteOp_count; // Progress counter for performed Delete ops
    int totalOp_count;  // Progress counter for all ops

} mutex_data;

// mutex execution signature
unsigned long mutexExecution(int total_operations, int member_frac, int insert_frac, int delete_frac, int thread_count);

#endif