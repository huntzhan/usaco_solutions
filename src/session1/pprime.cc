/*
ID: program41
LANG: C++11
TASK: pprime
*/
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::sqrt;
using std::stoi;
using std::lower_bound;
using std::upper_bound;

const string kTask = "pprime";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

#include <iostream>
using std::cout;

void SynthesisOneEnd(
    const string &prefix,
    const int &current_index,
    const int &size,
    vector<string> *left_ends_ptr) {
  if (current_index == size) {
    left_ends_ptr->push_back(prefix);
    return;
  }
  for (int digit = 0; digit <= 9; ++digit) {
    SynthesisOneEnd(
        prefix + to_string(digit),
        current_index + 1,
        size,
        left_ends_ptr);
  }
}

vector<int> SynthesisPalindromes(const int &size) {
  // make sure half_size not equals to 0.
  if (size == 1) {
    vector<int> palindromes;
    for (int digit = 1; digit <= 9; ++digit) {
      palindromes.push_back(digit);
    }
    return palindromes;
  }

  const int half_size = size / 2;
  // generate left side of palindromes.
  vector<string> left_ends;
  for (int digit = 1; digit <= 9; ++digit) {
    SynthesisOneEnd(
        to_string(digit),
        1,
        half_size,
        &left_ends);
  }

  // generate the final palindromes.
  vector<int> palindromes;
  for (const string &left_side : left_ends) {
    const string right_side(left_side.rbegin(),
                            left_side.rend());
    if (size % 2 == 0) {
      // is even.
      palindromes.push_back(
          stoi(left_side + right_side));
    } else {
      // is odd.
      for (int digit = 0; digit <= 9; ++digit) {
        const string number_text =
            left_side + to_string(digit) + right_side;
        palindromes.push_back(stoi(number_text));
      }
    }
  }
  return palindromes;
}

vector<int> GeneratePalindromesWithinRange(
    const int &range_a,
    const int &range_b) {
  vector<int> palindromes;

  const int size_a = to_string(range_a).size();
  const int size_b = to_string(range_b).size();
  for (int size = size_a; size <= size_b; ++size) {
    vector<int> palindromes_in_size = SynthesisPalindromes(size);
    palindromes.insert(
        palindromes.end(),
        palindromes_in_size.begin(), palindromes_in_size.end());
  }
  // filter out numbers not in range.
  auto first_iter = lower_bound(
      palindromes.cbegin(), palindromes.cend(),
      range_a);
  auto second_iter = upper_bound(
      palindromes.cbegin(), palindromes.cend(),
      range_b);

  return vector<int>(first_iter, second_iter);
}

bool IsPrime(const int &number) {
  for (int divisor = 2; divisor <= sqrt(number); ++divisor) {
    if (number % divisor == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int range_a = 0, range_b = 0;
  fin >> range_a >> range_b;

  const auto palindromes = GeneratePalindromesWithinRange(
      range_a, range_b);
  for (const int &number : palindromes) {
    if (IsPrime(number)) {
      fout << number << endl;
    }
  }
}
