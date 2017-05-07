#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>

using namespace std;

double slope(double x0, double x1, double y0, double y1) {
  return (y1 - y0) / (x1 - x0);
}

double interpolation(vector<double> &xn, vector<double> &yn, double x) {
  vector<double> fs(xn);
  vector<double> p(xn.size() - 1, 0);
  for (int i = 0; i < xn.size() - 2; i++) {
      vector<double> temp;
      for (int j = 0; j < fs.size() - 1; j++) {
        temp.push_back(slope(fs[2 * j], fs[2 * j + 1], yn[2 * j], yn[2 * j + 1]));
      }
      p[p.size() - (i + 2)] = temp[0];
      fs = temp;
  }
  p[p.size() - 1] = yn[0];
  // Print polynomial
  for (int i = 0; i < p.size(); i++) {
    cout << p[i] << " ";
  }
  cout << endl;

  // Evaluating the polynomial
  double temp_prod = 1;
  double temp_sum = p[p.size() - 1];
  for (int i = 0; i < p.size() - 1; i++) {
    temp_prod *= (x - xn[i]);
    temp_sum += p[i] * temp_prod;
  }

  return temp_sum;
}

int main(int argc, char *argv[]) {
  if (argc < 7) {
    cerr << "This algorithms takes the number of points, n points, their corresponding evaluation and an x to be calculated." << endl;
    return 1;
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
