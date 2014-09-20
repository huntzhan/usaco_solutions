/*
ID: program41
LANG: C++11
TASK: numtri
*/
#include <ostream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::vector;

const string kTask = "numtri";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

using Layer = vector<int>;
using Tree = vector<Layer>;

// DP, Update layer i based on layer (i + 1).
void UpdateLayer(const Layer &pre_layer,
                 Layer *current_layer_ptr) {
  for (int index = 0;
       index != current_layer_ptr->size(); ++index) {
    const int &max_of_children =
        pre_layer[index] > pre_layer[index + 1] ?
        pre_layer[index] : pre_layer[index + 1];
    (*current_layer_ptr)[index] += max_of_children;
  }
}

int MaxSumOfPath(Tree *tree_ptr) {
  for (auto pre_layer_iter = tree_ptr->rbegin();
       pre_layer_iter != tree_ptr->rend() - 1; ++pre_layer_iter) {
    Layer &pre_layer = *pre_layer_iter;
    Layer &current_layer = *(pre_layer_iter + 1);
    // Update internal layers.
    UpdateLayer(pre_layer, &current_layer);
  }
  const Layer &root_layer = tree_ptr->front();
  return root_layer.front();
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  // build tree.
  int number_of_layers = 0;
  fin >> number_of_layers;

  Tree tree;
  for (int current_layer_size = 1;
       current_layer_size <= number_of_layers; ++current_layer_size) {
    Layer layer;
    for (int counter = 0; counter != current_layer_size; ++counter) {
      int element = 0;
      fin >> element;
      layer.push_back(element);
    }
    tree.push_back(layer);
  }

  // output.
  fout << MaxSumOfPath(&tree) << endl;
}
