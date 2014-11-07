/*
ID: program41
LANG: C++11
TASK: combo
*/
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cstddef>
#include <algorithm>
#include <iterator>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::size_t;
using std::set_intersection;
using std::back_inserter;

const string kTask = "combo";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

const int kNumOfDial = 3;
const int kDiff = 2;

// number: signed integer.
// upper_bound: N.
// return number from 1 to N.
int SignedModulo(int number, const int &upper_bound) {
  while (number < 0) {
    number += upper_bound;
  }
  return ((number - 1 + upper_bound) % upper_bound) + 1;
}

set<int> BuildRangeSet(const int &midpoint,
                       const int &upper_bound) {
  set<int> number_in_range;
  for (int number = midpoint - kDiff;
       number <= midpoint + kDiff; ++number) {
    number_in_range.insert(SignedModulo(number, upper_bound));
  }
  return number_in_range;
}

int CalculateIntersectCombination(const vector<int> &john_combination,
                                  const vector<int> &master_combination,
                                  const int &upper_bound) {
  int size = 1;
  for (size_t index = 0; index != kNumOfDial; ++index) {
    auto john_range_set = BuildRangeSet(
        john_combination[index], upper_bound);
    auto master_range_set = BuildRangeSet(
        master_combination[index], upper_bound);
    vector<int> intersection;
    set_intersection(john_range_set.begin(), john_range_set.end(),
                     master_range_set.begin(), master_range_set.end(),
                     back_inserter(intersection));
    size *= intersection.size();
  }
  return size;
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  // load data.
  int upper_bound = 0;
  vector<int> john_combination(kNumOfDial);
  vector<int> master_combination(kNumOfDial);
  fin >> upper_bound;
  for (int &number : john_combination) {
    fin >> number;
  }
  for (int &number : master_combination) {
    fin >> number;
  }

  int range = 2 * kDiff + 1;
  range = upper_bound > range ? range : upper_bound;
  int total_combination = 1;
  for (size_t index = 0; index != kNumOfDial; ++index) {
    total_combination *= range;
  }
  total_combination *= 2;
  int intersect_combination = CalculateIntersectCombination(
      john_combination,
      master_combination,
      upper_bound);
  fout << total_combination - intersect_combination << endl;
}
