#include "functions.h"

vector<vector<int>> getChitonLevels(vector<string> data){ // data is a bunch of strings of digits
  vector<int> row;
  vector <vector<int>> chitons;
  for (int i = 0; i < data.size(); ++i){
    for (int j = 0; j < data[i].length(); ++j){
      row.push_back(data[i][j]-'0');
    }
    chitons.push_back(row);
    row.clear();
  }
  return chitons;
}


pair<int, stack<bool>> nextStep(int i, int j, vector<vector<int>> matrix, vector<vector<pair<int,stack<bool>>>> paths){
  int width = matrix.size();
  //std::cout << "(" << i << ", " << j << ") ";
  bool goRight = false;//true if we should move right, false if we should move down
  bool movedRight = false;
  bool movedDown = false;
  int right = 0;
  int down = 0;
  stack<bool> nextPath;
  pair<int,stack<bool>> nextShort;
  if (i + 1 < matrix.size()){//moves down and checks if it is still in the cavern
    movedDown = true;
    down = matrix[i+1][j] + paths[width - 1 - (i+1)][width - 1 - j].first;
  }
  if (j + 1 < matrix.size()){// moves right, checks if in cavern
    movedRight = true;
    right = matrix[i][j+1] + paths[width - 1 - i][width - 1 - (j+1)].first;
  }
  if (((down >= right) && (movedRight)) || ((down < right) && (!movedDown))){//right gives shorter path or down looks shorter because it's set to 0 since it is out of bounds
    goRight = true;
    nextPath = paths[width - 1 - i][width - 1 - (j+1)].second;
    nextPath.push(goRight);
    nextShort = make_pair(right,nextPath);
  }
  else if (((down > right) && (!movedRight)) || ((down <= right) && (movedDown))){//right looks shorter because it is set to 0 since it is out of bounds or we moved down and it is the shorter path forward
    nextPath = paths[width - 1 - (i+1)][width - 1 - j].second; //goRight is false since we only moved down
    nextPath.push(goRight);
    nextShort = make_pair(down,nextPath);
  }
  else{
    nextShort = make_pair(0,nextPath);
  }
  //std::cout << nextShort.first << std::endl;
  return nextShort;
}

vector<vector<pair<int,stack<bool>>>> getPaths(vector<vector<int>> riskMatrix){
  int width = riskMatrix.size();
  stack<bool> path;
  pair<int,stack<bool>> initialPair = make_pair(0, path);
  vector<pair<int,stack<bool>>> row(width, initialPair);
  vector<vector<pair<int,stack<bool>>>> pathMatrix(width, row);
  for (int i = 0; i < width; ++i){
    for (int j = 0; j < width; ++j){
      pathMatrix[i][j] = nextStep(width - 1 - i, width - 1 - j, riskMatrix, pathMatrix);
    }
  }
  return pathMatrix;
}


//Day 15, Part 2
/*
vector<vector<int>> expandMap(vector<vector<int>> matrix){
  int size = 5;
  vector<int> row(matrix.size() * size,0);
  vector<vector<int>> bigMap(matrix.size() * size,row);
  
  for (int i = 0; i < matrix.size(); ++i){ //go through the original matrix
    for (int j = 0; j < matrix.size(); ++j){
      vector<vector<int>> addOneToOriginal = increaseRisk(matrix[i][j]); //returns a 5x5 matrix of increased values
      for (int p = 0; p < size; ++p){ // put these values in the corresponding places in the big matrix
        for (int q = 0; q < size; ++q){
          bigMap[(p*matrix.size()) + i][(q*matrix.size()) + j] = addOneToOriginal[p][q];
        }
      }
    }
  }
  
  return bigMap;
}

vector<vector<int>> increaseRisk(int n){
  vector<vector<int>> addOneToRisk;
  vector<int> row;
  int size = 5;
  for (int i = 0; i < size; ++i){
    int k = wrapAdd(n, i);
    for (int j = 0; j < size; ++j){
      int newNum = wrapAdd(k, j);
      row.push_back(newNum);
    }
    addOneToRisk.push_back(row);
    row.clear();
  }
  return addOneToRisk;
}

int wrapAdd(int i, int j){
  int k = i + j;
  if (k > 9){
    k = k - 9;
  }
  return k;
}

int whichStep(int i, int j, vector<vector<int>> risks, vector<vector<int>> paths){
  int pathRisk = 0;
  int width = risks.size();
  bool movedRight = false;
  bool movedDown = false;
  int right = 0;
  int down = 0;
  if (i + 1 < risks.size()){//moves down and checks if it is still in the cavern
    movedDown = true;
    down = risks[i+1][j] + paths[width - 1 - (i+1)][width - 1 - j];
  }
  if (j + 1 < risks.size()){// moves right, checks if in cavern
    movedRight = true;
    right = risks[i][j+1] + paths[width - 1 - i][width - 1 - (j+1)];
  }
  if (((down >= right) && (movedRight)) || ((down < right) && (!movedDown))){//right gives shorter path or down looks shorter because it's set to 0 since it is out of bounds
    pathRisk = right;
  }
  else if (((down > right) && (!movedRight)) || ((down <= right) && (movedDown))){//right looks shorter because it is set to 0 since it is out of bounds or we moved down and it is the shorter path forward
    pathRisk = down;
  }
  else{
    pathRisk = 0;
  }
  //std::cout << nextShort.first << std::endl;
  return pathRisk;
}

vector<vector<int>> pathRisks(vector<vector<int>> risks){
  int width = risks.size();
  vector<int> row(width,0);//initialize a row of zeros
  vector<vector<int>> pathRiskMatrix(width,row); //initialize a width-by-width matrix of zeros
  for (int i = 0; i < width; ++i){
    for (int j = 0; j < width; ++j){
      pathRiskMatrix[i][j] = whichStep(width - 1 - i, width - 1 - j, risks, pathRiskMatrix);
    }
  }
  return pathRiskMatrix;
}
*/