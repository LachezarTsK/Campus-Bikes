
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {

    struct PairWorkerBike {
        int workerIndex{};
        int bikeIndex{};
        PairWorkerBike(int workerIndex, int bikeIndex) : workerIndex{workerIndex}, bikeIndex{bikeIndex}{};
    };

    inline static int manhattanDistance(const vector<int>& first, const vector<int>& second) {
        return abs(first[0] - second[0]) + abs(first[1] - second[1]);
    }

    inline const static vector<int> SMALLEST_COORDINATE {0, 0};
    inline const static vector<int> LARGEST_COORDINATE {999, 999};
    inline const static int MAX_DISTANCE = manhattanDistance(SMALLEST_COORDINATE, LARGEST_COORDINATE);

    unordered_map<int, vector<PairWorkerBike>> groupsOfPairsWithSameDistance;
    size_t numberOfWorkers{};
    size_t numberOfBikes{};

public:

    vector<int> assignBikes(vector<vector<int>>&workers, vector<vector<int>>&bikes) {

        numberOfWorkers = workers.size();
        numberOfBikes = bikes.size();
        initializeMap_groupsOfPairsWithSameDistance(workers, bikes);

        return setBikeToEachWorker();
    }

private:

    vector<int> setBikeToEachWorker() {

        vector<int> workersWithAssignedBikes(numberOfWorkers, -1);
        vector<int> bikesVisited(numberOfBikes, false);
        int countAssignedBikes = 0;

        for (int distance = 0; distance <= MAX_DISTANCE; ++distance) {
            if (groupsOfPairsWithSameDistance.find(distance) == groupsOfPairsWithSameDistance.end()) {
                continue;
            }

            vector<PairWorkerBike>& listPairsCurrentDistance{ groupsOfPairsWithSameDistance[distance]};
            for (const auto& pair : listPairsCurrentDistance) {
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

    void initializeMap_groupsOfPairsWithSameDistance(const vector<vector<int>>&workers, const vector<vector<int>>&bikes) {

        for (int w = 0; w < numberOfWorkers; ++w) {
            for (int b = 0; b < numberOfBikes; ++b) {
                int distance = manhattanDistance(workers[w], bikes[b]);

                if (groupsOfPairsWithSameDistance.find(distance) == groupsOfPairsWithSameDistance.end()) {
                    groupsOfPairsWithSameDistance[distance] = vector<PairWorkerBike>();
                }
                groupsOfPairsWithSameDistance[distance].push_back(PairWorkerBike(w, b));
            }
        }
    }
};
