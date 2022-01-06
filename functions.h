#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

#include "board.h"

using std::string;
using std::vector;
using std::array;
using std::pair;

//tools for all the days
vector <string> getData(string filename);

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

//day5
vector<pair<pair<int,int>,pair<int,int>>> getEndpoints(vector<string> data);
vector<vector<pair<int,int>>> getVentLines(vector<pair<pair<int,int>,pair<int,int>>> endpoints);
void markVentLines(int x_size, int y_size, int chart[], vector<vector<pair<int,int>>> lines);
int getDangerZone (int x_size, int y_size, int chart[]);
vector<vector<pair<int,int>>> addDiagVentLines(vector<vector<pair<int,int>>> lines,vector<pair<pair<int,int>,pair<int,int>>> endPoints);

//day6
vector<int> getInitTimers(vector<string> data);
vector<vector<int>> getDailyTimers(vector<int> timers, int days);
vector<int> oneDayLater(vector<int> timers);
//Part 2
vector<int> addNumbers(vector<int> firstNumber, vector<int> secondNumber);
vector<vector<int>> sortByTimer(vector<int> timers);
vector<vector<int>> fishOnDayGiven(vector<vector<int>> fishByTimer, int day);
vector<int> totalFish(vector<vector<int>> fishNumbers);

//day7
vector<int> getCrabPositions(vector<string> data);
int findMax(vector<int> xPositions);
int getFuelCost(int xValue, vector<int> positions);
int findMinFuel(vector<int> crabPositions);