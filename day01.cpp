#include "functions.h"

vector <int> getData1(string filename){
  string line;
  vector <int> inputData;
  // Read the depths from the text file
  std::ifstream InputFile1("datafiles/"+filename);

  // Use a while loop together with the getline() function to read the file line by line to     make a vector of the depths
  while (getline(InputFile1, line)) {
    inputData.push_back(std::stoi(line));
  }

  // Close the file
  InputFile1.close();
return inputData;
}


int countIncreases(int size, vector<int> numbers)
{
  int count = 0;
  for (int i=size; i<numbers.size(); i++){
    if (numbers[i]>numbers[i-size]){
      count++;
    }
  }
  return count;
}
