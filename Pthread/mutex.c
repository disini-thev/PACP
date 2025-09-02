#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include "linked_list.h"
#include "mutex.h"
#include "global.h"

unsigned long mutexExecution(int total_operations, int mMember, int mInsert, int mDelete, int thread_count)
{

    // initialize mutex_data structure
    mutex_data thread_data;
    thread_data.head = NULL;

    thread_data.total_operations = total_operations;
    thread_data.mMember = mMember;
    thread_data.mInsert = mInsert;
    thread_data.mDelete = mDelete;

    thread_data.memberOp_count = 0;
    thread_data.insertOp_count = 0;
    thread_data.deleteOp_count = 0;
    thread_data.totalOp_count = 0;

    // initialize the linked list

    int n = 1000;
    int count = 0;

    while (count < n)
    {
        Insert(rand() % MAX, &thread_data.head);
        count++;
    }

    // Initialize the mutex
    pthread_mutex_init(&thread_data.mutex, NULL);

    // Allocate memory for threads
    pthread_t *thread_handles = malloc(thread_count * sizeof(pthread_t));

    struct timeval start;
    struct timeval end;

    // Start time
    gettimeofday(&start, NULL);

    // Create threads
    for (int thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, threadFuncMutex, (void *)&thread_data);
    }

    // Join threads
    for (int thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

    // End time
    gettimeofday(&end, NULL);

    unsigned long exec_time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;

    // Destroy the mutex
    pthread_mutex_destroy(&thread_data.mutex);

    Destructor(thread_data.head);
    printf("Mutex run complete\n");
    return exec_time;
}

// Thread function for mutex implementation
void *threadFuncMutex(void *args)
{

    mutex_data *thread_data = args;

    while (thread_data->totalOp_count < thread_data->total_operations)
    {

        int rand_value = rand() % MAX;
        int operation_number = rand() % 3; // generate a random number between 0 and 2  ex:{0,1,2}

        if (operation_number == 0 && thread_data->insertOp_count < thread_data->mInsert)
        {
            if (thread_data->totalOp_count < thread_data->total_operations)
            {
                /* Critical section */
                pthread_mutex_lock(&thread_data->mutex);
                Insert(rand_value, &thread_data->head);
                thread_data->insertOp_count++;
                thread_data->totalOp_count++;
                pthread_mutex_unlock(&thread_data->mutex);
            }
        }
        else if (operation_number == 1 && thread_data->deleteOp_count < thread_data->mDelete)
        {
            if (thread_data->totalOp_count < thread_data->total_operations)
            {
                /* Critical section */
                pthread_mutex_lock(&thread_data->mutex);
                Delete(rand_value, &thread_data->head);
                thread_data->deleteOp_count++;
                thread_data->totalOp_count++;
                pthread_mutex_unlock(&thread_data->mutex);
            }
        }
        else if (thread_data->memberOp_count < thread_data->mMember)
        {
            if (thread_data->totalOp_count < thread_data->total_operations)
            {
                /* Critical section */
                pthread_mutex_lock(&thread_data->mutex);
                Member(rand_value, thread_data->head);
                thread_data->memberOp_count++;
                thread_data->totalOp_count++;
                pthread_mutex_unlock(&thread_data->mutex);
            }
        }
    }

    return NULL;
}