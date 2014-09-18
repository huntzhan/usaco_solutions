/*
ID: program41
LANG: C++11
TASK: dualpal
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

const string kTask = "dualpal";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

string NumberToString(
    const int &base,
    const int &number) {
  string number_text;
  int immediate_number = number;
  while (immediate_number > 0) {
    int remainder = immediate_number % base;
    immediate_number /= base;
    // generate string.
    number_text.push_back('0' + remainder);
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

  int size = 0, number = 0;
  fin >> size >> number;

  while (true) {
    ++number;

    int palindrome_count = 0;
    for (int base = 2; base <= 10; ++base) {
      const string number_text = NumberToString(base, number);
      if (IsPalindrome(number_text)) {
        ++palindrome_count;
      }
    }

    if (palindrome_count >= 2) {
      fout << number << endl; 
      // check exit.
      --size;
      if (size == 0) { break; }
    }
  }

}
