#define  _CRT_SECURE_NO_WARNINGS
#include<conio.h>
#include <winsock2.h>
#include <windows.h>
#include<iostream>
#include<string>
#include <my_global.h>
#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")
using namespace std;

#define BLACK 0
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3 
#define ENTER 4
using namespace std;
int MainPrint();
void printLogo();
void textcolor(int foreground, int background) {
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int keyControl() {
	int temp = _getch();
	if (temp == 72) {
		return UP;
	}
	else if (temp == 75) {
		return LEFT;
	}
	else if (temp == 80) {
		return DOWN;
	}
	else if (temp == 77) {
		return RIGHT;
	}
	else if (temp == 13) {
		return ENTER;
	}
}
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
	void DrawCalender(int temp) {
		int first;
		int sum = 0;
		int isyoon = 0;
		int basicyear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; // �⺻ 1~12�� �ϼ�
		gotoxy(40, 8);
		cout << year << "��" << month << "��";
		if (yoon(year)) {
			isyoon = 1;
			basicyear[1]++;
		}
		else
			isyoon = 0;
		sum = 365;
		for (int i = 1; i < year; i++) {
			if (yoon(i))
				sum += 366;
			else
				sum += 365;
		}
		for (int i = 0; i < month - 1; i++) {
			sum += basicyear[i];
		}
		first = sum % 7;
		gotoxy(40, 10);
		printf("SUN\tMON\tTUS\tWED\tTHU\tFRI\tSAT\n");
		gotoxy(40, 11);
		int h = 11;
		int w = 40;
		printf("\n");
		gotoxy(w, h++);
		for (int j = 0; j < first; j++) {
			printf("\t");
		}
		gotoxy(w, h++);
		for (int i = 1; i <= basicyear[month - 1]; i++) {
			cout << i << "\t";
			if (first == 6) {
				first = -1;
				cout << "\t";
				gotoxy(w, h++);
			}
			first++;
		}
		cout << endl;
	}
	int yoon(int a) {
		if ((a % 4 == 0) && !(a % 100 == 0) || (a % 400 == 0)) {
			return 1;
		}
		else {
			return 0;
		}
	}
};
class Maneger {
private:
	std::string Id;
	std::string Password;
	std::string Name;
	std::string Birth;
public:
	Maneger() {
		this->Id = "MIrimHos872";
		this->Password = "MirimMeister872!";
	}
	void loginPress() {
		std::string menu[2] = { "      id :", "Password :" };
		std::string id;
		std::string password;
		bool loginok = false;
		std::string mode = "";
		int key = 2;
		do {
			std::system("cls");
			gotoxy(40, 10);
			textcolor(BLACK, WHITE);
			std::cout << "�Ŵ��� ���� �α����� �ʿ��մϴ�.";
			gotoxy(40, 11);
			textcolor(BLACK, WHITE);
			std::cout << "���ΰ��� : m";
			for (int i = 0; i < 2; i++) {
				gotoxy(45, 13 + (i * 2));
				std::cout << menu[i];
			}
			int temp = 0;
			key = keyControl();
			switch (key)
			{
			case UP: temp--;
				if (temp == -1) temp = 0;
				for (int i = 0; i < 2; i++) {
					if (i == temp) {
						textcolor(BLUE, WHITE);
						gotoxy(45, 13 + (i * 2));
						std::cout << menu[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(45, 13 + (i * 2));
						std::cout << menu[i];
					}
				}
				gotoxy(55, 13 + (temp * 2));
				std::cin >> id;
			case DOWN: temp++;
				if (temp == 3) temp = 2;
				for (int i = 0; i < 2; i++) {
					if (i == temp) {
						textcolor(BLUE, WHITE);
						gotoxy(45, 13 + (i * 2));
						std::cout << menu[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(45, 13 + (i * 2));
						std::cout << menu[i];
					}
				}
				gotoxy(55, 13 + (temp * 2));
				std::cin >> password;

			case ENTER:
				if (login(id, password)) {
					loginok = true;
				}
				else {
					gotoxy(45, 25);
					textcolor(BLACK, WHITE);
					std::cout << "ID, PASSWORD�� ���� ���� �ʽ��ϴ�.";
				}
				Sleep(1500);
				break;
			case 109: MainPrint();
			}
		} while (loginok == false);
	}
	bool login(std::string id, std::string password) {
		if (this->Id == id && this->Password == password) {
			return 1;
		}
		else {
			return 0;
		}
	};
	void drawMainMenuManeger() {
		int key;
		std::string menu[3] = { "�˻� ����Ʈ","���� ����Ʈ" ,"    MAIN"};
		int temp = 0;
		std::string mode;
		system("cls");
		gotoxy(40, 11);
		textcolor(BLACK, WHITE);
		for (int i = 0; i < 3; i++) {
			if (i == temp) {
				gotoxy(55, 13 + i);
				textcolor(BLUE, WHITE);
				std::cout << "              " << std::endl;
				gotoxy(55, 13 + i);
				std::cout << menu[i] << std::endl;
				mode = menu[i];
			}
			else {
				gotoxy(55, 13 + i);
				textcolor(BLACK, WHITE);
				std::cout << "              " << std::endl;
				gotoxy(55, 13 + i);
				std::cout << menu[i] << std::endl;
			}
		}
		do {
			key = keyControl();
			switch (key)
			{
			case UP: temp--;
				if (temp == -1) {
					temp = 2;
				}
				for (int i = 0; i < 3; i++) {
					if (i == temp) {
						gotoxy(55, 13 + i);
						textcolor(BLUE, WHITE);
						std::cout << "              " << std::endl;
						gotoxy(55, 13 + i);
						std::cout << menu[i] << std::endl;
						mode = menu[i];
					}
					else {
						gotoxy(55, 13 + i);
						textcolor(BLACK, WHITE);
						std::cout << "              " << std::endl;
						gotoxy(55, 13 + i);
						std::cout << menu[i] << std::endl;
					}
				}
				break;
			case DOWN:
				temp++;
				if (temp == 3) {
					temp = 0;
				}
				for (int i = 0; i < 3; i++) {
					if (i == temp) {
						gotoxy(55, 13 + i);
						textcolor(BLUE, WHITE);
						std::cout << "                          " << std::endl;
						gotoxy(55, 13 + i);
						std::cout << menu[i] << std::endl;
						mode = menu[i];
					}
					else {
						gotoxy(55, 13 + i);
						textcolor(BLACK, WHITE);
						std::cout << "                        " << std::endl;
						gotoxy(55, 13 + i);
						std::cout << menu[i] << std::endl;
					}
				}
				break;
			case 109: MainPrint();
			}
		} while (key != ENTER);
		gotoPage(mode);
	}
	void gotoPage(std::string modes) {
		if (modes == "�˻� ����Ʈ") {
			printExamAppointment();
		}
		else if (modes == "���� ����Ʈ") {
			printDefaultAppointment();
		}
		else if (modes == "    MAIN") {
			system("cls");
			MainPrint();
		}
	}
	void printExamAppointment() {
		int key = 0;
		int temp = 0;
		system("cls");
		string year;
		string month;
		string day;
		gotoxy(50, 10);
		textcolor(BLACK, WHITE);
		std::cout << "��ȸ�� ���ϴ� ���� �Է����ּ���.";
		system("cls");
		gotoxy(40, 11);
		textcolor(BLACK, WHITE);
		gotoxy(35, 12);
		textcolor(BLACK, WHITE);
		std::cout << "�⵵ �� ���� ���� �Է����ּ���.(exam 2020 8 20)";
		gotoxy(45, 15);
		std::cout << "________________________";
		gotoxy(45, 14);
		std::cin >> year;
		gotoxy(49, 14);
		std::cout << "��";
		gotoxy(52, 14);
		std::cin >> month;
		gotoxy(54, 14);
		std::cout << "��";
		gotoxy(57, 14);
		std::cin >> day;
		gotoxy(59, 14);
		std::cout << "��";
		system("cls");
		gotoxy(40, 8);
		std::cout << "��ȸ�� ���Ͻô� �˻縦 �Է����ֽʽÿ�." << std::endl;
		std::string Exam[] = { "�κ� ���ð�","�κ� �ܼ���缱�Կ�","�˷����� �Ǻ� ����","�˷����� ���� �׿�"
		,"�๰ ����","���� �� ��⵵","�İ� ���� ���","�κ� ��ǻ�� �����Կ�(OMU CT)","�κ� �ڱ�������Կ�(MRI)"};
		for (int i = 0; i < 9; i++) {
			gotoxy(45, 10 + i);
			cout << Exam[i];
		}
		key = 0;
		temp = 0;
		std::string ExamSelect = "�κ� ���ð�";
		do {
			key = keyControl();
			switch (key)
			{
			case UP:
				temp--;
				if (temp == -1) temp = 8;
				for (int i = 0; i < 9; i++) {
					if (i == temp) {
						textcolor(BLUE, WHITE);
						gotoxy(45, 10 + i);
						std::cout << "                             " << std::endl;
						gotoxy(45, 10 + i);
						std::cout << Exam[i];
						ExamSelect = Exam[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(45, 10 + i);
						std::cout << "                             " << std::endl;
						gotoxy(45, 10 + i);
						std::cout << Exam[i];
					}
				}
			case DOWN:
				temp++;
				if (temp == 9) temp = 0;
				for (int i = 0; i < 9; i++) {
					if (i == temp) {
						textcolor(BLUE, WHITE);
						gotoxy(45, 10 + i);
						std::cout << Exam[i];
						ExamSelect = Exam[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(45, 10 + i);
						std::cout << Exam[i];
					}
				}
			}
		} while (key != ENTER);
		system("cls");
		std::string menu[2] = { "��ü ��ȸ","�̸� �˻� ��ȸ" };
		key = 0;
		temp = 0;
		for (int i = 0; i < 2; i++) {
			if (temp == i) {
				textcolor(BLUE, WHITE);
				gotoxy(45, 13 + i);
				std::cout << menu[i];
			}
			else {
				textcolor(BLACK, WHITE);
				gotoxy(45, 13 + i);
				std::cout << menu[i];
			}
		}
		do
		{
			key = keyControl();
			switch (key)
			{
			case UP:
				temp--;
				if (temp == -1) temp = 0;
				for (int i = 0; i < 2; i++) {
					if (temp == i) {
						textcolor(BLUE, WHITE);
						gotoxy(45, 13 + i);
						std::cout << menu[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(45, 13 + i);
						std::cout << menu[i];
					}
				}
			case DOWN:
				temp++;
				if (temp == 2) temp = 1;
				for (int i = 0; i < 2; i++) {
					if (temp == i) {
						textcolor(BLUE, WHITE);
						gotoxy(45, 13 + i);
						cout << menu[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(45, 13 + i);
						cout << menu[i];
					}
				}
			}
		} while (key != ENTER);
		if (temp == 0) {
			system("cls");
			MYSQL* conn, connection;
			MYSQL_RES* result;
			MYSQL_ROW row;
			char DB_HOST[] = "localhost";
			char DB_USER[] = "root";
			char DB_PASS[] = "1111";
			char DB_NAME[] = "PATI";
			char sql[1024];
			char str1[1024];
			mysql_init(&connection);
			conn = mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
			char find_day[9];
			strcat(find_day, (year + month + day).c_str());
			char sqr[50] = "SELECT * FROM appointment";
			mysql_query(conn, strcat(sqr, find_day));
			result = mysql_store_result(conn);
			int fields = mysql_num_fields(result);
			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < fields; i++) {
					gotoxy(45, 11 + i);
					cout << row[i];
				}
			}
			gotoxy(50, 8);
			cout << "m�� �����ø� �Ŵ��� ���� ���� ���ϴ�.";
			while (1) {
				key = keyControl();
				if (key == 109) drawMainMenuManeger();
				break;
			}
		}
		else {
			std::string name;
			system("cls");
			gotoxy(55, 10);
			textcolor(BLACK, WHITE);
			cout << "";
			gotoxy(35, 12);
			textcolor(BLACK, WHITE);
			cout << "��ȸ�� ���Ͻô� �̸��� �����ּ���.";
			gotoxy(45, 15);
			cout << "________________________";
			gotoxy(45, 14);
			std::cin >> name;
		}
	}
	void printDefaultAppointment() {
		MYSQL* conn, connection;
		MYSQL_RES* result;
		MYSQL_ROW row;
		bool ok = 0;
		char DB_HOST[] = "locahost";
		char DB_USER[] = "root";
		char DB_PASS[] = "1111";
		char DB_NAME[] = "PATI";
		char sql[1024];
		char str1[1024], str2[1024];

		mysql_init(&connection);
		conn = mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		system("cls");
		string year;
		string month;
		string day;
		gotoxy(50, 10);
		textcolor(BLACK, WHITE);
		cout << "���� ���� ��ȸ";
		gotoxy(35, 12);
		textcolor(BLACK, WHITE);
		cout << "�⵵ �� �� ������� �Է����ֽʽÿ�(exam 2020 8 20)";
		gotoxy(45, 15);
		cout << "________________________";
		gotoxy(45, 14);
		std::cin >> year;
		gotoxy(49, 14);
		cout << "��";
		gotoxy(52, 14);
		std::cin >> month;
		gotoxy(54, 14);
		cout << "��";
		gotoxy(57, 14);
		std::cin >> day;
		gotoxy(59, 14);
		cout << "��";
		system("cls");
		system("cls");
		std::string menu[2] = { "��ü ��ȸ�ϱ�","�̸����� ��ȸ�ϱ�" };
		int key = 0;
		int temp = 0;
		for (int i = 0; i < 2; i++) {
			if (temp == i) {
				textcolor(BLUE, WHITE);
				gotoxy(45, 13 + i);
				std::cout << menu[i];
			}
			else {
				textcolor(BLACK, WHITE);
				gotoxy(45, 13 + i);
				std::cout << menu[i];
			}
		}
		do
		{
			key = keyControl();
			switch (key)
			{
			case UP:
				temp--;
				if (temp == -1) temp = 0;
				for (int i = 0; i < 2; i++) {
					if (temp == i) {
						textcolor(BLUE, WHITE);
						gotoxy(45, 13 + i);
						std::cout << menu[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(45, 13 + i);
						std::cout << menu[i];
					}
				}
			case DOWN:
				temp++;
				if (temp == 2) temp = 1;
				for (int i = 0; i < 2; i++) {
					if (temp == i) {
						textcolor(BLUE, WHITE);
						gotoxy(45, 13 + i);
						cout << menu[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(45, 13 + i);
						cout << menu[i];
					}
				}
			}
		} while (key != ENTER);
		if (temp == 0) {
			system("cls");
			MYSQL* conn, connection;
			MYSQL_RES* result;
			MYSQL_ROW row;

			char DB_HOST[] = "localhost";
			char DB_USER[] = "root";
			char DB_PASS[] = "1111";
			char DB_NAME[] = "PATI";
			char sql[1024];
			char str1[1024], str2[1024];
			gotoxy(45, 7);
			cout << "";
			mysql_init(&connection);
			conn = mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
			char betemp[50] = "SELECT * FROM appointment where APPO_DATE = ";
			strcpy(sql, strcat(betemp, (year + month + day).c_str()));
			if (mysql_query(conn, sql) == 0) {
				int i = 0;
				result = mysql_store_result(conn);
				while ((row = mysql_fetch_row(result)) != NULL) {
					gotoxy(45, 8 + i);
					cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t"<<row[4];
					i++;
				}
				mysql_close(conn);
			}
		}
		else {
			MYSQL* conn, connection;
			MYSQL_RES* result;
			MYSQL_ROW row;
			std::string name;
			system("cls");
			gotoxy(55, 10);
			textcolor(BLACK, WHITE);
			cout << "�̸����� ��ȸ�ϱ�";
			gotoxy(35, 12);
			textcolor(BLACK, WHITE);
			cout << "��ȸ�Ͻð��� �ϴ� �̸��� �Է����ֽʽÿ�";
			gotoxy(45, 15);
			cout << "________________________";
			gotoxy(45, 14);
			std::cin >> name;
			mysql_init(&connection);
			conn = mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
			char betemp[50] = "SELECT * FROM appointment where APPO_DATE = ";
			strcpy(sql, strcat(betemp, (year + month + day).c_str()));
			strcat(betemp, "AND NAME = ");
			strcat(betemp, name.c_str());
			if (mysql_query(conn, sql) == 0) {
				int i = 0;
				result = mysql_store_result(conn);
				while ((row = mysql_fetch_row(result)) != NULL) {
					gotoxy(45, 8 + i);
					cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t";
					i++;
				}
				mysql_close(conn);
			}
		}
		gotoxy(50, 8);
		cout << "m�� �����ø� �Ŵ��� ���� ���� ���ϴ�.";
		while (1) {
			key = keyControl();
			if (key == 109) drawMainMenuManeger();
			break;
		}
	}
};
class User {
private:
	std::string ID;
	std::string PASSWORD;
	std::string NAME;
	std::string BIRTH;
	std::string PHONENUMBER;
public:
	void printUserMain() {
		int key;
		int temp = 0;
		gotoxy(40, 10);
		textcolor(BLACK, WHITE);
		cout << "���� �̿��� ���ؼ� ȸ�����ԶǴ� �α����� �ʿ��մϴ�.";
		int mode = 0;
		std::string menu[] = { "ȸ�� ����","�α���","MAIN" };
		std::system("cls");
		for (int i = 0; i < 3; i++) {
			if (i == temp) {
				gotoxy(55, 13 + i);
				textcolor(BLUE, WHITE);
				cout << menu[i];
			}
			else {
				gotoxy(55, 13 + i);
				textcolor(BLACK, WHITE);
				cout << menu[i];
			}
		}
		do
		{
			key = keyControl();
			switch (key) {
			case UP:
				temp--;
				if (temp == -1) {
					temp = 2;
				}
				for (int i = 0; i < 3; i++) {
					if (i == temp) {
						gotoxy(55, 13 + i);
						textcolor(BLUE, WHITE);
						cout << "              " << endl;
						gotoxy(55, 13 + i);
						cout << menu[i] << endl;
						mode = i;
					}
					else {
						gotoxy(55, 13 + i);
						textcolor(BLACK, WHITE);
						cout << "              " << endl;
						gotoxy(55, 13 + i);
						cout << menu[i] << endl;
					}
				}
				break;
			case DOWN:
				temp++;
				if (temp == 3) {
					temp = 0;
				}
				for (int i = 0; i < 3; i++) {
					if (i == temp) {
						gotoxy(55, 13 + i);
						textcolor(BLUE, WHITE);
						cout << "              " << endl;
						gotoxy(55, 13 + i);
						cout << menu[i] << endl;
						mode = i;
					}
					else {
						gotoxy(55, 13 + i);
						textcolor(BLACK, WHITE);
						cout << "              " << endl;
						gotoxy(55, 13 + i);
						cout << menu[i] << endl;
					}
				}
				break;
			}
		} while (key != ENTER);
		if (mode == 0) {
			Accountant();
		}
		else if (mode == 1) {
			LoginPress();
		}
		else {
			MainPrint();
		}
	}
	void Accountant() {
		MYSQL* conn, connection;
		MYSQL_RES* result;
		MYSQL_ROW row;
		bool ok = 0;
		char DB_HOST[] = "locahost";
		char DB_USER[] = "root";
		char DB_PASS[] = "1111";
		char DB_NAME[] = "PATI";
		char sql[1024];
		char str1[1024], str2[1024];

		mysql_init(&connection);
		conn = mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		std::string information[6] = { "","","","","","" }; // 0 = id 1 = password 2= password_Check 3 = name 4 = birth  5 = phone
		system("cls");
		int temp = 0;
		int key = 0;
		gotoxy(55, 7);
		textcolor(BLACK, WHITE);
		cout << "ȸ�� ����";
		gotoxy(40, 8);
		textcolor(BLACK, WHITE);
		cout << "s�� ������ �Է��� �� �� �ֽ��ϴ�.";
		gotoxy(40, 9);
		textcolor(BLACK, WHITE);
		cout << "������ ���� x, ��ȭ��ȣ�� - �� �־";
		std::string accountMenu[6] = { "ID","PASSWORD","PASSWORD CHECK","NAME","BIRTH","PHONE_NUM" };
		for (int i = 0; i < 6; i++) {
			if (i == temp) {
				gotoxy(50, 13 + i * 2);
				textcolor(BLUE, WHITE);
				cout << accountMenu[i] << endl;
			}
			else {
				gotoxy(50, 13 + i * 2);
				textcolor(BLACK, WHITE);
				cout << accountMenu[i] << endl;
			}
		}
		do {
			do
			{
				key = keyControl();
				switch (key) {
				case UP:temp--;
					if (temp == -1) {
						temp = 0;
					}
					for (int i = 0; i < 6; i++) {
						if (i == temp) {
							gotoxy(50, 13 + i * 2);
							textcolor(BLUE, WHITE);
							cout << accountMenu[i] << endl;
							gotoxy(65, 13 + temp * 2);
							cout << information[temp];
						}
						else {
							gotoxy(50, 13 + i * 2);
							textcolor(BLACK, WHITE);
							cout << accountMenu[i] << endl;
							gotoxy(65, 13 + temp * 2);
							cout << information[temp];
						}
					}
					break;

				case DOWN: temp++;
					if (temp == 6) {
						temp = 5;
					}
					for (int i = 0; i < 6; i++) {
						if (i == temp) {
							gotoxy(50, 13 + i * 2);
							textcolor(BLUE, WHITE);
							cout << accountMenu[i] << endl;
							gotoxy(65, 13 + temp * 2);
							cout << information[temp];
						}
						else {
							gotoxy(50, 13 + i * 2);
							textcolor(BLACK, WHITE);
							cout << accountMenu[i] << endl;
							gotoxy(65, 13 + temp * 2);
							cout << information[temp];
						}
					}
					break;
				case 115:
					gotoxy(65, 13 + temp * 2);
					cout << "                                          ";
					gotoxy(65, 13 + temp * 2);
					cin >> information[temp];
				}
			} while (key != ENTER);
			if (information[1] != information[2]) {
				gotoxy(45, 25);
				cout << "��й�ȣ�� üũ ��й�ȣ�� ���� ���� �ʽ��ϴ�.                           ";
				Sleep(2000);
				gotoxy(45, 25);
				cout << "                                                                                                ";
			}
			else if (information[0] != "" && information[1] != "" && information[2] != "" && information[3] != "" && information[4] != "" && information[5] != "") {
				system("cls");
				gotoxy(45, 10);
				strcat(sql, "INSERT INTO USER VALUES(");
				char* info = (char*)malloc(sizeof(information[0] + ", " + information[1] + ", " + information[2] + ", " + information[3] + ", " + information[4] + ", " + information[5]));
				strcpy(info, (information[0] + ", " + information[1] + ", " + information[2] + ", " + information[3] + ", " + information[4] + ", " + information[5]).c_str());
				strcat(sql, info);
				if (mysql_query(conn, sql) != 0) {
					gotoxy(45, 11);
					cout << information[0] << "�� ������ �Ϸ� �Ǽ̽��ϴ�.";
					this->ID = information[0];
					this->NAME = information[2];
				}
				else {
					cout << information[0] << "�� ������ ���������� ó���� ���� �ʾҽ��ϴ�.";
					ok = 1;
				}
			}
			else {
				gotoxy(45, 25);
				cout << "��� ������ �Է��� ���� �ʾҽ��ϴ�.                  ";
				Sleep(2000);
				gotoxy(45, 25);
				cout << "                                                            ";
			}
		} while (ok == 0);
		printUserMain();
		mysql_close(conn);
	};
	void LoginPress() {
		std::string menu[2] = { "      id : ", "Password : " };
		std::string id;
		std::string password;
		bool loginok = false;
		std::string mode = "";
		int key = 2;
		do {
			system("cls");
			gotoxy(48, 11);
			textcolor(BLACK, WHITE);
			cout << "m�� �����ø� �������� ���ϴ�.";
			for (int i = 0; i < 2; i++) {
				gotoxy(50, 13 + (i * 2));
				cout << menu[i];
			}
			int temp = 0;
			key = keyControl();
			switch (key)
			{
			case UP: temp--;
				if (temp == -1) temp = 0;
				for (int i = 0; i < 2; i++) {
					if (i == temp) {
						textcolor(BLUE, WHITE);
						gotoxy(50, 13 + (i * 2));
						cout << menu[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(50, 13 + (i * 2));
						cout << menu[i];
					}
				}
				gotoxy(61, 13 + (temp * 2));
				std::cin >> id;
			case DOWN: temp++;
				if (temp == 3) temp = 2;
				for (int i = 0; i < 2; i++) {
					if (i == temp) {
						textcolor(BLUE, WHITE);
						gotoxy(50, 13 + (i * 2));
						cout << menu[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(50, 13 + (i * 2));
						cout << menu[i];
					}
				}
				gotoxy(61, 13 + (temp * 2));
				std::cin >> password;

			case ENTER:
				if (login(id, password)) {
					loginok = true;
				}
				else {
					gotoxy(60, 25);
					textcolor(BLACK, WHITE);
					cout << "ID, PASSWORD�� �н����尡 �˸��� �ʽ��ϴ�.";
				}
				Sleep(1500);
				break;
			case 109: MainPrint();
			}
		} while (loginok == false);
		drawAppointment();
	}
	bool login(std::string ID, std::string PASSWORD) {
		MYSQL* conn, connection;
		MYSQL_RES* result;
		MYSQL_ROW row;

		char DB_HOST[] = "localhost";
		char DB_USER[] = "root";
		char DB_PASS[] = "1111";
		char DB_NAME[] = "PATI";
		char sql[1024];
		char str1[1024], str2[1024];

		mysql_init(&connection);
		conn = mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		strcpy(sql, "SELECT * FROM User");
		if (mysql_query(conn, sql) == 0) {
			result = mysql_store_result(conn);
			while ((row = mysql_fetch_row(result)) != NULL) {
				if (row[0] == ID && row[1] == PASSWORD) {
					
					return true;
				}
			}
			mysql_free_result(result);
			return false;
		}
	}
	void drawAppointment() {
		system("cls");
		textcolor(BLACK, WHITE);
		gotoxy(40, 10);
		cout << "���θ޴��� ���� �ʹٸ� m";
		std::string menu[3] = { "�˻� ����","���� ����","���� ����" };
		std::string mode = "�˻� ����";
		int key = 0;
		int temp = 0;
		for (int i = 0; i < 3; i++) {
			if (temp == i) {
				textcolor(BLUE, WHITE);
				gotoxy(55, 13 + i);
				cout << menu[i];
			}
			else {
				textcolor(BLACK, WHITE);
				gotoxy(55, 13 + i);
				cout << menu[i];
			}
		}
		do {
			key = keyControl();
			switch (key)
			{
			case UP:
				temp--;
				if (temp == -1) {
					temp = 2;
				}
				for (int i = 0; i < 3; i++) {
					if (i == temp) {
						gotoxy(55, 13 + i);
						textcolor(BLUE, WHITE);
						cout << "              " << std::endl;
						gotoxy(55, 13 + i);
						cout << menu[i] << std::endl;
						mode = menu[i];
					}
					else {
						gotoxy(55, 13 + i);
						textcolor(BLACK, WHITE);
						cout << "              " << std::endl;
						gotoxy(55, 13 + i);
						cout << menu[i] << std::endl;
					}
				}
				break;
			case DOWN:
				temp++;
				if (temp == 3) {
					temp = 0;
				}
				for (int i = 0; i < 3; i++) {
					if (i == temp) {
						gotoxy(55, 13 + i);
						textcolor(BLUE, WHITE);
						cout << "              " << std::endl;
						gotoxy(55, 13 + i);
						cout << menu[i] << std::endl;
						mode = menu[i];
					}
					else {
						gotoxy(55, 13 + i);
						textcolor(BLACK, WHITE);
						cout << "              " << std::endl;
						gotoxy(55, 13 + i);
						cout << menu[i] << std::endl;
					}
				}
				break;
			case 109:printUserMain();

			}
		} while (key != ENTER);
		if (temp == 0) {
			ExamAppointment();
		}
		else if (temp == 1) {
			defaultAppoint();
		}
		else {
			MYSQL* conn, connection;
			MYSQL_RES* result;
			MYSQL_ROW row;

			char DB_HOST[] = "localhost";
			char DB_USER[] = "root";
			char DB_PASS[] = "1111";
			char DB_NAME[] = "PATI";
			char sql[1024];
			char str1[1024], str2[1024];

			mysql_init(&connection);
			conn = mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
			strcpy(sql, "SELECT * FROM Appointment");
			if (mysql_query(conn, sql) == 0) {
				result = mysql_store_result(conn);
				while ((row = mysql_fetch_row(result)) != NULL) {
					if (row[1] == this->ID) {
						gotoxy(45, 15);
						cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "wt" << row[4] << "wt";
					}
				}
				mysql_free_result(result);
			}
		}

	}
	void ExamAppointment() {
		system("cls");
		gotoxy(45, 9);
		cout << "���ϴ� �˻縦 �������ֽʽÿ�.";
		string Exam[] = { "�κ� ���ð�","�κ� �ܼ���缱�Կ�","�˷����� �Ǻ� ����","�˷����� ���� �׿�"
		,"�๰ ����","���� �� ��⵵","�İ� ���� ���","�κ� ��ǻ�� �����Կ�(OMU CT)","�κ� �ڱ�������Կ�(MRI)"};
		for (int i = 0; i < 9; i++) {
			gotoxy(45, 10 + i);
			cout << Exam[i];
		}
		int key;
		int temp = 0;
		string ExamSelect = "�κ� ���ð�";
		do {
			key = keyControl();
			switch (key)
			{
			case UP:
				temp--;
				if (temp == -1) temp = 8;
				for (int i = 0; i < 9; i++) {
					if (i == temp) {
						textcolor(BLUE, WHITE);
						gotoxy(45, 10 + i);
						cout << Exam[i];
						ExamSelect = Exam[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(45, 10 + i);
						cout << Exam[i];
					}
				}
			case DOWN:
				temp++;
				if (temp == 9) temp = 0;
				for (int i = 0; i < 9; i++) {
					if (i == temp) {
						textcolor(BLUE, WHITE);
						gotoxy(45, 10 + i);
						cout << Exam[i];
						ExamSelect = Exam[i];
					}
					else {
						textcolor(BLACK, WHITE);
						gotoxy(45, 10 + i);
						cout << Exam[i];
					}
				}
			}
		} while (key != ENTER);
		do {
			system("cls");
			gotoxy(55, 9);
			cout << "���ϴ� ��¥�� �Է����ּ���.";
			gotoxy(55, 18);
			cout << "���� ���� n ������ b �Է��� s";
			time_t timer;
			struct tm* t;
			timer = time(NULL);
			t = localtime(&timer);
			Calendar cal(t->tm_year + 1900, t->tm_mon + 1);
			textcolor(BLACK, WHITE);
			cal.DrawCalender(t->tm_mday);
			int year;
			int month;
			int day;
			switch (key)
			{
			case 110:
				cal.AddMonth();
				break;
			case 98:
				cal.MinusMonth();
				break;
			case 115:gotoxy(55, 19);
				cin >> year;
				gotoxy(55, 20);
				cin >> month;
				gotoxy(55, 21);
				cin >> day;
			}
		} while (key != ENTER);
	}
	void defaultAppoint() {
		int key = 0;
		do {
			int year;
			int month;
			int day;
			system("cls");
			gotoxy(55, 9);
			cout << "���ϴ� ��¥�� �Է����ּ���";
			gotoxy(55, 10);
			cout << "���� ���� n ������ b �Է��� s";
			time_t timer;
			struct tm* t;
			timer = time(NULL);
			t = localtime(&timer);
			Calendar cal(t->tm_year + 1900, t->tm_mon + 1);
			textcolor(BLACK, WHITE);
			cal.DrawCalender(t->tm_mday);
			switch (key)
			{
			case 110:
				cal.AddMonth();
				break;
			case 98:
				cal.MinusMonth();
				break;
			case 115:gotoxy(55, 19);
				cin >> year;
				gotoxy(55, 20);
				cin >> month;
				gotoxy(55, 21);
				cin >> day;
			}
		} while (key != ENTER);
	}

};
int main() {
	system("mode con cols=100 lines = 50 | title Mirim_Hospital");
	MainPrint();
	MYSQL* conn, connection;
	MYSQL_RES* result;
	MYSQL_ROW row;

	char DB_HOST[] = "localhost";
	char DB_USER[] = "root";
	char DB_PASS[] = "1111";
	char DB_NAME[] = "PATI";
	char sql[1024];
	char str1[1024], str2[1024];
	mysql_init(&connection);
	conn = mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_close(conn);
	return 0;
}
void printLogo() {
	system("cls");
	gotoxy(25, 5);
	cout << ".-..-..-..---. .-..-..-.  .-..-. .--.  .--. .---. .-..-----. .--. .-. " << endl;
	gotoxy(25, 6);
	cout << ": `' :: :: .; :: :: `' :  : :; :: ,. :: .--': .; :: :`-. .-': .; :: :   " << endl;
	gotoxy(25, 7);
	cout << ": .. :: ::   .': :: .. :  :    :: :: :`. `. :  _.': :  : :  :    :: :   " << endl;
	gotoxy(25, 8);
	cout << ": :; :: :: :.`.: :: :; :  : :: :: :; : _`, :: :   : :  : :  : :: :: :__ " << endl;
	gotoxy(25, 9);
	cout << ":_;:_;:_;:_;:_;:_;:_;:_;  :_;:_;`.__.'`.__.':_;   :_;  :_;  :_;:_;:___.'" << endl;
}
int MainPrint() {
	textcolor(BLACK, WHITE);
	string menu[3] = { "�Ŵ��� �α���","���� �α���","���α׷� ����" };
	string mode = "�Ŵ��� �α���";
	int key = 0;
	int temp = 0;
	printLogo();
	gotoxy(55, 13);
	textcolor(BLUE, WHITE);
	cout << "�Ŵ��� �α���" << endl;
	gotoxy(55, 14);
	textcolor(BLACK, WHITE);
	cout << "���� �α���" << endl;
	gotoxy(55, 15);
	textcolor(BLACK, WHITE);
	cout << "���α׷� ����" << endl;
	do {
		key = keyControl();
		switch (key)
		{
		case UP:
			temp--;
			if (temp == -1) {
				temp = 2;
			}
			for (int i = 0; i < 3; i++) {
				if (i == temp) {
					gotoxy(55, 13 + i);
					textcolor(BLUE, WHITE);
					cout << "              " << endl;
					gotoxy(55, 13 + i);
					cout << menu[i] << endl;
					mode = menu[i];
				}
				else {
					gotoxy(55, 13 + i);
					textcolor(BLACK, WHITE);
					cout << "              " << endl;
					gotoxy(55, 13 + i);
					cout << menu[i] << endl;
				}
			}
			break;
		case DOWN:
			temp++;
			if (temp == 3) {
				temp = 0;
			}
			for (int i = 0; i < 3; i++) {
				if (i == temp) {
					gotoxy(55, 13 + i);
					textcolor(BLUE, WHITE);
					cout << "              " << endl;
					gotoxy(55, 13 + i);
					cout << menu[i] << endl;
					mode = menu[i];
				}
				else {
					gotoxy(55, 13 + i);
					textcolor(BLACK, WHITE);
					cout << "              " << endl;
					gotoxy(55, 13 + i);
					cout << menu[i] << endl;
				}
			}
			break;
		}
	} while (key != ENTER);
	system("cls");
	if (mode == "�Ŵ��� �α���") {
		Maneger mg;
		mg.loginPress();
		mg.drawMainMenuManeger();
	}
	else if (mode == "���� �α���") {
		User user;
		user.printUserMain();

	}
	else if (mode == "���α׷� ����") {
		cout << "���α׷� ����" << endl;
		return 0;
	}
	return 0;
}
