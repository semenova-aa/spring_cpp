#include <iostream>

using namespace std;

void  Equasion(double a, double b, double c) {
	double D = b*b-4*a*c;
	if (D >= 0) {
		cout << "First root: " << (-b + sqrt(D)) / (2 * a) << endl;
		cout << "Second root: " << (-b - sqrt(D)) / (2 * a) << endl;
	}
	else {
		cout << "Roots are irrational";
	}
}

int main() {
	double a, b, c;
	cin >> a >> b >> c;
	Equasion(a, b, c);
	return 0;
}