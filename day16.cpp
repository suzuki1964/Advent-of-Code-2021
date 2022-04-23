#include "functions.h"

pair<int, long long int> Day16(string filename) {
	int sum = 0; //sum of the version numbers of the packets
  long long int expression = 0; //value of the expression
	vector<string> bitData = getData(filename); //data is just one (long) string in hex
  string binaryData = makeBinary(bitData[0]);
  return std::make_pair(sum,expression) = parseData(binaryData);
}

pair<int, long long int> parseData(string bString){ //read in the packets and add up the version numbers
  int versionSum = 0; //the sum of the version numbers of the packets
  long long int expressionValue = 0; //the value of the expression
  int startPos = 0; //where to start reading in the next packet
  int packetVersion; //the version number of this packet
  int packetLength; //the length of this packet
  std::tuple<int,int, long long int> packetValue = std::make_tuple(packetVersion, packetLength, expressionValue);
  packetValue = getPacket(bString, startPos); //read in the packet and return the (version number,packet length) and expression value
  versionSum += std::get<0>(packetValue);
  expressionValue = std::get<2>(packetValue);
  return std::make_pair(versionSum,expressionValue);
}

std::tuple<int,int,long long int> getPacket(string bString, int k){ //start reading the packet from position k
  string version = bString.substr(k,3); //first 3 bits give the version number
  string type = bString.substr(k+3,3); //next 3 bits give the type ID
  int length = 6; //now we have read in the first 6 bits of the packet
  int versionDecimal = std::stoi(version, nullptr, 2); //convert the binary to decimal
  int typeDecimal = std::stoi(type, nullptr, 2);

  //read in the subpackets and store the numbers
  vector<long long int> packetNumbers;
  long long int expressionValue = 0; //the value of the expression
  if (typeDecimal == 4){
    pair<long int,int> literalDecimal = getLiterals(bString,k+length); //read in the literal number, return (decimal number,length)
    length += literalDecimal.second;
    expressionValue = literalDecimal.first;
  }
  else {
    if (bString[k+length] =='0'){ //if the next bit is 0
      string totalLengthString = bString.substr(k+length+1,15); //the next 15 bits gives the length of the subpackets
      int totalLengthDecimal = std::stoi(totalLengthString, nullptr, 2); //convert binary to decimal
      length += 16; //now we are 16 bits further into the packet
      int readLength = 0; //keep track of how many bits of subpackets we have read
      while (readLength < totalLengthDecimal){
        std::tuple<int,int,long long int> packetValue = getPacket(bString, k+length);
        versionDecimal += std::get<0>(packetValue); //keep a running sum of the version numbers
        readLength += std::get<1>(packetValue); //add up the number of bits we have read
        length += std::get<1>(packetValue); //move the starting position to the beginning of the next packet
        packetNumbers.push_back(std::get<2>(packetValue)); //store the number from the subpacket
      }
    }
    else { //if the next bit is 1
      string numberOfSubsString = bString.substr(k+length+1,11); //the next 11 bits give the number of subpackets
      int numberOfSubsDecimal = std::stoi(numberOfSubsString, nullptr, 2); //convert binary to decimal
      length += 12; //we are now 12 more bits into this packet
      int numberOfPackets = 0; //keep track of the number of subpackets read
      for (int i = 0; i < numberOfSubsDecimal; ++i){
        std::tuple<int,int, long long int> packetValue = getPacket(bString, k+length);
        versionDecimal += std::get<0>(packetValue); //keep a running sum of the version numbers
        length += std::get<1>(packetValue); //move the starting position to the beginning of the next packet
        packetNumbers.push_back(std::get<2>(packetValue)); //store the number from the subpacket
      }
    }
    //now evaluate the expression
    switch(typeDecimal){
      case 0:{
        for (int i = 0; i < packetNumbers.size(); ++i){
          expressionValue += packetNumbers[i];
        }
        break;
      }
      case 1:{
        expressionValue = 1;
        for (int i = 0; i < packetNumbers.size(); ++i){
          expressionValue *= packetNumbers[i];
        }
        break;
      }
      case 2:{
        expressionValue = packetNumbers[0];
        for (int i = 1; i < packetNumbers.size(); ++i){
          if (packetNumbers[i] < expressionValue){
            expressionValue = packetNumbers[i];
          }
        }
        break;
      }
      case 3:{
        expressionValue = packetNumbers[0];
        for (int i = 1; i < packetNumbers.size(); ++i){
          if (packetNumbers[i] > expressionValue){
            expressionValue = packetNumbers[i];
          }
        }
        break;
      }
      case 5:{
        expressionValue = (packetNumbers[0] > packetNumbers[1]);
        break;
      }
      case 6:{
        expressionValue = (packetNumbers[0] < packetNumbers[1]);
        break;
      }
      case 7:{
        expressionValue = (packetNumbers[0] == packetNumbers[1]);
        break;
      }
    }
  }
  return std::make_tuple(versionDecimal,length,expressionValue);
}

pair<long int,int> getLiterals(string bString,int k){ //return decimal number and length
  int length = 0;
  int prefix = 1;
  string literal; //hold the 5 bits,leading bit is 1 if continue, 0 if stop reading
  string literalString; //the 4 bits that are part of the literal binary number
  while (prefix != 0){
    literal = bString.substr(k+length,5); //read in 5 bits starting at k+length
    prefix = literal[0] - '0'; //1 if continue, 0 if stop
    literalString.append(literal, 1, 4);
    length += 5; //move forward 5 and read in the next group (or stop)
  }
  long int literalDecimal = std::stol(literalString, nullptr,2);
  return std::make_pair(literalDecimal, length);
}
  
string makeBinary(string hexString){
  string binaryString;
  for (int i = 0; i < hexString.length(); ++i){
    switch (hexString[i]){
      case '0': {
        binaryString.append("0000");
        break;
      }
      case '1': {
        binaryString.append("0001");
        break;
      }
      case '2': {
        binaryString.append("0010");
        break;
      }
      case '3': {
        binaryString.append("0011");
        break;
      }
      case '4': {
        binaryString.append("0100");
        break;
      }
      case '5': {
        binaryString.append("0101");
        break;
      }
      case '6': {
        binaryString.append("0110");
        break;
      }
      case '7': {
        binaryString.append("0111");
        break;
      }
      case '8': {
        binaryString.append("1000");
        break;
      }
      case '9': {
        binaryString.append("1001");
        break;
      }
      case 'A': {
        binaryString.append("1010");
        break;
      }
      case 'B': {
        binaryString.append("1011");
        break;
      }
      case 'C': {
        binaryString.append("1100");
        break;
      }
      case 'D': {
        binaryString.append("1101");
        break;
      }
      case 'E': {
        binaryString.append("1110");
        break;
      }
      case 'F': {
        binaryString.append("1111");
        break;
      }
    }
  }
  return binaryString;
}