#include <iostream>
#include <fstream>
#include <string>
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
	int razb, choice, n;
	double T, t[1000], h, ** y = new double* [3];
	for (int i = 0; i < 3; i++)
		y[i] = new double[1000];
	cout << "Введите номер примера (соответственно: линейная однородная третьего порядка, линейная неоднородная второго порядка, нелинейная - 1, 2 , 3): ";
	cin >> choice;
	cout << "введите точку конца: ";
	cin >> T;
	cout << ("Введите количество разбиений n: ");
	cin >> razb;
	ofstream file("C://Limbo//Purgatory//To_wf//2i//primer_" + to_string(choice) + ".txt");
	double* F_1 = new double[3];
	double* F_2 = new double[3];
	//switch с решениями трех систем
	switch (choice) {
	case 1:
		n = 3;
		//Начальные условия при свободной переменной t, равной нулю, и константах C, равных единице
		t[0] = 0;
		y[0][0] = 3;
		y[1][0] = -2;
		y[2][0] = -3;
		h = (T - t[0]) / razb;

		//Вывод в файл первых значений функций (известных от начальных условий)
		F_1 = primer1(t[0], y[0][0], y[1][0], y[2][0]);
		for (int i = 0; i < n; i++) {
			file << t[0] << "\t" << y[i][0] << '\t';
			cout << t[0] << "\t" << y[i][0] << '\t';
		}
		file << endl;
		cout << endl;

		//Подсчет и вывод в файл вторых значений функций с помощью метода Эйлера
		t[1] = t[0] + h;
		for (int i = 0; i < n; i++) {
			y[i][1] = y[i][0] + h * F_1[i];
			file << t[1] << "\t" << y[i][1] << '\t';
			cout << t[1] << "\t" << y[i][1] << '\t';
		}
		file << endl;
		cout << endl;
		F_2 = primer1(t[1], y[0][1], y[1][1], y[2][1]);
		//Цикл подсчета и вывода в файл остальный значений функций при помощи явного метода Адамса с шагом 2
		for (int i = 2; i <= razb; i++) {
			t[i] = t[0] + h * i;
			for (int j = 0; j < n; j++) {
				y[j][i] = y[j][i - 1] + h / 2 * (3 * F_2[j] - F_1[j]);
				file << t[i] << "\t" << y[j][i] << '\t';
				cout << t[i] << "\t" << y[j][i] << '\t';
			}
			file << endl;
			cout << endl;
			F_1 = F_2;
			F_2 = primer1(t[i], y[0][i], y[1][i], y[2][i]);
		}
		file.close();

		break;
	case 2:
		n = 2;
		t[0] = 0;
		y[0][0] = 0;
		y[1][0] = 0;
		h = (T - t[0]) / razb;

		F_1 = primer2(t[0], y[0][0], y[1][0]);
		for (int i = 0; i < n; i++) {
			file << t[0] << "\t" << y[i][0] << '\t';
			cout << t[0] << "\t" << y[i][0] << '\t';
		}
		file << endl;
		cout << endl;
		t[1] = t[0] + h;
		for (int i = 0; i < n; i++) {
			y[i][1] = y[i][0] + h * F_1[i];
			file << t[1] << "\t" << y[i][1] << '\t';
			cout << t[1] << "\t" << y[i][1] << '\t';
		}
		file << endl;
		cout << endl;
		F_2 = primer2(t[1], y[0][1], y[1][1]);
		for (int i = 2; i <= razb; i++) {
			t[i] = t[0] + h * i;
			for (int j = 0; j < n; j++) {
				y[j][i] = y[j][i - 1] + h / 2 * (3 * F_2[j] - F_1[j]);
				file << t[i] << "\t" << y[j][i] << '\t';
				cout << t[i] << "\t" << y[j][i] << '\t';
			}
			file << endl;
			cout << endl;
			F_1 = F_2;
			F_2 = primer2(t[i], y[0][i], y[1][i]);
		}
		file.close();
		break;
	case 3:
		n = 2;
		t[0] = 0;
		y[0][0] = 1;
		y[1][0] = 0.5;
		h = (T - t[0]) / razb;

		F_1 = primer3(t[0], y[0][0], y[1][0]);
		for (int i = 0; i < n; i++) {
			file << t[0] << "\t" << y[i][0] << '\t';
			cout << t[0] << "\t" << y[i][0] << '\t';
		}
		file << endl;
		cout << endl;
		t[1] = t[0] + h;
		for (int i = 0; i < n; i++) {
			y[i][1] = y[i][0] + h * F_1[i];
			file << t[1] << "\t" << y[i][1] << '\t';
			cout << t[1] << "\t" << y[i][1] << '\t';
		}
		file << endl;
		cout << endl;
		F_2 = primer3(t[1], y[0][1], y[1][1]);
		for (int i = 2; i <= razb; i++) {
			t[i] = t[0] + h * i;
			for (int j = 0; j < n; j++) {
				y[j][i] = y[j][i - 1] + h / 2 * (3 * F_2[j] - F_1[j]);
				file << t[i] << "\t" << y[j][i] << '\t';
				cout << t[i] << "\t" << y[j][i] << '\t';
			}
			file << endl;
			cout << endl;
			F_1 = F_2;
			F_2 = primer3(t[i], y[0][i], y[1][i]);
		}
		file.close();
		break;
	}
}