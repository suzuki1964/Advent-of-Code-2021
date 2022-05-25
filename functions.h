#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <stack>
#include <map>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <tuple>
#include <algorithm>
#include <stdlib.h>

#include "board.h"
#include "scanner.h"

using std::string;
using std::vector;
using std::array;
using std::pair;
using std::stack;
using std::map;

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

//day12
vector<pair<string, string>> getPairs(vector<string> data);
vector<pair<string, bool>> getCaves(vector<pair<string,string>> edges);
bool caveNameInList(string name, vector<pair<string, bool>> list);
vector<vector<int>> getConnections(vector<pair<string, string>> edges,vector<pair<string, bool>> list);
int caveIndex(string name,vector<pair<string, bool>> list);
vector<vector<string>> getPaths(vector<vector<int>> matrix,vector<pair<string, bool>> nodes, int &twice);
void getNextCave(int i, vector<vector<int>> matrix, vector<pair<string, bool>> nodes, vector<string> path, vector<vector<string>> &paths, int &twice);
int getSpecialPaths(vector<vector<int>> matrix, vector<pair<string, bool>> nodes);

//day13
pair<vector<pair<int, int>>, vector<pair<bool, int>>> getInstructions(vector<string> data);
vector<vector<bool>> markDots(vector<pair<int, int>> coords);
void showDots(vector<vector<bool>> paper);
vector<vector<bool>> foldY(vector<vector<bool>> paper, int y);
vector<vector<bool>> foldX(vector<vector<bool>> paper, int x);
int countDots(vector<vector<bool>> paper);
vector<vector<bool>> foldPaper(pair<vector<pair<int, int>>, vector<pair<bool, int>>> coordsAndInstructions, bool folds);//folds=1 for just first, =0 for all folds

//day14
pair<vector<pair<char, long int>>, vector<vector<pair<long int,int>>>> getPolymers(vector<string> data);
void addElement(char current, int &last, vector<pair<char,long int>> &list, vector<vector<pair<long int,int>>> &matrix, vector<pair<long int,int>> &row);
void makeBigger(vector<vector<pair<long int,int>>> &matrix,vector<pair<long int,int>> &row);
void printMatrix(vector<vector<pair<long int,int>>> matrix);
int getIndex(char c, vector<pair<char, long int>> list);
pair<vector<pair<char, long int>>, vector<vector<pair<long int,int>>>> insertElements(pair<vector<pair<char, long int>>, vector<vector<pair<long int,int>>>> countsAndInstructions, int steps);
long int getDifference(vector<pair<char, long int>> list);

//day15, Part 1 -- didn't need to know the path
vector<vector<int>> getChitonLevels(vector<string> data);
void printMatrix(vector <vector<int>> matrix);
int Day15_1(string filename);
int dijkstra(vector<vector<int>> chitons);
vector<vector<pair<int,bool>>> initializeDistances(int size);
bool isInCavern(int x, int y, int size);
vector<pair<int,int>> findNeighbors(int x,int y, int size, vector<vector<pair<int,bool>>> &distances);
pair<int,int> findMin(vector<pair<int, int>> &priority,vector<vector<pair<int,bool>>> &distances);
int update(vector<pair<int, int>> &priority,vector<vector<pair<int,bool>>> &distances,vector<vector<int>> &chitons,bool &done);
bool inPriority(pair<int,int> coords, vector<pair<int, int>> &priority);

//day15, Part 2
int Day15_2(string filename);
vector<vector<int>> expandMap(vector<vector<int>> matrix);
vector<vector<int>> increaseRisk(int n);
int wrapAdd(int i, int j);
vector<vector<vector<int>>> increasedNumbersByDigit(void);

//day16
pair<int,long long int> Day16(string filename);
string makeBinary(string hexString);
pair<int, long long int> parseData(string bString);
std::tuple<int,int,long long int> getPacket(string bString, int startPos);
pair<long int,int> getLiterals(string bString,int k);

pair<int,int> Day17(string filename);
vector<pair<int,int>> findRanges(string data);
pair<int,int> moveOnce(pair<int,int> position, pair<int,int> velocity);
pair<int,int> updateVelocity(pair<int,int>);
pair<bool,int> hitTarget(pair<int,int> initVelocity,vector<pair<int,int>> range);
bool inTarget(pair<int,int> position,vector<pair<int,int>> range);
pair<int,int> maxHeight(vector<pair<int,int>> range);

pair<int,int> Day18(string filename);
string getSum(vector<string> data);
int findMag(string number);
void reduce(string &number);
int explode(string &number,int i);
bool willExplode(string &number);
bool willSplit(string &number);
pair<pair<int,int>,size_t> findPair(string &number, int i, bool exploding);
int getMaxMag(vector<string> data);

pair<int,int> Day19(string filename);
pair<int,int> findTotalAndMax(vector<string> data);
vector<Scanner> getScanners(vector<string> data);
void combineCubes(vector<Scanner> &scannerList,int k);
vector<pair<int,int>> findOverlaps(vector<Scanner> list, int k, int l);
void findLocation(vector<pair<int,int>> matchingBeacons, vector<Scanner> &list, int k, int l);
tuple<int,int,int> addCoords(tuple<int,int,int> coordsOne,tuple<int,int,int> coordsTwo);
tuple<int,int,int> subtractCoords(tuple<int,int,int> coordsOne,tuple<int,int,int> coordsTwo);
tuple<pair<int,int>, pair<int,int>, pair<int,int>> findTransformation(tuple<int,int,int> vectorK,tuple<int,int,int> vectorL);
tuple<int,int,int> transformLtoK(tuple<int,int,int> coords,tuple<pair<int,int>, pair<int,int>, pair<int,int>> transformation);
void moveBeaconsToK(Scanner scannerK, Scanner scannerL);

pair<int,int> Day20(string filename);
string getAlgorithm(vector<string> data); //the first string is the algorithm
vector<string> getImage(vector<string> data); //the image is a grid of . and #
int findNumberOn(vector<string> image, string algorithm,int repetitions);
void displayImage(vector<string> image);
vector<string> enhanceImage(vector<string> image, string algorithm);
vector<string> enlargeImage(vector<string> image, char edge);
int findBinary(int i,int j, vector<string> image);
int countLitPixels(vector<string> image);