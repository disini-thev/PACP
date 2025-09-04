#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "serial.h"
#include "mutex.h"
#include "rw_lock.h"

void calculateStats(double *cpu_time_list, int num_of_sample, double *mean, double *std_dev)
{
    double sum = 0.0;
    double sum_of_squared_diff = 0.0;

    for (int i = 0; i < num_of_sample; i++)
    {
        sum += cpu_time_list[i];
    }

    // Calculate the mean (average)
    *mean = sum / num_of_sample;

    for (int i = 0; i < num_of_sample; i++)
    {
        sum_of_squared_diff += pow(cpu_time_list[i] - *mean, 2);
    }

    // Calculate the standard deviation
    *std_dev = sqrt(sum_of_squared_diff / num_of_sample);
}

int main()
{
    // Number of samples
    const int N = 400;
    unsigned long serial_runtime[N], mut_t1_runtime[N], mut_t2_runtime[N], mut_t4_runtime[N], mut_t8_runtime[N], rw_t1_runtime[N], rw_t2_runtime[N], rw_t4_runtime[N], rw_t8_runtime[N];

    // Number of operations
    int m = 10000;

    // Fractions for each case
    int member_frac;
    int insert_frac;
    int delete_frac;

    double mean = 0.0;
    double std_dev = 0.0;

    double cpu_time_list[N];

    // Use current time as seed for random generator
    srand(time(0));

    // Iterate for the 3 cases
    for (int i = 0; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            member_frac = lround(m * 0.99);
            insert_frac = lround(m * 0.005);
            delete_frac = lround(m * 0.005);
            break;

        case 1:
            member_frac = lround(m * 0.9);
            insert_frac = lround(m * 0.05);
            delete_frac = lround(m * 0.05);
            break;

        case 2:
            member_frac = lround(m * 0.5);
            insert_frac = lround(m * 0.25);
            delete_frac = lround(m * 0.25);
            break;

        default:
            break;
        }

        printf("\n------------------- Case %d -------------------\n", i + 1);

        for (int j = 0; j < N; j++)
        {
            serial_runtime[j] = serialExecution(m, member_frac, insert_frac, delete_frac);
            mut_t1_runtime[j] = mutexExecution(m, member_frac, insert_frac, delete_frac, 1);
            mut_t2_runtime[j] = mutexExecution(m, member_frac, insert_frac, delete_frac, 2);
            mut_t4_runtime[j] = mutexExecution(m, member_frac, insert_frac, delete_frac, 4);
            mut_t8_runtime[j] = mutexExecution(m, member_frac, insert_frac, delete_frac, 8);
            rw_t1_runtime[j] = readwriteExecution(m, member_frac, insert_frac, delete_frac, 1);
            rw_t2_runtime[j] = readwriteExecution(m, member_frac, insert_frac, delete_frac, 2);
            rw_t4_runtime[j] = readwriteExecution(m, member_frac, insert_frac, delete_frac, 4);
            rw_t8_runtime[j] = readwriteExecution(m, member_frac, insert_frac, delete_frac, 8);
        }

        // Array of names for labeling the outputs
        const char *labels[] = {"Serial", "Mutex_t1", "Mutex_t2", "Mutex_t4", "Mutex_t8", "ReadWrite_t1", "ReadWrite_t2", "ReadWrite_t4", "ReadWrite_t8"};
        unsigned long *runtime_arrays[] = {serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime, rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime};

        // Loop over each runtime array, calculate stats, and print the results
        for (int k = 0; k < 9; k++)
        {
            // Copy runtime values to the double array for statistics calculation
            for (int j = 0; j < N; j++)
            {
                cpu_time_list[j] = (double)runtime_arrays[k][j]; // Convert unsigned long to double
            }

            // Calculate mean and standard deviation
            calculateStats(cpu_time_list, N, &mean, &std_dev);

            // Calculate number of samples needed to achieve 95% confidence level and 5% margin of error
            double x = (100 * 1.96 * std_dev) / (5 * mean);
            double samples = ceil(pow(x, 2));

            // Print the results
            // printf("%s: Runs=%d, Mean=%.2f, StdDev=%.2f\n", labels[k], samples, mean, std_dev);
            printf("%s:\n", labels[k]);
            printf("Samples: %d\n", (int)samples);
            printf("Mean (Average): %f\n", mean);
            printf("Standard Deviation: %f\n", std_dev);
        }
        printf("----------------------------- Case %d completed -----------------------------", i + 1);
    }
    return 0;
}