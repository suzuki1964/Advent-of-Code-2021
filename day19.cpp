#include "functions.h"
# include "scanner.h"

//each beacon has a location relative to the scanner that sees it
Beacon::Beacon(){
  beacon_coords_ = std::make_tuple(0,0,0);
}

Beacon::Beacon(int beacon_number){
  beacon_coords_ = std::make_tuple(0,0,0);
  beacon_number_ = beacon_number;
}

void Beacon::SetBeaconNumber(int i){
  beacon_number_ = i;
}

int Beacon::GetBeaconNumber(){
  return beacon_number_;
}

void Beacon::SetBeaconCoords(int x, int y, int z){
  beacon_coords_ = std::make_tuple(x,y,z);
}

void Beacon::SetBeaconCoords(tuple<int,int,int> coords){
  beacon_coords_ = coords;
}

tuple<int,int,int> Beacon::GetBeaconCoords(){
  tuple<int,int,int> coords = beacon_coords_;
  return coords;
}

//Each scanner has a number, location and orientation(unknown), and a list of beacons it sees (and their locations)
//We look for overlaps where two scanners see the same beacons.
//As we find those overlaps, we can get the orientation and location of scanner l relative to scanner k.
//And we add all the beacons seen by scanner l to those seen by scanner k (coordinates w.r.t. scanner k).
//We need to keep track of the locations of all scanners by keeping a list of scanners already merged in.
Scanner::Scanner(int scanner_number){
  scanner_number_ = scanner_number;
}

int Scanner::GetNumber(){
  return scanner_number_;
} 

void Scanner::SetNumber(int scanner_number){
  scanner_number_ = scanner_number;
}

void Scanner::SetLocation(int x, int y, int z){
  location_ = std::make_tuple (x,y,z);
} 

void Scanner::SetLocation(tuple<int,int,int> coords){
  location_ = coords;
}

//set the orientation of l relative to k
//in the first pair, the first number tells you which coordinate x in k corresponds to in l, the second number is +/-1
void Scanner::SetOrientation (tuple<pair<int, int>, pair<int,int>, pair<int,int>> coordsNDirection){
  orientation_ = coordsNDirection;
} 

tuple<int,int,int> Scanner::GetLocation(){
  tuple<int,int,int> coords = location_;
  return coords;
} 

tuple<pair<int, int>, pair<int,int>, pair<int,int>> Scanner::GetOrientation(){
  tuple<pair<int, int>, pair<int,int>, pair<int,int>> orientation = orientation_;
  return orientation;
}

//we need the original number of beacons so we can check if the overlaps have 12 beacons
void Scanner::SetNumberOfBeacons(int number_of_beacons){
  number_of_beacons_ = number_of_beacons;
}

int Scanner::GetNumberOfBeacons(){
  return number_of_beacons_;
}

void Scanner::SetMerged(bool merged){ //set flag if this scanner's beacons have already been merged
  merged_ = merged;
}

bool Scanner::GetMerged(){
  return merged_;
}

//Scanner k contains a pair of beacons a given distance dist apart
pair<int,int> Scanner::Contains(int dist){ //returns the (a?) pair of beacons distance dist apart
  pair<int, int> whichBeacons = std::make_pair(-1,-1); //returns (-1,-1) if no such pair exists
  for (int m = 0; m < beacon_list_.size()-1; ++m){
    for (int n = m+1; n < beacon_list_.size(); ++n){
      if (distances_[m][n] == dist){
        whichBeacons = std::make_pair(m,n);
      }
    }
  }
  return whichBeacons;
} 

void Scanner::AddBeacon(int x, int y, int z){ //add a beacon to the end of the list
  int number = beacon_list_.size();
  Beacon beacon = Beacon(number);
  beacon.SetBeaconCoords(x,y,z);
  beacon_list_.push_back(beacon);
}

void Scanner::AddBeacon(tuple<int,int,int> coords){
  int number = beacon_list_.size();
  Beacon beacon = Beacon(number);
  beacon.SetBeaconCoords(coords);
  beacon_list_.push_back(beacon);
}

Beacon Scanner::GetBeacon(int i){
  Beacon beacon = beacon_list_[i];
  return beacon;
}

bool Scanner::ContainsBeacon(int x, int y, int z){ //check if a beacon at these coords is already in the list
  bool isInList = false;
  for (int i = 0; i < beacon_list_.size(); ++i){
    tuple<int,int,int> coords = beacon_list_[i].GetBeaconCoords();
    if ((x == std::get<0>(coords)) && (y == std::get<1>(coords)) && (z == std::get<2>(coords))){
      isInList = true;
    }
  }
  return isInList;
}

bool Scanner::ContainsBeacon(tuple<int,int,int> checkCoords){
  bool isInList = false;
  for (int i = 0; i < beacon_list_.size(); ++i){
    tuple<int,int,int> beaconCoords = beacon_list_[i].GetBeaconCoords();
    if (checkCoords == beaconCoords){
      isInList = true;
    }
  }
  return isInList;
}

int Scanner::FindNumberOfBeacons(){ //gives current number of beacons in the list of beacons seen by this scanner
  int number = beacon_list_.size();
  return number;
}

void Scanner::MakeDistanceArray(int n){ //makes an array to hold the distances between all pairs of n beacons
  if (n>0){
    vector<int> row;
    for (int k = 0; k < n; ++k){
      row.push_back(0);
    }
    for (int k = 0; k < n; ++k){
      distances_.push_back(row);
    }
  }
}

//sets distances between beacon m and beacon n
void Scanner::SetDistances(){
  for (int m = 0; m < beacon_list_.size() - 1 ; ++m){
    tuple<int,int,int> coordsOfM = beacon_list_[m].GetBeaconCoords();
    for (int n = m+1; n < beacon_list_.size() ; ++n){      
      tuple<int,int,int> coordsOfN = beacon_list_[n].GetBeaconCoords();
      int xDist = std::abs(std::get<0>(coordsOfM) - std::get<0>(coordsOfN));
      int yDist = std::abs(std::get<1>(coordsOfM) - std::get<1>(coordsOfN));
      int zDist = std::abs(std::get<2>(coordsOfM) - std::get<2>(coordsOfN));
      int dist = xDist+yDist+zDist;
      distances_[m][n] = dist;
      distances_[n][m] = dist;
    }
  } 
}

int Scanner::GetDistance(int m, int n){
  int d = distances_[m][n];
  return d;
}

void Scanner::PrintDistances (){ //to test
  std::cout << beacon_list_.size() << std::endl;
  for (int m = 0; m < beacon_list_.size()-1; ++m){
    for (int n = m+1; n < beacon_list_.size(); ++n){
      std::cout << m << ", " << n << ": " << distances_[m][n] << " ";
    }
    std::cout << std::endl;
  }
}

void Scanner::AddScannerToList(int k,tuple<int,int,int> coords){
  pair<int,tuple<int,int,int>> scannerAndPosition = std::make_pair(k,coords);
  scanner_list_.push_back(scannerAndPosition);
}

void Scanner::UpdateScannerPosition(int i,tuple<int,int,int> coords){
  pair<int,tuple<int,int,int>> scannerAndPosition = std::make_pair(scanner_list_[i].first,coords);
  scanner_list_[i] = scannerAndPosition;
}

tuple<int,int,int> Scanner::GetScannerPosition(int k){
  tuple<int,int,int> coords;
  for (int i = 0; i < scanner_list_.size(); ++i){
    if (scanner_list_[i].first == k){
      coords = scanner_list_[i].second;
    }
  }
  return coords;
}

int Scanner::GetScannerNumber(int i){
  return scanner_list_[i].first;
}

int Scanner::GetNumberOfScanners(){
  return scanner_list_.size();
}

int Scanner::MaxDistance(){ //find max Manhattan distance between pairs of scanners in the list
  int max = 0;
  for (int m = 0; m < scanner_list_.size()-1; ++m){
    tuple<int,int,int> coordsOfM = scanner_list_[m].second;
    for (int n = m + 1; n < scanner_list_.size(); ++n){
      tuple<int,int,int> coordsOfN = scanner_list_[n].second; //get the Manhattan distance between scanners
      int xDist = std::abs(std::get<0>(coordsOfM) - std::get<0>(coordsOfN));
      int yDist = std::abs(std::get<1>(coordsOfM) - std::get<1>(coordsOfN));
      int zDist = std::abs(std::get<2>(coordsOfM) - std::get<2>(coordsOfN));
      int dist = xDist+yDist+zDist;
      if (dist > max){
        max = dist;
      }
    }
  }
  return max;
}


pair<int,int> Day19(string filename) {
	vector<string> scannerData = getData(filename); //data is in the form 
  // --- scanner 0 ---
  // 404,-588,-901
  // 528,-643,409
  // -838,591,734
  
  pair<int,int> beaconsAndMax = findTotalAndMax(scannerData);
  return beaconsAndMax;
}

pair<int,int> findTotalAndMax(vector<string> data){
  pair<int,int> totalAndMax;
  vector<Scanner> scannerList = getScanners(data); //list of scanners with the beacons they see
  combineCubes(scannerList,0);

  int total = scannerList[0].FindNumberOfBeacons();
  int max = scannerList[0].MaxDistance();
  totalAndMax = std::make_pair(total, max);
  return totalAndMax;
}

void combineCubes(vector<Scanner> &scannerList,int k){
  scannerList[k].SetMerged(true);
  for (int l = 0; l < scannerList.size(); ++l){
    if (!scannerList[l].GetMerged()){
      vector<pair<int,int>> matchingBeacons = findOverlaps(scannerList, k, l); //find corresponding beacons in overlap
      if (matchingBeacons.size() >= 12){
        combineCubes(scannerList,l);
        findLocation(matchingBeacons, scannerList, k, l);
      }
    }
  }
}

vector<pair<int,int>> findOverlaps(vector<Scanner> list, int k, int l){ //return a list of matching beacons (from scanner k to l)
  vector<pair<int,int>> matchingBeaconsNumbers;
  for (int m = 0; m < list[k].GetNumberOfBeacons(); ++m){
    vector<int> matchingBeaconCounts (list[l].GetNumberOfBeacons(),0);
    for (int n = 0; n < list[l].GetNumberOfBeacons(); ++n){
      if (n != m){
        pair<int,int> theseBeacons = list[l].Contains(list[k].GetDistance(m,n));
        if (theseBeacons.first != -1){
          matchingBeaconCounts[theseBeacons.first]++;
          matchingBeaconCounts[theseBeacons.second]++;
        }
      }
    }
    if (*std::max_element(matchingBeaconCounts.begin(), matchingBeaconCounts.end())>5){
      int max = std::max_element(matchingBeaconCounts.begin(), matchingBeaconCounts.end()) - matchingBeaconCounts.begin();
      matchingBeaconsNumbers.push_back(std::make_pair(m,max));
    } 
  }
  return matchingBeaconsNumbers;
}

void findLocation(vector<pair<int,int>> matchingBeacons, vector<Scanner> &list, int k, int l){
  int x,y,z; //coordinates of scanner l relative to scanner k
  tuple<int,int,int> coordsOfK = list[k].GetLocation(); //location of scanner k
  //for the first pair of corresponding beacons, get their coords w.r.t. their scanners
  tuple<int,int,int> coordsOfBeaconK = list[k].GetBeacon(matchingBeacons[0].first).GetBeaconCoords();
  tuple<int,int,int> beaconCoordsK = addCoords(coordsOfK,coordsOfBeaconK);
  tuple<int,int,int> coordsOfBeaconL = list[l].GetBeacon(matchingBeacons[0].second).GetBeaconCoords(); 
  //to find the transformation, compare the vector from the first matching pair to the second in each scanner
  tuple<int,int,int> vectorBetweenBeaconsK = subtractCoords(list[k].GetBeacon(matchingBeacons[0].first).GetBeaconCoords(), list[k].GetBeacon(matchingBeacons[1].first).GetBeaconCoords());
  tuple<int,int,int> vectorBetweenBeaconsL = subtractCoords(list[l].GetBeacon(matchingBeacons[0].second).GetBeaconCoords(), list[l].GetBeacon(matchingBeacons[1].second).GetBeaconCoords());
  tuple<pair<int, int>, pair<int,int>, pair<int,int>> transformation = findTransformation(vectorBetweenBeaconsK,vectorBetweenBeaconsL);
  list[k].SetOrientation(transformation); //this gives the correspondence between coordinates
  tuple<int,int,int> coordsInK = transformLtoK(list[l].GetBeacon(matchingBeacons[0].second).GetBeaconCoords(),transformation);
  tuple<int,int,int> scannerLCoords = subtractCoords(list[k].GetBeacon(matchingBeacons[0].first).GetBeaconCoords(),coordsInK);
  list[l].SetLocation(scannerLCoords);
  //change to coordinates of all merged scanners to be relative to scanner k
  for (int i = 0; i < list[l].GetNumberOfScanners(); ++i){
    tuple<int,int,int> flipScannerCoords = transformLtoK(list[l].GetScannerPosition(list[l].GetScannerNumber(i)),transformation);
    tuple<int,int,int> newScannerCoords = addCoords(flipScannerCoords,list[l].GetLocation());
    list[k].AddScannerToList(list[l].GetScannerNumber(i), newScannerCoords);
  }
  list[k].AddScannerToList(l,scannerLCoords); //add scanner l with position relative to scanner k
  //move beacons from scanner l to scanner k
  int count = 0;
  for (int i = 0; i < list[l].FindNumberOfBeacons(); ++i){
    tuple<int,int,int> flipBeaconCoords = transformLtoK(list[l].GetBeacon(i).GetBeaconCoords(),transformation);
    tuple<int,int,int> newBeaconCoords = addCoords(flipBeaconCoords,list[l].GetLocation());
    if (list[k].ContainsBeacon(newBeaconCoords)){
      count++;
    }
    if (!list[k].ContainsBeacon(newBeaconCoords)){
      list[k].AddBeacon(newBeaconCoords);
    }
  }  
}

tuple<pair<int,int>, pair<int,int>, pair<int,int>> findTransformation(tuple<int,int,int> vectorK,tuple<int,int,int> vectorL){
  tuple<pair<int,int>, pair<int,int>, pair<int,int>> transform;
  int xCoord, yCoord, zCoord;
  int xUp, yUp, zUp;
  if (std::get<0>(vectorK) == std::get<0>(vectorL)){
    xCoord = 0; //x in k corresponds to x in l
    xUp = 1;
  }
  else if (std::get<0>(vectorK) == -(std::get<0>(vectorL))){
    xCoord = 0; //x in k corresponds to x in l
    xUp = -1; //direction is opposite
  }
  else if (std::get<0>(vectorK) == std::get<1>(vectorL)){
    xCoord = 1; //x in k corresponds to y in l
    xUp = 1;
  }
  else if (std::get<0>(vectorK) == -(std::get<1>(vectorL))){
    xCoord = 1; //x in k corresponds to y in l
    xUp = -1; //direction is opposite
  }
  else if (std::get<0>(vectorK) == std::get<2>(vectorL)){
    xCoord = 2; //x in k corresponds to z in l
    xUp = 1;
  }
  else if (std::get<0>(vectorK) == -(std::get<2>(vectorL))){
    xCoord = 2; //x in k corresponds to z in l
    xUp = -1; //direction is opposite
  }
  if (std::get<1>(vectorK) == std::get<0>(vectorL)){
    yCoord = 0; //y in k corresponds to x in l
    yUp = 1;
  }
  else if (std::get<1>(vectorK) == -(std::get<0>(vectorL))){
    yCoord = 0; //y in k corresponds to x in l
    yUp = -1; //direction is opposite
  }
  else if (std::get<1>(vectorK) == std::get<1>(vectorL)){
    yCoord = 1; //y in k corresponds to y in l
    yUp = 1;
  }
  else if (std::get<1>(vectorK) == -(std::get<1>(vectorL))){
    yCoord = 1; //y in k corresponds to y in l 
    yUp = -1; //direction is opposite 
  }
  else if (std::get<1>(vectorK) == std::get<2>(vectorL)){
    yCoord = 2; //y in k corresponds to z in l 
    yUp = 1;
  }
  else if (std::get<1>(vectorK) == -(std::get<2>(vectorL))){
    yCoord = 2; //y in k corresponds to z in l
    yUp = -1; //direction is opposite
  }
  if (std::get<2>(vectorK) == std::get<0>(vectorL)){
    zCoord = 0; //z in k corresponds to x in l
    zUp = 1;
  }
  else if (std::get<2>(vectorK) == -(std::get<0>(vectorL))){
    zCoord = 0; //z in k corresponds to x in l
    zUp = -1; //direction is opposite
  }
  else if (std::get<2>(vectorK) == std::get<1>(vectorL)){
    zCoord = 1; //z in k corresponds to y in l 
    zUp = 1;
  }
  else if (std::get<2>(vectorK) == -(std::get<1>(vectorL))){
    zCoord = 1; //z in k corresponds to y in l
    zUp = -1; //direction is opposite
  }
  else if (std::get<2>(vectorK) == std::get<2>(vectorL)){
    zCoord = 2; //z in k corresponds to z in l
    zUp = 1;
  }
  else if (std::get<2>(vectorK) == -(std::get<2>(vectorL))){
    zCoord = 2; //z in k corresponds to z in l
    zUp = -1; //direction is opposite
  }
  transform = std::make_tuple(std::make_pair(xCoord,xUp),std::make_pair(yCoord,yUp),std::make_pair(zCoord,zUp));
  return transform;
}

tuple<int,int,int> transformLtoK(tuple<int,int,int> coords,tuple<pair<int,int>, pair<int,int>, pair<int,int>> transformation){
  tuple<int,int,int> newCoords;
  if (std::get<0>(transformation).first == 0){
    std::get<0>(newCoords) = std::get<0>(coords) * std::get<0>(transformation).second;
  }
  else if (std::get<0>(transformation).first == 1){
    std::get<0>(newCoords) = std::get<1>(coords) * std::get<0>(transformation).second;
  }
  else if (std::get<0>(transformation).first == 2){
    std::get<0>(newCoords) = std::get<2>(coords) * std::get<0>(transformation).second;
  }
  if (std::get<1>(transformation).first == 0){
    std::get<1>(newCoords) = std::get<0>(coords) * std::get<1>(transformation).second;
  }
  else if (std::get<1>(transformation).first == 1){
    std::get<1>(newCoords) = std::get<1>(coords) * std::get<1>(transformation).second;
  }
  else if (std::get<1>(transformation).first == 2){
    std::get<1>(newCoords) = std::get<2>(coords) * std::get<1>(transformation).second;
  }
  if (std::get<2>(transformation).first == 0){
    std::get<2>(newCoords) = std::get<0>(coords) * std::get<2>(transformation).second;
  }
  else if (std::get<2>(transformation).first == 1){
    std::get<2>(newCoords) = std::get<1>(coords) * std::get<2>(transformation).second;
  }
  else if (std::get<2>(transformation).first == 2){
    std::get<2>(newCoords) = std::get<2>(coords) * std::get<2>(transformation).second;
  }
  return newCoords;
}

tuple<int,int,int> addCoords(tuple<int,int,int> coordsOne,tuple<int,int,int> coordsTwo){
  tuple<int,int,int> sum;
  std::get<0>(sum) = std::get<0>(coordsOne) + std::get<0>(coordsTwo);
  std::get<1>(sum) = std::get<1>(coordsOne) + std::get<1>(coordsTwo);
  std::get<2>(sum) = std::get<2>(coordsOne) + std::get<2>(coordsTwo);
  return sum;
}

tuple<int,int,int> subtractCoords(tuple<int,int,int> coordsOne,tuple<int,int,int> coordsTwo){
  tuple<int,int,int> result;
  std::get<0>(result) = std::get<0>(coordsOne) - std::get<0>(coordsTwo);
  std::get<1>(result) = std::get<1>(coordsOne) - std::get<1>(coordsTwo);
  std::get<2>(result) = std::get<2>(coordsOne) - std::get<2>(coordsTwo);
  return result;
}

vector<Scanner> getScanners(vector<string> data){
  Scanner scanner = Scanner(0);
  scanner.SetLocation(0,0,0);
  vector<Scanner> scanners;
  size_t split_pos = 0;
  size_t last_pos = 0;
  int lastLine = 0; // -- WHY DOES TAKING THIS LINE OUT CAUSE A SEG FAULT???
  for (int i=0; i < data.size(); i++){
	  split_pos = data[i].find("scanner ");
    last_pos = split_pos +8; //advance past the string "scanner "
    split_pos = data[i].find(" ", last_pos); //find the space after the number
    int number = stoi(data[i].substr(last_pos,split_pos -last_pos)); //convert the string to an int
    scanner = Scanner(number);
    ++i;
    while ((!data[i].empty()) && (i < data.size())){ //add all the beacons this scanner sees
      size_t split_pos = 0;
      size_t last_pos = 0;
      split_pos = data[i].find(",", last_pos);
      int x = stoi(data[i].substr(last_pos,split_pos -last_pos));
      last_pos = split_pos +1;
      split_pos = data[i].find(",", last_pos);
      int y = stoi(data[i].substr(last_pos,split_pos -last_pos));
      last_pos = split_pos +1;
      int z = stoi(data[i].substr(last_pos));
      scanner.AddBeacon(x,y,z);
      ++i;
    }
    int n = scanner.FindNumberOfBeacons();
    scanner.SetNumberOfBeacons(n); //keep track of the original number of beacons seen by this scanner
    scanner.MakeDistanceArray(n);
    scanner.SetDistances();
    scanners.push_back(scanner);
    //lastLine = i;
	}
  return scanners;
}
  