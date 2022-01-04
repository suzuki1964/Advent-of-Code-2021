#include "functions.h"

vector<int> getTimers(vector<string> data){
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

vector
//so, dailyTimerValues[0] is the set of initial timer values
  dailyTimerValues.push_back(timerValues);
  //the number of days you want to check on the fish
  int days = 18;


vector<vector<int>> oneDayLater(vector<vector<int>> timers){
  <vector<int>> nextDay;
  int lastDay = timers.size();
  for (int i = 0; i < timers[lastDay].size(); i++)
    
}