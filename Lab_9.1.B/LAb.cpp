#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;
enum Spec { KN = 0, IT, M_end_E, Ph_end_I, L_E};
string SpecStr[] = { "КН", "ІТ","М_і_Екон", "Ф_і_Інф", "Труд"};

union Mark
{
	double prog_mark;
	double chys_mark;
	double ped_mark;
};

struct Student
{
	string prizv;
	int kurs;
	Spec spec;
	double physics_mark;
	double math_mark;
	Mark third_mark;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Student_Who_have_5(Student* p, const int N);
double LineSearch(Student* p, const int N);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;
	Student* p = new Student[N];

	double proc;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід прізвищ  студентів," << endl;
		cout << " які отримали з фізики оцінку 5 " << endl << endl;
		cout << " [4] - вивід прізвищ і процент студентів які вчаться на відмінно" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			cout << "Студенти які отримали з фізики 5:" << endl;
			Student_Who_have_5(p, N);
			break;
		case 4:
			proc = LineSearch(p, N);
			cout << "Процент студентів які вчаться на відмінно:" << endl;
			cout << proc << "%" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int specialnist;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;

		cin.get();
		cin.sync();

		cout << " Прізвище: "; getline(cin, p[i].prizv);
		cout << "Курс: "; cin >> p[i].kurs;
		cout << " Спеціальність (0 - КН, 1 - ІТ, 2 - М_і_Екон, 3 - Ф_і_Інф, 4 - Труд):  ";
		cin >> specialnist;
		p[i].spec = static_cast<Spec>(specialnist);

		cout << "Оцінка з Фізики: ";
		cin >> p[i].physics_mark;
		cout << "Оцінка з Математики: ";
		cin >> p[i].math_mark;
		
		switch (p[i].spec)
		{
		case KN:
			cout << "Оцінка з Програмування :";
			cin >> p[i].third_mark.prog_mark;
			break;
		case IT:
			cout << "Оцінка з Чис. метод :";
			cin >> p[i].third_mark.chys_mark;
			break;
		case M_end_E:
		case Ph_end_I:
		case L_E:
			cout << "Оцінка з Педагогіки :";
			cin >> p[i].third_mark.ped_mark;
			break;
		}

	}
}
void Print(Student* p, const int N)
{
	cout << "========================================================================================================="
		<< endl;
	cout << "| № | Прізвище  | Курс | Спеціальність  | Фізика | Математика | Програмування | Чис. мед  | Педагогіка |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(10) << left << p[i].prizv
			<< "| " << setw(5) << right << p[i].kurs
			<< "| ";
		switch (p[i].spec)
		{
		case KN: cout << setw(15) << "КН";
			break;
		case IT: cout << setw(15) << "ІТ";
			break;
		case M_end_E: cout << setw(15) << "М_і_Екон";
			break;
		case Ph_end_I: cout << setw(15) << "Ф_і_Інф";
			break;
		case L_E: cout << setw(15) << "Труд";
			break;
		}
		cout << "| " << setw(7) << right << p[i].physics_mark << "| "
			<< setw(11) << p[i].math_mark;
		switch (p[i].spec)
		{
		case KN:
			cout << "|" << setw(15) << left << p[i].third_mark.prog_mark;
			cout << "|" << setw(11) << left << "Н/О";
			cout << "|" << setw(12) << left << "Н/О";
			break;
		case IT:
			cout << "|" << setw(12) << left << "Н/О";
			cout << "|" << setw(12) << left << p[i].third_mark.chys_mark;
			cout << "|" << setw(12) << left << "Н/О";
			break;
		case M_end_E:
		case Ph_end_I:
		case L_E:
			cout << "|" << setw(15) << left << "Н/О";
			cout << "|" << setw(11) << left << "Н/О";
			cout << "|" << setw(12) << left << p[i].third_mark.ped_mark;
			break;
		}
		cout << "|" << endl;
	}
	cout << "========================================================================================================="
		<< endl;
	cout << endl;
}
double LineSearch(Student* p, const int N)
{
	cout << "Прізвища студентів які вчаться на відмінно:" << endl;
	int  n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].physics_mark == 5 && p[i].math_mark == 5 && (p[i].third_mark.chys_mark == 5 
			|| p[i].third_mark.ped_mark == 5 
			|| p[i].third_mark.prog_mark == 5 ))
		{
			n++;

			cout << setw(3) << right << n
				<< " " << p[i].prizv << endl;

		}
	}
	return n * 100.0 / N;
}
void Student_Who_have_5(Student* p, const int N)
{
	for (int i = 0; i < N; i++)
	{
		if (p[i].physics_mark == 5)
		{
			cout << p[i].prizv << endl;
		}
	}
}