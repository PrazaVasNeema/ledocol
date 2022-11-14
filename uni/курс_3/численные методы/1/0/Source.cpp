#include <iostream>
#include <fstream>
using namespace std;
void print(double[20][20], int);
void main() {
	int N;
	double a[20][20], a_cur_ratio, line_swap;
	string num;
	cout << "0, 1, 2, 3: ";
	cin >> num;
	ifstream file("V://matrix_"+num+".txt");
	file >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N + 1; j++) {
			file >> a[i][j];
		}
	}
	print(a, N);
	file.close();

	for (int k = 0; k < N; k++) {
		for (int i = N-1; i > k; i--) {
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
			a_cur_ratio = a[i][k]/a[k][k];
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
	double x[20];
	for (int i = N - 1; i >= 0; i--) {
		for (int ii = i + 1; ii < N; ii++) {
			if (a[i][ii] != 0)
				a[i][N] -= a[i][ii] * x[ii];
		}
		x[i] = a[i][N] / a[i][i];
	}
	for (int i = 0; i < N; i++)
		cout << "x[" << i << "]==" << x[i] << endl;
}
void print(double a[20][20], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << a[i][j] << '\t';
		}
		cout << '|' << a[i][N] << endl;
	}
	cout << endl;
}