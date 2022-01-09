#include "functions.h"

vector<int> getCrabPositions(vector<string> data){
  vector<int> positions;
  int split_pos = 0;
  int last_pos = 0;
  while (split_pos != string::npos){
    split_pos = data[0].find(",", last_pos);
    positions.push_back(stoi(data[0].substr(last_pos, split_pos-last_pos)));
    last_pos = split_pos + 1;
  }
  return positions;
}

int findMax(vector<int> xPositions){
  int max = 0;
  for (int i = 0; i < xPositions.size(); i++){
    if (xPositions[i] > max){
      max = xPositions[i];
    }
  }
  return max;
}

int getFuelCost(int xValue, vector<int> positions){
  int fuel = 0;
  for (int i = 0; i < positions.size(); i++){
    fuel += std::abs(xValue - positions[i]);
  }
  return fuel;
}

int findMinFuel(vector<int> positions){
  int maxPos = findMax(positions);
  int fuel = getFuelCost(maxPos, positions);
  for (int i = 0; i < maxPos; i++){
    int fuelCost = getFuelCost(i, positions);
    if (fuelCost < fuel){
      fuel = fuelCost;
    }
  }
return fuel;
}

int getNewFuelCost(int xValue, vector<int> positions){
  int fuel = 0;
  for (int i = 0; i < positions.size(); i++){
    int distance = std::abs(xValue - positions[i]);
    fuel += (distance * (distance + 1)/2);
  }
  return fuel;
}

int findNewMinFuel(vector<int> positions){
  int maxPos = findMax(positions);
  int fuel = getNewFuelCost(maxPos, positions);
  for (int i = 0; i < maxPos; i++){
    int fuelCost = getNewFuelCost(i, positions);
    if (fuelCost < fuel){
      fuel = fuelCost;
    }
  }
return fuel;
}