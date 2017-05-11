#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>

using namespace std;

double f(double x) {
  return exp(pow(x, 2));
}

double trapezoids(double a, double b, int n) {
  double I = f(a);
  double h = (b - a) / n;
  for (int i = 1; i < n; i++) {
    I += 2 * f(a + i * h);
  }
  I += f(b);
  return I * h / 2;
}

double romberg(double a, double b, int k) {
  vector<double> integrals(k, 0);
  for (int i = 0; i < k; i++) {
    integrals[i] = trapezoids(a, b, pow(2, i));
  }

  for (int i = 2; i <= k; i++) {
    for (int j = 0; j < k - i + 1; j++) {
      cout << integrals[j] << ", " << integrals[j + 1] << endl;
      double I = pow(4, i - 1) / (pow(4, i - 1) - 1.0) * integrals[j + 1] - 1 / (pow(4, i - 1) - 1.0) * integrals[j];
      integrals[j] = I;
    }
  }

  return integrals[0];
}

int main(int argc, char **argv) {
  if (argc != 4) {
    cerr << "This method receives an interval to integrate and the number of levels." << endl;
    return -1;
  }
  double a = atof(argv[1]);
  double b = atof(argv[2]);
  int k = atoi(argv[3]);
  double I = romberg(a, b, k);
  cout << "The area of f(x) from " << a << " to " << b << " in " << k << " levels is: " << I << endl;
  return 0;
}
