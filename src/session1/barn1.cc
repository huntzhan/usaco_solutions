/*
ID: program41
LANG: C++11
TASK: barn1
*/
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <iterator>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::vector;
using std::sort;
using std::multiset;
using std::accumulate;
using std::distance;

const string kTask = "barn1";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int board_size, stall_size, cow_size;
  fin >> board_size >> stall_size >> cow_size;
  // get index of existing cows.
  vector<int> cow_indices;
  while (cow_size--) {
    int index;
    fin >> index;
    cow_indices.push_back(index);
  }
  sort(cow_indices.begin(), cow_indices.end());

  // groups adjacent cows.
  vector<int> groups;
  multiset<int> gaps;

  int last_index = cow_indices[0] - 1;
  int accumulator = 0;
  for (const int &index : cow_indices) {
    if (index == last_index + 1) {
      // still in a group.
      ++accumulator;
    } else {
      // here is another group.
      int current_gap = index - last_index - 1;
      gaps.insert(current_gap);
      groups.push_back(accumulator);
      accumulator = 1;
    }
    // anyway, set last_index to current index.
    last_index = index;
  }
  // keep last one.
  groups.push_back(accumulator);

  int min_length = accumulate(
      groups.cbegin(), groups.cend(), 0);
  const int exceeded_size = groups.size() - board_size;
  for (auto iter = gaps.cbegin(); iter != gaps.cend(); ++iter) {
    if (distance(gaps.cbegin(), iter) >= exceeded_size) {
      break;
    }
    min_length += *iter;
  }

  // output.
  fout << min_length << endl;
}
