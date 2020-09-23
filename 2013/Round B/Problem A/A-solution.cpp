#include <bits/stdc++.h>
#include <cstring>
#include <unordered_set>

bool solve() {
  int n;
  cin >> n;
  int max = n * n;
  vector<vector<int>> matrix(max, vector<int>(max));
  unordered_set<int> s(max);
  bool isValid = true;
  for (int i = 0; i < max; ++i) {
    long long sum = 0;
    for (int j = 0; j < max; ++j) {
      int x;
      cin >> x;
      if (x < 1 or x > max) {
        isValid = false;
      }
      sum += x;
      if (isValid){
          s.insert(x);
      }
      matrix[i][j] = sum;
    }
    if (sum != max * (max + 1) / 2 or s.size()!=max) {
      isValid = false;
    }
  }
  for (int i = 0; i < max; ++i) {
    for (int j = 1; j < max; ++j) {
      matrix[j][i] += matrix[j - 1][i];
    }
    if (matrix[max - 1][i] != (i + 1) * max * (max + 1) / 2) {
      isValid = false;
    }
  }
  int countX = 0;
  int countY = 0;

  for (int i = n - 1; i < max; i += n) {
    countX++;
    countY = 1;
    for (int j = n - 1; j < max; j += n) {
      if (matrix[i][j] != (countX * countY) * max * (max + 1) / 2) {
        isValid = false;
      }
      countY++;
    }
  }
  return isValid;
}

int main() {
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    cout << "Case #" << i << ": " << (solve() ? "Yes" : "No") << endl;
  }
}
