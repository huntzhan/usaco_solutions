/*
ID: program41
LANG: C++11
TASK: gift1
*/
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <list>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::map;
using std::list;

const string kTask = "gift1";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

void UpdateMapping(map<string, int> *mapping_ptr,
                   ifstream &fin) {
  // get provider's name.
  string giver;
  fin >> giver;

  // get money and size of receivers.
  int money, size_of_receiver;
  fin >> money >> size_of_receiver;
  if (size_of_receiver == 0) {
    // meaningless input.
    return;
  }

  // update giver's money.
  int avg_given_money = money / size_of_receiver;
  int saved_money = money % size_of_receiver;
  (*mapping_ptr)[giver] -= (money - saved_money);

  // update receivers' money.
  for (int counter = 0; counter != size_of_receiver; ++counter) {
    string receiver;
    fin >> receiver;
    (*mapping_ptr)[receiver] += avg_given_money;
  }
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int np = 0;
  fin >> np;

  // init mapping.
  map<string, int> name_money_mapping;
  list<string> names_order;
  for (int counter = 0; counter != np; ++counter) {
    string name;
    fin >> name;
    name_money_mapping[name] = 0;
    names_order.push_back(name);
  }

  while (fin) {
    UpdateMapping(&name_money_mapping, fin);
  }

  for (const string &name : names_order) {
    fout << name << " "
         << name_money_mapping[name] << endl;
  }
}
