#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void RK3_2(double* t, double* y, double h, double n, double(*F) (double, double), string nomer) {
	double k1, k2, k3;
	ofstream file("Z://chm//2//file_" + nomer + ".txt");
	file << t[0] << "\t" << y[0] << '\t';
	cout << t[0] << "\t" << y[0] << '\t';
	file << endl;
	cout << endl;
	for (int i = 0; i < n; i++) {
		t[i+1] = t[0] + h*(i+1);
		k1 = F(t[i], y[i]);
		k2 = F(t[i] + h / 3, y[i] + h*k1 / 3);
		k3 = F(t[i] + 2 * h / 3, y[i] + 2 * h * k2 / 3);
		y[i + 1] = y[i] + h / 4 * (k1 + 3 * k3);
		file << t[i+1] << "\t" << y[i+1] << '\t';
		cout << t[i+1] << "\t" << y[i+1] << '\t';
		file << endl;
		cout << endl;
	}
	file.close();
}
double nomer1(double t, double y) {
	return 1 / (t + 2 * y);
}
double nomer2(double t, double y) {
	return 1 + 2 * y / t;
}
double nomer3(double t, double y) {
	return 2 * pow(t, 3) + 2 * y / t;
}
double nomer4(double t, double y) {
	return 2 * y / t + 2 * t * sqrt(y);
}
double nomer5(double t, double y) {
	return t / (t * t - 2 * y + 1);
}
void main() {
	int nomer, n;
	cout << "nomer: ";
	cin >> nomer;
	cout << "n: ";
	cin >> n;
	double* t = new double[n], * y = new double[n], T, h;
	switch(nomer) {
	case 1:
		t[0] = 0;
		y[0] = -1;
		cout << "konec: ";
		cin >> T;
		h = (T - t[0]) / n;
		RK3_2(t, y, h, n, nomer1, to_string(nomer));
		break;
	case 2:
		t[0] = 1;
		y[0] = 0;
		cout << "konec: ";
		cin >> T;
		h = (T - t[0]) / n;
		RK3_2(t, y, h, n, nomer2, to_string(nomer));
		break;
	case 3:
		t[0] = 1;
		y[0] = 2;
		cout << "konec: ";
		cin >> T;
		h = (T - t[0]) / n;
		RK3_2(t, y, h, n, nomer3, to_string(nomer));
		break;
	case 4:
		t[0] = 1;
		y[0] = 1;
		cout << "konec: ";
		cin >> T;
		h = (T - t[0]) / n;
		RK3_2(t, y, h, n, nomer4, to_string(nomer));
		break;
	case 5:
		t[0] = 6.34;
		y[0] = 1.8;
		cout << "konec: ";
		cin >> T;
		h = (T - t[0]) / n;
		RK3_2(t, y, h, n, nomer5, to_string(nomer));
		break;
	}
	system("pause");
}