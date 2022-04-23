#include "functions.h"

vector<vector<int>>
getChitonLevels(vector<string> data) { // data is a bunch of strings of digits
	vector<int> row;
	vector<vector<int>> chitons; // make a matrix with each digit as an entry
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].length(); ++j) { // turn each string into a row of the matrix
			row.push_back(data[i][j] - '0'); // turn each digit from the string into an int
		}
		chitons.push_back(row);
		row.clear();
	}
	return chitons;
}

int Day15_1(string filename) {
	int risk = 0;
	vector<string> riskData = getData(filename);
	vector<vector<int>> chitonRisk = getChitonLevels(riskData);
	//printMatrix(chitonRisk);
	risk = dijkstra(chitonRisk);
	return risk;
}

int dijkstra(vector<vector<int>> chitons) {
	int pathLength = 0;
	int matrixSize = chitons.size();
	vector<vector<pair<int, bool>>> distances = initializeDistances(matrixSize); // set all to infinity except the starting point and set flag to indicated if visited
	vector<pair<int, int>> priorityList; // set up a list of neighbors of visited points
	priorityList.push_back(std::make_pair(0, 0)); // put the starting point in the priority list
  bool done = false;
  while (!done){
    pathLength = update(priorityList, distances, chitons, done);
  }
	return pathLength;
}

vector<vector<pair<int,bool>>> initializeDistances(int size) { // 0 at the start point, infinity elsewhere for the distance and set bool to false to indicate that no point has been visited
  pair<int,bool> initial = std::make_pair(INT_MAX,false); //set the initial values to infinite distance and not visited
  vector<pair<int,bool>> row(size,initial); //set up the row of the correct length with the initial values
	vector<vector<pair<int,bool>>> maxDistances(size,row); //fill a matrix of the correct size with the initial values
	maxDistances[0][0].first = 0;
	return maxDistances;
}

vector<pair<int, int>> findNeighbors(int x,int y,int size,vector<vector<pair<int,bool>>> &distances) { // make a list of unvisited neighboring points in the cavern
	vector<pair<int, int>> neighbors;
	if ((isInCavern(x - 1, y, size)) && (!distances[x - 1][y].second)) {
		neighbors.push_back(std::make_pair(x - 1, y));
	}
	if ((isInCavern(x + 1, y, size)) && (!distances[x + 1][y].second)) {
		neighbors.push_back(std::make_pair(x + 1, y));
	}
	if ((isInCavern(x, y - 1, size)) && (!distances[x][y - 1].second)) {
		neighbors.push_back(std::make_pair(x, y - 1));
	}
	if ((isInCavern(x, y + 1, size)) && (!distances[x][y + 1].second)) {
		neighbors.push_back(std::make_pair(x, y + 1));
	}
	return neighbors;
}

bool isInCavern(int x,int y,int size) { // check if the point (x,y) is in the cavern
	bool isIn = true;
	if ((x < 0) || (x >= size) || (y < 0) || (y >= size)) {
		isIn = false;
	}
	return isIn;
}

pair<int, int> findMin(vector<pair<int, int>> &priority, vector<vector<pair<int,bool>>> &distances) {
	int min = INT_MAX;
	int x = 0;
	int y = 0;
	int index = 0;
	pair<int,int> coords;
	for (int i = 0; i < priority.size(); ++i) { // go through priority list and find the closest point not yet visited
		if ((!distances[priority[i].first][priority[i].second].second) && (distances[priority[i].first][priority[i].second].first <= min)) { // if it hasn't been visited and its distance is less than the min distance found so far
			min = distances[priority[i].first][priority[i].second].first; //reset the min distance
			x = priority[i].first; //store the coordinates
			y = priority[i].second;
			index = i; //store the index
		}
	}
	priority.erase(priority.begin() + index); // remove this point from the priority list
	coords = std::make_pair(x,y);
	return coords;
}

bool inPriority(pair<int,int> coords, vector<pair<int, int>> &priority){
  bool isInList;
  int x = coords.first;
  int y = coords.second;
  for (int i = 0; i < priority.size(); ++i){
    if ((priority[i].first == x) && (priority[i].second == y)){
      isInList = true;
    }
  }
  return isInList;
}

int update(vector<pair<int, int>> &priority,vector<vector<pair<int,bool>>> &distances,vector<vector<int>> &chitons,bool &done) { //add points checked to visited list, set distances
	int minDistance = 0;
	int size = distances.size();
	pair<int, int> minCoords = findMin(priority,distances); // get an unvisited point at min distance in priority queue
	vector<pair<int, int>> toCheck = findNeighbors(minCoords.first, minCoords.second, size,distances); // get a list of unvisited neighbors in cavern
	for (int i = 0; i < toCheck.size(); ++i) { //for each unvisited neighbor
		if (!inPriority(toCheck[i],priority)) {
			priority.push_back(toCheck[i]); // add to the priority queue if it isn't there yet
		}
		int xCheck = toCheck[i].first;
		int yCheck = toCheck[i].second;
		int checkDistance = distances[minCoords.first][minCoords.second].first + chitons[xCheck][yCheck]; // add new section distance to distance at min point
		if (checkDistance < distances[xCheck][yCheck].first) { // if new distance is less, update the distance at the neighbor
			distances[xCheck][yCheck].first = checkDistance;
			if ((xCheck == size - 1) && (yCheck == size - 1)) { // if you have reached the endpoint, you are done
				done = true;
				minDistance = checkDistance;
			}
    }
		std::cout << "(" << xCheck << ", " << yCheck << ") "  << std::endl;
  }
	distances[minCoords.first][minCoords.second].second = true; // set the flag to visited
	return minDistance;
}

// Day 15, Part 2

int Day15_2(string filename) {
	int risk = 0;
	vector<string> riskData = getData(filename);
	vector<vector<int>> chitonRisk = getChitonLevels(riskData);
	vector<vector<int>> chitonExpanded = expandMap(chitonRisk);
	risk = dijkstra(chitonExpanded);
	return risk;
}

vector<vector<int>> expandMap(vector<vector<int>> matrix) {
	int multiplier = 5;
	vector<int> row(matrix.size() * multiplier, 0);
	vector<vector<int>> bigMap(matrix.size() * multiplier, row);
  vector<vector<vector<int>>> increasedRiskNumbers = increasedNumbersByDigit();
	for (int i = 0; i < matrix.size(); ++i) { // go through the original matrix
		for (int j = 0; j < matrix.size(); ++j) {
			vector<vector<int>> addOneToOriginal = increasedRiskNumbers[matrix[i][j]]; //gives a 5x5 matrix of increased values
			for (int p = 0; p < multiplier; ++p) { // put these values in the corresponding places in the big matrix
				for (int q = 0; q < multiplier; ++q) {
					bigMap[(p * matrix.size()) + i][(q * matrix.size()) + j] = addOneToOriginal[p][q];
				}
			}
		}
	}
	return bigMap;
}

vector<vector<vector<int>>> increasedNumbersByDigit(void){
  vector<vector<vector<int>>> increasedValues;
  for (int i = 0; i < 10; ++i){ //for each digit, make a 5x5 matrix of the increased values
    increasedValues.push_back(increaseRisk(i));
  }
  return increasedValues;
}

vector<vector<int>> increaseRisk(int n) {
	vector<vector<int>> addOneToRisk;
	vector<int> row;
	int size = 5;
	for (int i = 0; i < size; ++i) {
		int k = wrapAdd(n, i);
		for (int j = 0; j < size; ++j) {
			int newNum = wrapAdd(k, j);
			row.push_back(newNum);
		}
		addOneToRisk.push_back(row);
		row.clear();
	}
	return addOneToRisk;
}

int wrapAdd(int i, int j) {
	int k = i + j;
	if (k > 9) {
		k = k - 9;
	}
	return k;
}