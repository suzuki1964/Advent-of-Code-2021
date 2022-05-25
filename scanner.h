#pragma once

#include <vector>
#include <utility>

using std::vector;
using std::tuple;

class Beacon {
  public:
    Beacon();
    Beacon(int beacon_number);
    void SetBeaconNumber(int i);
    int GetBeaconNumber();
    void SetBeaconCoords(tuple<int,int,int> coords);
    tuple<int,int,int> GetBeaconCoords();
  private:
    int beacon_number_;
    tuple<int,int,int> beacon_coords_;
};

class Scanner {
  public:
    Scanner(int scanner_number);
    int GetNumber();
    void SetNumber(int scanner_number);
    void SetLocation(int x, int y, int z); //set the location of Scanner k relative to Scanner j
    void SetLocation(tuple<int,int,int> coords);
    void SetOrientation(tuple<pair<int, int>, pair<int,int>, pair<int,int>> coordsNDirection); //set the orientation of k relative to j
    tuple<int,int,int> GetLocation(); //get the location of Scanner k relative to Scanner j
    tuple<pair<int, int>, pair<int,int>, pair<int,int>> GetOrientation();
    void SetNumberOfBeacons(int number_of_beacons);
    int GetNumberOfBeacons();
    void SetMerged(bool merged);
    bool GetMerged();
    pair<int,int> Contains(int dist); //Scanner k contains beacon m at distance dist from beacon n
    void AddBeacon(tuple<int,int,int> coords);
    Beacon GetBeacon(int i);
    bool ContainsBeacon(int x, int y, int z);
    bool ContainsBeacon(tuple<int,int,int> checkCoords);
    void MakeDistanceArray(int n);
    int FindNumberOfBeacons();
    void SetDistances(); //make an array of the distances between beacon m and beacon n
    int GetDistance(int m, int n);
    void PrintDistances();
    void AddScannerToList(int k, tuple<int,int,int> coords);
    void UpdateScannerPosition(int k,tuple<int,int,int> coords);
    tuple<int,int,int> GetScannerPosition(int k);
    int GetScannerNumber(int i);
    int GetNumberOfScanners();
    int MaxDistance();

  private:
    int scanner_number_;
    tuple<int, int, int> location_;
    tuple<pair<int, int>, pair<int,int>, pair<int,int>> orientation_; //pair gives the axis (0 for x, 1, for y, 2 for z) and positive direction +/-1
    int number_of_beacons_;
    vector<Beacon> beacon_list_;
    vector<vector<int>> distances_; //distances between pairs of beacons
    bool merged_; // flag to indicate if this scanner has been merged in
    vector<pair<int, tuple<int,int,int>>> scanner_list_; //all scanners merged in, coords w.r.t. this scanner
};

