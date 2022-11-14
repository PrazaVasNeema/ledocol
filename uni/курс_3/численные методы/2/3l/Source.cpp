#include <iostream>
#include <string>
#include <fstream>
using namespace std;

double* primer1(double t, double y_1, double y_2, double y_3) {
	double* F = new double[3];
	F[0] = y_1 - y_2 + y_3;
	F[1] = y_1 + y_2 - y_3;
	F[2] = 2 * y_1 - y_2;
	return F;
}
double* primer2(double t, double y_1, double y_2) {
	double* F = new double[3];
	F[0] = y_2 + 2 * exp(t);
	F[1] = y_1 + t * t;
	return F;
}
double* primer3(double t, double y_1, double y_2) {
	double* F = new double[3];
	F[0] = t / y_2;
	F[1] = -t / y_1;
	return F;
}
void main() {
	setlocale(LC_ALL, "Russian");
	int razb, primer, n;
	double T, t[1000], h, ** y = new double* [3];
	for (int i = 0; i < 3; i++)
		y[i] = new double[1000];
	cout << "Введите номер примера (соответственно: линейная однородная третьего порядка, линейная неоднородная второго порядка, нелинейная - 1, 2 , 3): ";
	cin >> primer;
	cout << "введите точку конца: ";
	cin >> T;
	cout << ("Введите количество разбиений n: ");
	cin >> razb;
	ofstream file("primer_" + to_string(primer) + ".txt");
	double** k = new double* [4];
	for (int i = 0; i < 3; i++)
		k[i] = new double[4];

	switch (primer) {
	case 1:
		n = 3;



		t[0] = 0;
		y[0][0] = 3;
		y[1][0] = -2;
		y[2][0] = -3;
		h = (T - t[0]) / razb;
		file << t[0];
		cout << t[0];


		for (int i = 0; i < n; i++) {
			file << "\t" << y[i][0] << '\t';
			cout << "\t" << y[i][0] << '\t';
		}
		file << endl;
		cout << endl;


		for (int i = 0; i < razb; i++) {
			t[i + 1] = t[0] + h * (i + 1);
			file << t[i + 1];
			cout << t[i + 1];
			k[0] = primer1(t[i], y[0][i], y[1][i], y[2][i]);
			k[1] = primer1(t[i] + h / 4, y[0][i] + h * k[0][0] / 4, y[1][i] + h * k[0][1] / 4, y[2][i] + h * k[0][2] / 4);
			k[2] = primer1(t[i] + h / 2, y[0][i] + h * k[1][0] / 2, y[1][i] + h * k[1][1] / 2, y[2][i] + h * k[1][2] / 2);
			k[3] = primer1(t[i] + h, 
				y[0][i] + h * k[0][0] - 2 * h * k[1][0] + 2 * h * k[2][0], 
				y[1][i] + h * k[0][1] - 2 * h * k[1][1] + 2 * h * k[2][1],
				y[2][i] + h * k[0][2] - 2 * h * k[1][2] + 2 * h * k[2][2]);
			for (int j = 0; j < n; j++) {
				y[j][i + 1] = y[j][i] + h / 6 * (k[0][j] + 4 * k[2][j] + k[3][j]);
				file << "\t" << y[j][i + 1] << '\t';
				cout << "\t" << y[j][i + 1] << '\t';
			}
			file << endl;
			cout << endl;
		}
		file.close();

		break;
	case 2:
		n = 2;



		t[0] = 0;
		y[0][0] = 0;
		y[1][0] = -1;
		h = (T - t[0]) / razb;
		file << t[0];
		cout << t[0];

		for (int i = 0; i < n; i++) {
			file << "\t" << y[i][0] << '\t';
			cout << "\t" << y[i][0] << '\t';
		}
		file << endl;
		cout << endl;

		for (int i = 0; i < razb; i++) {
			t[i + 1] = t[0] + h * (i + 1);
			file << t[i + 1];
			cout << t[i + 1];
			k[0] = primer2(t[i], y[0][i], y[1][i]);
			k[1] = primer2(t[i] + h / 4, y[0][i] + h * k[0][0] / 4, y[1][i] + h * k[0][1] / 4);
			k[2] = primer2(t[i] + h / 2, y[0][i] + h * k[1][0] / 2, y[1][i] + h * k[1][1] / 2);
			k[3] = primer2(t[i] + h,
				y[0][i] + h * k[0][0] - 2 * h * k[1][0] + 2 * h * k[2][0],
				y[1][i] + h * k[0][1] - 2 * h * k[1][1] + 2 * h * k[2][1]);
			for (int j = 0; j < n; j++) {
				y[j][i + 1] = y[j][i] + h / 6 * (k[0][j] + 4 * k[2][j] + k[3][j]);
				file << "\t" << y[j][i + 1] << '\t';
				cout << "\t" << y[j][i + 1] << '\t';
			}
			file << endl;
			cout << endl;
		}
		file.close();

		break;
	case 3:
		n = 2;


		t[0] = 0;
		y[0][0] = 1;
		y[1][0] = 0.5;
		h = (T - t[0]) / razb;
		file << t[0];
		cout << t[0];


		for (int i = 0; i < n; i++) {
			file << "\t" << y[i][0] << '\t';
			cout << "\t" << y[i][0] << '\t';
		}
		file << endl;
		cout << endl;

		for (int i = 0; i < razb; i++) {
			t[i + 1] = t[0] + h * (i + 1);
			file << t[i + 1];
			cout << t[i + 1];
			k[0] = primer3(t[i], y[0][i], y[1][i]);
			k[1] = primer3(t[i] + h / 4, y[0][i] + h * k[0][0] / 4, y[1][i] + h * k[0][1] / 4);
			k[2] = primer3(t[i] + h / 2, y[0][i] + h * k[1][0] / 2, y[1][i] + h * k[1][1] / 2);
			k[3] = primer3(t[i] + h,
				y[0][i] + h * k[0][0] - 2 * h * k[1][0] + 2 * h * k[2][0],
				y[1][i] + h * k[0][1] - 2 * h * k[1][1] + 2 * h * k[2][1]);
			for (int j = 0; j < n; j++) {
				y[j][i + 1] = y[j][i] + h / 6 * (k[0][j] + 4 * k[2][j] + k[3][j]);
				file << "\t" << y[j][i + 1] << '\t';
				cout << "\t" << y[j][i + 1] << '\t';
			}
			file << endl;
			cout << endl;
		}
		file.close();

		break;
	}
}