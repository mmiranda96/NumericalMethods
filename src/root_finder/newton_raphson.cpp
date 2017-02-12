#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

double f(double x) {
  double fx = pow(x, 10) - 1; //Something
  if (isnan(fx)) {
    cerr << "Function is discontinuous on " << x << endl;
  }
  return fx;
}

double df(double x) {
  double dfx = 10 * pow(x, 9); //Derivative of f
  if (isnan(dfx)) {
    cerr << "First derivative is discontinuous on " << x << endl;
  }
  return dfx;
}

double nrf(double x0) {
  return x0 - f(x0) / df(x0);
}

double newton_rapson(double x0, double p) {
  double x1 = x0;
    int it = 1;
    do {
      x0 = x1;
      x1 = nrf(x0);
      it++;
    }
    while (abs(x0 - x1) > p);
    cout << it << " iterations.\n";
    return x1;
}

int main(int argc, char* argv[]) {
  if (argc != 2 && argc != 3) {
    cerr << "This method receives a starting value and (optionally) an error margin." << endl;
    return 0;
  }

  double r;
  if (argc == 2) {
    r = newton_rapson(atof(argv[1]), 1e-12);
  }
  else if (argc == 3) {
    r = newton_rapson(atof(argv[1]), atof(argv[2]));
  }
  if (!isnan(r)) {
    cout << r << " is a root." << endl;
  }
  else {
    cout << "No root could be found." << endl;
  }
  return 0;
}
