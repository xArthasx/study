#include <bits/stdc++.h>
#include <bitset>
#include <vector>
vector<int> numbers = {
    0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011,
    0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011,
};
string solve() {
  int N;
  cin >> N;
  vector<vector<int>> plausibles(N);
  vector<int> inputs(N);
  int y = 0;
  int mask = 0;
  for (int i = 0; i < N; ++i) {
    string input;
    cin >> input;
    for (int j = 0; j < 7; ++j) {
      y += input[j] - '0';
      if (j + 1 != 7)
        y <<= 1;
    }
    bitset<7> x(y);
    inputs[i] = y;
    mask |= y;
    y = 0;
  }
  int noMask = ~mask;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < 10; ++j) {
      int input = inputs[i];
      int number = numbers[j];
      if ((input & number) == input) {
        int bad = (input ^ number);
        if (((input ^ number) & noMask) == bad) {
          plausibles[i].push_back(j);
        }
      }
    }
  }
  int sol = -1;
  for (int j = 0; j < plausibles[0].size(); ++j) {
    int plausible = plausibles[0][j];
    int knownBad = inputs[0] ^ numbers[plausible];
    bool found = false;
    int lastFound = -1;
    if (N == 1 && plausibles[0].size() == 1) {
      lastFound = plausibles[0][0];
      if (lastFound == 0) {
        lastFound = 10;
      }
      found = true;
    }
    for (int i = 1; i < N; ++i) {
      if (plausible == 0) {
        plausible = 10;
      }
      found = false;
      for (int k = 0; k < plausibles[i].size(); ++k) {
        if (plausibles[i][k] == plausible - 1) {
          lastFound = plausible - 1;
          found = true;
          plausible--;
          knownBad |= inputs[i] ^ numbers[lastFound];
          break;
        }
      }
      if (!found) {
        break;
      }
    }
    if (found) {
      if (lastFound == 0) {
        lastFound = 10;
      }
      int num = numbers[lastFound - 1];
      int xorBad = num ^ knownBad;
      int xorGood = num ^ mask;
      int unknown = knownBad ^ noMask;
      int unnum = unknown & num;
      if (unnum == 0) {
        int csol = numbers[lastFound - 1] & mask;
        if (sol != -1 && sol != csol) {
          sol = -1;
          break;
        }
        sol = csol;
      } else {
        // Solution uses unknown bits then it should return error
        sol = -1;
        break;
      }
    }
  }
  if (sol != -1) {
    return bitset<7>(sol).to_string();
  }
  return "ERROR!";
}

int main() {
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    string s = solve();
    cout << "Case #" << i << ": " << s << endl;
  }
}
