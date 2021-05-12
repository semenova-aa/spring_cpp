#pragma once
#include <iostream>
#include <iomanip>
#include <stack>
#include "LetterGenerator.h"
#include "Poly.h"

using namespace std;

struct student {
	string name;
	int amountOfCorrectAns = 0;
};

int Check(Answer ans, Answer correctAns) {
	if (ans.ans1 == correctAns.ans1 && ans.ans2 == correctAns.ans2)
		return 1;
	else
		return 0;
}

void TableOfPerformance(stack <letter> mails) {
	student obj[5];
	while (!mails.empty()) {
		if (mails.top().name == "Ivanov") {
			obj[0].name = "Ivanov";
			obj[0].amountOfCorrectAns += Check(mails.top().answer, mails.top().correct);
		};
		if (mails.top().name == "Petrov") {
			obj[1].name = "Petrov";
			obj[1].amountOfCorrectAns += Check(mails.top().answer, mails.top().correct);
		};
		if (mails.top().name == "Sidorov") {
			obj[2].name = "Sidorov";
			obj[2].amountOfCorrectAns += Check(mails.top().answer, mails.top().correct);
		};
		if (mails.top().name == "Artyomov") {
			obj[3].name = "Artyomov";
			obj[3].amountOfCorrectAns += Check(mails.top().answer, mails.top().correct);
		};
		if (mails.top().name == "Semenov") {
			obj[4].name = "Semenov";
			obj[4].amountOfCorrectAns += Check(mails.top().answer, mails.top().correct);
		};
		mails.pop();
	};
	cout << setw(25) << "Correctness" << endl;
	for (int i = 0; i < 5; i++) {
		cout << setw(10) << obj[i].name << setw(10) << obj[i].amountOfCorrectAns << endl;
	}
};
