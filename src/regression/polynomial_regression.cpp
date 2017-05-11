#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

void print_matrix(vector< vector<double> > &A, vector<double> &B) {
  int n = A.size();
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cout << A[i][j] << "\t";
    }
    cout << "|  " << B[i];
    cout << endl;
  }
}

void gauss(vector< vector<double> > &A, vector<double> &B) {
  // Backward substitution
  int n = A.size();
  double factor;
  for(int k = 0; k < n; k++) {
    for(int i = k + 1; i < n; i++) {
        factor = A[i][k] / A[k][k];
        for(int j = k; j < n; j++) {
          A[i][j] -= factor * A[k][j];
        }
        B[i] -= factor * B[k];
      }
  }

  // Forward elimination
  double sum;
  B[n - 1] = B[n - 1] / A[n - 1][n - 1];
  for(int i = n - 2; i >= 0; i--) {
    sum = 0;
    for(int j = i + 1; j < n; j++) {
      sum += A[i][j] * B[j];
      A[i][j] = 0;
    }
    B[i] = (B[i] - sum) / A[i][i];
  }
}

void polynomial_regression(vector<double> &x, vector<double> &y, int degree) {
  int n = x.size();
  double sum_x = 0, sum_xy = 0;

  vector< vector<double> > A;
  for(int i = 0; i < degree + 1; i++){
    vector<double> temp(degree + 1, 0);
    A.push_back(temp);
  }
  vector<double> B(degree + 1, 0);

  for(int i = 0; i < degree + 1; i++) {
    sum_xy = 0;

    for(int j = 0; j < n; j++) {
      sum_xy += pow(x[j], i) * y[j];
    }
    B[i] = sum_xy;

    for (int j = 0; j < degree + 1; j++) {
      sum_x = 0;
      if (i == 0 && j == 0) {
        sum_x = n;
      }
      else {
        //Calculate the sum of x to a certain power.
        for (int h = 0; h < n; h++) {
          sum_x += pow(x[h], j + i);
        }
      }
      A[i][j] = sum_x;
    }
  }

  double sum_y = B[0];

  cout << "\nGauss to get [a0...an] ..." << endl << "------------------------------------------" << endl;
  print_matrix(A, B);
  cout << endl;
  gauss(A, B);
  print_matrix(A, B);

  cout << "\nPolynomial ..." << endl << "------------------------------------------" << endl;
  for (int i = 0; i < B.size() - 2; i++) {
    cout << B[B.size() - (i + 1)] << " * x ^ " << B.size() - (i + 1) << " + ";
  }
  cout << B[1] << " * x + " << B[0] << endl;

  cout << endl;
  cout << "\nErrors ..." << endl << "------------------------------------------" << endl;
	double e[n];
	for (int i = 0; i < n; i++) {
		double y_calculated = 0;
		for (int j = degree; j >= 1; j--) {
      y_calculated += B[j] * pow(x[i], j);
    }
		y_calculated += B[0];
		e[i] = pow(y[i] - y_calculated,2);
	}

	double sr = 0;
	double st = 0;
	for (int i = 0; i < n; i++) {
		sr += e[i];
		st += pow(y[i] - (sum_y / n), 2);
	}

	double syx = sqrt(sr / (n - (degree + 1)));
	double r2 = (st - sr) / st;
	double r = sqrt(r2);

	cout << "STANDARD ERROR: " << syx;
  if(n - degree - 1 == 0) {
    cout << "\tS y/x is a division by 0";
  }
  cout << endl;
	cout << "CORRELATION COEFFICIENT: " << r << endl;
  cout << "DETERMINATION COEFFICIENT: " << r2 << endl;
	cout << endl;

}

int main(int argc, char **argv) {
  if (argc != 5) {
    cerr << "This method receives two files (x and y), the number of registers and the degree of the polynomial." << endl;
    return -1;
  }

  ifstream inx(argv[1]);
  ifstream iny(argv[2]);
  int n = atoi(argv[3]);
  int degree = atoi(argv[4]);

  if(!inx || !iny){
    cout << "Error" << endl;
  }

  vector<double> x(n, 0);
  vector<double> y(n, 0);

  cout << "\n  x\t  y" << endl << "-------------" << endl;
  for(int i = 0; inx && iny && i < n; i++) {
    inx >> x[i];
    iny >> y[i];

    cout << x[i] << "\t" << y[i] << endl;
  }

  inx.close();
  iny.close();

  polynomial_regression(x, y, degree);

  return 0;
}
