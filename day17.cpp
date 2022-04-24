#include "functions.h"

pair<int,int> Day17(string filename) {
  pair<int,int> highestAndNumber;
	vector<string> targetData = getData(filename); //data is just one string of the form "target area: x=20..30, y=-10..-5"
  vector<pair<int,int>> ranges;
  ranges = findRanges(targetData[0]); //the vector of ranges (start, end) for x and y
  highestAndNumber = maxHeight(ranges); //max height of probe and number of initial velocities that hit the target
  return highestAndNumber;
}

pair<int,int> maxHeight(vector<pair<int,int>> range){ //find the max height of probe over all initial velocities that hit target and the number of initial velocities that work
  int maxHeight = 0;
  int count = 0;
  pair<int,int> heightAndCount;
  //the x velocity goes down by 1 each time and then stays at 0, so the furthest it can go is x(x+1)/2
  //this has to get to the target area, so it should be in the range of x values
  //take the smaller of the x values in range[0], multiply by 2, take the square root
  //make into an int, subtract 1 to be safe, make sure it isn't negative
  int xMin = std::max(0, int(sqrt(2*std::min(range[0].first,range[0].second))-1)); 
  int xMax = std::max(range[0].first,range[0].second); //find the larger of the x range values
  //the y velocity also goes down by 1 each time, so if it goes up at first, it comes down at the same y velocity
  //when it passes the 0 level, it will have the same y velocity as it did going up initially
  //if the absolute value of the y velocity is larger than the further end of the y target range, then it will go right past the target
  int yMax = std::max(abs(range[1].first),abs(range[1].second)); //find the larger magnitude
  for (int xVel = xMin; xVel <= xMax; ++xVel){ //we only need to check these initial velocities
    for (int yVel = -yMax; yVel <= yMax; ++yVel){
      pair<bool,int> didHit = hitTarget(std::make_pair(xVel,yVel),range);
      
      if (didHit.first){ //if the probe hit the target
        count ++;
        if (didHit.second > maxHeight){ //and if the max height on that trajectory was higher than before
          maxHeight = didHit.second; //change the max height to this height
        }
      }
    }
  }
  heightAndCount = std::make_pair(maxHeight,count);
  return heightAndCount;
}

pair<bool,int> hitTarget(pair<int,int> initVelocity,vector<pair<int,int>> range){ //returns true if probe hits target, max height of trajectory
  bool hit = false;
  int height = 0;
  pair<bool,int> probeHit = std::make_pair(hit,height);
  int x = 0; //starting point of probe
  int y = 0;
  pair<int,int> position = std::make_pair(x,y);
  pair<int,int> velocity = initVelocity;
  //while the x position is less than the further part of the target range, and while the y position is larger than the lowest possible part of the target
  while ((position.first <= std::max(range[0].first,range[0].second)) && (position.second >= -std::max(abs(range[1].first),abs(range[1].second)))){ //move the probe one step at a time
    position = moveOnce(position, velocity); //new position after one step
    if (position.second > height){ //store height if higher than previous height
      height = position.second;
    }
    velocity = updateVelocity(velocity); //new velocity after one step
    if (inTarget(position,range)){ //check if it hits the target
      hit = true;
      probeHit = std::make_pair(hit,height);
    } 
  }
  return probeHit;
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

bool inTarget(pair<int,int> position,vector<pair<int,int>> range){
  bool isInTarget = false;
  if ((position.first >= range[0].first) && (position.first <= range[0].second) && (position.second >= range[1].first) && (position.second <= range[1].second)){
    isInTarget = true;
  }
  return isInTarget;
}