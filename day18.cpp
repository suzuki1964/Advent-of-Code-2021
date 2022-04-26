#include "functions.h"

pair<int,int> Day18(string filename) {
	vector<string> snailNumberData = getData(filename); //data is strings of the form [7,[5,[[3,8],[1,4]]]]
  string sum = getSum(snailNumberData); //get the reduced sum of all the snail numbers
  int magnitude = findMag(sum); //find the magnitude of the sum
  int maxMag = getMaxMag(snailNumberData); //find the maximum magnitude of the sums of all pairs
  pair<int,int> magnitudeAndMax = std::make_pair(magnitude, maxMag);
  return magnitudeAndMax;
}

int getMaxMag(vector<string> data){
  int max = 0;
  for (int i = 0; i < data.size(); ++i){ //snail number addition is not commutative
    for (int j = 0; j < data.size(); ++j){ //so we have to run through all pairs (i,j) with i != j
      if (i != j){
        string sum = "[" + data[i] + "," + data[j] + "]"; //add the two snail numbers
        reduce(sum); //reduce this sum first
        int mag = findMag(sum); //then find the magnitude
        if (mag > max){ //if it is larger than any of the previous sums, then update the max value
          max = mag;
        }
      }
    }
  }
  return max;
}

string getSum(vector<string> data){
  string sum = data[0]; //set the first snail number
  for (int i = 1; i < data.size(); ++i){ //then add one at a time
    sum = "[" + sum + "," + data[i] + "]";
    reduce(sum); //and reduce before adding the next number
  }
  return sum;
}

int findMag(string number){ //calculate the magnitude of the snail number
  int mag = 0;
  string num = number;
  size_t pos = 1;
  while (pos != 0){
    pair<pair<int,int>,size_t> pairMag = findPair(num,pos, false); //find a pair and replace it by its magnitude
    pos = pairMag.second; //change the position to the location of that number
  }
  mag = stoi(num); //the string ends up being just the magnitude, so convert it to an int
  return mag;
}

void reduce(string &number){ //we reduce the snail number by looking for pairs to explode and numbers to split
  bool didReduce = true;
  while (didReduce){ //keep reducing until there is nothing more to reduce
    didReduce = willExplode(number); //if there was a pair to explode, then keep going
    didReduce = willSplit(number); //if there was a number to split, then keep going
  }
}

bool willSplit(string &number){ //a number bigger than 9 splits into a pair
  size_t p = 0;
  bool done = false;
  while ((p != string::npos) && (!done)){ //keep looking until you find a number bigger than 9
    p = number.find_first_of("0123456789",p); //if you find a number
    if (p != string::npos){
      size_t q = number.find_first_of("[],",p); //look for the bracket or comma so you get all the digits
      string nextNum = number.substr(p,q-p); //this is the string of all the digits
      int next = stoi(nextNum); //convert that string to an int
      if (next>=10){ //if it is bigger than 9, split it into a pair
        int first = floor (float(next)/2); //round down the first
        int second = ceil (float(next)/2); //round up the second
        string firstNum = std::to_string(first); //convert them to strings 
        string secondNum = std::to_string(second);
        string newPair = "[" + firstNum + "," + secondNum + "]"; //make the new pair
        number.replace(p,q-p,newPair); //replace the too-big number by the new pair
        p = number.find("]",p); //set the location to the end of the new pair
        done = true; //set to done so you stop if you found a number to split
      }
      p++; //go to the next character and keep looking for a too-big number if you haven't found one yet
    }
  }
  return done; //let them know if you found a number to split
}

bool willExplode(string &number){
  bool didExplode = false;
  int nestingNum = 0; //if there is a pair nested more than 4 times, the it explodes
  for (int i = 0; i < number.length(); ++i){ //so through the string 
    if (number[i] == '['){ //count the number of open brackets
      nestingNum ++;
    }
    if (number[i] == ']'){ //and subtract the close brackets
      nestingNum --;
    }
    if (nestingNum > 4){ //if it is larger than 4, the next pair explodes
      didExplode = true; //set the flag to tell them that a pair exploded
      while (number[i+1] != ']'){ //look for the first close bracket
        if (number[i+1] == '['){ //but keep counting the open brackets
          nestingNum ++;
        }
        i++;
      }
      i = explode(number,i); //when you find the first close bracket, explode that pair
      nestingNum--; //and reduce the nesting number after you remove the pair
    }
  }
  return didExplode; //let them know whether or not a pair exploded
}

int explode(string &number,int i){ 
  pair<int,int> explodingPair;
  pair<pair<int,int>,int> exploder = findPair(number,i, true); //find the pair and replace it with 0 (the last flag tells you that this is an exploding pair that needs to be replace by 0)
  size_t k = exploder.second; //set the location
  if ((k != string::npos) && (k != 0)){ //if it is not at the front
    size_t p = number.find_last_of("0123456789",k-1); //look for the last number before the exploding pair
    if (p != string::npos){ //if there was a number
      size_t q = number.find_last_of("[],",p); //find the bracket or comma so you get all the digits
      if (q != string::npos){
        string leftNum = number.substr(q+1,p-q); //this is the string of all the digits
        int left = stoi(leftNum); //convert to int
        int newLeft = left + exploder.first.first; //add the first number of the pair to the number of the left
        leftNum = std::to_string(newLeft); //convert back to string
        number = number.replace(q+1,p-q,leftNum); //replace the old number by the sum
      }
    }
  }
  size_t p = number.find_first_of("0123456789",k+2); //do the same on the right
  if (p != string::npos){ //find the first number on the right
    size_t q = number.find_first_of("[],",p); //find the end of the number
    if (q != string::npos){
      string rightNum = number.substr(p,q-p); //this is the string of all the digits
      int right = stoi(rightNum); //convert to int
      int newRight = right + exploder.first.second; //add the second number of the pair
      rightNum = std::to_string(newRight); //convert back to a string
      number = number.replace(p,q-p,rightNum); //replace the number on the right by the sum
    }
  }
  return k; //send back the location
}

pair<pair<int,int>,size_t> findPair(string &number, int i, bool exploding){ //this finds the pair
  string exploder;
  size_t j = number.find(']',i); //look for the first close bracket
  size_t k = number.find_last_of('[',j); //go back and find the closest open bracket
  size_t m = number.find(',',k+1); //and look for the comma so you get all the digits of the numbers
  string firstNumber = number.substr(k+1,m-k-1); //this string is all the digits of the first number of the pair
  int first = stoi(firstNumber);
  string secondNumber = number.substr(m+1,j-m-1);
  int second = stoi(secondNumber);
  exploder = number.substr(k,j-k+1); //this string is the whole pair
  if (exploding){ //if the flag is set to exploding, then replace the pair with 0
    number = number.replace(k,j-k+1,"0");
  }
  else{ //if the flag is set to getting the magnitude, replace the pair with the magnitude
    int mag = 3*first + 2*second;
    string magStr = std::to_string(mag); //convert the magnitude to a string
    number = number.replace(k,j-k+1,magStr); //replace the pair with the magnitude string
  }
  pair<pair<int,int>,size_t> explodingPair = std::make_pair(std::make_pair(first,second),k);
  return explodingPair; //send back the pair of numbers and the location
}