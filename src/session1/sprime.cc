/*
ID: program41
LANG: C++11
TASK: sprime
*/
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::to_string;
using std::stoi;
using std::vector;
using std::sqrt;

const string kTask = "sprime";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

bool IsPrime(const int &number) {
  if (number == 1) {
    return false;
  }
  for (int divisor = 2; divisor <= sqrt(number); ++divisor) {
    if (number % divisor == 0) {
      return false;
    }
  }
  return true;
}

void GenerateSuperprime(const string &prime_prefix,
                        const int &current_index,
                        const int &size,
                        vector<string> *super_primes_ptr) {
  if (current_index == size) {
    // keep it.
    super_primes_ptr->push_back(prime_prefix);
    return;
  }

  for (int prime_digit = 1; prime_digit <= 9; ++prime_digit) {
    const string number = prime_prefix + to_string(prime_digit);
    if (IsPrime(stoi(number))) {
      // keep searching.
      GenerateSuperprime(
          number,
          current_index + 1,
          size,
          super_primes_ptr);
    }
  }
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int size = 0;
  fin >> size;

  vector<string> super_primes;
  GenerateSuperprime(
      "",
      0,
      size,
      &super_primes);

  // output.
  for (const string &number : super_primes) {
    fout << number << endl;
  }
}
