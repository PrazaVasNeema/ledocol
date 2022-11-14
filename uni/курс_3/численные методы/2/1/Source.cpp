#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
using namespace std;
void print(double[20][20], int);
void main() {
	int N, counter = -1, temp;
	double a[20][20], y[20], y_norma = 0, x[3][20], lambda[3], eps, s = 0, t;
	string num;
	cout << "matrix num (1, 2, 3): ";
	cin >> num;
	ifstream file("C://Limbo//Purgatory//To_wf//1//matrix_" + num + ".txt");
	file >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			file >> a[i][j];
		}
	}
	file >> temp;
	cout << "max sobstv znach: " << temp << "\nsobstv vector: ";
	for (int i = 0; i < N; i++) {
		file >> temp;
		cout << temp << "\t";
	}
	cout << endl;
	print(a, N);
	file.close();

	cout << "eps: ";
	cin >> eps;
	cout << "y0: ";
	for (int i = 0; i < N; i++)
		cin >> y[i];
	for (int i = 0; i < N; i++)
		s += y[i] * y[i];
	y_norma = sqrt(s);
	for (int i = 0; i < N; i++) {
		x[2][i] = y[i] / y_norma;
		x[1][i] = x[2][i];
	}
	lambda[2] = 0;
	lambda[1] = 0;
	do {
		lambda[0] = lambda[1];
		lambda[1] = lambda[2];
		for (int i = 0; i < N; i++) {
			x[0][i] = x[1][i];
			x[1][i] = x[2][i];
		}

		s = 0; t = 0;
		for (int i = 0; i < N; i++) {
			y[i] = 0;
			for (int j = 0; j < N; j++)
				y[i] += a[i][j] * x[2][j];
		}
		for (int i = 0; i < N; i++)
			s += y[i] * y[i];
		for (int i = 0; i < N; i++)
			t += y[i] * x[2][i];
		y_norma = sqrt(s);
		for (int i = 0; i < N; i++)
			x[2][i] = y[i] / y_norma;
		lambda[2] = s / t;
		if (counter % 3 == 0 && counter != 0) {
			for (int i = 0; i < N; i++)
				x[2][i] = x[0][i] - pow(x[1][i] - x[0][i], 2) / (x[2][i] - 2 * x[1][i] + x[0][i]);
		}
		counter++;
//		cout << counter << "\t";
	} while (abs(lambda[2]-lambda[1]) > eps);
	cout << setprecision(8);
	cout << "\nlambda1: " << lambda[2] << endl;
//	cout << endl << lambda[0] << endl << lambda[1] << endl << lambda[2];
	lambda[2] = lambda[0] - pow(lambda[1] - lambda[0], 2) / (lambda[2] - 2 * lambda[1] + lambda[0]);

	cout << "\nlambda1 (esk): " << lambda[2] << endl << endl;
	cout << "x1: ";
	for (int i = 0; i < N; i++) {
		if (x[2][i] <= 0.001) {
			cout << 0 << '\t';
			continue;
		}
		cout << x[2][i] << '\t';
	}
}
void print(double a[20][20], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << a[i][j] << '\t';
		cout << endl;
	}
	cout << endl;
}