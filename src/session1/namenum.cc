/*
ID: program41
LANG: C++11
TASK: namenum
*/
#include <ostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::set;
using std::vector;
using std::map;
using std::sort;
using std::distance;

const string kTask = "namenum";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

using Seeds = map<char, vector<char>>;

set<string> GetValidNames() {
  ifstream fin("dict.txt");
  set<string> valid_names;
  while (fin) {
    string name;
    fin >> name;
    valid_names.insert(name);
  }
  return valid_names;
}

void RecursiveGenerateNames(
    const set<string> valid_names,
    const Seeds &seeds,
    const string &digits,
    const string &prefix,
    const int &current_index,
    vector<string> *names_ptr) {

  const char &current_digit = digits[current_index];
  const auto &next_chars = seeds.at(current_digit);
  for (const auto &next_char : next_chars) {
    string next_prefix = prefix + next_char;
    const int next_index = current_index + 1;

    // reduce search space by checking valid_names.
    string first_name = next_prefix;
    string second_name = next_prefix;
    for (int counter = next_index; counter != digits.size(); ++counter) {
      first_name += 'A';
      second_name += 'Z';
    }

    auto first_iter = valid_names.lower_bound(first_name);
    auto second_iter = valid_names.lower_bound(second_name);

    if (distance(first_iter, second_iter) > 0) {
      // if there's candidate names, keep searching.
      RecursiveGenerateNames(
          valid_names,
          seeds, digits,
          next_prefix, next_index,
          names_ptr);
    } else if (next_index == digits.size()) {
      // end recursion.
      auto iter = valid_names.find(next_prefix);
      if (iter != valid_names.cend()) {
        names_ptr->push_back(next_prefix);
      }
    }
  }
}

vector<string> GenerateNames(
    const set<string> valid_names,
    const Seeds &seeds,
    const string &digits) {
  vector<string> generated_names;
  RecursiveGenerateNames(
      valid_names, seeds, digits,
      "", 0, &generated_names);
  return generated_names;
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  string digits;
  fin >> digits;
  const auto valid_names = GetValidNames();

  // build seeds for generating names.
  Seeds seeds;
  seeds.insert({'2', {'A', 'B', 'C'}});
  seeds.insert({'3', {'D', 'E', 'F'}});
  seeds.insert({'4', {'G', 'H', 'I'}});
  seeds.insert({'5', {'J', 'K', 'L'}});
  seeds.insert({'6', {'M', 'N', 'O'}});
  seeds.insert({'7', {'P', 'R', 'S'}});
  seeds.insert({'8', {'T', 'U', 'V'}});
  seeds.insert({'9', {'W', 'X', 'Y'}});

  auto generated_names= GenerateNames(
      valid_names, seeds, digits);

  // output.
  sort(generated_names.begin(), generated_names.end());
  if (generated_names.empty()) {
    fout << "NONE" << endl;
  } else {
    for (const string &name : generated_names) {
      fout << name << endl;
    }
  }
}
