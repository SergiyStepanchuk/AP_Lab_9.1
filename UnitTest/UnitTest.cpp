#include "pch.h"
#include "CppUnitTest.h"
#include "../Program/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(met_get_min_avarage_student)
		{
			Student* st = new Student[2];
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

			Assert::AreEqual(get_min_avarage_student(st, 2), 1);
			delete[] st;
		}
	};
}
