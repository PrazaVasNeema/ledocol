#include <iostream>
#include <math.h>
using namespace std;
# define pi           3.14159265358979323846
double integral(double, double, int);
double func(double);
void main() {
    double a, b, result;
    int N;
    cout << "a, b: ";
    cin >> a >> b;
    cout << "N: ";
    cin >> N;
    result = integral(a, b, N);
    cout << result;
}
double integral(double a, double b, int N) {
    double width = (b - a) / N;

    double integral = 0;
    for (int i = 0; i < N; i++) {
        const double x1 = a + i * width;
        const double x2 = a + (i + 1) * width;

        integral += 0.5 * (x2 - x1) * (func(x1) + func(x2));
    }

    return integral;
}
//double func(double x) {
//    return pow(x, 2);
//}
//double func(double x) {
//    return pow(sin(x), 2);
//}
double func(double x) {
    return 5/(exp(pi)+2)*exp(2*x)*cos(x);
}