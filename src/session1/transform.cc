/*
ID: program41
LANG: C++11
TASK: transform
*/
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::ostringstream;

const string kTask = "transform";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

string ReadSquare(ifstream &fin, const int &dimension) {
  ostringstream strm;
  for (int counter = 0; counter != dimension; ++counter) {
    string buffer;
    fin >> buffer;
    strm << buffer;
  }
  return strm.str();
}

inline int GenIndex(
    const int &dimension,
    const int &x, const int &y) {
  return x * dimension + y;
}

string Rotate90Degree(const string &square,
                      const int &dimension) {
  string processed_square(dimension * dimension, '\0');
  for (int i = 0; i != dimension; ++i) {
    for (int j = 0; j != dimension; ++j) {
      // transform.
      processed_square[GenIndex(dimension, j, dimension - i - 1)] =
          square[GenIndex(dimension, i, j)];
    }
  }
  return processed_square;
}

string ReflectedHorizontally(const string &square,
                             const int &dimension) {
  string processed_square(dimension * dimension, '\0');
  for (int i = 0; i != dimension; ++i) {
    for (int j = 0; j != dimension; ++j) {
      // transform.
      processed_square[GenIndex(dimension, i, dimension - j - 1)] =
          square[GenIndex(dimension, i, j)];
    }
  }
  return processed_square;
}

int GetTransformationID(
    const string &init_square,
    const string &final_square,
    const int &dimension) {

  string processed_square = init_square;
  // #1 - #3: 90 - 270 Degree Rotation.
  for (int id = 1; id <= 3; ++id) {
    processed_square = Rotate90Degree(processed_square, dimension);
    if (processed_square == final_square) {
      return id;
    }
  }

  string reflected_suqare = ReflectedHorizontally(init_square, dimension);
  if (reflected_suqare == final_square) {
    // #4: Reflection.
    return 4;
  }
  for (int counter = 0; counter != 3; ++counter) {
    reflected_suqare = Rotate90Degree(reflected_suqare, dimension);
    if (reflected_suqare == final_square) {
      // #5: Combination.
      return 5;
    }
  }

  if (init_square == final_square) {
    // #6: No Change.
    return 6;
  }
  // #7: Invalid Transformation.
  return 7;
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int dimension = 0;
  fin >> dimension;
  // read square before transformation.
  const string init_square = ReadSquare(fin, dimension);
  // read square after transformation.
  const string final_square = ReadSquare(fin, dimension);

  // output.
  fout << GetTransformationID(init_square, final_square, dimension) << endl;
}
