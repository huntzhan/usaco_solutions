/*
ID: program41
LANG: C++11
TASK: milk
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

const string kTask = "milk";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int required_amount = 0, number_of_farmers = 0;
  fin >> required_amount >> number_of_farmers;

  multimap<int, int> price_amount_mapping;
  while (number_of_farmers--) {
    int price = 0, amount = 0;
    fin >> price >> amount;
    price_amount_mapping.insert({price, amount});
  }
  
  int min_cost = 0;
  for (const auto &price_amount_pair : price_amount_mapping) {
    if (required_amount == 0) {
      break;
    }

    const int &price = price_amount_pair.first;
    int amount = price_amount_pair.second;
    if (amount > required_amount) {
      amount = required_amount;
    }
    min_cost += price * amount;
    required_amount -= amount;
  }

  // output.
  fout << min_cost << endl;
}
