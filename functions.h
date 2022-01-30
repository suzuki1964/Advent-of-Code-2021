#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <stack>
#include <math.h>

#include "board.h"

using std::string;
using std::vector;
using std::array;
using std::pair;
using std::stack;

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
//Part 2
int getNewFuelCost(int xValue, vector<int> positions);
int findNewMinFuel(vector<int> positions);

//day8
vector<pair<vector<string>,vector<string>>> getSensorDisplays(vector<string> data);
int findEasyDigits(vector<pair<vector<string>,vector<string>>> displays);
int findOutputSum(vector<pair<vector<string>,vector<string>>> displays);
string segmentsOn(vector<string> displays, int numberOn);
bool isContainedIn(string key, string display);

//day9
vector<vector<pair<int,int>>> getFloorHeights(vector<string> data);
int getRiskLevel(vector<vector<pair<int,int>>> &heights, vector<int> &sizes);
bool isLowPoint(int x, int y, vector<string> heights);
int markBasin(int x,int y,int basin,int &size,vector<vector<pair<int,int>>> &heights);
int getRiskProduct(vector<int> sizes);

//day10
vector<char> getSyntaxErrors(vector<string> data);
bool isOpen(char c);
int getScore(vector<char> syntaxErrors);
vector<vector<char>> getFixes(vector<string> data);
vector<pair<int,int>> sortByLength(vector<vector<int>> scores);
vector<vector<int>> getAutoScore(vector<vector<char>> fixes);
vector<int> getMidScore(vector<pair<int,int>> length, vector<vector<int>> scores);
vector<int> sortByKey(int key, int &middle, vector<int> list, vector<vector<int>> scores);

//day11
array<array<pair<int,bool>,10>,10> getEnergyLevels(vector<string> data);
array<array<pair<int,bool>,10>,10> addOne(array<array<pair<int,bool>,10>,10> oldLevels, int &flashCount);
void willFlash(int i,int j,array<array<pair<int,bool>,10>,10> &newLevels,int &flashCount);
void checkNeighbors(int i,int j,array<array<pair<int,bool>,10>,10> &newLevels,int &flashCount);
bool inGrid(int i, int j);