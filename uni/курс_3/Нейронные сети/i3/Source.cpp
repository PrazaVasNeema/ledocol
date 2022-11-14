#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int heaviside(double x) {
	if (x <= 0)
		return 0;
	else
		return 1;
}



void main() {
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> rand_value(1, 100);
	uniform_int_distribution<mt19937::result_type> rand_sign(1, 2);

	setlocale(LC_ALL, "ru");

	ifstream f("f.txt");
	ifstream f_test("test.txt");
	ofstream f_result("result.txt");


	double w[15][2], y1 = 0, y2 = 0, test[19][15], x_y[14][17], epohi, delta[2], eta;
	cout << "Количество эпох: ";
	cin >> epohi;
	cout << "Скорость обучения: ";
	cin >> eta;
	cout << "Матрица весов ребер W до обучения: " << endl;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 2; j++) {
			w[i][j] = rand_sign(rng) == 1 ? rand_value(rng) / 100.000 : rand_value(rng) / 100.000 * -1;
			cout << w[i][j] << '\t';
		}
		cout << endl;
	}

	cout << "Обучающая выборка: ";
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 17; j++) {
			f >> x_y[i][j];
			cout << x_y[i][j] << '\t';
		}
		cout << endl;
	}
	int epoha, error;
	for (epoha = 0, error = 0; epoha < epohi; epoha++, error = 0) {
		for (int i = 0; i < 14; i++) {
			for (int j = 0; j < 15; j++) {
				y1 += x_y[i][j] * w[j][0];
				y2 += x_y[i][j] * w[j][1];
			}
			y1 = heaviside(y1);
			y2 = heaviside(y2);
			delta[0] = x_y[i][15] - y1;
			delta[1] = x_y[i][16] - y2;
			error += max(abs(delta[0]), abs(delta[1]));
			for (int j = 0; j < 15; j++) {
				w[j][0] += eta * x_y[i][j] * delta[0];
				w[j][1] += eta * x_y[i][j] * delta[1];
			}
		}
		if (error == 0)
			break;
	}
	
	cout << endl << "epoha: " << epoha << endl;

	cout << "Матрица весов ребер W после обучения: " << endl;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 2; j++) {
			cout << w[i][j] << '\t';
		}
		cout << endl;
	}

	cout << "Подтверждающая и тестовая выборки: " << endl;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 15; j++) {
			f_test >> test[i][j];
			cout << test[i][j] << '\t';
		}
		if (i == 13)
			cout << endl;
		cout << endl;
	}

	cout << "Результат: " << endl;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 15; j++) {
			y1 += test[i][j] * w[j][0];
			y2 += test[i][j] * w[j][1];
		}
		cout << heaviside(y1) << '\t' << heaviside(y2) << endl;
		f_result << heaviside(y1) << ' ' << heaviside(y2) << endl;
		y1 = 0;
		y2 = 0;
		if (i == 13)
			cout << endl;
	}
}