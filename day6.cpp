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

// Part 2

vector<int> addNumbers(vector<int> firstNumber, vector<int> secondNumber){
  vector<int> sum;
  int n = firstNumber.size();
  int m = secondNumber.size();
  int M = std::max(m,n);//make both number vectors the same length
  if (n < m){
    for (int i = 0; i < m-n; i++){
      firstNumber.push_back(0);
    }
  }
  if (m < n){
    for (int i = 0; i < n-m; i++){
      secondNumber.push_back(0);
    }
  }
  
  //add digit by digit, starting with the 1s, then the 10s, and so on
  int carry = 0;
  for (int i = 0; i < M; i++){
    if (firstNumber[i] + secondNumber[i] + carry > 9){
      sum.push_back(firstNumber[i] + secondNumber[i] + carry - 10);
      carry = 1;
      if (i == M-1){
        sum.push_back(1);
      }
    }
    else{
      sum.push_back(firstNumber[i] + secondNumber[i] + carry);
      carry = 0;
    }
  }
  return sum;
}


vector<vector<int>> sortByTimer(vector<int> timers){
  vector<vector<int>> numberByTimer;//possible timer values are 0 through 8
  for (int i = 0; i < 9; i++){
    vector<int> number;
    number.push_back(0);
    numberByTimer.push_back(number);//initialize each timer value to have a vector<int> to hold the number of fish with that timer value
  }

  //go through the initial list of fish (timers) and count the number of fish with each timer value
  for (int j = 0; j < timers.size(); j++){ 
    vector<int> one;
    one.push_back(1);//turn the number 1 into a vector with 1 in the 0th place
    numberByTimer[timers[j]] = addNumbers(numberByTimer[timers[j]],one);
  }
  return numberByTimer;
}

vector<vector<int>> fishOnDayGiven(vector<vector<int>> fishByTimer, int day){
  vector<vector<int>> currentFish = fishByTimer;
  for (int i = 0; i < day; i++){
    vector<int> momFish = currentFish[0];
    for (int j = 1; j < 9; j++){
      currentFish[j-1] = currentFish[j];//each fish gets a day closer to giving birth
    }
    currentFish[8] = momFish;//give birth to fish
    currentFish[6] = addNumbers(momFish,currentFish[6]);//reset mom's timer to 6
  }
  return currentFish;
}

vector<int> totalFish(vector<vector<int>> fishNumbers){
  vector<int> totalNumber = fishNumbers[0];
  for (int i = 1; i < 9; i++){
    totalNumber = addNumbers(totalNumber,fishNumbers[i]);
  }
  return totalNumber;
}
