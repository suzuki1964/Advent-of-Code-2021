#include "functions.h"

vector <string> getData(string filename){
  string line;
  vector <string> inputData;
  // Read the data from the text file line by line
  std::ifstream InputFile("datafiles/"+filename);

  // Use a while loop together with the getline() function to read the file line by line
  while (getline(InputFile, line)) {
    inputData.push_back(line);
  }
  InputFile.close();
  return inputData;
}

void printMatrix(vector <vector<int>> matrix){
  for (int i = 0; i < matrix.size(); ++i){
    for (int j = 0; j < matrix.size(); ++j){
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void printStack(stack<bool> path){
  while(!path.empty()){
    std::cout << path.top() << " " ;
    path.pop();
  }
}