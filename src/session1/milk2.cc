/*
ID: program41
LANG: C++11
TASK: milk2
*/
#include <ostream>
#include <fstream>
#include <string>
#include <map>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::multimap;

const string kTask = "milk2";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  // build sorted pairs.
  multimap<int, int> start_end_pairs;
  int size = 0;
  fin >> size;
  while (size--) {
    int start = 0, end = 0;
    fin >> start >> end;
    start_end_pairs.insert({start, end});
  }

  // init.
  auto &first_time_pair = *start_end_pairs.cbegin();
  int current_start = first_time_pair.first;
  int current_end = first_time_pair.second;
  // analyse.
  int longest_continue_time = current_end - current_start;
  int longest_idle_time = 0;
  for (const auto &time_pair : start_end_pairs) {
    const int &start_time = time_pair.first;
    const int &end_time = time_pair.second;

    // check if start_time within [current_start, current_end].
    if (start_time <= current_end) {
      // within the range, update current_end.
      if (end_time > current_end) {
        current_end = end_time;
      }
    } else {
      // here's a idle gap, update everything.
      // longest_continue_time.
      int current_continue_time = current_end - current_start;
      if (current_continue_time > longest_continue_time) {
        longest_continue_time = current_continue_time;
      }
      // longest_idle_time.
      int current_idle_time = start_time - current_end;
      if (current_idle_time > longest_idle_time) {
        longest_idle_time = current_idle_time;
      }
      // change to next state.
      current_start = start_time;
      current_end = end_time;
    }
  }

  // output.
  fout << longest_continue_time << " " << longest_idle_time << endl;
}
