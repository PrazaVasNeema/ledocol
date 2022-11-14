#include <iostream>
#include <fstream>
using namespace std;

double lag(double cur_x, double x[20], double y[20], int N) {
	double sum = 0;
	for (int i = 0; i < N; i++) {
		double mult = 1;
		for (int j = 0; j < N; j++) {
			if (i != j) mult *= (cur_x - x[j]) / (x[i] - x[j]);
		}
		sum += y[i] * mult;
	}
	return sum;
}

void main() {
	double a, b, cur_x, x[20], y[20];
	int points_am, N, in;
	cout << "0, 1: ";
	int numm;
	cin >> numm;
	string num;
	switch (numm) {
	case 0:
		num = "0";
		break;
	case 1:
		num = "1";
		break;
	}
	ifstream func("V://2_func_" + num + ".txt");
	ofstream res("V://res.txt", ios::trunc);
	func >> N;
	cout << "points_am: ";
	cin >> points_am;
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	for (int i = 0; i < N * 2; i++)
		func >> x[i] >> y[i];
	func.close();
	for (int i = 0; i < points_am; i++) {
		cur_x = a + (b - a) / (points_am - 1) * i;
		cout << cur_x << '\t' << lag (cur_x, x, y, N) << endl;
		res << cur_x << '\t' << lag(cur_x, x, y, N) << '\n';
	}
	system("pause");
}