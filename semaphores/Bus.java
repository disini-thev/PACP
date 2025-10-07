public class Bus implements Runnable {
    private final int busId;
    private final BusStop busStop;

    public Bus(int busId, BusStop stop) {
        this.busId = busId;
        this.busStop = stop;
    }

    public int getBusId() {
        return busId;
    }

    @Override
    public void run() {
        try {
            busStop.busArrives(busId);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
