#include "functions.h"

vector<pair<vector<string>,vector<string>>> getSensorDisplays(vector<string> data){
  vector<pair<vector<string>,vector<string>>> recordedDisplays;
  vector<string> digitDisplays;
  vector<string> outputDisplays;
  for (int i = 0; i < data.size(); i++){
    int split_pos = 0;
    int last_pos = 0;
    int delimiter_pos = data[i].find('|');
    while (split_pos < delimiter_pos){  
      split_pos = data[i].find(" ", last_pos);
      if (split_pos > delimiter_pos){
        last_pos = delimiter_pos + 2;
      }
      else {
        digitDisplays.push_back(data[i].substr(last_pos,split_pos-last_pos));
        last_pos = split_pos + 1;
      }
    }
    while (split_pos != string::npos){
      split_pos = data[i].find(" ", last_pos);
      outputDisplays.push_back(data[i].substr(last_pos, split_pos - last_pos));
      last_pos = split_pos + 1;
    }
    recordedDisplays.push_back(make_pair(digitDisplays,outputDisplays));
    digitDisplays.clear();
    outputDisplays.clear();
  }
  return recordedDisplays;
}

int findEasyDigits(vector<pair<vector<string>,vector<string>>> displays){
  int count = 0;
  for (int i = 0; i < displays.size(); i++){
    for (int j = 0; j < displays[i].second.size(); j++){
      if ((displays[i].second[j].length() < 5) || (displays[i].second[j].length() == 7)){
        count++;
      }
    }
  }
  return count;
}

string segmentsOn(vector<string> displays, int numberOn){
  string digit;
  for (int i = 0; i < displays.size(); i++){
    if (displays[i].length() == numberOn)
      digit = displays[i];
  }
  return digit;
}

bool isContainedIn(string key, string display){
  bool isFound = true;
  int split_pos = 0;
  for (string::iterator it = key.begin(); it != key.end(); ++it){
    split_pos = display.find(*it, 0);
    if (split_pos == string::npos){
      isFound = false;
    }
  }
  return isFound;
}

int findOutputSum(vector<pair<vector<string>,vector<string>>> displays){
  int sum = 0;
  for (int i = 0; i < displays.size(); i++){
    int split_pos = 0;
    string one = segmentsOn(displays[i].first, 2);//find the segment on for the digit 1
    string four = segmentsOn(displays[i].first, 4);//find the segments on for the digit 4
    //remove the segments that are on in the digit 1
    for (string::iterator it=one.begin(); it!=one.end(); ++it){
      split_pos = four.find(*it, 0);
      four.erase(split_pos,1);
    }
    //use these keys to identify the digits with the same number of segments on as you go through the outputs
    int power = 1000; // because there are four digits in the output display
    for (int j = 0; j < displays[i].second.size(); j++){ 
      string segments = displays[i].second[j];// go through the output digits
      if (segments.length() == 2){
        sum += 1 * power; // this digit is 1, and power multiplies by the jth power of 10
      }
      else if (segments.length() == 3){
        sum += 7 * power; // this digit is 7, and power multiplies by the jth power of 10
      }
      else if (segments.length() == 4){
        sum += 4 * power; // this digit is 4, and power multiplies by the jth power of 10
      }
      else if (segments.length() == 7){
        sum += 8 * power; // this digit is 8, and power multiplies by the jth power of 10
      }
      else if (segments.length() == 5){ //there are 3 digits with 5 segments on
        if (isContainedIn(one, segments)){
          sum += 3 * power; // this digit is 3, and power multiplies by the jth power of 10
        }
        else if (isContainedIn(four, segments)){
          sum += 5 * power; // this digit is 5, and power multiplies by the jth power of 10
        }
        else {
          sum += 2 * power; // this digit is 2, and power multiplies by the jth power of 10
        }
      }
      else if (segments.length() == 6){ // there are 3 digits with 6 segments on
        if ((isContainedIn(one, segments)) && (isContainedIn(four, segments))){
          sum += 9 * power; // this digit is 9, and power multiplies by the jth power of 10
        }
        else if (isContainedIn(one, segments)){
          sum += 0 * power; // this digit is 0, and power multiplies by the jth power of 10
        }
        else {
          sum += 6 * power; // this digit is 6, and power multiplies by the jth power of 10
        }
      }
      power = power / 10;
    }
  }
  return sum;
}
  
