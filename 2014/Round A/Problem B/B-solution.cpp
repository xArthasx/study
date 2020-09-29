#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

void sum_row(vector<int> &row, bool dir) {
  int i = 0;
  if (dir) {
    while (i + 1 < row.size()) {
      if (row[i] == row[i + 1]) {
        row[i] += row[i + 1];
        row.erase(row.begin() + i + 1);
      }
      i++;
    }
  } else {
    i = row.size() - 1;
    while (i - 1 >= 0) {
      if (row[i] == row[i - 1]) {
        row[i] += row[i - 1];
        row.erase(row.begin() + i - 1);
        i--;
      }
      i--;
    }
  }
}

void solve() {
  int N;
  cin >> N;
  string dir;
  cin >> dir;
  bool readDir = dir == "right" or dir == "left";
  bool sum_dir = dir == "left" or dir == "up";
  vector<vector<int>> board(N, vector<int>(0));

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int cell;
      cin >> cell;
      if (cell == 0)
        continue;
      if (readDir) {
        board[i].push_back(cell);
      } else {
        board[j].push_back(cell);
      }
    }
  }

  for (int i = 0; i < N; ++i) {
    sum_row(board[i], sum_dir);
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (readDir) {
        int size = board[i].size();
        if (sum_dir) {
          if (j < size) {
            cout << board[i][j];
          } else {
            cout << 0;
          }
        } else {
          if (j >= N - size) {
            cout << board[i][j - N + size];
          } else {
            cout << 0;
          }
        }
      } else {
        int size = board[j].size();
        if (sum_dir) {
          if (i < size) {
            cout << board[j][i];
          } else {
            cout << 0;
          }
        } else {
          if (i >= N - size) {
            cout << board[j][i - N + size];
          } else {
            cout << 0;
          }
        }
      }
      if (j + 1 < N) {
        cout << " ";
      }
    }
    cout << endl;
  }
}

int main() {

  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    cout << "Case #" << i << ":" << endl;
    solve();
  }
}
