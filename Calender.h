#include <iostream>
#include <iomanip>
using namespace std;
class Calendar {
public:
	int year, month;
	Calendar(int year, int month) :year(year), month(month) {}
	void AddMonth() {
		month++;
		if (month == 13) {
			AddYear();
			month = 1;
		}
	}
	void MinusMonth() {
		month--;
		if (month == 0) {
			MinueYear();
			month = 12;
		}
	}
	void MinueYear() {
		year--;
	}
	void AddYear() {
		year++;
	}
	void DrawCalender() {
		int day[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		int days = 0;
		int first_data = 0;
		int count = 0;
		cout << setw(10)<<year << "³â " << month <<"¿ù " << endl;
		days = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
		for (int i = 0; i < month - 1; i++) {
			if (i == 1) {
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
					day[1] = 29;
				else
					day[1] = 28;
			}
			days += day[i];
		}
		first_data = days % 7;

		for (int i = 0; i <= first_data; i++) {
			cout << "\t";
			count++;
		}

		for (int i = 1; i <= day[month - 1]; i++) {
			if (count >= 7) {
				cout << endl;
				count = 0;
			}
			cout << i << "\t";
			count++;
		}
		cout << endl << endl;
	}
};