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
		int basicyear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; // 占썩본 1~12占쏙옙 占싹쇽옙
		gotoxy(40, 8);
		cout << year << "년" << month << "월";
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
			std::cout << "매니저 모드는 로그인이 필요합니다.";
			gotoxy(40, 11);
			textcolor(BLACK, WHITE);
			std::cout << "메인가기 : m";
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
					std::cout << "ID, PASSWORD가 서로 맞지 않습니다.";
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
		std::string menu[3] = { "검사 리스트","진료 리스트" ,"    MAIN"};
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
		if (modes == "검사 리스트") {
			printExamAppointment();
		}
		else if (modes == "진료 리스트") {
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
		std::cout << "조회를 원하는 날을 입력해주세요.";
		system("cls");
		gotoxy(40, 11);
		textcolor(BLACK, WHITE);
		gotoxy(35, 12);
		textcolor(BLACK, WHITE);
		std::cout << "년도 달 일을 각각 입력해주세요.(exam 2020 8 20)";
		gotoxy(45, 15);
		std::cout << "________________________";
		gotoxy(45, 14);
		std::cin >> year;
		gotoxy(49, 14);
		std::cout << "년";
		gotoxy(52, 14);
		std::cin >> month;
		gotoxy(54, 14);
		std::cout << "월";
		gotoxy(57, 14);
		std::cin >> day;
		gotoxy(59, 14);
		std::cout << "일";
		system("cls");
		gotoxy(40, 8);
		std::cout << "조회를 원하시는 검사를 입력해주십시오." << std::endl;
		std::string Exam[] = { "부비동 내시경","부비동 단순방사선촬영","알레르기 피부 반응","알레르기 혈액 항원"
		,"콧물 세포","음향 비강 통기도","후각 인지 기능","부비동 컴퓨터 단층촬영(OMU CT)","부비동 자기공명영상촬영(MRI)"};
		for (int i = 0; i < 9; i++) {
			gotoxy(45, 10 + i);
			cout << Exam[i];
		}
		key = 0;
		temp = 0;
		std::string ExamSelect = "부비동 내시경";
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
		std::string menu[2] = { "전체 조회","이름 검색 조회" };
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
			cout << "m을 누르시면 매니저 메인 모드로 갑니다.";
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
			cout << "조회를 원하시는 이름을 적어주세요.";
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
		cout << "진료 예약 조회";
		gotoxy(35, 12);
		textcolor(BLACK, WHITE);
		cout << "년도 달 일 순서대로 입력해주십시오(exam 2020 8 20)";
		gotoxy(45, 15);
		cout << "________________________";
		gotoxy(45, 14);
		std::cin >> year;
		gotoxy(49, 14);
		cout << "년";
		gotoxy(52, 14);
		std::cin >> month;
		gotoxy(54, 14);
		cout << "월";
		gotoxy(57, 14);
		std::cin >> day;
		gotoxy(59, 14);
		cout << "일";
		system("cls");
		system("cls");
		std::string menu[2] = { "전체 조회하기","이름으로 조회하기" };
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
			cout << "이름으로 조회하기";
			gotoxy(35, 12);
			textcolor(BLACK, WHITE);
			cout << "조회하시고자 하는 이름을 입력해주십시오";
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
		cout << "m을 누르시면 매니저 메인 모드로 갑니다.";
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
		cout << "서비스 이용을 위해선 회원가입또는 로그인이 필요합니다.";
		int mode = 0;
		std::string menu[] = { "회원 가입","로그인","MAIN" };
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
		cout << "회원 가입";
		gotoxy(40, 8);
		textcolor(BLACK, WHITE);
		cout << "s를 눌를시 입력을 할 수 있습니다.";
		gotoxy(40, 9);
		textcolor(BLACK, WHITE);
		cout << "생일은 띄어쓰기 x, 전화번호는 - 를 넣어서";
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
				cout << "비밀번호랑 체크 비밀번호랑 서로 같지 않습니다.                           ";
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
					cout << information[0] << "님 가입이 완료 되셨습니다.";
					this->ID = information[0];
					this->NAME = information[2];
				}
				else {
					cout << information[0] << "님 가입이 정상적으로 처리가 되지 않았습니다.";
					ok = 1;
				}
			}
			else {
				gotoxy(45, 25);
				cout << "모든 조건이 입력이 되지 않았습니다.                  ";
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
			cout << "m을 누르시면 메인으로 갑니다.";
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
					cout << "ID, PASSWORD와 패스워드가 알맞지 않습니다.";
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
		cout << "메인메뉴로 가고 싶다면 m";
		std::string menu[3] = { "검사 예약","진료 예약","나의 예약" };
		std::string mode = "검사 예약";
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
		cout << "원하는 검사를 선택해주십시오.";
		string Exam[] = { "부비동 내시경","부비동 단순방사선촬영","알레르기 피부 반응","알레르기 혈액 항원"
		,"콧물 세포","음향 비강 통기도","후각 인지 기능","부비동 컴퓨터 단층촬영(OMU CT)","부비동 자기공명영상촬영(MRI)"};
		for (int i = 0; i < 9; i++) {
			gotoxy(45, 10 + i);
			cout << Exam[i];
		}
		int key;
		int temp = 0;
		string ExamSelect = "부비동 내시경";
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
			cout << "원하는 날짜를 입력해주세요.";
			gotoxy(55, 18);
			cout << "다음 달은 n 전달은 b 입력은 s";
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
			cout << "원하는 날짜를 입력해주세요";
			gotoxy(55, 10);
			cout << "다음 달은 n 전달은 b 입력은 s";
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
	string menu[3] = { "매니저 로그인","유저 로그인","프로그램 종료" };
	string mode = "매니저 로그인";
	int key = 0;
	int temp = 0;
	printLogo();
	gotoxy(55, 13);
	textcolor(BLUE, WHITE);
	cout << "매니저 로그인" << endl;
	gotoxy(55, 14);
	textcolor(BLACK, WHITE);
	cout << "유저 로그인" << endl;
	gotoxy(55, 15);
	textcolor(BLACK, WHITE);
	cout << "프로그램 종류" << endl;
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
	if (mode == "매니저 로그인") {
		Maneger mg;
		mg.loginPress();
		mg.drawMainMenuManeger();
	}
	else if (mode == "유저 로그인") {
		User user;
		user.printUserMain();

	}
	else if (mode == "프로그램 종료") {
		cout << "프로그램 종료" << endl;
		return 0;
	}
	return 0;
}
