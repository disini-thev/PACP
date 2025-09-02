#ifndef RWLOCK_H
#define RWLOCK_H

#include <pthread.h>

void * threadFuncRW(void * args);

typedef struct rw_lock_data{
    pthread_rwlock_t rwlock;
    pthread_mutex_t count_mutex;
    list_node *head;

    int m;
    int member_frac;
    int insert_frac;
    int delete_frac;

    int member_op_count;
    int insert_op_count;
    int delete_op_count;
    int total_op_count;

} rw_lock_data;

unsigned long readwriteExecution(int total_ops, 
    int member_frac, int insert_frac, int delete_frac, 
    int thread_count);

#endif