#include "functions.h"

vector <string> getData2(string filename){
  string line;
  vector <string> inputData;
  // Read the commands from the text file
  std::ifstream InputFile2("datafiles/"+filename);

  // Use a while loop together with the getline() function to read the file line by line
  while (getline(InputFile2, line)) {
    inputData.push_back(line);
  }
  InputFile2.close();
  return inputData;
}

int newLocation (vector<pair<string,int>> strings)
{
  int horizontalPosition = 0;
  int verticalDepth = 0;
  int aim = 0;
  int product = 0;
  for (int i=0; i<strings.size(); i++){
    if (strings[i].first == "forward"){
      horizontalPosition += strings[i].second;
      verticalDepth += aim*strings[i].second;
    }
    else if (strings[i].first == "down"){
      //verticalDepth += strings[i].second;
      aim +=strings[i].second;
    }
    else if (strings[i].first == "up"){
      //verticalDepth -= strings[i].second;
      aim -= strings[i].second;
    }
  }

  product = horizontalPosition*verticalDepth;
  return product;
}