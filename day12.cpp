#include "functions.h"

vector<pair<string, string>> getPairs(vector<string> data){
  vector<pair<string, string>> pairs;
  for (int i = 0; i < data.size(); ++i){
    string caveNameOne; //for each connected pair of caves, we read out the cave names
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
  caves.push_back(std::make_pair("start", false)); // we start with the "start" cave (which is small)
  for (int i = 0; i < edges.size(); ++i){ //for each edge, we check the names of the caves
    string caveNameOne = edges[i].first;
    string caveNameTwo = edges[i].second;
    if ((!caveNameInList(caveNameOne, caves)) && (caveNameOne != "end")){ //if the name of the cave is not in the list yet (and is not "end", we add it to the list and set a flag if it is large
      caves.push_back(std::make_pair(caveNameOne, isupper(caveNameOne[0])));
    }
    if ((!caveNameInList(caveNameTwo, caves)) && (caveNameTwo != "end")){
      caves.push_back(std::make_pair(caveNameTwo, isupper(caveNameTwo[0])));
    }
  }
  caves.push_back(std::make_pair("end", false)); // we put the "end" cave last on our list
  return caves;
}

bool caveNameInList(string caveName, vector<pair<string, bool>> caves){ // this just checks if the name is in the list
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

  /* // prints out the adjacency matrix
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
      return i;
    }
  }
  return 0;
}

vector<vector<string>> getPaths(vector<vector<int>> matrix, vector<pair<string, bool>> nodes, int &twice){
  // gets all paths that visit small caves once (twice if it is the special cave with index "twice")
  vector<vector<string>> paths;
  vector<string> path;
  path.push_back("start");
  getNextCave(0, matrix, nodes, path, paths, twice);
  return paths;
}

void getNextCave(int i, vector<vector<int>> matrix, vector<pair<string, bool>> nodes, vector<string> path, vector<vector<string>> &paths, int &twice){
//gets the next cave in the current path
  vector<vector<int>> activeCaves = matrix;
  vector<string> currentPath = path;
  bool didAdd = false; //we need to know if we successfully added a cave to the path or if we need to reset and go back a step
  int addedIndex; //we need to know the index of the cave we added just before we had to step back
  int originalTwice = twice; //this is the special small cave we can visit twice
  int j = 1; //skip the "start" cave
  while (j < matrix[i].size()){
    if (matrix[i][j] == 1){ //if the two caves are connected then add the cave j
      didAdd = true;
      currentPath.push_back(nodes[j].first);
      if (j != nodes.size()-1){ //if we are not at end
        if ((!nodes[j].second) && (j != twice)){//if it is a small cave and it is not special, then we can't visit it again
          addedIndex = j;
          for (int k = 0; k < matrix.size(); ++k){
            activeCaves[k][j] = 0; // remove from adjacency matrix of active caves
          }
        }
        if (j == twice){ //if this is the first time we are visiting the special cave, then set "twice" to zero to we can't visit any small cave twice again
          twice = 0;
        }
        getNextCave(j, activeCaves, nodes, currentPath, paths, twice);
      }
      else { //if we are at end
        paths.push_back(currentPath);
        return;
      }
    }
    if (didAdd){ //if we added a cave and are now going back, we need to take off the last cave added to the path
      currentPath.pop_back();
      for (int k = 0; k < matrix.size(); ++k){ // return adjacency matrix values
        activeCaves[k][addedIndex] = matrix[k][addedIndex];
      }
      addedIndex = 0; // and reset all these values  
      didAdd = false;
      twice = originalTwice;
    }
    ++j;
  }
  if (didAdd){
    currentPath.pop_back();
    didAdd = false;
  }
  return;
}

//Part 2
int getSpecialPaths(vector<vector<int>> matrix, vector<pair<string, bool>> nodes){
  int pathCount = 0;
  int pathSingleCount = 0;
  for (int i = 0; i < matrix.size(); ++i){
    if (!nodes[i].second){ //if it is a small cave, set it equal to the special cave to visit twice
      int twice = i;
      vector<vector<string>> pathTwiceList = getPaths(matrix,nodes,twice);
      if (twice == 0){
        pathSingleCount = pathTwiceList.size(); //we need to subtract out the paths with only single visits to get the number of paths with two visits to small cave i
      }
      pathCount += pathTwiceList.size() - pathSingleCount;
    
    }
  }
  pathCount += pathSingleCount; // then we need to add back in the number of paths with onlh single visits
  return pathCount;
}
  
