#include "functions.h"

vector<int> getInitTimers(vector<string> data){
  vector<int> timers;
  int split_pos = 0;
  int last_pos = 0;
  for (int i = 0; i < data.size(); i++){
    while (split_pos != string::npos){
      split_pos = data[i].find(",",last_pos); // looking for the end of the first number
      timers.push_back(stoi(data[i].substr(last_pos, split_pos-last_pos)));
      last_pos = split_pos+1;
    }
  }
  return timers;
}

vector<vector<int>> getDailyTimers(vector<int> timers, int days){
  //days is the number of days you want to check on the fish
  vector<vector<int>> dailyTimers;
  vector<int> currentDayTimers = timers;
  vector<int> nextDayTimers;
  dailyTimers.push_back(timers); //put in initial values
  for (int i = 0; i < days; i++){
    nextDayTimers = oneDayLater(currentDayTimers);
    dailyTimers.push_back(nextDayTimers);
    currentDayTimers = nextDayTimers;
  }
  return dailyTimers;
}
 // dailyTimerValues.push_back(timerValues);

vector<int> oneDayLater(vector<int> timers){
  int birthTime = 6;
  int growthTime = 8;
  vector<int> nextTimers = timers;
  for (int i = 0; i < timers.size(); i++){
    //count down timer by one day if it is not zero
    if (timers[i] > 0){
      nextTimers[i]-- ;
    }
    else {
      //if it is 0, then it should produce a child and reset the timer to the birthTime
      nextTimers[i] = birthTime;
      nextTimers.push_back(growthTime);
    }
  }
  return nextTimers;
}
