#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
void out(double A[20][20], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << A[i][j] << "    ";
		cout << endl;
	}
	cout << endl;
}
void main() {
	setlocale(LC_ALL, "rus");
	double A[20][20], y[20], y_dlina = 0, x_prev[20], x_next[20];
	double vector_znach_prev[20], vector_znach_next[20], sobstv_znach_max = 0, eps;
	int N, counter;
	bool flag = true;
	string nomer;
	cout << "Выберете номер примера: ";
	//вывести примеры на экран
	cin >> nomer;
	fstream f("C://Limbo//Purgatory//To_wf//l//" + nomer + ".txt");
	f >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			f >> A[i][j];
		}
	}
	cout << endl << "Выбранная матрица:" << endl;
	out(A, N);
	f.close();

	double temp;
	double** E = new double* [N];
	for (int i = 0; i < N; i++)
		E[i] = new double[N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			E[i][j] = 0.0;

			if (i == j)
				E[i][j] = 1.0;
		}
	for (int k = 0; k < N; k++)
	{
		temp = A[k][k];
		for (int j = 0; j < N; j++)
		{
			A[k][j] /= temp;
			E[k][j] /= temp;
		}
		for (int i = k + 1; i < N; i++)
		{
			temp = A[i][k];
			for (int j = 0; j < N; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}
	for (int k = N - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = A[i][k];
			for (int j = 0; j < N; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			A[i][j] = E[i][j];
	out(A, N);

	cout << "Введите eps: ";
	cin >> eps;
	cout << "Первое приближение y0: ";
	for (int i = 0; i < N; i++) {
		cin >> y[i];
		y_dlina += y[i] * y[i];
	}
	y_dlina = sqrt(y_dlina);
	for (int i = 0; i < N; i++)
		x_next[i] = y[i] / y_dlina;
	for (int i = 0; i < N; i++)
		vector_znach_next[i] = 0;
	do {
		counter = 0;
		y_dlina = 0;
		for (int i = 0; i < N; i++) {
			vector_znach_prev[i] = vector_znach_next[i];
			x_prev[i] = x_next[i];
		}
		for (int i = 0; i < N; i++) {
			y[i] = 0;
			for (int j = 0; j < N; j++) {
				y[i] += A[i][j] * x_next[j];
			}
			y_dlina += y[i] * y[i];
		}
		y_dlina = sqrt(y_dlina);
		for (int i = 0; i < N; i++)
			x_next[i] = y[i] / y_dlina;
		for (int i = 0; i < N; i++) {
			if (abs(x_prev[i]) < 0.1) {
				vector_znach_next[i] = 0;
				continue;
			}
			vector_znach_next[i] = y[i] / x_next[i];
			counter++;
		}
		for (int i = 0; i < N; i++) {
			if (vector_znach_prev[i] == 0 || vector_znach_next[i] == 0)
				continue;
			if (abs(vector_znach_next[i] - vector_znach_prev[i]) <= eps) {
				flag = 0;
				break;
			}
		}
	} while (flag);
	for (int i = 0; i < N; i++) {
		sobstv_znach_max += vector_znach_next[i];
	}
	sobstv_znach_max /= counter;
	cout << "Максимальное собственное значение: " << setprecision(8) << sobstv_znach_max;
	cout << "\nМаксимальный собственный вектор: ";
	for (int i = 0; i < N; i++) {
		cout << setprecision(8) << x_next[i] << "    ";
	}
	cout << endl;
	system("pause");
}