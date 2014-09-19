/*
ID: program41
LANG: C++11
TASK: ariprog
*/
#include <ostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::set;
using std::multimap;
using std::unordered_set;
using std::vector;

const string kTask = "ariprog";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

set<int> BuildBisquaresSet(const int &upper_bound_of_bisquares) {
  set<int> bisquare_set;
  for (int p = 0; p <= upper_bound_of_bisquares; ++p) {
    for (int q = 0; q <= upper_bound_of_bisquares; ++q) {
      bisquare_set.insert(p * p + q * q);
    }
  }
  return bisquare_set;
}

bool ExistArithmeticProgression(
    const int &first_element,
    const int &difference,
    const int &progressions_length,
    const unordered_set<int> &bisquare_set) {
  for (int multiplicand = 0;
       multiplicand < progressions_length; ++multiplicand) {
    const int number = first_element + multiplicand * difference;
    if (bisquare_set.find(number) == bisquare_set.cend()) {
      return false;
    }
  }
  return true;
}

// debug.
#include <iostream>
using std::cout;

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int progressions_length = 0, upper_bound_of_bisquares = 0;
  fin >> progressions_length >> upper_bound_of_bisquares;

  const auto bisquare_set = BuildBisquaresSet(
      upper_bound_of_bisquares);

  // output cache.
  multimap<int, int> difference_first_element_mapping;

  // space-time trade off.
  unordered_set<int> unordered_bisquare_set(
      bisquare_set.cbegin(), bisquare_set.cend());
  vector<int> linear_bisquare_set(
      bisquare_set.cbegin(), bisquare_set.cend());

  const int max_element = linear_bisquare_set.back();

  for (auto second_iter = linear_bisquare_set.cbegin() + 1;
       second_iter != linear_bisquare_set.cend(); ++second_iter) {
    // calculate max difference between first_iter and second_iter.
    const int max_difference =
        (max_element - *second_iter) / (progressions_length - 2);
    // get first_iter based on max_difference.
    auto first_iter = second_iter - 1;
    while (first_iter > linear_bisquare_set.cbegin()) {
      if (*first_iter <= *second_iter - max_difference) {
        break;
      }
      --first_iter;
    }

    // check arithmatic progression.
    for (; first_iter != second_iter; ++first_iter) {
      const int first_element = *first_iter;
      const int difference = *second_iter - *first_iter;
      bool exist = ExistArithmeticProgression(
          first_element, difference,
          progressions_length,
          unordered_bisquare_set);
      if (exist) {
        difference_first_element_mapping.insert(
            {difference, first_element});
      }
    }
  }

  // output.
  for (const auto &data_pair : difference_first_element_mapping) {
    fout << data_pair.second << " "
         << data_pair.first << endl;
  }
  if (difference_first_element_mapping.empty()) {
    fout << "NONE" << endl;
  }
}
