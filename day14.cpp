#include "functions.h"

pair<vector<pair<char, long int>>, vector<vector<pair<long int,int>>>> getPolymers(vector<string> data){//the data is a list of elements in the polymer, followed by a blank line, then a list of instructions like "CH -> B" which tell you what element to insert between the two adjacent elements
  vector<pair<char, long int>> elementList;//list of elements and how many times the element is in the polymer
  vector<vector<pair<long int,int>>> polymerPairsAndInsert;//matrix of pairs of adjacent elements:first is the number of times the pair is in the polymer, second is the index of the element to insert between them
  
  char newElement = data[0][0];//read in the first element
  elementList.push_back(std::make_pair(newElement,1));
  int lastElementIndex = 0;
  vector<pair<long int,int>> row;//set up a vector to add a row to the matrix of adjacent elements
  row.push_back(std::make_pair(0,0));
  polymerPairsAndInsert.push_back(row);

//load in the initial polymer: make a list of elements, set up matrix that counts adjacent pairs
  for (int i = 1; i < data[0].length(); ++i){//read through the polymer
    newElement = data[0][i];
    std::cout << newElement << std::endl;
    addElement(newElement, lastElementIndex, elementList, polymerPairsAndInsert, row);//put each element in the list and count them, and make a matrix that counts the adjacent pairs of elements
  }

  //read in the instructions on which element to insert between pairs of elements
  int noAdjacent = -1; // set a flag to say this is a new element from the insertions, so no adjacent element
  for (int i = 2; i < data.size(); ++i){//read in which element to insert between given pairs of elements
    int firstIndex = getIndex(data[i][0], elementList);
    if (firstIndex == -1){
      addElement(data[i][0], noAdjacent, elementList, polymerPairsAndInsert, row);
      firstIndex = elementList.size()-1;
    }
    int secondIndex = getIndex(data[i][1], elementList);
    if (secondIndex == -1){
      addElement(data[i][1], noAdjacent, elementList, polymerPairsAndInsert, row);
      secondIndex = elementList.size()-1;
    }
    int insertIndex = getIndex(data[i][6], elementList);
    polymerPairsAndInsert[firstIndex][secondIndex].second = insertIndex;
  }

  //return both the list of elements and the matrix of adjacent pairs
  pair<vector<pair<char, long int>>, vector<vector<pair<long int,int>>>> pair = std::make_pair(elementList,polymerPairsAndInsert);
  //printMatrix(polymerPairsAndInsert);
  return pair;
}

void addElement(char current, int &last, vector<pair<char,long int>> &list,  vector<vector<pair<long int,int>>> &matrix, vector<pair<long int,int>> &row){
  int indexOf = getIndex(current, list);
  if (indexOf != -1){ //if the current element is already in the list,
    list[indexOf].second ++; // add one to the count
    matrix[last][indexOf].first ++;//add one to the count of the adjacent pair in the matrix 
    last = indexOf; //set to the index of the last element in the polymer
    return;
  }
  else{ //if it is not in the list
    list.push_back(std::make_pair(current,0));//add the element to the list
    makeBigger(matrix, row);
    if (last != -1){ //if current is part of the polymer
      list[list.size() - 1].second = 1;//set the count to 1 if it is part of the polymer
      matrix[last][list.size()-1].first ++;//add one to the count of adjacent pairs
      last = list.size() - 1;//set the index to the last element in the list
    }
    return;
  }
}

void makeBigger(vector<vector<pair<long int,int>>> &matrix,vector<pair<long int,int>> &row){
  matrix.push_back(row);//add a row to the matrix
  row.push_back(std::make_pair(0,0)); //add a pair to the blank row
  for (int i = 0; i < matrix[0].size(); ++i){//add a pair to each row of the matrix (so add a column to the matrix)
    matrix[i].push_back(std::make_pair(0,0));
  }
  
}

void printMatrix(vector<vector<pair<long int,int>>> matrix){
  for (int i = 0; i < matrix.size(); ++i){
    for (int j = 0; j < matrix[i].size(); ++j){
      //std::cout << matrix[i][j].first << ", " << matrix[i][j].second << "   ";
      std::cout << matrix[i][j].first << "   ";//print just the counts of pairs
    }
  std::cout << std::endl;
  }
  std::cout << std:: endl;
}

int getIndex(char c, vector<pair<char, long int>> list){
  for (int i = 0; i < list.size(); ++i){
    if (c == list[i].first){
      return i;
    }
  }
  return -1;
}

pair<vector<pair<char, long int>>, vector<vector<pair<long int,int>>>> insertElements(pair<vector<pair<char, long  int>>, vector<vector<pair<long int,int>>>> countsAndInstructions, int steps){
  vector<pair<char, long int>> list = countsAndInstructions.first;
  vector<pair<char, long int>> newList = countsAndInstructions.first;
  vector<vector<pair<long int,int>>> matrix = countsAndInstructions.second;
  vector<vector<pair<long int,int>>> newMatrix = countsAndInstructions.second;
  for (int n = 0; n < steps; ++n){
    for (int i = 0; i < matrix.size(); ++i){
      for (int j = 0; j < matrix.size(); ++j){
        if (matrix[i][j].first != 0){//if this pair (i,j) is in the polymer
          long int numberOfThesePairs = matrix[i][j].first; 
          int indexOfElementToInsert = matrix[i][j].second; 
          newMatrix[i][j].first -= numberOfThesePairs;
          newMatrix[i][indexOfElementToInsert].first += numberOfThesePairs; // add to count of new first pair
          newMatrix[indexOfElementToInsert][j].first += numberOfThesePairs; // add to count of new second pair
          newList[indexOfElementToInsert].second += numberOfThesePairs; // add to count of inserted element
        }
      }
    }
    matrix = newMatrix;
    list = newList;
  }
  pair<vector<pair<char, long int>>, vector<vector<pair<long int,int>>>> pair = std::make_pair(newList,newMatrix);
  return pair;
}

long int getDifference(vector<pair<char, long int>> list){
  long int min = list[0].second;
  long int max = list[0].second;
  long int difference = 0;
  for (int i = 1; i < list.size(); ++i){
    if (list[i].second < min){
      min = list[i].second;
    }
    if (list[i].second > max){
      max = list[i].second;
    }
  }
  difference = max - min;
  return difference;
}