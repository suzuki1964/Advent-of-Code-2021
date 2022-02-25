#include "functions.h"

pair<vector<pair<int, int>>, vector<pair<bool, int>>> getInstructions(vector<string> data){
  pair<vector<pair<int, int>>, vector<pair<bool, int>>> inputs;
  vector<pair<int, int>> dotCoordinates;//add max x and y values at the end
  vector<pair<bool, int>> foldInstructions;
  int i = 0;
  int firstCoordinate;
  int secondCoordinate;
  int maxWidth = 0;
  int maxDepth = 0;
  
  while (data[i].find(",") != -1){ //until you get to the blank line
    int split_pos = 0;
    int last_pos = 0;
    split_pos = data[i].find(","); // looking for the end of the first number
    firstCoordinate = stoi(data[i].substr(last_pos, split_pos-last_pos));
    if (maxWidth < firstCoordinate){
      maxWidth = firstCoordinate;
    } 
    last_pos = split_pos+1; //move past the comma
    split_pos = data[i].find(" ",last_pos); // looking for the end of the second number
    secondCoordinate = stoi(data[i].substr(last_pos, split_pos-last_pos));
    if (maxDepth < secondCoordinate){
      maxDepth = secondCoordinate;
    }
    //std::cout << " coords " << firstCoordinate << ", " << secondCoordinate << std::endl;
    dotCoordinates.push_back(std::make_pair(firstCoordinate, secondCoordinate));
    ++i;
  }
  dotCoordinates.push_back(std::make_pair(maxWidth + 1, maxDepth + 1));// add the width and depth at the end
  //std::cout << "found blank line" << std::endl;
  for (int j = i+1; j < data.size(); ++j){ //start after the blank line
    //std::cout << "j " << j << std::endl;
    bool xFold = false;
    int split_pos = 0;
    int last_pos = 0;
    split_pos = data[j].find("="); // direction is just before the "="
    //std::cout << data[j].substr(split_pos-1, 1);
    if (data[j].substr(split_pos-1, 1) == "x"){
      xFold = true;
    }
    last_pos = split_pos+1;
    split_pos = data[j].find(" ",last_pos); // looking for the end of the number
    //std::cout <<  " j " << j << " " << data[j].substr(last_pos, split_pos-last_pos) << std::endl;
    firstCoordinate = stoi(data[j].substr(last_pos, split_pos-last_pos));
    //std::cout << " coord " << firstCoordinate << std::endl;
    foldInstructions.push_back(std::make_pair(xFold, firstCoordinate));
  }
  inputs = std::make_pair(dotCoordinates, foldInstructions);
  return inputs;
}

vector<vector<bool>> markDots(vector<pair<int, int>> coords){
  int maxWidth = coords[coords.size()-1].first;//size gives number of elements, last index is 1 less
  int maxDepth = coords[coords.size()-1].second;
  //std::cout << "width " << maxWidth << ", depth " << maxDepth << std::endl;
  vector<bool> row(maxWidth, false);//initialize a row with all false
  vector<vector<bool>> paper(maxDepth, row);
  for (int i = 0; i < coords.size()-1; ++i){//leave off the last pair which gives the paper size
    paper[coords[i].second][coords[i].first] = true;//the first index goes down
  }
  //showDots(paper);
  return paper;
}

void showDots(vector<vector<bool>> paper){
  for (int i = 0; i < paper.size(); ++i){
    for (int j = 0; j < paper[0].size(); ++j){
      if (paper[i][j]){
        std::cout << "#";
      }
      else{
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

vector<vector<bool>> foldY(vector<vector<bool>> paper, int y){
  vector<bool> row(paper[0].size(), false);
  vector<vector<bool>> foldedPaper(y,row);
  for (int i = 0; i < y; ++i){
    for (int j = 0; j < paper[0].size(); ++j){
      foldedPaper[i][j] = paper[i][j] || paper[2*y - i][j];
    }
  }
  //showDots(foldedPaper);
  return foldedPaper;
}

vector<vector<bool>> foldX(vector<vector<bool>> paper, int x){
  vector<bool> row(x, false);
  vector<vector<bool>> foldedPaper(paper.size(),row);
  for (int i = 0; i < paper.size(); ++i){
    for (int j = 0; j < x; ++j){
      foldedPaper[i][j] = paper[i][j] || paper[i][2*x - j];
    }
  }
  //showDots(foldedPaper);
  return foldedPaper;
}

int countDots(vector<vector<bool>> paper){
  int count = 0;
  for (int i = 0; i < paper.size(); ++i){
    for (int j = 0; j < paper[0].size(); ++j){
      if (paper[i][j]){
        count++;
      }
    }
  }
  return count;
}

vector<vector<bool>> foldPaper(pair<vector<pair<int, int>>, vector<pair<bool, int>>> coordsAndInstructions){
  vector<pair<int, int>> coords = coordsAndInstructions.first;
  vector<pair<bool, int>> instructions = coordsAndInstructions.second;
  vector<vector<bool>> paper = markDots(coords);
  vector<vector<bool>> foldedPaper;
  if (instructions[0].first == true){
    //std::cout << "x" << std::endl;
    foldedPaper = foldX(paper,instructions[0].second);
  }
  else{
    //std::cout << "y" << std::endl;
    foldedPaper = foldY(paper,instructions[0].second);
  }
  return foldedPaper;
}