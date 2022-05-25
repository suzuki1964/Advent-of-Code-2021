#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::pair;
using std::string;
using std::vector;

#include "board.h"
#include "functions.h"

int main() {
	string datafolder = "datafiles/";

	/*
	  //Day 1
	  // Create a vector to hold the depths, a variable to count the number of
	  times the depth increases, and a variable to count the number of times the
	  three measurement sum increases string line; vector<string> depthData =
	  getData("Day01-input.txt");//vector of the depths as strings vector<int>
	  depths; int countDepthInc = 0;//count the number of times the depth
	  increases int countSumInc = 0;//count the number of times the
	  three-measurement sum increases

	  //vector<string> depthData = getData("Day01-input.txt");//vector of the
	  depths as strings depths = getData1("Day01-input.txt");

	  countDepthInc = countIncreases(1, depths);
	  countSumInc = countIncreases(3, depths);
	  std::cout << "The depth increases " << countDepthInc << " times.\n";
	  std::cout << "The three measurement sum increases " << countSumInc << "
	  times.\n";

	  //Day 2
	  vector<string> commandData = getData2("Day02-input.txt");//a vector of
	  commands of the form "forward 5" vector<std::pair <string,int>>
	  commands;//each pair is forward/up/down and the integer int split_pos =
	  0;//index of the space between the direction and the integer int
	  subPosition = 0;//is the product of the horizontal position and the depth
	  of the submarine

	  for (int i=0; i<commandData.size(); i++){
		split_pos = commandData[i].find(" ");
		commands.push_back (std::pair<string,int> (commandData[i].substr(0,
	  split_pos),stoi (commandData[i].substr(split_pos+1))));
	  }

	  subPosition = newLocation(commands);
	  std::cout << "The submarine is at " << subPosition << ".\n";
	*/

	/*
	  //Day 3
	  vector<string> binaryData = getData("Day03-input.txt");//vector of the
	  binary numbers vector<int> sums;//sum of all the 1s in each column
	  vector<int> gammaBits;//each bit is the most common bit in the data (by
	  column) vector<int> epsilonBits;//each bit is the least common bit in the
	  data int gamma = 0; int epsilon = 0; int bit = 0;

	  //find the most common bit (by column)
	  for (int column=0; column < binaryData[0].length(); column++){
		vector <string> sortedByColumn = mostCommonBit(column, binaryData,
	  true);//this returns the numbers in the data list that have the most
	  common bit in this column

		if (sortedByColumn.size() > 0){
		  gammaBits.push_back (sortedByColumn[0][column]-'0');//the bit in this
	  column of sortedByColumn should be the most common bit in this column
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

	  //find the decimal expansion of gamma and epsilon and multiply them to get
	  the power consumption gamma = binaryToDecimal (gammaBits); epsilon =
	  binaryToDecimal (epsilonBits); std::cout << "Power consumption is " <<
	  gamma*epsilon << ".\n";

	  //oxygen generator rating
	  vector <string> oxygenLastSorted =  binaryData;
	  vector <string> co2LastSorted = binaryData;

	  for (int column=0; column < binaryData[0].length(); column++){
		if (oxygenLastSorted.size() > 1){
		  vector <string> oxygenSortedByColumn = mostCommonBit(column,
	  oxygenLastSorted, true); oxygenLastSorted = oxygenSortedByColumn;//this
	  returns the numbers in the data list that have the most common bit in this
	  column
		}
	  }

	  //CO2 scrubber rating
	  for (int column=0; column < binaryData[0].length(); column++){
		if (co2LastSorted.size() > 0){
		  vector <string> co2SortedByColumn = mostCommonBit(column,
	  co2LastSorted, false); co2LastSorted = co2SortedByColumn;
		  //this returns the numbers in the data list that have the least common
	  bit in this column
		}
	  }

	  //life support rating is oxygen generator rating times CO2 scrubber rating
	  int oxygen = std::stoi(oxygenLastSorted[0],0,2);
	  int carbondiox = std::stoi(co2LastSorted[0],0,2);
	  std::cout << "life support rating is " << oxygen*carbondiox << ".\n";
	*/

	/*
	  //Day 4
	  //vector<string> bingoData = getData4("test04.txt");
	  vector<string> bingoData = getData("Day04-input.txt");//the first entry is
	  //the list of draw numbers, and the rest are the boards, each number in a
	  //row separated by a space, and the boards separated by empty lines
	  vector<int> numbersDrawn = getNumbers(bingoData[0]);
	  //vector<vector<vector<int>>> bingoBoardVectors; //to test parsing of data into bingo boards
    vector<Board> bingoBoards = getBoards(bingoData);

	  int i = 0;
	  int score = 0;
	  int whichBoard = 0;
	  bool won = false;

	// Part 1
	  while (!won && (i < numbersDrawn.size())){
		whichBoard = 0;
		while (!won && (whichBoard < bingoBoards.size())){ // if whichBoard contains the number drawn, then mark the tile as
	    //visited and check if you won
      if (bingoBoards[whichBoard].Contains(numbersDrawn[i]) != pair(-1,-1)){
			  bingoBoards[whichBoard].SetVisited(bingoBoards[whichBoard].Contains(numbersDrawn[i]));
			  //std::cout << "board " << whichBoard << ", (" << bingoBoards[whichBoard].Contains(numbersDrawn[i]).first << ", " <<  bingoBoards[whichBoard].Contains(numbersDrawn[i]).second << ") \n";
        if (bingoBoards[whichBoard].HasWon(bingoBoards[whichBoard].Contains(numbersDrawn[i]))){
			    score = bingoBoards[whichBoard].Points() * numbersDrawn[i];
			    std::cout << "Day04, Part 1: score " << score <<"\n";
			    won = true;
			  }
		  }
		  whichBoard++;
		}
		i++;
	}
	*/

	/*
	  //Part 2

	 while (i < numbersDrawn.size()){
		whichBoard = 0;
		while (whichBoard < bingoBoards.size()){
		  //if whichBoard contains the number drawn, mark the tile as visited and check if it won
      if (bingoBoards[whichBoard].Contains(numbersDrawn[i]) != pair(-1,-1)){
			  bingoBoards[whichBoard].SetVisited(bingoBoards[whichBoard].Contains(numbersDrawn[i]));
			  //std::cout << "board " << whichBoard << ", (" << bingoBoards[whichBoard].Contains(numbersDrawn[i]).first << ", << bingoBoards[whichBoard].Contains(numbersDrawn[i]).second << ") \n";
        if (bingoBoards[whichBoard].HasWon(bingoBoards[whichBoard].Contains(numbersDrawn[i]))){
			    score = bingoBoards[whichBoard].Points() * numbersDrawn[i];
			    std::cout << "board " << whichBoard <<" score " << score <<"\n";
			    won = true;
			    bingoBoards.erase(bingoBoards.begin()+whichBoard);
			  }
		  }
		  if (won){
			  won = false;
			  whichBoard--;
		  }
		  whichBoard++;
		}

		i++;
	  }
	  std::cout << "Day 4, Part 2: score " << score <<"\n";
	*/

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

	/*
	//to test parsing of data into bingo boards
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

	/*
	//Day 5
	  //vector of strings of the form 427,523 -> 427,790 which give the
	endpoints of the lines of vents vector<string> binaryData =
	getData("Day05-input.txt");
	  //vector of the endpoints of the lines and the last pair is (0,0) and
	(x-maximum, y_maximum) vector<pair<pair<int,int>, pair<int,int>>>
	ventEndpoints = getEndpoints(binaryData);
	  //vector of a vector of all the points on each horizontal and vertical
	line vector<vector<pair<int,int>>> ventHVLines =
	getVentLines(ventEndpoints);
	  //the array for the graph of the lines which is x_maximum by y_maximum
	  int ventChart[(ventEndpoints[ventEndpoints.size()-1].second.second + 1) *
	(ventEndpoints[ventEndpoints.size()-1].second.first + 1)];
	  //tried to call the function on a 2D array...
	  //markVentLines(ventEndpoints[ventEndpoints.size()-1].second.second,
	ventEndpoints[ventEndpoints.size()-1].second.first, ventChart, ventLines);
	  //the graph of all the points covered by the lines with multiplicity (so 1
	if on one line, two if at an intersection of two lines)
	  markVentLines(ventEndpoints[ventEndpoints.size()-1].second.first,
	ventEndpoints[ventEndpoints.size()-1].second.second, ventChart,
	ventHVLines);
	  //the number of points where at least two vent lines overlap
	  int dangerZone =
	getDangerZone(ventEndpoints[ventEndpoints.size()-1].second.first,
	ventEndpoints[ventEndpoints.size()-1].second.second, ventChart); std::cout
	<< "Danger zone with horizontal and vertical lines is " << dangerZone <<
	"\n";
	*/

	/*
	//Part 2
	 //add the diagonal lines too
	  vector<vector<pair<int,int>>> ventHVDLines =
	addDiagVentLines(ventHVLines,ventEndpoints);
	  markVentLines(ventEndpoints[ventEndpoints.size()-1].second.first,
	ventEndpoints [ventEndpoints.size()-1].second.second, ventChart,
	ventHVDLines);
	  //the number of points where at least two vent lines overlap
	  int dangerZoneAll =
	getDangerZone(ventEndpoints[ventEndpoints.size()-1].second.first,
	ventEndpoints[ventEndpoints.size()-1].second.second, ventChart); std::cout
	<< "Danger zone with horizontal, vertical, and diagonal lines is " <<
	dangerZoneAll << "\n";
	*/

	/*
	  //print out the pairs of endpoints to make sure it was parsed correctly
	  with the test case for (int i = 0; i < ventEndpoints.size(); i++){
		std::cout << "(" << ventEndpoints[i].first.first << ", " <<
	  ventEndpoints[i].first.second << ") (" << ventEndpoints[i].second.first <<
	  ", " << ventEndpoints[i].second.second << ") \n";
	  }
	*/

	/*
	  //print out the points on the lines to make sure it was done correctly
	  for (int i = 0; i < ventHVDLines.size(); i++){
		for (int j = 0; j < ventHVDLines[i].size(); j++){
		  std::cout << "(" << ventHVDLines[i][j].first << ", " <<
	  ventHVDLines[i][j].second << ") " << "line " << i << ", point " << j <<
	  "\n";
		}
	  }
	*/

	/*
	  //print out the graph of the lines to check the test case
	  for (int i = 0; i <= ventEndpoints[ventEndpoints.size()-1].second.second;
	  i++){ for (int j = 0; j <=
	  ventEndpoints[ventEndpoints.size()-1].second.first; j++){ std::cout <<
	  ventChart[(i * (ventEndpoints[ventEndpoints.size()-1].second.first+1)) +
	  j] << " ";
	   }
	   std::cout << "\n";
	  }
	*/

	/*
	//Day 6, Part 1
	  //vector<string> fishData = getData("test06.txt");//this is to run test
	case vector<string> fishData = getData("Day06-input.txt");//the data is just
	one string

	  //parse the string into numbers which give the timer values for each fish
	on the initial day vector<int> timerValues = getInitTimers(fishData);
	*/

	/*
	  //each line (vector) represents the timers of all the fish that day and
	  numberOfDays is the number of days you want to check
	  //so, dailyTimerValues[0] is the set of initial timer values
	  //int numberOfDays = 18; //easier to toggle between the two values 18 and
	  80 int numberOfDays = 80; vector<vector<int>> dailyTimerValues =
	  getDailyTimers(timerValues, numberOfDays); std::cout << "total number of
	  fish " << dailyTimerValues[numberOfDays].size();
	*/

	/*
	//Part 2
	  //too inefficient. No need to store all the previous days' timer values.
	  //In fact, for each day, you only need to know how many fish have which
	timer value. vector<vector<int>> timerFishNumbers =
	sortByTimer(timerValues);//number of fish can be large, so we use a
	vector<int> to hold the number, stored so that the digit in the ith place
	represents 10^i int numberOfDays = 256; vector<vector<int>> fishByTimer =
	fishOnDayGiven(timerFishNumbers, numberOfDays);

	  vector<int> total = totalFish(fishByTimer);
	  //print out number in the normal way, so we need to reverse the digits
	  std::cout << "After " << numberOfDays << " days, there are ";
	  for (int i = 0; i < total.size(); i++){
		std::cout << total[total.size() - i - 1];
	  }
	  std::cout << " fish\n";
	*/

	/*
	//check if properly sorted by timer values
	  for (int i = 0; i < 9; i++){
		std::cout << "timer " << i << " has " << fishByTimer[i][0] << " fish\n";
	  }
	*/

	/*
	  //check daily timer values
	  for (int i = 0; i < dailyTimerValues.size(); i++){
		for (int j = 0; j < dailyTimerValues[i].size(); j++){
		  std::cout << dailyTimerValues[i][j] << " ";
		}
		std::cout << "\n";
	  }
	*/

	/*
	  //check the initial timer values
	  for (int i = 0; i < timerValues.size(); i++){
		std::cout << timerValues[i] << "\n";
	  }
	*/

	/*
	//Day 7, Part 1
	  //vector<string> crabData = getData("test07.txt");//this is to run test
	case vector<string> crabData = getData("Day07-input.txt");//a vector of
	horizontal positions vector<int> crabPositions = getCrabPositions(crabData);
	  int maxPosition = findMax(crabPositions);
	  int xPosition = 5;
	  int fuelCost = getFuelCost(xPosition, crabPositions);
	  int minFuel = findMinFuel(crabPositions);
	  std::cout << "fuel cost " << minFuel << "\n";
	*/

	/*
	for (int i = 0; i < crabPositions.size(); i++){
	  std::cout << crabPositions[i] << " ";
	}
	std::cout << "\n";
	*/

	/*
	//Day 7, Part 2
	  int newFuel = getNewFuelCost(xPosition, crabPositions);
	  int newMinFuel = findNewMinFuel(crabPositions);
	  std::cout << "new min fuel " << newMinFuel << "\n";
	*/

	/*
	//Day 8, Part 1
	  //vector<string> sensorData = getData("test08.txt");//this is to run test
	case vector<string> sensorData = getData("Day08-input.txt");//the data is a
	list of the signal patterns for the 10 digits, followed by the delimiter |,
	then the signal patterns of the four-digit output

	  //parse the strings into a list of the patterns for the 10 digits and a
	list of the patterns for the outputs
	  vector<pair<vector<string>,vector<string>>> sensorDisplays =
	getSensorDisplays(sensorData);

	  //find the patterns for 1,4,7,and 8 (the ones with length 2,3,4, and 7) in
	the outputs int easyDigits = findEasyDigits(sensorDisplays); std::cout <<
	easyDigits << " easy digits\n";
	*/

	/*
	  for (int i = 0; i < sensorDisplays.size(); i++){
		std::cout << i << ": " ;
		for (int j = 0; j < sensorDisplays[i].first.size(); j++){
		  std::cout << sensorDisplays[i].first[j] << " ";
		}
		std::cout << "| ";
		for (int j = 0; j < sensorDisplays[i].second.size(); j++){
		  std::cout << sensorDisplays[i].second[j] << " ";
		}
	  }
	*/

	// Day 8, Part 2
	// To decode the patterns, you only need to check for two pairs: the one
	// from 1, and the extra ones in 4.
	/*
	  int sum = findOutputSum(sensorDisplays);
	  std::cout << "sum " << sum << "\n";
	*/
	/*
	int sum = findOutputSum(sensorDisplays);
	*/

	/*
	//Day 9, Part 1 and Part 2
	  //vector<string> floorData = getData("test09.txt");//this is to run test
	case vector<string> floorData = getData("Day09-input.txt");//the data is a
	list of the floor heights (from 0 to 9) vector<vector<pair<int,int>>>
	floorHeights = getFloorHeights(floorData);

	  vector<int> basinSizes;
	  int riskLevel = getRiskLevel(floorHeights, basinSizes);
	  std::cout << "risk " << riskLevel << "\n";
	  int riskProduct = getRiskProduct(basinSizes);
	  std::cout << "product " << riskProduct << "\n";
	*/

	/* to check the map of the basins
	  for (int i = 0; i < floorHeights.size(); ++i){
		for (int j = 0; j < floorHeights[i].size(); ++j){
		  std::cout << floorHeights[i][j].second << " ";
		}
		std::cout << "\n";
	  }
	*/

	/*
	//Day 10, Part 1
	  //vector<string> syntaxData = getData("test10.txt");//this is to run test
	case vector<string> syntaxData = getData("Day10-input.txt");//the data is a
	list of lines of ()[]{}<> vector<char> syntaxErrors =
	getSyntaxErrors(syntaxData);//this gives the first incorrect character in
	each corrupted line int errorScore = getScore(syntaxErrors); std::cout <<
	"score " << errorScore << std::endl;
	*/

	/*
	//Day 10, Part 2
	  vector<vector<char>> fixErrors = getFixes(syntaxData);//each line gives a
	list of the characters needed to complete all the pairs for (int i = 0; i <
	fixErrors.size(); ++i){ // print out the fixes for (int j = 0; j <
	fixErrors[i].size(); ++j){
		  //std::cout << fixErrors[i][j];
		}
		//std::cout << std::endl;
	  }

	  //the score is represented in base 5 by the above vectors with
	)=1,]=2,}=3,and >=4. So the autocorrect score can be calculated digit by
	digit (the numbers are too big for ints), stored from lowest power of ten
	  vector<vector<int>> autoScore = getAutoScore(fixErrors);
	   // print out the scores
	  for (int i = 0; i < autoScore.size(); ++i){ // print out the scores
		for (int j = autoScore[i].size()-1; j >= 0; j--){
		  std::cout << autoScore[i][j];
		}
		std::cout << std::endl;
	  }
	  */

	/*
	vector<pair<int, int>> lengthOrder = sortByLength(autoScore); //sort scores
	by number of digits (length), which line it fixes for (int i = 0; i <
	lengthOrder.size(); ++i){ // print out the scores (digits from the back end)
		//std::cout << "line " << lengthOrder[i].second << ": " <<
	lengthOrder[i].first << std::endl;
	}

	vector<int> score = getMidScore(lengthOrder, autoScore);
	std::cout << "middle score ";
	for (int i = 0; i < score.size(); ++i){ // print out the score (digits from
	the back end) std::cout << score[score.size() - i - 1];
	}
	std::cout << std::endl;
  */

	/*
	//Day 11, Part 1
	  //vector<string> energyData = getData("test11.txt");//this is to run test
	case vector<string> energyData = getData("Day11-input.txt");//the data is a
	list of 10 lines of 10 digits from 0 to 9

	  array<array<pair<int,bool>,10>,10> energyLevels =
	getEnergyLevels(energyData);//this gives the energy level of each octopus in
	the 10x10 grid vector<array<array<pair<int,bool>,10>,10>>
	energyLevelsAfterStep; energyLevelsAfterStep.push_back(energyLevels); int
	steps = 100; int totalFlashes = 0; for (int i = 1; i <= steps;i++){ int
	currentFlashes = 0;
		energyLevelsAfterStep.push_back(addOne(energyLevelsAfterStep[i-1],currentFlashes));
		totalFlashes += currentFlashes;
	  }

	  //print out grid
	  for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
		  std::cout << energyLevelsAfterStep[steps][i][j].first << " ";
		}
		std::cout << std::endl;
	  }
	  std::cout << "flashes " << totalFlashes << std::endl;
	  energyLevelsAfterStep.clear();

	//Day 11, Part 2
	  energyLevelsAfterStep.push_back(energyLevels);
	  int currentFlashes = 0;
	  int i = 1;
	  while (currentFlashes != 100){
		currentFlashes = 0;
		energyLevelsAfterStep.push_back(addOne(energyLevelsAfterStep[i-1],currentFlashes));
		i++;
	  }
	  std::cout << "first step " << i-1 << std::endl;
	  */
	/*
	//Day 12, Part 1
	  //vector<string> caveData = getData("test12-1.txt");//this is to run test
	cases
	  //vector<string> caveData = getData("test12-2.txt");//this is to run test
	cases
	  //vector<string> caveData = getData("test12-3.txt");//this is to run test
	cases

	  vector<string> caveData = getData("Day12-input.txt");//the data is a list
	of connected cave pairs like A-c

	  vector<pair<string, string>> connectedCaves = getPairs(caveData);//these
	are the edges of the graph vector<pair<string, bool>> caveList =
	getCaves(connectedCaves);//list of caves (nodes) and if they are big
	  vector<vector<int>> caveConnections =
	getConnections(connectedCaves,caveList);//a matrix with 1 where two caves
	connect int twiceCave = 0;
	  //std::cout << "special cave: " << caveList[twiceCave].first << std::endl;
	  vector<vector<string>> pathList =
	getPaths(caveConnections,caveList,twiceCave); int pathNum =
	getSpecialPaths(caveConnections, caveList);

	  std::cout << "number of paths is " << pathNum << std::endl;
	  //std::cout << "number of paths is " << pathList.size() << std::endl;
	*/

	/*
	//Day 13, Parts 1 and 2
	  //vector<string> codeData = getData("test13.txt");//this is to run test
	case vector<string> codeData = getData("Day13-input.txt");//the data is a
	list of pairs of coordinates, then a list of instructions like "fold along
	x=655"

	  pair<vector<pair<int, int>>, vector<pair<bool, int>>> dotsAndFolds =
	getInstructions(codeData); vector<vector<bool>> paperWithDots =
	markDots(dotsAndFolds.first); vector<vector<bool>> firstFold =
	foldPaper(dotsAndFolds, 1); //1 for first, 0 for all vector<vector<bool>>
	allFolds = foldPaper(dotsAndFolds, 0); //1 for first, 0 for all
	  showDots(allFolds);
	  int numberOfDots = countDots(firstFold);
	  std::cout << "number of dots:" << numberOfDots << std::endl;
	*/

	/*
	//Day 14, Parts 1 and 2
	  //vector<string> polymerData = getData("test14.txt");//this is to run test case
    vector<string> polymerData = getData("Day14-input.txt");

	  pair<vector<pair<char, long int>>, vector<vector<pair<long int,int>>>>
	elementsAndPairs = getPolymers(polymerData); pair<vector<pair<char, long
	int>>, vector<vector<pair<long int,int>>>> newElementsAndPairs =
	insertElements(elementsAndPairs,40); long int elementDifference =
	getDifference(newElementsAndPairs.first);

	  for (int i = 0; i < newElementsAndPairs.first.size(); ++i){ // print out
	the scores std::cout << newElementsAndPairs.first[i].first << ", " <<
	newElementsAndPairs.first[i].second << std::endl ;
	  }
	  std::cout << elementDifference << std::endl;
	*/

	// Day 15

	//int pathChitonRisk = Day15_1("test15.txt");  //this is to run test case
	//int pathChitonRisk = Day15_1("Day15-input.txt");

	//int pathChitonRisk = Day15_2("test15.txt");  //this is to run test case
	//int pathChitonRisk = Day15_2("Day15-input.txt");
	//std::cout << "lowest total risk: " << pathChitonRisk << std::endl;

  // Day 16

	//pair<int,long long int> versionAndValue = Day16("test16-1.txt");  //this is to run test case
	//pair<int,long long int> versionAndValue = Day16("test16-2.txt");  //this is to run test case
	//pair<int,long long int> versionAndValue = Day16("test16-3.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-4.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-5.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-6.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-7.txt");  //this is to run test case

	//pair<int,long long int> versionAndValue = Day16("test16-8sum.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-8prod.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-8min.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-8max.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-8lt.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-8gt.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-8ne.txt");  //this is to run test case
  //pair<int,long long int> versionAndValue = Day16("test16-8eq.txt");  //this is to run test case
  /*
	pair<int,long long int> versionAndValue = Day16("Day16-input.txt");
	std::cout << "sum of version numbers: " << versionAndValue.first << std::endl;
  std::cout << "expression value: " << versionAndValue.second << std::endl;
  */
  
  //Day 17

  //pair<int,int> maxHeightAndNumber = Day17("test17.txt"); //test case
  /*
  pair<int,int> maxHeightAndNumber = Day17("Day17-input.txt");
  std::cout << "max height " << maxHeightAndNumber.first << std::endl;
  std::cout << "count " << maxHeightAndNumber.second << std::endl;
  */

  //Day 18
/*
  //pair<int,int> magnitudeAndMax = Day18("test18.txt"); //test case
  pair<int,int> magnitudeAndMax = Day18("Day18-input.txt");
  std::cout << "magnitude " << magnitudeAndMax.first << std::endl;
  std::cout << "max " << magnitudeAndMax.second << std::endl;
  */
  //Day 19
  /*
  //pair<int,int> beaconsAndMax = Day19("test19.txt"); //test case
  pair<int,int> beaconsAndMax = Day19("Day19-input.txt");
  std::cout << "beacons " << beaconsAndMax.first << std::endl;
  std::cout << "max " << beaconsAndMax.second << std::endl;
*/
  //Day 20
  pair<int,int> pixelsAndMax = Day20("test20.txt"); //test case
  //pair<int,int> pixelsAndMax = Day20("Day20-input.txt");
  std::cout << "2 enhancements " << pixelsAndMax.first << std::endl;
  std::cout << "50 enhancements " << pixelsAndMax.second << std::endl;
  
	return 0;
}