#include "functions.h"

//each line of data looks like 0,9 -> 5,9; last line gives the maximum values of x and y
vector<pair<pair<int,int>,pair<int,int>>> getEndpoints(vector<string> data){
  vector<std::pair<pair<int,int>,pair<int,int>>> endPoints;\
  int split_pos = 0;
  int last_pos = 0;
  int x_max = 0;
  int y_max = 0;
  for (int i=0; i<data.size(); i++){
    endPoints.push_back(pair(pair(0,0),std::pair(0,0)));
    split_pos = data[i].find(",",last_pos); // looking for the end of the first number
    endPoints[i].first.first = stoi(data[i].substr(last_pos, split_pos-last_pos));
    if (endPoints[i].first.first > x_max){x_max = endPoints[i].first.first;}
    last_pos = split_pos+1;
    split_pos = data[i].find(" ",last_pos); // looking for the end of the second number
    endPoints[i].first.second = stoi(data[i].substr(last_pos, split_pos-last_pos));
    if (endPoints[i].first.second > y_max){y_max = endPoints[i].first.second;}
    last_pos = split_pos+1;
    split_pos = data[i].find(" ",last_pos); // looking for the start of the third number
    last_pos = split_pos+1;
    split_pos = data[i].find(",",last_pos); // looking for the end of the third number
    endPoints[i].second.first = stoi(data[i].substr(last_pos, split_pos-last_pos));
    if (endPoints[i].second.first > x_max){x_max = endPoints[i].second.first;}
    last_pos = split_pos+1;
    split_pos = data[i].find("\n",last_pos); // looking for the end of the last number
    endPoints[i].second.second = stoi(data[i].substr(last_pos, split_pos-last_pos));
    if (endPoints[i].second.second > y_max){y_max = endPoints[i].second.second;}
    split_pos = 0;
    last_pos = 0;
  }
  endPoints.push_back(pair(pair(0,0),std::pair(x_max,y_max)));
  return endPoints;
}

vector<vector<pair<int,int>>> getVentLines(vector<pair<pair<int,int>,pair<int,int>>> endPoints){
  vector<vector<pair<int,int>>> lines;
  vector<pair<int,int>> linePoints;
  int x_start = 0;
  int y_start = 0;
  int x_end = 0;
  int y_end = 0;
  //don't do the last pair in endPoints -- it is the x_max, y_max line
  for (int i = 0; i < endPoints.size() - 1; i++){
    x_start = endPoints[i].first.first;
    y_start = endPoints[i].first.second;
    x_end = endPoints[i].second.first;
    y_end = endPoints[i].second.second;
    if (x_start == x_end){
      if (y_start < y_end){
        for (int j = y_start; j <= y_end; j++){
          linePoints.push_back(pair(x_start,j));
        }
      }
      else if (y_start > y_end){
        for (int j = y_end; j <= y_start; j++){
          linePoints.push_back(pair(x_start,j));
        }
      }
    }
    else if (y_start == y_end){
      if (x_start < x_end){
        for (int j = x_start; j <= x_end; j++){
          linePoints.push_back(pair(j,y_start));
        }
      }
      else if (x_start > x_end){
        for (int j = x_end; j <= x_start; j++){
          linePoints.push_back(pair(j,y_start));
        }
      }
    }
    lines.push_back(linePoints);
    linePoints.clear();
  }
  return lines;
}

vector<vector<pair<int,int>>> addDiagVentLines(vector<vector<pair<int,int>>> lines,vector<pair<pair<int,int>,pair<int,int>>> endPoints){
  vector<pair<int,int>> linePoints;
  int x_start = 0;
  int y_start = 0;
  int x_end = 0;
  int y_end = 0;
  //again, don't do the last line in endPoints -- it is just there to find x_max and y_max
  for (int i = 0; i < endPoints.size() - 1; i++){
    
    x_start = endPoints[i].first.first;
    y_start = endPoints[i].first.second;
    x_end = endPoints[i].second.first;
    y_end = endPoints[i].second.second;
    if ((x_end - x_start) == (y_end - y_start)){
      if (y_start < y_end){
        for (int j = y_start; j <= y_end; j++){
          linePoints.push_back(pair(x_start + j - y_start,j));
        }
      }
      else if (y_start > y_end){
        for (int j = y_end; j <= y_start; j++){
          linePoints.push_back(pair(x_end + j - y_end,j));
        }
      }
    }
    else if ((x_end - x_start) == -(y_end - y_start)){
      if (x_start < x_end){
        for (int j = x_start; j <= x_end; j++){
          linePoints.push_back(pair(j,y_start - j + x_start));
        }
      }
      else if (x_start > x_end){
        for (int j = x_end; j <= x_start; j++){
          linePoints.push_back(pair(j,y_end - j + x_end));
        }
      }
    }
    lines.push_back(linePoints);
    linePoints.clear();
  }
  return lines;
}

void markVentLines (int x_size, int y_size, int chart[], vector<vector<pair<int,int>>> lines){
  //int map[(y_size+1) * (x_size+1)];
  for (int i = 0; i <= y_size; i++){
   for (int j = 0; j <= x_size; j++){
     chart[(i * (x_size+1)) + j] = 0;
    }
  }
  /*
  for (int i = 0; i <= y_size; i++){
   for (int j = 0; j <= x_size; j++){
     std::cout << chart[(i * (x_size+1)) + j] << " ";
    }
    std::cout << "\n";
  }
  */
  for (int i = 0; i < lines.size(); i++){
   for (int j = 0; j < lines[i].size(); j++){
     //std::cout << "(" << lines[i][j].first << ", " << lines[i][j].second << ") ";
     chart[(lines[i][j].second * (x_size+1)) + lines[i][j].first]+= 1;
     //std::cout << chart[(lines[i][j].second * (x_size+1)) + lines[i][j].first] << "\n";
     //chart[lines[i][j].second][lines[i][j].first] ;
   }
 }
 /*
 for (int i = 0; i <= y_size; i++){
   for (int j = 0; j <= x_size; j++){
     std::cout << chart[(i * (x_size+1)) + j] << " ";
   }
   std::cout << "\n";
  }
  */
}


int getDangerZone (int x_size, int y_size, int chart[]){
  int danger = 0;
  for (int i = 0; i <= y_size; i++){
    for (int j = 0; j <= x_size; j++){
      if (chart[(i * (x_size+1)) + j] > 1){
       danger++;
      }
    }
  }
  return danger;
}