// Lab_9_1
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <stdlib.h>
using namespace std;

enum StudentProfession : unsigned short {
	StudentProfession_ComputerScience = 0, // Комп’ютерні науки // програмування
	StudentProfession_Informatics, // Інформатика // чисельних методів
	StudentProfession_MathematicsEconomics, // Математика та економіка // педагогіки
	StudentProfession_PhysicsComputerScience, //  Фізика та інформатика // педагогіки
	StudentProfession_WorkTraining // Трудове навчання // педагогіки
};

enum StudentSubject : unsigned short {
	StudentSubject_Physics = 0,
	StudentSubject_Math,
	StudentSubject_Programming,
	StudentSubject_NumericalMethods,
	StudentSubject_Pedagogy
};

struct Student {
	string lastname; // прізвище
	unsigned short course; // курс
	StudentProfession profession; // спеціальність

	unsigned short mark_physics; // фізика
	unsigned short mark_math; // математика
	union
	{
		unsigned short programming; // програмування
		unsigned short numerical_methods; // чисельних методів
		unsigned short pedagogy; // педагогіки
	};
};

Student* studentFactory(const int& count) {
	Student* st = new Student[count];
	int prof;
	for (int i = 0; i < count; i++)
	{
		cout << endl << "Student № " << i + 1 << ":" << endl;
		cin.ignore(); // очищуємо буфер клавіатури – бо залишаються символи
		// "кінець рядка", які не дають ввести наступний літерний рядок
		cout << "Lastname: "; getline(cin, st[i].lastname);
		cout << "Course  : "; cin >> st[i].course;
		cout << "Professions:\n0 - Computer science\n1 - Informatics\n2 - Mathematics and economics\n3 - Physics and computer science\n4 - Work training\nSelect profession: ";
		cin >> prof; st[i].profession = (StudentProfession)prof;
		switch (st[i].profession)
		{
		case StudentProfession_ComputerScience:
			cout << "Mark of programming:";
			break;
		case StudentProfession_Informatics:
			cout << "Mark of numerical methods:";
			break;
		case StudentProfession_MathematicsEconomics:
		case StudentProfession_PhysicsComputerScience:
		case StudentProfession_WorkTraining:
			cout << "Mark of pedagogy:";
		}
		cin >> st[i].programming;
		cout << "Mark of physics:"; cin >> st[i].mark_physics;
		cout << "Mark of math:"; cin >> st[i].mark_math;
	}
	return st;
}

void darwStudents(Student* st, const int& count)
{
	cout << "=============================================================================================================" << endl;
	cout << "| № | Lastname | Course | Profession            | Physics | Math | Programming | Numerical methods | Pedagogy" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << "| " << setw(2) << i + 1
			<< "| " << setw(9) << st[i].lastname
			<< "| " << setw(7) << st[i].course;

		switch (st[i].profession)
		{
		case StudentProfession_ComputerScience:
			cout << "| " << setw(28) << "Computer science";
			break;
		case StudentProfession_Informatics:
			cout << "| " << setw(28) << "Informatics";
			break;
		case StudentProfession_MathematicsEconomics:
			cout << "| " << setw(28) << "Mathematics and economics";
		case StudentProfession_PhysicsComputerScience:
			cout << "| " << setw(28) << "Physics and computer science";
		case StudentProfession_WorkTraining:
			cout << "| " << setw(28) << "Work training";
		}
		cout << "| " << setw(8) << st[i].mark_physics
			<< "| " << setw(5) << st[i].mark_math;

		switch (st[i].profession)
		{
		case StudentProfession_ComputerScience:
			cout << "| " << setw(12) << st[i].programming
				<< "| " << setw(18) << " "
				<< "| " << setw(8) << " ";
			break;
		case StudentProfession_Informatics:
			cout << "| " << setw(12) << " "
				<< "| " << setw(18) << st[i].programming
				<< "| " << setw(8) << " ";
			break;
		case StudentProfession_MathematicsEconomics:
		case StudentProfession_PhysicsComputerScience:
		case StudentProfession_WorkTraining:
			cout << "| " << setw(12) << " "
				<< "| " << setw(18) << " "
				<< "| " << setw(8) << st[i].programming;
		}
		cout << endl;
	}
	cout << "==========================================================================================================" << endl;
	cout << endl;
}

int get_min_avarage_student(const Student* st, const int& count) {
	int min = 0;
	float l_min = (st->mark_math + st->mark_physics + st->programming) / 3., c_min;
	for (int i = 1; i < count; i++)
	{
		c_min = (st[i].mark_math + st[i].mark_physics + st[i].programming) / 3.;
		if (c_min < l_min) {
			l_min = c_min;
			min = i;
		}
	}
	return min;
}

int get_count_marks(const Student* st, const int& count, const unsigned int &mark, const StudentSubject& subject) {
	unsigned int ok_count = 0;
	const unsigned short* tmp_mark;
	for (int i = 0; i < count; i++)
	{
		if (subject < StudentSubject_Programming)
			tmp_mark = (const unsigned short*)(reinterpret_cast<const char*>(st + i) + sizeof(string) + sizeof(unsigned short) * (2 + subject));
		else if ((st[i].profession > 1 && subject == StudentSubject_Pedagogy) ||
			(st[i].profession == StudentProfession_ComputerScience && subject == StudentSubject_Programming) ||
			(st[i].profession == StudentProfession_Informatics && subject == StudentSubject_NumericalMethods))
			tmp_mark = (const unsigned short*)(reinterpret_cast<const char*>(st + i) + sizeof(string) + sizeof(unsigned short) * 4);
		else tmp_mark = nullptr;

		if (tmp_mark != nullptr && *tmp_mark == mark)
			ok_count++;
	}
	return ok_count;
}

void main() {
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	cout.setf(ios_base::left);

	int count;
	cout << "Input count: "; cin >> count;

	Student* st = studentFactory(count);
	darwStudents(st, 2);
	cout << endl <<  "Min avarage mark: " << st[get_min_avarage_student(st, count)].lastname << endl;
	cout << "Count ok marks of physics: " << get_count_marks(st, count, 3, StudentSubject_Physics) << endl;
	cout << "Count ok marks of math   : " << get_count_marks(st, count, 3, StudentSubject_Math) << endl;
	cout << "Count ok marks of programming: " << get_count_marks(st, count, 3, StudentSubject_Programming) << endl;
	cout << "Count ok marks of numerical methods: " << get_count_marks(st, 2, 3, StudentSubject_NumericalMethods) << endl;
	cout << "Count ok marks of pedagogy: " << get_count_marks(st, count, 3, StudentSubject_Pedagogy) << endl;

	// test

	/*Student* st = new Student[2];
	st->lastname = "asdasdd";
	st->profession = StudentProfession_ComputerScience;
	st->course = 2;
	st->mark_physics = 3;
	st->mark_math = 3;
	st->programming = 4;
	st[1].lastname = "asdasd";
	st[1].profession = StudentProfession_ComputerScience;
	st[1].course = 1;
	st[1].mark_physics = 3;
	st[1].mark_math = 3;
	st[1].programming = 3;
	darwStudents(st, 2);
	cout << "Min avarage mark: " << st[get_min_avarage_student(st, 2)].lastname << endl;
	cout << "Count ok marks of physics: " << get_count_marks(st, 2, 3, StudentSubject_Physics) << endl;
	cout << "Count ok marks of math   : " << get_count_marks(st, 2, 3, StudentSubject_Math) << endl;
	cout << "Count ok marks of programming: " << get_count_marks(st, 2, 3, StudentSubject_Programming) << endl;
	cout << "Count ok marks of numerical methods: " << get_count_marks(st, 2, 3, StudentSubject_NumericalMethods) << endl;
	cout << "Count ok marks of pedagogy: " << get_count_marks(st, 2, 3, StudentSubject_Pedagogy) << endl;*/

	delete[] st;
}