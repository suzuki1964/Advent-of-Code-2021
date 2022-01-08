#include "functions.h"

int getRiskLevel(vector<string> heights){
  int risk = 0;
  int count = 0;
  for (int i = 0; i < heights.size(); ++i){ // go through each line of floor heights
    for (int j = 0; j < heights[i].length(); ++j){ // go through each location in the row
      int height = heights[i].at(j) - '0'; // convert the char to an int
      if ((j-1 < 0) || ((j-1 >= 0) && (height < (heights[i].at(j-1) - '0')))){ // if left location is out of bounds, then skip; otherwise, check if higher
        if ((j+1 >= heights[i].length()) || ((j+1 < heights[i].length()) && (height < (heights[i].at(j+1) - '0')))){ // if right location is out of bounds, then skip; otherwise, check if higher
          if ((i-1 < 0) || ((i-1 >= 0) && (height < (heights[i-1].at(j) - '0')))){ // if the location above is out of bounds, then skip; otherwise, check if higher
            if ((i+1 >= heights.size()) || ((i+1 < heights.size()) && (height < (heights[i+1].at(j) - '0')))){ // if location below is out of bounds, then skip; otherwise, check if higher
            risk += height;
            ++count;
            }
          }
        }
      }
    }
  }
  return risk + count;
}