#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int OneOrZero(double x) {
	if (x <= 0)
		return 0;
	else
		return 1;
}

void main() {
	random_device dev;
	mt19937 rand_this(dev());
	uniform_int_distribution<mt19937::result_type> rand_value(1, 100);
	uniform_int_distribution<mt19937::result_type> rand_value_sign(1, 2);

	ifstream f_sample("sample.txt");
	ifstream f_test("test.txt");
	ofstream f_result("result.txt");


	double w[15][2], y1 = 0, y2 = 0, test[20][15], x_y[20][17], gens, delta[2], eta, cur_gen, error;
	cout << "Gens: ";
	cin >> gens;
	cout << "Eta: ";
	cin >> eta;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 2; j++) {
			w[i][j] = rand_value_sign(rand_this) == 1 ? rand_value(rand_this) / 100.000 : rand_value(rand_this) / 100.000 * -1;
		}
	}

	cout << "\nLearning samples: \n";
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			f_sample >> x_y[i][j];
			cout << x_y[i][j] << '\t';
		}
		cout << endl << endl;
	}

	for (cur_gen = 0, error = 0; cur_gen < gens; cur_gen++, error = 0) {
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 15; j++) {
				y1 += x_y[i][j] * w[j][0];
				y2 += x_y[i][j] * w[j][1];
			}
			y1 = OneOrZero(y1);
			y2 = OneOrZero(y2);
			delta[0] = x_y[i][15] - y1;
			delta[1] = x_y[i][16] - y2;
			error += max(abs(delta[0]), abs(delta[1]));
			for (int j = 0; j < 15; j++) {
				w[j][0] += eta * x_y[i][j] * delta[0];
				w[j][1] += eta * x_y[i][j] * delta[1];
			}
		}
		if (error == 100)
			break;
	}

	cout << endl << "gen: " << cur_gen << endl;

	cout << "Test samples: " << endl;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 15; j++) {
			f_test >> test[i][j];
			cout << test[i][j] << '\t';
		}
		if (i == 12)
			cout << endl;
		cout << endl;
	}

	cout << "Result: " << endl;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 15; j++) {
			y1 += test[i][j] * w[j][0];
			y2 += test[i][j] * w[j][1];
		}
		cout << OneOrZero(y1) << '\t' << OneOrZero(y2) << endl;
		f_result << OneOrZero(y1) << ' ' << OneOrZero(y2) << endl;
		y1 = 0;
		y2 = 0;
		if (i == 12)
			cout << endl;
	}
}