#include "functions.h"

vector <string> getData3(string filename){
  string line;
  vector <string> inputData;
  // Read the commands from the text file
  std::ifstream InputFile3("datafiles/"+filename);

  // Use a while loop together with the getline() function to read the file line by line
  while (getline(InputFile3, line)) {
    inputData.push_back(line);
  }
  InputFile3.close();
  return inputData;
}

int binaryToDecimal (vector<int> bits){
  int binaryExponent = bits.size();
  int decimal = 0;
  int powerOfTwo = 1;
  for (int exponent = binaryExponent-1; exponent >= 0 ; exponent--){
    decimal += bits[exponent]*powerOfTwo; 
    powerOfTwo = powerOfTwo*2;
  }
return decimal;
}

vector<string> mostCommonBit (int column, vector<string> binaryList, bool most) {
  vector<string> sortFor1ByColumn;
  vector<string> sortFor0ByColumn;
  for (int row=0; row < binaryList.size(); row++){
    int bit = 0;
    bit = binaryList[row][column] - '0';//converts the char to an integer
    if (bit == 0){
      sortFor0ByColumn.push_back (binaryList[row]);//if the number in this column is 0, then append the binary number from the list to the end of sortFor0ByColumn
    }
    else if (bit == 1){
      sortFor1ByColumn.push_back (binaryList[row]);//if the number in this column is 1, then append the binary number from the list to the end of sortFor1ByColumn
    }
  }

  if ((sortFor0ByColumn.size() <= sortFor1ByColumn.size()) && (most)) {
      return sortFor1ByColumn;//1 was the most common bit
  }
  else if ((sortFor0ByColumn.size() <= sortFor1ByColumn.size()) && (!most)) {
    return sortFor0ByColumn;//0 is the least common bit
  }
  else if ((sortFor0ByColumn.size() > sortFor1ByColumn.size()) && (most)) {
    return sortFor0ByColumn;//0 is the most common bit
  }
  else {
    return sortFor1ByColumn;//1 is the least common bit
  }
}
