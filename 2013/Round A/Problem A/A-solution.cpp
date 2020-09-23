#include <bits/stdc++.h>
#include <string>

vector<string> numbers = {"zero", "one", "two",   "three", "four",
                          "five", "six", "seven", "eight", "nine"};

vector<string> consecutives = {"double",    "triple",   "quadruple",
                               "quintuple", "sextuple", "septuple",
                               "octuple",   "nonuple",  "decuple"};

string readnumber(string number, int start, int end) {
  string ans = "";
  string currentNumberRead = " " + numbers[number[start] - '0'];
  int occurences = 1;
  char currentNumber = number[start];
  for (int i = start + 1; i < end; ++i) {
    if (number[i] != currentNumber) {
      if (1 < occurences and occurences <= 10) {
        ans += " " + consecutives[occurences - 2] + " " +
               numbers[currentNumber - '0'];
      } else {
        ans += currentNumberRead;
      }
      currentNumberRead = " " + numbers[number[i] - '0'];
      currentNumber = number[i];
      occurences = 1;
    } else {
      occurences++;
      currentNumberRead += " " + numbers[number[i] - '0'];
    }
  }
  if (1 < occurences and occurences <= 10) {
    ans += " " + consecutives[occurences - 2] + " " +
           numbers[number[end - 1] - '0'];
  } else {
    ans += currentNumberRead;
  }
  return ans;
}

vector<int> split(string format) {
  vector<int> stops;
  string stop = "";
  for (int i = 0; i < format.size(); ++i) {
    if (format[i] == '-') {
      stops.push_back(stoi(stop));
      stop = "";
    } else {
      stop += format[i];
    }
  }
  stops.push_back(stoi(stop));
  return stops;
}

string solve() {
  string number, format;
  cin >> number >> format;
  vector<int> stops = split(format);
  string ans = "";
  int start = 0;
  for (int i = 0; i < stops.size(); ++i) {
    ans += readnumber(number, start, start + stops[i]);
    start += stops[i];
  }
  return ans;
}

int main() {
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    cout << "Case #" << i << ":" << solve() << endl;
  }
}
