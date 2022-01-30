#include "functions.h"

array<array<pair<int,bool>,10>,10> getEnergyLevels(vector<string> data){
  array<array<pair<int,bool>,10>,10> levels;
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      levels[i][j].first = data[i][j] - '0';//convert char to int
      levels[i][j].second = false;
    }
  }
  return levels;
}

array<array<pair<int,bool>,10>,10> addOne(array<array<pair<int,bool>,10>,10> oldLevels, int &flashCount){
  array<array<pair<int,bool>,10>,10> newLevels;
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      newLevels[i][j].first = oldLevels[i][j].first + 1;
    }
  }
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      willFlash(i,j, newLevels,flashCount);
    }
  }
  return newLevels;
}

void willFlash(int i, int j, array<array<pair<int,bool>,10>,10> &newLevels, int &flashCount){
  if ((newLevels[i][j].first > 9) && (newLevels[i][j].second == false)){
    newLevels[i][j].second = true;
    flashCount++;
    //std::cout << newLevels[i][j].first << " flashes at " << i << ", " << j << std::endl;
    newLevels[i][j].first = 0;
    checkNeighbors(i, j, newLevels,flashCount);
  }
}

void checkNeighbors(int x,int y,array<array<pair<int,bool>,10>,10> &newLevels, int &flashCount){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      if (inGrid(x-1+i,y-1+j) && (newLevels[x-1+i][y-1+j].second == false)){
        newLevels[x-1+i][y-1+j].first = newLevels[x-1+i][y-1+j].first + 1;
        //std::cout << "neighbor " << newLevels[x-1+i][y-1+j].first << ", " << newLevels[x-1+i][y-1+j].second << " at " << x-1+i << ", " << y-1+j << std::endl;
        willFlash(x-1+i, y-1+j, newLevels, flashCount);
      }
    }
  }
}

bool inGrid(int i, int j){
  bool inRange = false;
  if ((i >= 0) && (i < 10) && (j >= 0) && (j < 10)){
    inRange = true;
  }
  return inRange;
}