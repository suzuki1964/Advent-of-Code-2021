#include "functions.h"

bool isOpen(char c){
  string openChars = {"([{<"};
  bool open = false;
  int split_pos = openChars.find(c,0);
  if (split_pos != string::npos){
    open = true;
  }
  return open;
}

bool isPair(char a, char b){
  bool matches = false;
  if ((a == '(') && (b == ')')){
    matches = true;
  }
  if ((a == '[') && (b == ']')){
    matches = true;
  }
  if ((a == '{') && (b == '}')){
    matches = true;
  }
  if ((a == '<') && (b == '>')){
    matches = true;
  }
  return matches;
}

vector<char> getSyntaxErrors(vector<string> data){
  vector<char> errors;
  stack<char> syntax;
  for (int i = 0; i < data.size(); ++i){
    for (int j = 0; j < data[i].length(); ++j){
      bool addToStack = isOpen(data[i].at(j));
      if (addToStack){
        syntax.push(data[i].at(j));
      }
      else {
        if (isPair(syntax.top(),data[i].at(j))){
          syntax.pop();
        }
        else {
          errors.push_back(data[i].at(j));
          break;
        }
        
      }
    }
  }
  return errors;
}

int getScore(vector<char> errors){
  int score = 0;
  for (int i = 0; i < errors.size(); ++i){
    switch (errors[i]){
      case ')': score += 3;
      break;
      case ']': score += 57;
      break;
      case '}': score += 1197;
      break;
      case '>': score += 25137;
      break;
    }
  }
  return score;
}

//Part 2

vector<vector<char>> getFixes(vector<string> data){
  vector<char> fixes;
  vector<vector<char>> allFixes;
  stack<char> syntax;
  for (int i = 0; i < data.size(); ++i){
    for (int j = 0; j < data[i].length(); ++j){
      bool addToStack = isOpen(data[i].at(j));
      if (addToStack){
        syntax.push(data[i].at(j));
      }
      else {
        if (isPair(syntax.top(),data[i].at(j))){
          syntax.pop();
        }
        else {
          while (!syntax.empty()){
            syntax.pop();
          }
          break;
        }
      }
    }
    while (!syntax.empty()){
      switch (syntax.top()){
        case '(': fixes.push_back(')'); break;
        case '[': fixes.push_back(']'); break;
        case '{': fixes.push_back('}'); break;
        case '<': fixes.push_back('>'); break;
      }
      syntax.pop();
    }
    if (fixes.size() > 0){
      allFixes.push_back(fixes);
    }
    fixes.clear();
  }
  return allFixes;
}

vector<vector<int>> getAutoScore(vector<vector<char>> fixes){ //numbers too big for int
  vector<vector<int>> scoreList;
  for (int i = 0; i < fixes.size(); i++){
    vector<int> score; //store and calculate digit by digit, with the 1s digit in the 0th place, the 10s in 1st place, 100s in 2nd,...
    score.push_back(0);
    int exponent = fixes[i].size();
    for (int j = 0; j < exponent; j++){
      int pointValue = 0;
      switch (fixes[i][j]){
        case ')': pointValue = 1;
        break;
        case ']': pointValue = 2;
        break;
        case '}': pointValue = 3;
        break;
        case '>': pointValue = 4;
        break;
      }
      int carry = 0;
      int product = 0;
      for (int k = 0; k < score.size(); ++k){
        product = (score[k] * 5) + carry;
        if (k == 0){
          product += pointValue;
        }
        carry = floor(product / 10);
        score[k] = (product % 10);
      }
      if (carry != 0){
        score.push_back(carry);
      }
    }  
    scoreList.push_back(score);
  }
  return scoreList;
}

vector<pair<int, int>> sortByLength(vector<vector<int>> scores){
  vector<pair<int, int>> length; // pair of (length, which line it fixes)
  length.push_back(std::make_pair(scores[0].size(), 0));
  for (int i = 1; i < scores.size(); ++i){
    int j = 1;
    if (scores[i].size() >= length[i-1].first){
      length.push_back(std::make_pair(scores[i].size(),i));
    }
    else {
      while ((scores[i].size() < length[i-j].first) && (j <= i)){
        j++;
      }
      length.insert(length.end()-j+1, std::make_pair(scores[i].size(),i));
    }
  }
  return length;
}


vector<int> getMidScore(vector<pair<int,int>> length, vector<vector<int>> scores){
  // length is a list of pairs of (length of autocorrect scores, which line it fixes)
  //find the middle value
  int midPoint = (length.size() - 1)/2;
  //std::cout << "middle point " << midPoint << std::endl;
  
  //take all the scores of that same length and sort them by the last digit (which is the highest power of ten)
  int scoreLength = length[midPoint].first; //this is the length of the score in the middle of the list
  int j = 1;
  while ((scoreLength == length[midPoint-j].first) && (j <= midPoint)){ //find the first score in the list with the same length
    j++;
  }
  //now j-1 is the offset, that is, how many scores of the same length were before the middle value

  //sort the list of line numbers (with the same score length) by the last digit
  //the middle value will be the (j-1)st one in this new list of indices
  //use the next digit in that "middle" score to sort the now shorter list of scores that have the same length and the same last digit
  //same steps: find the offset, sort by key digit, use the "middle" score to set the next digit to sort by
  
  //make a shortList of the line numbers with the same length as the middle score
  vector<int> shortList;
  shortList.push_back(length[midPoint-j+1].second);
  int lastDigitOfLastScore = scores[length[midPoint-j+1].second][scoreLength - 1];
  int k = 1;
  while ((scoreLength == length[midPoint-j+1+k].first) && (k < midPoint+j)){
    int lastDigitOfCurrentScore = scores[length[midPoint-j+1+k].second][scoreLength - 1];
    if (lastDigitOfCurrentScore >= lastDigitOfLastScore){
      shortList.push_back(length[midPoint-j+1+k].second);
      lastDigitOfLastScore = lastDigitOfCurrentScore;
    }
    else{
      int m = 1;
      int n = shortList.size();
      while ((lastDigitOfCurrentScore < scores[shortList[n-m]][scoreLength - 1]) && (m <= n)){
        m++;
      }
      shortList.insert(shortList.end()-m+1, length[midPoint-j+1+k].second);
    }
    k++;
  }
  /*
  std::cout << "short list ";
  for (int print = 0; print < shortList.size(); print++){
    std::cout << shortList[print] << " ";
  }
  std::cout << std::endl;
  */

  //for each key p (which digit in the score to sort by)
  //start with a list of line numbers which all have the same length, last digit, ..., (p+1)st digit
  //find the offset j where j-1 of the scores on the list have the same p-th digit
  //sort the shorter list of line numbers (with the same (p)th digit) by the p-th digit
  //the middle value will be the (j-1)st one in this new list of indices
  midPoint = j - 1;
  for (int key = scoreLength - 2; key >= 0; key--){
    shortList = sortByKey(key, midPoint, shortList, scores);
    /*
    std::cout << "key " << key << " short list ";
    for (int print = 0; print < shortList.size(); print++){
      std::cout << shortList[print] << " ";
    }
    std::cout << std::endl;
    */
    if (shortList.size() == 1){
      return scores[shortList[0]];
    }
  }
  return scores[shortList[0]];
}

vector<int> sortByKey(int key, int &middle, vector<int> list, vector<vector<int>> scores){
  int offset = 1;
  int digit = scores[list[middle]][key+1];//this is the (key+1)th digit of the middle score
  //find the first score in the list with the same (key+1)th digit
  while ((digit == scores[list[middle-offset]][key+1]) && (offset <= middle)){ 
    offset++;
  }
  vector<int> lineNumbers;
  lineNumbers.push_back(list[middle-offset+1]);
  int i = 1;
  while ((digit == scores[list[middle-offset+1+i]][key+1]) && (middle-offset+1+i < list.size())){
    int keyDigitOfCurrentScore = scores[list[middle-offset+1+i]][key];
    if (keyDigitOfCurrentScore >= scores[lineNumbers.back()][key]){
      lineNumbers.push_back(list[middle-offset+1+i]);
    }
    else{
      int m = 1;
      int n = lineNumbers.size();
      while ((keyDigitOfCurrentScore < scores[list[n-m]][key]) && (m <= n)){
        m++;
      }
      lineNumbers.insert(lineNumbers.end()-m+1, list[middle-offset+1+i]);
    }
    i++;
  }
  middle = offset - 1;
  return lineNumbers;
}
