import java.util.Random;

public class Main {
    public static void main(String[] args) {
        BusStop stop = new BusStop();
        Random rand = new Random();

        //demonstration mean times
        double meanRider = 0.5;  // 0.5 min → scaled down to 0.5 s
        double meanBus = 5;      // 20 min → scaled down to 5 s  

        // Rider generation
        Thread riderGenerator = new Thread(() -> {
            int riderId = 0;
            try {
                while (true) {
                    riderId++;
                    Thread riderThread = new Thread(new Rider(riderId, stop));
                    riderThread.start();

                    // exponential inter-arrival time for riders
                    double nextRiderDelay = -meanRider * Math.log(1 - rand.nextDouble());
                    Thread.sleep((long) (nextRiderDelay * 1000));  // convert to ms
                }
            } catch (InterruptedException e) {
                System.out.println("Rider generation interrupted");
            }
        });

        // Bus generation
        Thread busGenerator = new Thread(() -> {
            int busId = 0;
            try {
                while (true) {
                    busId++;
                    Thread busThread = new Thread(new Bus(busId, stop));
                    busThread.start();

                    // exponential inter-arrival time for buses
                    double nextBusDelay = -meanBus * Math.log(1 - rand.nextDouble());
                    Thread.sleep((long) (nextBusDelay * 1000));  // convert to ms
                }
            } catch (InterruptedException e) {
                System.out.println("Bus generation interrupted");
            }
        });

        // Start both generators
        riderGenerator.start();
        busGenerator.start();
    }
}