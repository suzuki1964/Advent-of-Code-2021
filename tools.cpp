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