#pragma once

#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Board {
  public:
    Board(int board_width);
    void SetTile(int x, int y, int value);
    void SetVisited (pair<int, int>);
    int GetTile(int x, int y);
    pair<int, int> Contains (int value);
    bool HasWon (pair<int, int>);
    int Points ();
  private:
    int board_width_;
    vector<vector<pair<int, bool>>> bingo_board_;
};