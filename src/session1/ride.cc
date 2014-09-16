/*
ID: program37
LANG: C++11
TASK: ride
*/
#include <ostream>
#include <fstream>
#include <string>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;

const string kTask = "ride";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

int scheme(const string &number){
  int converted_num = 1;
  for (const char &c : number) {
    converted_num *= c - 'A' + 1;
  }
  return converted_num % 47;
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  string comet, group;
  fin >> comet;
  fin >> group;

  if (scheme(comet) == scheme(group)) {
    fout << "GO" << endl;
  } else {
    fout << "STAY" << endl;
  }
}
