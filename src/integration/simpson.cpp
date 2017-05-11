#include <iostream>
#include <cmath>

using namespace std;

double simpson_third(double *values, double a, double b, int n) {
  double segments = n - 1;
  double h = (b - a)/segments/3.0;
  cout << "h = " << h * 3 << endl;
  double sum = values[0];

  for(int i = 1; i < n - 1; i += 2) {
    sum += 4*values[i];
    if(i < n - 2)
      sum += 2*values[i+1];
  }
  sum += values[n-1];
  sum *= h;

  return sum;
}

double simpson_eighth(double *values, double a, double b) {
  return ( (b - a)/8.0 ) * (values[0] + 3*values[1] + 3*values[2] + values[3]);
}

double f(double x) {
  return exp( x );
}

int main(){
  int n;
  double a, b;
  cout << "Initial Value (a): "; cin >> a;
  cout << "Final Value (b): "; cin >> b;
  n = b - a + 1;
  cout << "n = " << n << endl;
  double v[n];
  for(int i = a, j = 0; i <= b; i++, j++) {
    v[j] = f(i);
  }
  for(int i = 0; i < n; i++) {
    cout << v[i] << " ";
  }
  cout << endl;
  cout << "Simpson 1/3: " << simpson_third(v, a, b, n) << endl;

  double values[] = {1,4,9,16};
  simpson_eighth(values, 1, 4);
  return 0;
}
