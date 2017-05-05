#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>

using namespace std;

double lagrange(vector<double> &xn, int i, double x) {
  double p = 1.0;
  for (int j = 0; j < xn.size(); j++) {
    if (j != i) {
      p *= (x - xn[j]) / (xn[i] - xn[j]);
    }
  }

  return p;
}

double interpolation(vector<double> &xn, vector<double> &yn, double x) {
  double s = 0.0;
  for (int i = 0; i < xn.size(); i++) {
    s += lagrange(xn, i, x) * yn[i];
  }

  return s;
}

int main(int argc, char **argv) {
  if (argc < 7) {
    cerr << "This algorithms takes the number of points, n points, their corresponding evaluation and an x to be calculated." << endl;
  }
  vector<double> xn, yn;
  int n = atoi(argv[1]);
  double x = atof(argv[argc - 1]);
  for (int i = 0; i < n; i++) {
    xn.push_back(atof(argv[i + 2]));
    yn.push_back(atof(argv[n + i + 2]));
  }

  double r = interpolation(xn, yn, x);
  cout << "The calculated value is " << r << endl;
}
