#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

double interpolation(double x1, double y1, double x2, double y2, double x) {
  return y1 + (y2 - y1) / (x2 - x1) * (x - x1);
}

int main(int argc, char *argv[]) {
  if (argc != 6) {
    cerr << "This method takes two points and an x value for calculating its y." << endl;
    return 0;
  }
  cout << "Value: " << interpolation(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5])) << endl;
  return 0;
}
