#include <iostream>
#include <iomanip>
using namespace std;
double F(double x) {
	return x * x - 9 * x + 13;
}
double FindMin(double a, double b, double eps, double(*F)(double), int N) {
	double x, y;
	x = a + (3 - sqrt(5)) / 2 * (b - a);
	y = a + b - x;
	for (int i = 1; i < N; i++) {
		if (abs(b - a) < 2 * eps) {
			break;
		}
		if (F(x) < F(y)) {
			a = a;
			b = y;
			y = x;
			x = a + b - y;
		}
		else {
			a = x;
			b = b;
			x = y;
			y = a + b - x;
		}
	}
	cout << setprecision(8) << "x*: ";
	return  (a + b) / 2;
}
void main() {
	double a, b, eps;
	int N;
	cout << "a:";
	cin >> a;
	cout << "b:";
	cin >> b;
	//	a = -6;
	//	b = 4;
	cout << "eps:";
	cin >> eps;
	//	cout << "alpha:";
	//	cin >> alpha;
	//	eps = 0.01;
	cout << "N:";
	cin >> N;

	cout << FindMin(a, b, eps, F, N);
}