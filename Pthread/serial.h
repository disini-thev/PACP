#ifndef SERIAL_H
#define SERIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "linked_list.h"
#include "global.h"

// Serial Linked List implementation function signature
unsigned long serialExecution(int total_operations, int member_frac, int insert_frac, int delete_frac);

#endif