#include "functions.h"

vector<pair<string, string>> getPairs(vector<string> data){
  vector<pair<string, string>> pairs;
  for (int i = 0; i < data.size(); ++i){
    string caveNameOne;
    string caveNameTwo;
    int split_pos = 0;
    int last_pos = 0;
    split_pos = data[i].find("-", last_pos);
    caveNameOne = data[i].substr(last_pos, split_pos-last_pos);
    last_pos = split_pos + 1;
    caveNameTwo = data[i].substr(last_pos);
    pairs.push_back(make_pair(caveNameOne, caveNameTwo));
  }
  return pairs;
}

vector<pair<string, bool>> getCaves(vector<pair<string,string>> edges){
  vector<pair<string, bool>> caves;
  caves.push_back(std::make_pair("start", false));
  for (int i = 0; i < edges.size(); ++i){
    string caveNameOne = edges[i].first;
    string caveNameTwo = edges[i].second;
    if ((!caveNameInList(caveNameOne, caves)) && (caveNameOne != "end")){
      caves.push_back(std::make_pair(caveNameOne, isupper(caveNameOne[0])));
    }
    if ((!caveNameInList(caveNameTwo, caves)) && (caveNameTwo != "end")){
      caves.push_back(std::make_pair(caveNameTwo, isupper(caveNameTwo[0])));
    }
  }
  caves.push_back(std::make_pair("end", false));
  return caves;
}

bool caveNameInList(string caveName, vector<pair<string, bool>> caves){
  bool inList = false;
  for (int i = 0; i < caves.size(); ++i){
    if (caveName.compare(caves[i].first) == 0){
      inList = true;
      break;
    }
  }
  return inList;
}

vector<vector<int>> getConnections(vector<pair<string, string>> edges, vector<pair<string, bool>> list){
  vector<vector<int>> adjacencyMatrix;// 1 if caves i and j are connected; true if visited
  vector<int> zero;
  zero.assign(list.size(),0);
  adjacencyMatrix.assign(list.size(),zero);

  for (int i = 0; i < edges.size(); ++i){
    int j = caveIndex(edges[i].first,list);
    int k = caveIndex(edges[i].second,list);
    adjacencyMatrix[j][k] = 1;
    adjacencyMatrix[k][j] = 1;
  }

  /*
  for (int i = 0; i < list.size(); ++i){
    for (int j = 0; j < list.size(); ++j){
      std::cout << adjacencyMatrix[i][j] << " at " << i << ", " << j << std::endl;
    }
  }
  */
  return adjacencyMatrix;
}

int caveIndex(string name, vector<pair<string, bool>> list){
  for (int i = 0; i < list.size(); ++i){
    if (name.compare(list[i].first) == 0){
      //std::cout << "name " << name << ", index " << i << std::endl;
      return i;
    }
  }
  return 0;
}

vector<vector<string>> getPaths(vector<vector<int>> matrix,vector<pair<string, bool>> nodes){
  vector<vector<string>> paths;
  vector<string> path;
  path.push_back("start");
  getNextCave(0, matrix, nodes, path, paths);
  return paths;
}

void getNextCave(int i, vector<vector<int>> matrix, vector<pair<string, bool>> nodes, vector<string> path, vector<vector<string>> &paths){
  vector<vector<int>> activeCaves = matrix;
  vector<string> currentPath = path;
  bool didAdd = false;
  int addedIndex;
  int j = 1;
  while (j < matrix[i].size()){
    if (matrix[i][j] == 1){
      didAdd = true;
      currentPath.push_back(nodes[j].first);
      if (j != nodes.size()-1){ //if we are not at end
        if (!nodes[j].second){//if it is a small cave, then we can't visit it again
          addedIndex = j;
          for (int k = 0; k < matrix.size(); ++k){
            activeCaves[k][j] = 0; // remove from adjacency matrix of active caves
          }
        }
        getNextCave(j, activeCaves, nodes, currentPath, paths);
      }
      else{ //if we are at end
        paths.push_back(currentPath);
        return;
      }
    }
    if (didAdd){
      currentPath.pop_back();
      for (int k = 0; k < matrix.size(); ++k){ // return adjacency matrix values
        activeCaves[k][addedIndex] = matrix[k][addedIndex];
      }
      addedIndex = 0;
      didAdd = false;
    }
    ++j;
  }
  if (didAdd){
    currentPath.pop_back();
    didAdd = false;
  }
  return;
}
  
