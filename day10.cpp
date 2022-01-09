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