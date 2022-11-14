#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
void print(double[200][200], int);
double f0_1(double[20]);
double f0_2(double[20]);
double f1_1(double[20]);
double f1_2(double[20]);
double f2_1(double[20]);
double f2_2(double[20]);
double b(double(*curfunc)(double[20]), double x[200]) {
	return (*curfunc)(x);
}
void main() {
	int N;
	double a[200][200], c, s, temp_a, line_swap, a_cur_ratio;
	double x_cur[200], x_next[200], a_ex[200][200];
	int pN = 10;
	int numm;
	double(*func1)(double[200]) = NULL, (*func2)(double[200]) = NULL;
	string num;
	cout << "0, 1, 2, 3: ";
	cin >> numm;
	switch (numm) {
	case 0:
		num = "0";
		func1 = &f0_1;
		func2 = &f0_2;
		break;
	case 1:
		num = "1";
		func1 = &f1_1;
		func2 = &f1_2;
	case 2:
		num = "2";
		func1 = &f2_1;
		func2 = &f2_2;
	}

	ifstream file("V://matrix_" + num + ".txt");
	file >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			file >> a_ex[i][j];
		}
		cin >> x_cur[i];
	}
	file.close();
	for (int p = 0; p < pN; p++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				a[i][j] = a_ex[i][j];
			}
		}
		a[0][N] = func1(x_cur);
		a[1][N] = func2(x_cur);
		print(a, N);
		for (int k = 0; k < N; k++) {
			for (int i = N - 1; i > k; i--) {
				for (int ii = k; ii < i; ii++) {
					if (a[ii][k] == 0) {
						for (int swap = k; swap < N + 1; swap++) {
							line_swap = a[ii][swap];
							a[ii][swap] = a[ii + 1][swap];
							a[ii + 1][swap] = line_swap;
						}
					}
				}
			}
			if (a[k][k] == 0)
				continue;
			for (int i = k + 1; i < N; i++) {
				a_cur_ratio = a[i][k] / a[k][k];
				for (int j = k; j < N; j++) {
					a[i][j] -= a_cur_ratio * a[k][j];
					if (abs(a[i][j]) < 0.0001)
						a[i][j] = 0;
				}
				a[i][N] -= a_cur_ratio * a[k][N];
				if (abs(a[i][N]) < 0.0001)
					a[i][N] = 0;
			}
		}
		print(a, N);
		double x[200];
		for (int i = 0; i < N; i++)
			x[i] = 0;
		for (int i = N - 1; i >= 0; i--) {
			for (int ii = i + 1; ii < N; ii++) {
				if (a[i][ii] != 0)
					a[i][N] -= a[i][ii] * x[ii];
			}
			x[i] = a[i][N] / a[i][i];
			x_cur[i] = x[i];
		}
		for (int i = 0; i < N; i++)
			cout << "x[" << i << "]==" << x[i] << endl;
	}
	system("pause");
}
void print(double a[200][200], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << a[i][j] << '\t';
		}
		cout << '|' << a[i][N] << endl;
	}
	cout << endl;
}

double f0_1(double x[20]) {
	return pow(x[0], 2);
}
double f0_2(double x[20]) {
	return pow(x[1], 2);
}
double f1_1(double x[20]) {
	return -pow(x[0], 2) + sin(x[0]*x[1]);
}
double f1_2(double x[20]) {
	return pow(x[0], 2) * x[1] - exp(x[0]);
}
double f2_1(double x[20]) {
	return -2*pow(x[0], 2) + x[0]*x[1]-1;
}
double f2_2(double x[20]) {
	return -3*log10(x[0]) + pow(x[1], 2);
}