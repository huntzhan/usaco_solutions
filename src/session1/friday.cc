/*
ID: program41
LANG: C++11
TASK: friday
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

const string kTask = "friday";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

using Year = vector<int>;

bool IsLeapYear(const int &year_num) {
  if (year_num % 100 == 0) {
    return year_num % 400 == 0;
  } else {
    return year_num % 4 == 0;
  }
}

Year GenerateYear(const int &year_num) {
  // 0 -> January; ..; 11 -> December.
  Year year(12, 31);
  // change September, April, June, and November to 30.
  year[3] = 30;
  year[5] = 30;
  year[8] = 30;
  year[10] = 30;
  // change February to 29 or 28.
  year[1] = IsLeapYear(year_num) ? 29 : 28;

  return year;
}

int GetDayIndex(const int &counted_days) {
  const int kOffset = 13;
  // 1 -> Monday; ..; 6 -> Saturday; 0 -> Sunday.
  return (counted_days + kOffset) % 7; 
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int year_size = 0;
  fin >> year_size;

  // generate years.
  const int kStartYear = 1900;
  vector<Year> years;
  for (int year_num = kStartYear;
       year_num != kStartYear + year_size; ++year_num) {
    years.push_back(GenerateYear(year_num));
  }

  // count 13th of each month.
  vector<int> day_count(7, 0);
  int counted_days = 0;
  for (const auto &year : years) {
    for (const int &day_size : year) {
      // counting.
      int index = GetDayIndex(counted_days);
      ++day_count[index];
      // accumulation.
      counted_days += day_size;
    }
  }

  // output.
  int saturday_count = day_count[5];
  int sunday_count = day_count[6];
  for (size_t index = 6;
       index != 6 + day_count.size(); ++index) {
    const size_t actual_index = index % day_count.size();
    fout << day_count[actual_index];
    if (index != 6 + day_count.size() - 1) {
      fout << " ";
    }
  }
  fout << endl;
}
