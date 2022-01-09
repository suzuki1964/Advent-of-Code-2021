#include "functions.h"

vector<vector<pair<int,int>>> getFloorHeights(vector<string> data){
  vector<vector<pair<int,int>>> heights;
  vector<pair<int, int>> row;
  pair<int, int> height; // the first int will be the height, the second will mark the basin
  for (int i = 0; i < data.size(); ++i){
    for (int j = 0; j < data[i].length(); ++j){
      height = std::make_pair( data[i].at(j) - '0', 0); // convert char to int by subtracting '0'; set basin marker to 0
      row.push_back(height); // add to the row vector
    }
    heights.push_back(row); // put the row onto the heights vector
    row.clear(); // clear for the next row
  }
  return heights;
}

bool isLowPoint(int x, int y, vector<vector<pair<int,int>>> heights){
  bool low = false;
  if ((x-1 < 0) || ((x-1 >= 0) && (heights[y][x].first < heights[y][x-1].first))) { // if left location is out of bounds, then skip; otherwise, check if higher
    if ((x+1 >= heights[y].size()) || ((x+1 < heights[y].size()) && (heights[y][x].first < heights[y][x+1].first))){ // if right location is out of bounds, then skip; otherwise, check if higher
      if ((y-1 < 0) || ((y-1 >= 0) && (heights[y][x].first < heights[y-1][x].first))){ // if the location above is out of bounds, then skip; otherwise, check if higher
        if ((y+1 >= heights.size()) || ((y+1 < heights.size()) && (heights[y][x].first < heights[y+1][x].first))){ // if location below is out of bounds, then skip; otherwise, check if higher
          low = true; //if all the neighbors are higher, then it is the lowest point
          //std::cout << "low at " << x << ", " << y << "height " << heights[y][x].first << "\n";
        }
      }
    }
  }
  return low;
}

int getRiskLevel(vector<vector<pair<int,int>>> &heights,vector<int> &sizes){ // pass vectors by reference in order to be able to make changes to the values
  int risk = 0;
  int count = 0;
  for (int i = 0; i < heights.size(); ++i){ // go through each line of floor heights
    for (int j = 0; j < heights[i].size(); ++j){ // go through each location in the row
      if (isLowPoint(j, i, heights)){
        risk += heights[i][j].first;
        ++count;
        int basinSize = 0;
        //std::cout << "low point " << count << ": " << heights[i][j].first << " basin size " << basinSize << "\n";
        basinSize = markBasin(j,i,count,basinSize,heights);
        //std::cout << "basin " << count << " size " << basinSize << "\n";
        sizes.push_back(basinSize);
      }
    }
  }
  return risk + count;
}

int markBasin(int x,int y,int basin,int &size,vector<vector<pair<int,int>>> &heights){ // pass size by reference to it will keep track properly over the recursive calls
  //std::cout << "mark " << x << ", " << y << ": " << basin << "\n";
  heights[y][x].second = basin;
  size++;
  //std::cout << "size " << size << "\n";
  if ((x-1 >= 0) && (heights[y][x-1].first != 9) && (heights[y][x-1].second == 0)) { // if left location is in bounds and less than height 9 and unmarked, then move to it
    markBasin(x-1, y, basin, size, heights);
  }
  if ((x+1 < heights[y].size()) && (heights[y][x+1].first != 9) && (heights[y][x+1].second == 0)){ // if right location is in bounds and less than height 9 and unmarked, then move to it
    markBasin(x+1, y, basin, size, heights);
  }
  if ((y-1 >= 0) && (heights[y-1][x].first != 9) && (heights[y-1][x].second == 0)) { // if the location above is in bounds and less than height 9 and unmarked, then move to it
    markBasin(x, y-1, basin, size, heights);
  }
  if ((y+1 < heights.size()) && (heights[y+1][x].first != 9) && (heights[y+1][x].second == 0)) { // if the location below is in bounds and less than height 9 and unmarked, then move to it
    markBasin(x, y+1, basin, size, heights);
  }
  return size;    
}

int getRiskProduct(vector<int> sizes){
  int product = 0;
  int max1 = 0;
  int max2 = 0;
  int max3 = 0;
  int temp1 = 0;
  int temp2 = 0;
  for (int i = 0; i < sizes.size(); ++i){
    if (sizes[i] >= max1){
      temp1 = max1;
      temp2 = max2;
      max1 = sizes[i];
      max2 = temp1;
      max3 = temp2;
    }
    else if (sizes[i] >= max2){
      temp2 = max2;
      max2 = sizes[i];
      max3 = temp2;
    }
    else if (sizes[i] >= max3){
      max3 = sizes[i];
    }
  }
  product = max1 * max2 * max3;
  return product;
}