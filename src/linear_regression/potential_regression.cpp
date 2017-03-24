#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

void min_squares(vector<double> &x, vector<double> &y) {
  double xs = 0.0, ys = 0.0, logxs = 0.0, logys = 0.0, logxlogys = 0.0, logxsq;
  int n = x.size();

  // Setup calculations
  for (int i = 0; i < n; i++) {
    xs += x[i];
    ys += y[i];
    logxs += log10(x[i]);
    logys += log10(y[i]);
    logxlogys += log10(x[i]) * log10(y[i]);
    logxsq += pow(log10(x[i]), 2);
  }
  double xmean = xs / n;
  double ymean = ys / n;
  double logxmean = logxs / n;
  double logymean = logys / n;


  double a1 = (n * logxlogys - logxs * logys) / (n * logxsq - pow(logxs, 2));
  double a0 = logymean - a1 * logxmean;

  cout << "EQUATION" << endl;
  cout << "y = " << pow(10, a0) << "x^" << a1 << endl;
  double st = 0.0, sr = 0.0;
  for (int i = 0; i < n; i++) {
    sr += pow(y[i] - pow(10, a0) * pow(x[i], a1), 2);
    st += pow(y[i] - ymean, 2);
  }
  cout << "ST: " << st << endl;
  cout << "SR: " << sr << endl;
  // Standard error
  double serr = sqrt(sr / (n - 2));
  cout << "STANDARD ERROR" << endl;
  cout << serr << endl;
  // Determination coefficient
  double r = sqrt((st - sr) / st);
  cout << "CORRELATION COEFFICIENT" << endl;
  cout << r << endl;
  cout << "DETERMINATION COEFFICIENT" << endl;
  cout << pow(r, 2) << endl;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "This method receives two files containing values of x and y respectively." << endl;
  }
  ifstream file_x;
  ifstream file_y;
  file_x.open(argv[1]);
  file_y.open(argv[2]);

  if (file_x.is_open() & file_y.is_open()) {
      vector<double> x, y;
      while (!file_x.eof() && !file_y.eof()) {
        x.push_back(0);
        file_x >> x[x.size() - 1];
        y.push_back(0);
        file_y >> y[y.size() - 1];
      }
      x.pop_back();
      y.pop_back();
      file_x.close();
      file_y.close();

      min_squares(x, y);
  }
  else {
    cerr << "Problem with the file. Cannot be opened" << endl;
  }

  return 0;
}
