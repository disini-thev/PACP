# Semaphores Lab - Senate Bus Problem

This folder contains a Java implementation of the senate bus problem, a classic synchronization challenge involving semaphores, riders, and buses coordinating at a bus stop.

## Overview

The riders and busses arrive at the bus stop continuously with their inter arrival times exponentially distributed with a mean of 30 seconds and 20 minutes respectively. For the simulation, 0.5 seconds and 5 seconds are used.

A bus can pick a maximum of 50 riders at a time, no riders can join the queue while the bus is boarding riders. No order is enforced for picking riders. With semaphores synchronization is ensured.

## Implementations

* Bus class : Implements `Runnable`. Represents a bus arriving at the stop. It acquires the necessary semaphores to start boarding riders and ensures all riders have boarded before departing.
* Rider class : Implements `Runnable`. Represents an individual rider arriving at the stop. Each rider waits until the bus signals that boarding can begin.
* BusStop class : Manages the synchronization of busses and riders with semaphores and counters.
* Main file : The entry point of the program. Creates and starts the **thread generator** threads for riders and buses. Each generator spawns new `Thread` objects wrapping `Bus` and `Rider` instances.

## Makefile

- `build` — compile all `.java` files into the `bin/` directory
- `run` — build and run the `Main` class
- `clean` — remove the `bin/` directory
