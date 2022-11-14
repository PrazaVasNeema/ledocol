#include<iostream>
#include<omp.h>
#include <chrono> // для функций из std::chrono
using namespace std;
class Timer
{
private:
	// Псевдонимы типов используются для удобного доступа к вложенным типам
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
int main()
{
	long int original_massiv[10000], count[10000], result_mas[10000];
	long int i, j, n = 0, N;
	cin >> N;
	for (i = 0; i < N; i++) {
		count[i] = 0;
		result_mas[i] = 0;
	}
	Timer t;
	cout << "massiv: " << endl;
	for (i = 0; i < N; i++) {
		original_massiv[i] = getRandomNumber(1,100);
	}
	for (i = 0; i < N; i++) {
		cout << original_massiv[i] << " ";
	}
	cout << endl;
#pragma omp parallel num_threads(1)
	{
#pragma omp for
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (original_massiv[i] > original_massiv[j]) {
					count[i]++;
				}
			}
		}
#pragma omp for
		for (i = 0; i < N; i++) {
			while (result_mas[count[i]] != 0)count[i]++;
			result_mas[count[i]] = original_massiv[i];
		}
	}
	cout << "result :" << endl;
	for (i = 0; i < N; i++) {
		cout << result_mas[i] << " ";
	}
	cout << endl;
	std::cout << "Time taken: " << t.elapsed() << '\n';
	system("pause");
}