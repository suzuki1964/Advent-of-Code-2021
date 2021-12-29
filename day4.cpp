#include "functions.h"
#include "board.h"

//set up an n*n board with 0 in all the squares and all squares marked unvisited
Board::Board(int board_width){
  board_width_ = board_width;
  bingo_board_ = vector(board_width_,vector(board_width_,pair<int, bool>(0,false)));
}
//put the value in the (row,column) square of the board
void Board::SetTile(int row, int column, int value){
  bingo_board_[row][column].first = value;
}
//mark the (row,column) square as visited if the number drawn is on the board
void Board::SetVisited (pair<int, int> coords){
  bingo_board_[coords.first][coords.second].second = true;
}
//output the value in the (row,column) square of the board
int Board::GetTile(int row, int column){
  return bingo_board_[row][column].first;
}
//check if the number drawn is on the board and return the coordinates of the square
pair<int, int> Board::Contains (int value){
  for (int row=0; row < board_width_; row++){
    for (int column=0; column < board_width_; column++){
      if (bingo_board_[row][column].first == value){
        return pair(row,column);
      }
    }
  }
  return pair(-1,-1);
}
//check to see if there is a complete row or column
bool Board::HasWon (pair<int, int> coords){
  bool rowComplete = true;
  bool columnComplete = true;
  for (int row=0; row < board_width_; row++){
    if (bingo_board_[row][coords.second].second == false){
      columnComplete = false;
    }
  }
  for (int column=0; column < board_width_; column++){
    if (bingo_board_[coords.first][column].second == false){
      rowComplete = false;
    }
  }
  if (rowComplete || columnComplete){
    return true;
  }
  else {
    return false;
  } 
}
//add up the numbers on the board that have not been visited
int Board::Points (){
  int points = 0;
  for (int row=0; row < board_width_; row++){
    for (int column=0; column < board_width_; column++){
      if (bingo_board_[row][column].second == false){
        points += bingo_board_[row][column].first;
      }
    }
  }
  return points;
}

//get the data. The first line will be the list of numbers drawn. The next is an empty line, then the first row of the first board, each number separated by a space, etc.
vector <string> getData4(string filename){
  string line;
  vector <string> inputData;
  // Read the numbers from the text file
  std::ifstream InputFile4("datafiles/"+filename);

  // Use a while loop together with the getline() function to read the file line by line
  while (getline(InputFile4, line)) {
    inputData.push_back(line);
  }
  InputFile4.close();
  return inputData;
}
//take the first line of the data and make a vector of the numbers drawn
vector<int> getNumbers(string data){
  vector<int> numbersList;
  int last_pos = 0;
  int split_pos = 0;
  while (split_pos != string::npos){
    split_pos = data.find(",",last_pos);
    numbersList.push_back (stoi(data.substr(last_pos, split_pos-last_pos)));
    last_pos = split_pos+1;
  }
  return numbersList;
}

//take the rest of the data and make a vector of the bingo boards
vector<Board> getBoards(vector<string> data){
  vector<Board> boardList;
  int whichBoard = -1;
  int row = 0;
  int column = 0;
  int value = 0;
  int last_pos = 0;
  int split_pos = 0;

  for (int i = 1; i < data.size(); i++){
    if (data[i] == ""){//if it is a blank line, make a new board
      boardList.push_back (Board(5));
      whichBoard++;
      row = 0;
    }
    else{
      column = 0;
      split_pos = 0;
      last_pos = 0;
      while (split_pos != string::npos){
        split_pos = data[i].find(" ",last_pos);
        if (split_pos == last_pos){
          last_pos++;
        }
        else{
          value = stoi(data[i].substr(last_pos, split_pos-last_pos));
          boardList[whichBoard].SetTile(row, column, value);
          last_pos = split_pos+1;
          column++;
        }
      }
      row++;
    }
  }
  return boardList;
}

/* to test the parsing of data into bingo boards
vector<vector<vector<int>>> tryBoards(vector<string> data){
  vector<vector<vector<int>>> boardList;
  vector<vector<int>> bingoBlank;
  vector<int> rowBlank;
  int whichBoard = -1;
  int row = 0;
  int column = 0;
  int value = 0;
  int last_pos = 0;
  int split_pos = 0;

  
  for (int row = 0; row < 5; row++){
    for (int column = 0; column < 5; column++){
      rowBlank.push_back(0);
    }
    bingoBlank.push_back(rowBlank);
  }
  

  for (int i = 1; i < data.size(); i++){
    std::cout << "line " << i << ": " << data[i] << "\n";
    if (data[i] == ""){//if it is a blank line, make a new board
    std::cout << "blank line\n";
      boardList.push_back(bingoBlank);
      whichBoard++;
      row = 0;
    }
    else{
      column = 0;
      int last_pos = 0;
      int split_pos = 0;
      while (split_pos != string::npos){
        split_pos = data[i].find(" ",last_pos);
        std::cout << "last " << last_pos << "\n";
        std::cout << "split " << split_pos << "\n";
        if (split_pos == last_pos){
          last_pos++;
          std::cout << "two blanks \n";
        }
        else {
          value = stoi(data[i].substr(last_pos, split_pos-last_pos));
          std::cout << "row " << row << ", column " << column << ", value " << value << "\n";
          boardList[whichBoard][row][column] = value;
          last_pos = split_pos+1;
          std::cout << "last " << last_pos << "\n";
          column++;
          std::cout << "column " << column << "\n";
        }
      }
      row++;
      column = 0;
      last_pos = 0;
    }
  }
  return boardList;
}
*/