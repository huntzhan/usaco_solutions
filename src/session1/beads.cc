/*
ID: program41
LANG: C++11
TASK: beads
*/
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstddef>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::vector;
using std::size_t;

const string kTask = "beads";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

bool IsWhite(const char &color) {
  return color == 'w';
}

bool IsInSameGroup(const char &base_color,
                   const char &target_color) {
  if (IsWhite(target_color)) {
    return true;
  } else {
    return base_color == target_color;
  }
}

int GetFirstDiffIndex(const string &necklace) {
  int cache_index = 0;
  for (int index = 0; index != necklace.size() - 1; ++index) {
    // 1. split different colors;
    // 2. white beads don't appears to the left of split point.
    // 3. white beads don't appears to the right of split point.
    const char &current_color = necklace[index];
    const char &next_color = necklace[index + 1];
    if (current_color != next_color) {
      if (!IsWhite(current_color) && !IsWhite(next_color)) {
        return index + 1;
      } else {
        cache_index = index + 1;
      }
    }
  }
  // check edge condition.
  if (necklace.front() != necklace.back()
      && !IsWhite(necklace.front())
      && !IsWhite(necklace.back())) {
    return 0;
  } else {
    return cache_index;
  }
}

char GetColor(const int &started_index,
              const vector<char> &colors) {
  int index = started_index;
  while (IsWhite(colors[index])) {
    ++index;
  }
  return colors[index];
}

int RightExpend(const int &started_index,
                const vector<char> &colors) {
  if (started_index >= colors.size()) {
    return colors.size();
  }

  int end_index = started_index + 1;
  const char color = GetColor(started_index, colors);
  while (IsInSameGroup(color, colors[end_index])) {
    ++end_index;
    if (end_index == colors.size()) {
      break;
    }
  }
  return end_index;
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int beads_size = 0;
  string beads;
  fin >> beads_size;
  fin >> beads;

  // generate count and white flag.
  vector<int> color_counts;
  vector<char> colors;

  const int offset = GetFirstDiffIndex(beads);
  int counter = 0;
  char current_color = beads[offset]; 

  for (size_t index = 0; index != beads.size(); ++index) {
    const size_t actual_index = (index + offset) % beads.size();
    if (beads[actual_index] == current_color) {
      ++counter;
    } else {
      // save data.
      color_counts.push_back(counter);
      colors.push_back(current_color);
      // update state.
      counter = 1;
      current_color = beads[actual_index];
    }
  }
  // save last items.
  color_counts.push_back(counter);
  colors.push_back(current_color);

  vector<int> final_color_counts = color_counts;
  vector<char> final_colors = colors;
  final_color_counts.insert(
      final_color_counts.end(),
      color_counts.begin(), color_counts.end());
  final_colors.insert(
      final_colors.end(),
      colors.begin(), colors.end());

  // count max.
  int max_count = 0;
  for (size_t index = 0; index != final_color_counts.size(); ++index) {
    // expend to the right.
    const int first_end = RightExpend(index, final_colors);
    const int second_end = RightExpend(first_end, final_colors);

    if (second_end - index >= colors.size()) {
      max_count = beads.size();
      break;
    }

    int current_count = 0;
    for (int count_index = index;
         count_index != second_end; ++count_index) {
      current_count += final_color_counts[count_index];
    }
    if (current_count > max_count) {
      max_count = current_count;
    }
  }

  // output.
  fout << max_count << endl;
}
