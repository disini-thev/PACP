
import java.util.concurrent.Semaphore;

public class BusStop {
    private int waiting = 0; // number of waiting riders
    private final int capacity = 50;

    public Semaphore mutex = new Semaphore(1); // doesn't let changing the rider count when acquired - multiple riders changing at the same time - riders attempting to enter when bus is boarding
    public Semaphore bus = new Semaphore(0); // riders wait for bus, bus signals riders to board - 1 at a time
    public Semaphore boarded = new Semaphore(0); // bus waits for riders to board, riders signal bus when boarded

    // rider arrival
    public void riderArrives(int riderId) throws InterruptedException {

        System.out.println("Rider " + riderId + " is trying to enter the bus stop.");
        mutex.acquire();
        waiting++;
        System.out.println("Rider " + riderId + " arrived. Waiting = " + waiting);
        mutex.release();

        // wait for bus
        System.out.println("Rider " + riderId + " is waiting for a bus.");
        bus.acquire();
        // boarding simulation
        System.out.println("Rider " + riderId + " is boarding...");
        Thread.sleep(100); // simulate boarding time

        boarded.release();
    }

    // bus arrival
    public void busArrives(int busId) throws InterruptedException {

        System.out.println("\nBus " + busId + " arrived at stop.");
        mutex.acquire();

        int n = Math.min(waiting, capacity);
        System.out.println("Bus " + busId + " is boarding " + n + " riders (waiting = " + waiting + ")");

        for (int i = 0; i < n; i++) {
            bus.release();       // allow one rider to board
            boarded.acquire();   // wait until rider boards
        }

        waiting = Math.max(waiting - capacity, 0);
        mutex.release();

        System.out.println("Bus " + busId + " is departing\n");
    }
}
