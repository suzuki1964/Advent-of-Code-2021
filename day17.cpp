#include "functions.h"

int Day17(string filename) {
	int height = 0; //max height of probe
	vector<string> targetData = getData(filename); //data is just one string of the form "target area: x=20..30, y=-10..-5"
  vector<pair<int,int>> ranges;
  ranges = findRanges(targetData[0]); //the vector of ranges (start, end) for x and y
  int x = 0;
  int y = 0;
  pair<int,int> intialPosition = std::make_pair(x,y);
  pair<int,int> initialVelocity = std::make_pair(7,2);
  for (int i = 0; i < 7; ++i){
    pair<int,int> newPosition = moveOnce(intialPosition, initialVelocity);
    std::cout << "position (" << newPosition.first << ", " << newPosition.second << ")" << std::endl;
    pair<int,int> updatedVelocity = updateVelocity(initialVelocity);
    std::cout << "velocity (" << updatedVelocity.first << ", " << updatedVelocity.second << ")" << std::endl;
    intialPosition = newPosition;
    initialVelocity = updatedVelocity;
  }
  
  return height;
}

vector<pair<int,int>> findRanges(string data){
  vector<pair<int,int>> range;
  int split_pos = 0;
  int last_pos = 0;
  while (split_pos != string::npos){
    last_pos = data.find("=",last_pos); // looking for the start of the range
    split_pos = data.find(".",last_pos);
    int start = stoi(data.substr(last_pos+1,split_pos-last_pos-1)); //the start of the range
    last_pos = split_pos+2; //move past the two periods
    split_pos = data.find(",",last_pos); // looking for the end of the second number
    int end = stoi(data.substr(last_pos, split_pos-last_pos)); //the end of the range
    last_pos = split_pos + 1;
    range.push_back(std::make_pair(start,end)); //the first gives the range of x, the second gives the range of y
  }
  return range;
}

pair<int,int> moveOnce(pair<int,int> position, pair<int,int> velocity){
  pair<int,int> newPosition;
  newPosition.first = position.first + velocity.first;
  newPosition.second = position.second + velocity.second;
  return newPosition;
}

pair<int,int> updateVelocity(pair<int,int> velocity){
  pair<int,int> newVelocity;
  if (velocity.first > 0){
    newVelocity.first = velocity.first - 1;
  }
  else if (velocity.first < 0){
    newVelocity.first = velocity.first + 1;
  }
  newVelocity.second = velocity.second - 1;
  return newVelocity;
}