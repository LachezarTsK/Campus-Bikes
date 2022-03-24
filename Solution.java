
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Solution {

    private static record PairWorkerBike(int workerIndex, int bikeIndex){}
    private Map<Integer, List<PairWorkerBike>> groupsOfPairsWithSameDistance;

    private static final int[] SMALLEST_COORDINATE = new int[]{0, 0};
    private static final int[] LARGEST_COORDINATE = new int[]{999, 999};
    private static final int MAX_DISTANCE = manhattanDistance(SMALLEST_COORDINATE, LARGEST_COORDINATE);

    private int numberOfWorkers;
    private int numberOfBikes;

    public int[] assignBikes(int[][] workers, int[][] bikes) {
        numberOfWorkers = workers.length;
        numberOfBikes = bikes.length;
        initializeMap_groupsOfPairsWithSameDistance(workers, bikes);

        return setBikeToEachWorker();
    }

    private int[] setBikeToEachWorker() {

        int[] workersWithAssignedBikes = new int[numberOfWorkers];
        Arrays.fill(workersWithAssignedBikes, -1);

        boolean[] bikesVisited = new boolean[numberOfBikes];
        int countAssignedBikes = 0;

        for (int distance = 0; distance <= MAX_DISTANCE; distance++) {
            if (groupsOfPairsWithSameDistance.containsKey(distance) == false) {
                continue;
            }

            List<PairWorkerBike> listPairsCurrentDistance = groupsOfPairsWithSameDistance.get(distance);
            for (PairWorkerBike pair : listPairsCurrentDistance) {
                if (workersWithAssignedBikes[pair.workerIndex] == -1 && bikesVisited[pair.bikeIndex] == false) {
                    bikesVisited[pair.bikeIndex] = true;
                    workersWithAssignedBikes[pair.workerIndex] = pair.bikeIndex;
                    ++countAssignedBikes;
                }
            }
            if (countAssignedBikes == numberOfWorkers) {
                break;
            }
        }
        return workersWithAssignedBikes;
    }

    private void initializeMap_groupsOfPairsWithSameDistance(int[][] workers, int[][] bikes) {
        groupsOfPairsWithSameDistance = new HashMap<>();

        for (int w = 0; w < numberOfWorkers; w++) {
            for (int b = 0; b < numberOfBikes; b++) {
                int distance = manhattanDistance(workers[w], bikes[b]);
                groupsOfPairsWithSameDistance.putIfAbsent(distance, new ArrayList<>());
                groupsOfPairsWithSameDistance.get(distance).add(new PairWorkerBike(w, b));
            }
        }
    }

    private static int manhattanDistance(int[] first, int[] second) {
        return Math.abs(first[0] - second[0]) + Math.abs(first[1] - second[1]);
    }
}
