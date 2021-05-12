#pragma once
#include <iostream>

using namespace std;

struct Answer {
	double  ans1, ans2;
	bool roots;
};

enum ERROR {
	NO_ROOTS,
};

	Answer Equasion(double a, double b, double c) {
		double D = b * b - 4 * a * c;
		Answer ans;

		if (D >= 0) {
			ans.roots = true;
			ans.ans1 = (-b + sqrt(D)) / (2 * a);
			ans.ans2 = (-b - sqrt(D)) / (2 * a);
		}
		else {
			ans.ans1 = NO_ROOTS;
			ans.ans1 = NO_ROOTS;
			ans.roots = false;
		}
		return ans;
	};


