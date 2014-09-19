/*
ID: program41
LANG: C++11
TASK: crypt1
*/
#include <ostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::set;
using std::to_string;
using std::vector;
using std::stoi;

const string kTask = "crypt1";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

bool IsValidNumber(const int &number,
                   const int &size,
                   const set<char> &valid_digits) {
  // check size.
  const string &number_text = to_string(number);
  if (number_text.size() != size) {
    return false;
  }
  // check every digit.
  for (const char &digit : number_text) {
    if (valid_digits.find(digit) == valid_digits.cend()) {
      return false;
    }
  }
  return true;
}
                   
bool CheckPrimeCryptarithm(const int &multiplier,
                           const int &multiplicant,
                           const set<char> &valid_digits) {
  const int single_digit = multiplicant % 10;
  const int ten_digit = multiplicant / 10;
  const int first_result = single_digit * multiplier;
  const int second_result = ten_digit * multiplier;

  if (IsValidNumber(first_result, 3, valid_digits)
      && IsValidNumber(second_result, 3, valid_digits)) {
    // immediate data is ok, check the final data.
    const int final_result = first_result + 10 * second_result;
    if (IsValidNumber(final_result, 4, valid_digits)) {
      return true;
    }
  }
  return false;
}

void RecursizeGenerateValidNumbers(
    vector<string> *valid_numbers_ptr,
    const string &prefix,
    const int &index,
    const int &size,
    const set<char> &valid_digits) {
  if (index == size) {
    // end recursion.
    valid_numbers_ptr->push_back(prefix);
    return;
  }
  // generate next digit.
  for (const char &digit : valid_digits) {
    RecursizeGenerateValidNumbers(
        valid_numbers_ptr,
        prefix + digit,
        index + 1,
        size,
        valid_digits);
  }
}

vector<string> GenerateValidNumbers(
    const int &size,
    const set<char> &valid_digits) {
  vector<string> valid_numbers;
  for (const char &digit : valid_digits) {
    if (digit == '0') {
      continue;
    }
    RecursizeGenerateValidNumbers(
        &valid_numbers,
        string("") + digit,
        1,
        size,
        valid_digits);
  }
  return valid_numbers;
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int number_of_digits = 0;
  fin >> number_of_digits;
  set<char> valid_digits;
  while (number_of_digits--) {
    char digit;
    fin >> digit;
    valid_digits.insert(digit);
  }

  const auto multipliers = GenerateValidNumbers(
      3, valid_digits);
  const auto multiplicants = GenerateValidNumbers(
      2, valid_digits);

  int counter = 0;
  for (const string &multiplier : multipliers) {
    for (const string &multiplicant : multiplicants) {
      bool flag = CheckPrimeCryptarithm(
          stoi(multiplier), stoi(multiplicant),
          valid_digits);
      if (flag) {
        ++counter;
      }
    }
  }
  // output.
  fout << counter << endl;
}
