#pragma once
#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>  
#include "Poly.h"

struct letter {
	double a = 0, b = 0, c = 0;
	Answer answer;
	string name;
	Answer correct;
};


string students[5] = { "Ivanov", "Petrov", "Sidorov", "Artyomov", "Semenov" };

using namespace std;

	stack <letter> CreateLetter() {
		stack <letter> mail;
		vector<string> nums;
		string num;
		letter letter;
		int counter = 0;
		ifstream task("tasks.txt");
		if (task.is_open()) {
			while (task >> num)
				nums.push_back(num);
			while (counter < nums.size()) {
				letter.a = stoi(nums[counter++]);
				letter.b = stoi(nums[counter++]);
				letter.c = stoi(nums[counter++]);

				//Вносим решения студентов
				for (int i = 0; i < sizeof(students)/sizeof(students[0]); i++) {
					letter.answer = Equasion(letter.a, letter.b, letter.c);
					letter.correct = Equasion(letter.a, letter.b, letter.c);
					//Если решения есть
					if (Equasion(letter.a, letter.b, letter.c).roots == true) {
						if (students[i] == "Ivanov" || students[i] == "Sidorov") {
							letter.answer.ans2 += (rand() % 3);
						}
						else if (students[i] == "Petrov")
							letter.answer.ans1 += (rand() % 4 + 1);
					}
					//Если решений нет
					else {
						if (students[i] == "Ivanov" || students[i] == "Sidorov") {
							if (rand()%1 == 1)
							letter.answer.ans1 = (rand() % 3);
							letter.answer.ans2 = (rand() % 3);
						}
						else if (students[i] == "Petrov")
							letter.answer.ans1 = (rand() % 10);
					}
					letter.name = students[i];
					mail.push(letter);
				}
			}


			
		};
		task.close();    
		return mail;
	};


