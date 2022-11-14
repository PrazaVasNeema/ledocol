#include<iostream>
#include <math.h>
using namespace std;
double F(double x1, double x2)
{
	return x1 * x1 + 7 * x2 * x2 - x1 * x2 + x1;
}

double f_dx(double x1, double x2)
{
	return 2 * x1 - x2 + 1;
}

double f_dy(double x1, double x2)
{
	return 14 * x2 - x1;
}

double g(double x1, double x2, double alpha, double S[2])
{
	return F(x1 + alpha * S[0], x2 + alpha * S[1]);
}

double norma(double x1, double x2)
{
	return sqrt(x1 * x1 + x2 * x2);
}


double Dihotomia(double a, double b, double x1, double x2, double S[2])
{
	double x, y, d = 0.0001, eps = 0.0001;
	int N = 100000;
	int i = 0;
	while (abs(b - a) / 2 >= eps || i < N) {
		x = ((a + b - d) / 2);
		y = ((a + b + d) / 2);
		if (g(x1, x2, x, S) < g(x1, x2, y, S)) {
			a = a;
			b = y;
		}
		else {
			if (g(x1, x2, x, S) > g(x1, x2, y, S)) {
				a = x;
				b = b;
			}
			//			else (g(x1, x2, x) == g(x1, x2, y)) {
			else {
				a = x;
				b = y;
			}
		}
		i++;
	}
	return abs(a + b) / 2;
}

void Newton_rafson(double x1, double x2, double delta, double eps, int N, double a, double b)
{
	double x1_prev, x2_prev, alpha, S[2],
		H_rev[2][2] = {
		{14.0 / 27.0, 1.0 / 27.0},
		{1.0 / 27.0, 2.0 / 27.0} };
	int i = 0;
	int k = 0;
	alpha = 1;

	cout << "x0: (" << x1 << ", " << x2 << ")" << endl << endl << "---------------\n";
	do
	{
		if (norma(f_dx(x1, x2), f_dy(x1, x2)) < delta) {
			break;
		}
		cout << "Итерация " << k + 1 << endl;
		cout << "ydx, ydy: " << f_dx(x1, x2) << '\t' << f_dy(x1, x2) << endl;



		S[0] = -(H_rev[0][0] * f_dx(x1, x2) + H_rev[0][1] * f_dy(x1, x2));
		S[1] = -(H_rev[1][0] * f_dx(x1, x2) + H_rev[1][1] * f_dy(x1, x2));
		alpha = Dihotomia(a, b, x1, x2, S);
		cout << "Альфа: " << alpha << endl;

		x1_prev = x1;
		x2_prev = x2;
		x1 = x1 + alpha * S[0];
		x2 = x2 + alpha * S[1];
		cout << "x1, x2: " << x1 << '\t' << x2 << "\n---------------\n";
		if (norma(x1 - x1_prev, x2 - x2_prev) < eps && abs(F(x1, x2) - F(x1_prev, x2_prev)) < eps) {
			i++;
		}
		else
			i = 0;
		k++;
		if (i == 2)
			break;

	} while (k < N);

	cout << "\nИтераций: " << k << endl << endl;
	cout << "F(" << x1 << ", " << x2 << ") = " << F(x1, x2) << endl;

}

void main()
{
	setlocale(LC_ALL, "Russian");

	double x1, x2, delta, eps, a, b;
	int N;
	a = 0;
	b = 1;
	//	N = 2;
	cout << "N: ";
	cin >> N;
	x1 = 1.1;
	x2 = 1.1;
	cout << "delta: ";
	cin >> delta;
	//	delta = 0.1;
//	cout << "eps: ";
//	cin >> eps;
	cout << "eps: ";
	cin >> eps;
	//	eps = 0.0001;
	Newton_rafson(x1, x2, delta, eps, N, a, b);
}