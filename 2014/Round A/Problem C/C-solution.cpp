#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void extract(string eq, string &x, string &y, string &z, bool zAvailable) {
  int xFinal;
  for (int j = 0; j < eq.length(); ++j) {
    if (eq[j] == '+') {
      xFinal = j + 1;
      x = eq.substr(0, j);
      if (!zAvailable) {
        y = eq.substr(j + 1, eq.length() - j);
        break;
      }
    } else if (eq[j] == '=') {
      y = eq.substr(xFinal, j - xFinal);
      z = eq.substr(j + 1, eq.length() - j);
      break;
    }
  }
}

void extract(string eq, string &x, string &y, string &z) {
  extract(eq, x, y, z, true);
}

void extract(string eq, string &x, string &y) {
  string z;
  extract(eq, x, y, z, false);
}

void solve() {
  int N;
  cin >> N;
  map<string, int> variableMap;
  set<pair<pair<int, int>, long>> equationsOr;
  vector<vector<long>> matrix(N * 2, vector<long>(N * 2));

  for (int i = 0; i < N * 2; i++) {
    fill(matrix[i].begin(), matrix[i].end(), LONG_MIN);
  }

  int currIndex = 0;
  for (int i = 0; i < N; ++i) {
    string eq;
    cin >> eq;
    string x, y, zString;
    extract(eq, x, y, zString);

    int z = stoi(zString);
    if (variableMap.find(x) == variableMap.end()) {
      variableMap[x] = currIndex++;
    }

    if (variableMap.find(y) == variableMap.end()) {
      variableMap[y] = currIndex++;
    }
    int xIndex = variableMap[x];
    int yIndex = variableMap[y];
    matrix[xIndex][yIndex] = z;
    matrix[yIndex][xIndex] = z;
    equationsOr.insert(make_pair(make_pair(xIndex, yIndex), z));
    equationsOr.insert(make_pair(make_pair(yIndex, xIndex), z));
  }

  vector<pair<pair<pair<int, int>, long>, pair<pair<int, int>, long>>>
      combinations;
  auto i = equationsOr.begin();
  while (i != equationsOr.end()) {
    auto j = i;
    while (j != equationsOr.end()) {
      auto i1 = make_pair(i->first, i->second);
      auto j1 = make_pair(j->first, j->second);
      combinations.push_back(make_pair(i1, j1));
      j = next(j);
    }
    i = next(i);
  }
  int inserted = -1;
  while (inserted != 0) {
    inserted = 0;
    for (auto it : combinations) {
      int x1, y1, x2, y2;
      int z1, z2, z;
      x1 = it.first.first.first;
      y1 = it.first.first.second;
      z1 = it.first.second;
      x2 = it.second.first.first;
      y2 = it.second.first.second;
      z2 = it.second.second;

      if (matrix[x1][x2] != LONG_MIN and matrix[y1][y2] == LONG_MIN) {
        z = z1 + z2 - matrix[x1][x2];
        matrix[y1][y2] = z;
        matrix[y2][y1] = z;
        inserted++;
      }

      if (matrix[x1][y2] != LONG_MIN and matrix[y1][x2] == LONG_MIN) {
        z = z1 + z2 - matrix[x1][y2];
        matrix[x2][y1] = z;
        matrix[y1][x2] = z;
        inserted++;
      }

      if (matrix[y1][x2] != LONG_MIN and matrix[x1][y2] == LONG_MIN) {
        z = z1 + z2 - matrix[y1][x2];
        matrix[y2][x1] = z;
        matrix[x1][y2] = z;
        inserted++;
      }

      if (matrix[y1][y2] != LONG_MIN and matrix[x1][x2] == LONG_MIN) {
        z = z1 + z2 - matrix[y1][y2];
        matrix[x1][x2] = z;
        matrix[x2][x1] = z;
        inserted++;
      }
    }
  }
  int Q;
  cin >> Q;
  for (int i = 0; i < Q; ++i) {
    string eq, x, y;
    int xIndex, yIndex;
    cin >> eq;
    extract(eq, x, y);
    if (variableMap.find(x) == variableMap.end() or
        variableMap.find(y) == variableMap.end()) {
      continue;
    }
    xIndex = variableMap[x];
    yIndex = variableMap[y];
    if (matrix[xIndex][yIndex] != LONG_MIN) {
      cout << x << "+" << y << "=" << matrix[xIndex][yIndex] << endl;
    } else if (matrix[xIndex][xIndex] != LONG_MIN and
               matrix[yIndex][yIndex] != LONG_MIN) {
      long z = matrix[xIndex][xIndex] + matrix[yIndex][yIndex];
      z /= 2;
      cout << x << "+" << y << "=" << z << endl;
    }
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
