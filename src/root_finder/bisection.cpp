#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

double avg(double x0, double x1) {
  return (x0 + x1) / 2;
}

double f(double x) {
  double fx = exp(x) + pow(x, 2) - 2; //Change function
  if (isnan(fx)) {
    cerr << "Function is discontinuous on " << x << endl;
  }
  return fx;
}

double bisection(double x1, double x2, double p) {
  if(f(x1) * f(x2) > 0.0) {
    return NAN;
  }
  else {
    double xm;
    int it = 0;
    do {
      if (abs(f(x1)) <= p) {
        cout << it << " iterations." << endl;
        return x1;
      }
      else if (abs(f(x2)) <= p) {
        cout << it << " iterations." << endl;
        return x2;
      }
      else {
        xm = avg(x1, x2);
        if (f(x1) * f(xm) < 0.0)
          x2 = xm;
        else
          x1 = xm;
      }
      it++;
    }
    while (abs(f(xm)) > p);
    cout << it << " iterations." << endl;
    return xm;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3 && argc != 4) {
    cerr << "This method receives an interval and (optionally) an error margin." << endl;
    return 0;
  }

  double r;
  if (argc == 3) {
    r = bisection(atof(argv[1]), atof(argv[2]), 1e-12);
  }
  else if (argc == 4) {
    r = bisection(atof(argv[1]), atof(argv[2]), atof(argv[3]));
  }
  if (!isnan(r)) {
    cout << r << " is a root." << endl;
  }
  else {
    cout << "No root could be found." << endl;
  }
  return 0;
}
