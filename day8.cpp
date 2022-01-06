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