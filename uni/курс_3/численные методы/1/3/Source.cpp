#include <iostream>
#include <fstream>
#include <math.h>  
using namespace std;
double f(double);
void main() {
	double x_p, x_n, x_temp, eps = 0.0000001, a, b, x[20];
	int cur = 0;
	bool check = 1;
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	for (int i = a; i <= b; i++) {
		x_p = i;
		x_n = i + 1;
		if (f(x_p) * f(x_n) < 0) {
			while (abs(x_n - x_p) > eps) {
				x_temp = x_n;
				x_n = x_p - (f(x_p) * (x_n - x_p)) / (f(x_n) - f(x_p));
				x_p = x_temp;
			}
			if (f(x_p) <= 0.00001 && check)
				x[cur++] = x_p;
		}
	}
	for (int i = 0; i < cur; i++)
		cout << x[i] << endl;
	system("pause");
}
//double f(double x) {
//	return (2-x)*exp(x) - 0.5;
//}
double f(double x) {
	return pow(x, 2) * log10(x) - 3.8;
}