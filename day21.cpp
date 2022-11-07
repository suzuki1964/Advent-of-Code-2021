#include "functions.h"

pair<int,long int> Day21(string filename) {
	vector<string> startData = getData(filename); //data is strings "Player 1 starting position: 8"
  vector<int> startingPositions = getPositions(startData);
  //vector<int> startingPositions; //to test
  //startingPositions.push_back(4);
  //startingPositions.push_back(8);
  int score = runDeterministic(startingPositions);
  long int max = runDirac(startingPositions);
  pair<int,long int> scoreAndMax = std::make_pair(score, max);
  return scoreAndMax;
}

vector<int> getPositions(vector<string> data){
  vector<int> positions;
  size_t last_pos = 0;
  size_t split_pos = 0;
  for (int i = 0; i < 2; ++i){
    split_pos = data[i].find(':');
    last_pos = split_pos +2; //advance past the space after the :
    split_pos = data[i].find(" ", last_pos); //find the space after the number
    positions.push_back(stoi(data[i].substr(last_pos,split_pos -last_pos))); //convert the string to an int
    //std::cout << positionOne << std::endl;
  }
  return positions;
}
  
int runDeterministic(vector<int> positions){
  std::cout << "start " << positions[0] << ", " << positions[1] << std::endl;
  vector<int> playerPositions = positions; // mod 10
  vector<int> playerScores(2,0);
  int numberOfRolls = 0;
  int lastNumberRolled = 0;
  int sumOfRolls = 0;
  bool whichPlayer = false; //false for player 1, true for player 2
  int score = 0;
  while ((playerScores[0] < 1000) && (playerScores[1] < 1000)){
    numberOfRolls+=3;
    /*actually don't need this whole section since 100 is a multiple of 10
    lastNumberRolled = numberOfRolls%100;
    if (numberOfRolls > 100){
      if (lastNumberRolled == 0){ // previous last roll was 97
        sumOfRolls = 98+99+100;
      }
      else if (lastNumberRolled == 1){ // previous last roll was 98
        sumOfRolls = 99+100+1;
      }
      else if (lastNumberRolled == 2){ // previous last roll was 99
        sumOfRolls = 100+1+2;
      }
      else { // we rolled three consecutive integers, so their sum is 3 times the middle number
      sumOfRolls = (lastNumberRolled - 1) * 3;
      }
    }
    else { // we rolled three consecutive integers, so their sum is 3 times the middle number
      sumOfRolls = (lastNumberRolled - 1) * 3;
    }
    */
    sumOfRolls = (lastNumberRolled - 1) * 3;
    playerPositions[whichPlayer] = (playerPositions[whichPlayer] + sumOfRolls)%10;
    playerScores[whichPlayer] += playerPositions[whichPlayer];
    if (playerPositions[whichPlayer] == 0){
      playerScores[whichPlayer] += 10;
    }
    if (playerScores[whichPlayer] >= 1000){
      score = numberOfRolls * playerScores[!whichPlayer];
    }
    whichPlayer = !whichPlayer;
  }
  return score;
}

//still too slow
long int runDirac(vector<int> positions){
  vector<int> playerPositions = positions; //starting positions of players 1 and 2
  vector<int> playerScores(2,0);
  bool whichPlayer = false; //false for player 1, true for player 2
  vector<long int> tallyOfWins(2,0); //number of games each player wins
  tallyOfWins = moveOnce(playerPositions,playerScores,whichPlayer);
  if (tallyOfWins[0] < tallyOfWins[1]){
    return tallyOfWins[1]; //return the larger number
  }
  else {
    return tallyOfWins[0];
  }
}

vector<long int> moveOnce(vector<int> positions,vector<int> scores,bool player){
  vector<int> newPositions(2,0);
  vector<int> newScores(2,0);
  vector<long int> newTally(2,0);
  vector<long int> addToTally(2,0);
  for (int dieRoll = 3; dieRoll < 10; dieRoll++){ // the three rolls of the die sum to 3,4,5,6,7,8,or 9
    newPositions[player] = (positions[player] + dieRoll)%10; //move the player
    newPositions[!player] = positions[!player]; //don't move the other guy
    newScores[player] = scores[player] + newPositions[player];
    newScores[!player] = scores[!player];
    if (newPositions[player] == 0){
      newScores[player] += 10; //add 10 if the player lands on place 10
    }
    if (newScores[player] >= 21){ //if the player won, set the tally to 1
      addToTally[player] = 1; 
      addToTally[!player] = 0;
    }
    else {
      addToTally = moveOnce(newPositions,newScores,!player); //get the tally from this point on
    }
    switch(dieRoll){ //there is 1 way to roll 3, 3 ways to roll 4, 6 ways to roll 5, 7 ways to roll 6, etc.
      case 3:
        newTally[player] += 1 * addToTally[player];
        newTally[!player] += 1 * addToTally[!player];
        newPositions[player] = positions[player];
        newScores[player] = scores[player];
        break;
      case 4:
        newTally[player] += 3 * addToTally[player];
        newTally[!player] += 3 * addToTally[!player];
        newPositions[player] = positions[player];
        newScores[player] = scores[player];
        break;
      case 5:
        newTally[player] += 6 * addToTally[player];
        newTally[!player] += 6 * addToTally[!player];
        newPositions[player] = positions[player];
        newScores[player] = scores[player];
        break;
      case 6:
        newTally[player] += 7 * addToTally[player];
        newTally[!player] += 7 * addToTally[!player];
        newPositions[player] = positions[player];
        newScores[player] = scores[player];
        break;
      case 7:
        newTally[player] += 6 * addToTally[player];
        newTally[!player] += 6 * addToTally[!player];
        newPositions[player] = positions[player];
        newScores[player] = scores[player];
        break;
      case 8:
        newTally[player] += 3 * addToTally[player];
        newTally[!player] += 3 * addToTally[!player];
        newPositions[player] = positions[player];
        newScores[player] = scores[player];
        break;
      case 9:
        newTally[player] += 1 * addToTally[player];
        newTally[!player] += 1 * addToTally[!player];
        newPositions[player] = positions[player];
        newScores[player] = scores[player];
        break;
    }
  }
  return newTally;
}