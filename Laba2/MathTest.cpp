#include <iostream>
#include "Poly.h"
#include "LetterGenerator.h"
#include "StudentsPerformance.h"

using namespace std;

int main() {
	stack <letter> mail;
	mail = CreateLetter();
	TableOfPerformance(mail);
	return 0;
}