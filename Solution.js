
/**
 * @param {number[][]} workers
 * @param {number[][]} bikes
 * @return {number[]}
 */
var assignBikes = function (workers, bikes) {

    this.SMALLEST_COORDINATE = [0, 0];
    this.LARGEST_COORDINATE = [999, 999];
    this.MAX_DISTANCE = manhattanDistance(this.SMALLEST_COORDINATE, this.LARGEST_COORDINATE);

    this.groupsOfPairsWithSameDistance = new Map();
    this.numberOfWorkers = workers.length;
    this.numberOfBikes = bikes.length;
    initializeMap_groupsOfPairsWithSameDistance(workers, bikes);

    return setBikeToEachWorker();
};

/**
 * @param {number} workerIndex
 * @param {number} bikeIndex
 */
function PairWorkerBike(workerIndex, bikeIndex) {
    this.workerIndex = workerIndex;
    this.bikeIndex = bikeIndex;
}

/**
 * @return {number}
 */
function setBikeToEachWorker() {

    const workersWithAssignedBikes = new Array(this.numberOfWorkers).fill(-1);
    const bikesVisited = new Array(this.numberOfBikes).fill(false);
    let countAssignedBikes = 0;

    for (let distance = 0; distance <= this.MAX_DISTANCE; distance++) {
        if (this.groupsOfPairsWithSameDistance.has(distance) === false) {
            continue;
        }

        const listPairsCurrentDistance = this.groupsOfPairsWithSameDistance.get(distance);
        for (let pair of listPairsCurrentDistance) {
            if (workersWithAssignedBikes[pair.workerIndex] === -1 && bikesVisited[pair.bikeIndex] === false) {
                bikesVisited[pair.bikeIndex] = true;
                workersWithAssignedBikes[pair.workerIndex] = pair.bikeIndex;
                ++countAssignedBikes;
            }
        }
        if (countAssignedBikes === numberOfWorkers) {
            break;
        }
    }
    return workersWithAssignedBikes;
}

/**
 * @param {number[][]} workers
 * @param {number[][]} bikes
 * @return void
 */
function initializeMap_groupsOfPairsWithSameDistance(workers, bikes) {

    for (let w = 0; w < this.numberOfWorkers; w++) {
        for (let b = 0; b < this.numberOfBikes; b++) {
            let distance = manhattanDistance(workers[w], bikes[b]);

            if (this.groupsOfPairsWithSameDistance.has(distance) === false) {
                this.groupsOfPairsWithSameDistance.set(distance, []);
            }
            this.groupsOfPairsWithSameDistance.get(distance).push(new PairWorkerBike(w, b));
        }
    }
}

/**
 * @param {number[]} first
 * @param {number[]} second
 * @return {number}
 */
function manhattanDistance(first, second) {
    return Math.abs(first[0] - second[0]) + Math.abs(first[1] - second[1]);
}
