#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "board.h"

using std::string;
using std::vector;
using std::pair;

//day 1
vector <int> getData1(string filename);
int countIncreases(int size, vector<int> numbers);

//day 2
vector <string> getData2(string filename);
int newLocation (vector<pair<string,int>> strings);

//day 3
vector <string> getData3(string filename);
int binaryToDecimal (vector<int> bits);
vector<string> mostCommonBit (int column, vector<string> binaryList, bool);

//day4
vector<string> getData4(string filename);
vector<int> getNumbers(string data);
vector<Board> getBoards(vector<string> data);
vector<vector<vector<int>>> tryBoards(vector<string> data);