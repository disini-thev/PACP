public class Rider implements Runnable {
    private final int riderId;
    private final BusStop busStop;

    public Rider(int riderId, BusStop stop) {
        this.riderId = riderId;
        this.busStop = stop;
    }

    public int getRiderId() {
        return riderId;
    }

    @Override
    public void run() {
        try {
            busStop.riderArrives(riderId);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
