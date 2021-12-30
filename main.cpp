#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::pair;

#include "functions.h"
#include "board.h"

int main() {
  string datafolder = "datafiles/";
  
  /*
  // Create a vector to hold the depths, a variable to count the number of times the depth increases, and a variable to count the number of times the three measurement sum increases
  string line;
  vector<int> depths;
  int countDepthInc = 0;//count the number of times the depth increases
  int countSumInc = 0;//count the number of times the three-measurement sum increases

  depths = getData1("Day1-input.txt");
 
  countDepthInc = countIncreases(1, depths);
  countSumInc = countIncreases(3, depths);
  std::cout << "The depth increases " << countDepthInc << " times.\n";
  std::cout << "The three measurement sum increases " << countSumInc << " times.\n";

  //Day 2
  vector<string> commandData = getData2("Day2-input.txt");//a vector of commands of the form "forward 5"
  vector<std::pair <string,int>> commands;//each pair is forward/up/down and the integer
  int split_pos = 0;//index of the space between the direction and the integer
  int subPosition = 0;//is the product of the horizontal position and the depth of the submarine

  for (int i=0; i<commandData.size(); i++){
    split_pos = commandData[i].find(" ");
    commands.push_back (std::pair<string,int> (commandData[i].substr(0, split_pos),stoi (commandData[i].substr(split_pos+1))));
  }
  
  subPosition = newLocation(commands);
  std::cout << "The submarine is at " << subPosition << ".\n";

  //Day 3
  vector<string> binaryData = getData3("Day3-input.txt");//vector of the binary numbers
  vector<int> sums;//sum of all the 1s in each column
  vector<int> gammaBits;//each bit is the most common bit in the data (by column)
  vector<int> epsilonBits;//each bit is the least common bit in the data
  int gamma = 0;
  int epsilon = 0;
  int bit = 0;

  //find the most common bit (by column)
  for (int column=0; column < binaryData[0].length(); column++){
    vector <string> sortedByColumn = mostCommonBit(column, binaryData, true);//this returns the numbers in the data list that have the most common bit in this column
    
    if (sortedByColumn.size() > 0){
      gammaBits.push_back (sortedByColumn[0][column]-'0');//the bit in this column of sortedByColumn should be the most common bit in this column
    }
  }
  
  //set epsilon to be the least common bits (the opposite of gamma)
  for (int column=0; column < gammaBits.size();   column++){
    if (gammaBits[column] == 0) {
     epsilonBits.push_back(1);//sets epsilon to the "opposite" of gamma
    }
    else if (gammaBits[column] == 1) {
      epsilonBits.push_back(0);
    }
  }

  //find the decimal expansion of gamma and epsilon and multiply them to get the power consumption
  gamma = binaryToDecimal (gammaBits);
  epsilon = binaryToDecimal (epsilonBits);
  std::cout << "Power consumption is " <<   gamma*epsilon << ".\n";

  //oxygen generator rating
  vector <string> oxygenLastSorted =  binaryData;
  vector <string> co2LastSorted = binaryData;

  for (int column=0; column < binaryData[0].length(); column++){
    if (oxygenLastSorted.size() > 1){
      vector <string> oxygenSortedByColumn = mostCommonBit(column, oxygenLastSorted, true);
      oxygenLastSorted = oxygenSortedByColumn;//this returns the numbers in the data list that have the most common bit in this column
    }
  }

  //CO2 scrubber rating
  for (int column=0; column < binaryData[0].length(); column++){
    if (co2LastSorted.size() > 0){
      vector <string> co2SortedByColumn = mostCommonBit(column, co2LastSorted, false);
      co2LastSorted = co2SortedByColumn;
      //this returns the numbers in the data list that have the least common bit in this column
    }
  }

  //life support rating is oxygen generator rating times CO2 scrubber rating
  int oxygen = std::stoi(oxygenLastSorted[0],0,2);
  int carbondiox = std::stoi(co2LastSorted[0],0,2);
  std::cout << "life support rating is " << oxygen*carbondiox << ".\n";
*/

  //Day 4
  //vector<string> bingoData = getData4("test.txt");
  vector<string> bingoData = getData4("Day4-input.txt");//the first entry is the list of draw numbers, and the rest are the boards, each number in a row separated by a space, and the boards separated by empty lines
  vector<int> numbersDrawn = getNumbers(bingoData[0]);
  //vector<vector<vector<int>>> bingoBoardVectors; //to test parsing of data into bingo boards
  vector<Board> bingoBoards = getBoards(bingoData);

  int i = 0;
  pair<int, int> coords;
  int score = 0;
  int whichBoard = 0;
  coords = bingoBoards[whichBoard].Contains(numbersDrawn[i]);
  bool won = false;

  while (!won && (i < numbersDrawn.size())){
    whichBoard = 0;
    while (!won && (whichBoard < bingoBoards.size())){
      if (bingoBoards[whichBoard].Contains(numbersDrawn[i]) != pair(-1,-1)){
        bingoBoards[whichBoard].SetVisited(bingoBoards[whichBoard].Contains(numbersDrawn[i]));
        //std::cout << "board " << whichBoard << ", (" << bingoBoards[whichBoard].Contains(numbersDrawn[i]).first << ", " << bingoBoards[whichBoard].Contains(numbersDrawn[i]).second << ") \n";
        if (bingoBoards[whichBoard].HasWon(bingoBoards[whichBoard].Contains(numbersDrawn[i]))){
          score = bingoBoards[whichBoard].Points() * numbersDrawn[i];
          std::cout << "score " << score <<"\n";
          won = true;
        }
      }
      whichBoard++;
    }
    i++;
  }
 
 /* print out boards to make sure they loaded in properly
  for (int i = 0; i < bingoBoards.size(); i++){
    std::cout << "new board \n";
    for (int row = 0; row < 5; row++){
      for (int column = 0; column < 5; column++){
        std::cout << bingoBoards[i].GetTile(row, column) << " ";
      }
      std::cout << "\n";
    }
  }
  */

//to test parsing of data into bingo boards
/*
bingoBoardVectors = tryBoards(bingoData);
for (int i = 0; i < 3; i++){
  std::cout << "new board\n";
  for (int row = 0; row < 5; row++){
    for (int column = 0; column < 5; column++){
      std::cout << bingoBoardVectors[i][row][column] << " ";
    }
    std::cout << "\n";
  }
}
*/

  return 0;
}