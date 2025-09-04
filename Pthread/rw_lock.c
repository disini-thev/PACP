#include "rw_lock.h"
#include "linked_list.h"
#include "global.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

unsigned long readwriteExecution(int total_ops,
                                 int member_frac, int insert_frac, int delete_frac,
                                 int thread_count)
{

    rw_lock_data thread_data; // initialize
    // populating threa_data
    //  rw_lock, count_mutex
    thread_data.head = NULL;

    thread_data.m = total_ops;
    thread_data.member_frac = member_frac;
    thread_data.insert_frac = insert_frac;
    thread_data.delete_frac = delete_frac;

    thread_data.total_op_count = 0;
    thread_data.member_op_count = 0;
    thread_data.insert_op_count = 0;
    thread_data.delete_op_count = 0;

    // Initializing a linkedlist with 1000 random nodes
    int n = 1000;  // number of nodes in the linked list
    int nodes = 0; // do the operations until

    while (nodes < n)
    {
        Insert(rand() % MAX, &thread_data.head);
        nodes++;
    }

    // initialize rw_lock and count_mutex
    pthread_rwlock_init(&thread_data.rwlock, NULL);
    pthread_mutex_init(&thread_data.count_mutex, NULL);

    pthread_t *thread_handles = malloc(thread_count * sizeof(pthread_t));

    // Threading and time calculation
    struct timeval start, end;  // from sys.time.h
    gettimeofday(&start, NULL); // start time

    for (long i = 0; i < thread_count; i++)
    {
        pthread_create(&thread_handles[i], NULL, threadFuncRW, (void *)&thread_data);
    }

    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(thread_handles[i], NULL);
    }
    free(thread_handles);
    gettimeofday(&end, NULL); // end time

    // Destroy locks and threads
    pthread_rwlock_destroy(&thread_data.rwlock);
    pthread_mutex_destroy(&thread_data.count_mutex);

    unsigned long time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec; // tv_sec = seconds since epoch, //tv_usec = microseconds within that second

    Destructor(thread_data.head);
    // printf("RW run complete\n");
    return time;
}

void *threadFuncRW(void *args)
{
    rw_lock_data *thread_data = args;

    while (thread_data->total_op_count < thread_data->m)
    {
        int rand_value = rand() % MAX;
        int op = rand() % 3; // 0-insert, 1-delete, 2-member

        if (op == 0 && thread_data->insert_op_count < thread_data->insert_frac)
        {
            if (thread_data->total_op_count < thread_data->m)
            { // going to the critical section rechecking if total count is still within m
                // critical section
                pthread_rwlock_wrlock(&thread_data->rwlock);
                Insert(rand_value, &thread_data->head);
                thread_data->insert_op_count++;
                thread_data->total_op_count++;
                pthread_rwlock_unlock(&thread_data->rwlock);
            }
        }
        else if (op == 1 && thread_data->delete_op_count < thread_data->delete_frac)
        {
            if (thread_data->total_op_count < thread_data->m)
            {
                // critical section
                pthread_rwlock_wrlock(&thread_data->rwlock);
                Delete(rand_value, &thread_data->head);
                thread_data->delete_op_count++;
                thread_data->total_op_count++;
                pthread_rwlock_unlock(&thread_data->rwlock);
            }
        }
        else if (op == 2 && thread_data->member_op_count < thread_data->member_frac)
        {
            if (thread_data->total_op_count < thread_data->m)
            {
                // critical section
                pthread_rwlock_rdlock(&thread_data->rwlock); // read only lock for checking member
                Member(rand_value, thread_data->head);
                pthread_rwlock_unlock(&thread_data->rwlock);

                /* Critical section (read lock is not suitable for writing) */
                pthread_mutex_lock(&thread_data->count_mutex);
                thread_data->member_op_count++;
                thread_data->total_op_count++;
                pthread_mutex_unlock(&thread_data->count_mutex);
            }
        }
    }

    return NULL;
}