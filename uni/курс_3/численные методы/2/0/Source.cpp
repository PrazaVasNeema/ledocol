#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
void print(double[20][20], int);
void main() {
	int N, count, temp;
	double a[20][20], y[20], y_norma = 0, x[3][20], lambda_vect[2][20], lambda_max = 0, eps;
	bool check = 1;
	string num;
	cout << "num: ";
	cin >> num;
	ifstream file("C://Limbo//Purgatory//To_wf//0//matrix_" + num + ".txt");
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
	for (int i = 0; i < N; i++) {
		cin >> y[i];
		y_norma += y[i]*y[i];
	}
	y_norma = sqrt(y_norma);
	for (int i = 0; i < N; i++)
		x[1][i] = y[i] / y_norma;

	for (int i = 0; i < N; i++)
		lambda_vect[1][i] = -10000;
	do {
		count = 0;
		for (int i = 0; i < N; i++) {
			lambda_vect[0][i] = lambda_vect[1][i];
			x[0][i] = x[1][i];
		}
		for (int i = 0; i < N; i++) {
			y[i] = 0;
			for (int j = 0; j < N; j++) {
				y[i] += a[i][j] * x[0][j];
			}
			y_norma += y[i] * y[i];
//			cout << y[1][i] << '\t';
		}
		y_norma = sqrt(y_norma);
		for (int i = 0; i < N; i++)
			x[1][i] = y[i] / y_norma;

		for (int i = 0; i < N; i++) {
			if (abs(x[0][i]) < 0.1) {
				lambda_vect[1][i] = 0;
				continue;
			}
			lambda_vect[1][i] = y[i] / x[0][i];
			count++;
		}
		for (int i = 0; i < N; i++) {
			if (lambda_vect[0][i] == 0 || lambda_vect[1][i] == 0)
				continue;
			if (abs(lambda_vect[1][i] - lambda_vect[0][i]) <= eps)
			check = 0;
			break;
		}
//		for (int i = 0; i < N; i++)
//			y[0][i] = y[1][i];
//		cout << compare << endl;
	} while (check);

	for (int i = 0; i < N; i++) {
		lambda_max += lambda_vect[1][i];
	}
	lambda_max /= count;

	cout << setprecision(8);
	cout << "lambda max: " << lambda_max;
	cout << "\nx max: ";
	for (int i = 0; i < N; i++) {
		if (x[1][i] <= 0.01) {
			cout << 0 << '\t';
			continue;
		}
		cout << x[1][i] << '\t';
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