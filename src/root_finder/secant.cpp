#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

double f(double x) {
  double fx = log(abs(x)); //Something
  if (isnan(fx)) {
    cerr << "Function is discontinuous on " << x << endl;
  }
  return fx;
}

double sf(double x0, double x1) {
  return (x0 * f(x1) - x1 * f(x0)) / (f(x1) - f(x0));
}

double secant(double x0, double x1, double p) {
    int it = 1;
    double t;
    do {
      t = x0;
      x0 = sf(x0, x1);
      x1 = t;
      it++;
    }
    while (abs(x0 - x1) > p);
    cout << it << " iterations.\n";
    return x1;
}

int main(int argc, char* argv[]) {
  if (argc != 3 && argc != 4) {
    cerr << "This method receives two starting values and (optionally) an error margin." << endl;
    return 0;
  }

  double r;
  if (argc == 3) {
    r = secant(atof(argv[1]), atof(argv[2]), 1e-12);
  }
  else if (argc == 4) {
    r = secant(atof(argv[1]), atof(argv[2]), atof(argv[3]));
  }
  if (!isnan(r)) {
    cout << r << " is a root." << endl;
  }
  else {
    cout << "No root could be found." << endl;
  }
  return 0;
}
