#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct complex {
  double r;
  double i;
};

void syn_div(vector<double> &pol, vector<double> &res, vector<double> &aux, double r, double s) { // Check results on res
  int deg = pol.size() - 1;
  int i, j;
  for(i = deg, j = 0; i >= 0; i--, j++){
    if(i == deg){
      res[j] = pol[j];
    }
    else if(i == deg - 1){
      res[j] = pol[j] + res[j - 1] * r;
    }
    else{
      res[j] = pol[j] + res[j - 1] * r + res[j - 2] * s;
    }
  }

  for(i = deg, j = 0; i >= 0; i--, j++){
    if(i == deg){
      aux[j] = res[j];
    }
    else if(i == deg - 1){
      aux[j] = res[j] + aux[j - 1] * r;
    }
    else{
      aux[j] = res[j] + aux[j - 1] * r + aux[j - 2] * s;
    }
  }
}

void cramer(double a1, double b1, double c1, double a2, double b2, double c2, double &x, double &y) {
  double d = (a1 * b2) - (a2 * b1);
  x = (c1 * b2 - c2 * b1) / d;
  y = (a1 * c2 - a2 * c1) / d;
}

/*
double quadratic(double a, double b, double c, bool sign) {
  return sign ? (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a) : (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
}
*/

void bairstow(vector<double> &pol, vector<complex*> &roots, double pi, double qi, double err) {
  while (pol.size() > 3) {
    vector<double> res(pol.size(), 0.0);
    vector<double> aux(pol.size(), 0.0);

    double p = pi;
    double q = qi;
    double dp = 0.0;
    double dq = 0.0;
    double error_p = 1.0;
    double error_q = 1.0;

    do {
      // Fill auxiliar polynomials with zeros
      for (int i = 0; i < res.size(); i++) {
        res[i] = 0;
        aux[i] = 0;
      }

      syn_div(pol, res, aux, p, q);

      for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
      }
      cout << endl;

      int deg = pol.size() - 1;
      double d = aux[deg - 2] * aux[deg - 2] - aux[deg - 1] * aux[deg - 3];
      dp = (-res[deg - 1] * aux[deg - 2] + res[deg] * aux[deg - 3]) / d;
      dq = (-aux[deg - 2] * res[deg] + aux[deg - 1] * res[deg - 1]) / d;

      error_p = dp / p;
      error_q = dq / q;
      p += dp;
      q += dq;
    } while (abs(error_p) > err && abs(error_q) > err);

    cout << endl;
    // 2 Roots
    double det = pow(p, 2) + 4 * q;

    complex *r1 = new complex;
    complex *r2 = new complex;
    if (det < 0) {
      r1->r = p / 2;
      r1->i = sqrt(-det) / 2;
      r2->r = p / 2;
      r2->i = -sqrt(-det) / 2;
    }
    else {
      r1->r = (p + sqrt(det)) / 2;
      r1->i = 0;
      r2->r = (p - sqrt(det)) / 2;
      r2->i = 0;
    }
    roots.push_back(r1);
    roots.push_back(r2);

    res = vector<double>(pol.size(), 0.0);
    aux = vector<double>(pol.size(), 0.0);

    syn_div(pol, res, aux, p, q);

    // Adjust polynomial
    for (int i = 0; i < pol.size() - 2; i++) {
      pol[i] = res[i];
    }
    pol.pop_back();
    pol.pop_back();


    cout << "NEW POLYNOMIAL" << endl;
    for (int i = 0; i < pol.size(); i++) {
      cout << pol[i] << " ";
    }
  }

  if (pol.size() == 3) {
    int p = -pol[1];
    int q = -pol[2];
    double det = pow(p, 2) + 4 * q;

    complex *r1 = new complex;
    complex *r2 = new complex;
    if (det < 0) {
      r1->r = p / 2;
      r1->i = sqrt(-det) / 2;
      r2->r = p / 2;
      r2->i = -sqrt(-det) / 2;
    }
    else {
      r1->r = (p + sqrt(det)) / 2;
      r1->i = 0;
      r2->r = (p - sqrt(det)) / 2;
      r2->i = 0;
    }
    roots.push_back(r1);
    roots.push_back(r2);
  }
  else if (pol.size() == 2) {
    complex *r = new complex;
    r->r = -pol[1] / pol[0];
    r->i = 0;
    roots.push_back(r);
  }
}

int main(int argc, char* argv[]) {
  //vector<double> pol = {1.0, -4.0, -11.0, 30};
  vector<double> pol = {6.7, -4, 0, 3.2, -3, 8, 1.2, 2, 0, 1, -4};
  vector<complex*> roots;
  double p = -1;
  double q = -1;
  cout << "ORIGINAL POLYNOMIAL" << endl;
  for(int i = 0; i < pol.size(); i++) {
    cout << pol[i] << " ";
  }
  cout << endl;

  cout << endl << "BAIRSTOW" << endl;
  bairstow(pol, roots, p, q, 1e-4);

  cout << endl << endl << "ROOTS" << endl;
  for (int i = 0; i < roots.size(); i++) {
    cout << roots[i]->r << " + " << roots[i]->i << "i" << endl;
  }
}
