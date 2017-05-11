#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>

using namespace std;

double f(double x) {
  return exp(pow(x, 2));
}

double left_sum(double a, double b, int n) {
  double I = 0;
  double h = (b - a) / n;
  for (int i = 0; i < n; i++) {
    I += f(a + i * h);
  }
  return I * h;
}

double right_sum(double a, double b, int n) {
  double I = 0;
  double h = (b - a) / n;
  for (int i = 0; i < n; i++) {
    I += f(a + (i + 1) * h);
  }
  return I * h;
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

double left_sum(double a, double b, double e) {
  double a1 = (b - a) * f(a);
  double a2 = a1;
  int n = 2;

  do {
    a1 = a2;
    double w = (b - a) / n;
    a2 = 0;
    for (int i = 0; i < n; i++) {
      a2 += f(a + i * w);
    }
    a2 *= w;
    n++;
    cout << "Error: " << 100 * abs((a2 - a1)) / a2  << "%" << endl;
  }
  while (abs((a2 - a1)) / a2 > e / 100);

  cout << "No. of rectangles: " << n - 1 << endl;
  return a2;
}

double right_sum(double a, double b, double e) {
  double a1 = (b - a) * f(b);
  double a2 = a1;
  int n = 2;

  do {
    a1 = a2;
    double w = (b - a) / n;
    a2 = 0;
    for (int i = 0; i < n; i++) {
      a2 += f(a + (i + 1) * w);
    }
    a2 *= w;
    n++;
    cout << "Error: " << 100 * abs((a2 - a1)) / a2  << "%" << endl;
  }
  while (abs((a2 - a1)) / a2 > e / 100);

  return a2;
  cout << "No. of rectangles: " << n - 1 << endl;
}

double trapezoids(double a, double b, double e) {
  double a1 = left_sum(a, b, 1) + right_sum(a, b, 1) / 2;
  double a2 = a1;
  int n = 2;

  do {
    a1 = a2;
    a2 = trapezoids(a, b, n);
    n++;
    cout << "Error: " << 100 * abs((a2 - a1)) / a2  << "%" << endl;
  }
  while (abs((a2 - a1)) / a1 > e / 100);

  cout << "No. of rectangles: " << n - 1 << endl;
  return a2;
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "This method takes an interval, the number of desired slices and a type of method." << endl;
    return 1;
  }
  int method = atoi(argv[4]);
  switch(method) {
    case 1:
      cout << "The area estimated with left sum is: " << left_sum(atof(argv[1]), atof(argv[2]), atoi(argv[3])) << endl;
      break;
    case 2:
      cout << "The area estimated with right sum is: " << right_sum(atof(argv[1]), atof(argv[2]), atoi(argv[3])) << endl;
      break;
    case 3:
      cout << "The area estimated with trapezoids sum is: " << trapezoids(atof(argv[1]), atof(argv[2]), atoi(argv[3])) << endl;
      break;
    case 4:
      cout << "The area estimated with left sum is: " << left_sum(atof(argv[1]), atof(argv[2]), atof(argv[3])) << endl;
      break;
    case 5:
      cout << "The area estimated with right sum is: " << right_sum(atof(argv[1]), atof(argv[2]), atof(argv[3])) << endl;
      break;
    case 6:
      cout << "The area estimated with trapezoids sum is: " << trapezoids(atof(argv[1]), atof(argv[2]), atof(argv[3])) << endl;
      break;
    default:
      cerr << "Invalid method number." << endl;
      return 1;
  }
  return 0;
}
