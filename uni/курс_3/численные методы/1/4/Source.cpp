#include <iostream>
#include <math.h>
using namespace std;

#define Y1(x) pow(x,3)/3
#define Y2(x) pow(x,3)/3*(1+pow(x,4)/21)
#define Y3(x) pow(x,3)/3*(1+pow(x,4)/21+2*pow(x,8)/693+pow(x,12)/19845)

void main()
{
    double a = 0, b = 2, step = 0.2;
    bool f = 1;
    cout << "X: \n";
    for (double i = a; i <= b; i += step) {
        printf("%*f ", 8, i);
        if (i >= 1 && f) {
            printf("%s ", "|");
            f = 0;
        }
    }
    cout << endl;
    cout << "\nY1: \n";
    f = 1;
    for (double i = a; i <= b;i+=step) {
        printf("%*f ",8, Y1(i));
        if (i >= 1 && f) {
            printf("%s ", "|");
            f = 0;
        }
    }
    cout << "\nY2: \n";
    f = 1;
    for (double i = a; i <= b; i += step) {
        printf("%*f ", 8, Y2(i));
        if (i >= 1 && f) {
            printf("%s ", "|");
            f = 0;
        }
    }
    cout << "\nY3: \n";
    f = 1;
    for (double i = a; i <= b; i += step) {
        printf("%*f ", 8, Y3(i));
        if (i >= 1 && f) {
            printf("%s ", "|");
            f = 0;
        }
    }
    cout << endl;
    system("pause");
}