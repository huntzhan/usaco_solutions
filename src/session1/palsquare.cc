/*
ID: program41
LANG: C++11
TASK: palsquare
*/
#include <ostream>
#include <fstream>
#include <string>
#include <map>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::map;
using std::to_string;

const string kTask = "palsquare";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

string NumberToString(
    const int &base,
    const map<int, char> &number_char_mapping,
    const int &number) {
  string number_text;
  int immediate_number = number;
  while (immediate_number > 0) {
    int remainder = immediate_number % base;
    immediate_number /= base;
    // generate string.
    number_text.push_back(number_char_mapping.at(remainder));
  }
  return string(number_text.rbegin(), number_text.rend());
}

bool IsPalindrome(const string &number) {
  const string reversed_number(
      number.crbegin(), number.crend());
  return number == reversed_number;
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int base = 0;
  fin >> base;

  map<int, char> number_char_mapping;
  for (int number = 0; number <= 20; ++number) {
    if (number < 10) {
      number_char_mapping.insert({number, '0' + number});
    } else {
      number_char_mapping.insert(
          {number, 'A' + number - 10});
    }
  }

  for (int number = 1; number <= 300; ++number) {
    const int square_of_number = number * number;

    const string &number_text = NumberToString(
        base, number_char_mapping, number);
    const string &square_number_text = NumberToString(
        base, number_char_mapping, square_of_number);

    if (IsPalindrome(square_number_text)) {
      fout << number_text << " "
           << square_number_text << endl;
    }
  }

}
