#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

double interpolation(double x0, double y0, double x1, double y1, double x2, double y2, double x) {
  double b0, b1, b2;
  b0 = y0;
  b1 = (y1 - y0) / (x1 - x0);
  b2 = ((y2 - y1) / (x2 - x1) - b1) / (x2 - x0);

  double a0, a1, a2;
  a0 = b0 - b1 * x0 + b2 * x0 * x1;
  a1 = b1 - b2 * x0 - b2 * x1;
  a2 = b2;
  return a0 + a1 * x + a2 * pow(x, 2);
}

int main(int argc, char *argv[]) {
  if (argc != 8) {
    cerr << "This method takes three points and an x value for calculating its y." << endl;
    return 0;
  }
  cout << "Value: " << interpolation(atof(argv[1]), atof(argv[2]),
                                     atof(argv[3]), atof(argv[4]),
                                     atof(argv[5]), atof(argv[6]),
                                     atof(argv[7])) << endl;
  return 0;
}
