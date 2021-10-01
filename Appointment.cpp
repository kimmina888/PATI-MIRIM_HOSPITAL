#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include <ctime>
#include <xiosbase>
#include<string> 
#include <fstream>
#include "Calender.h"
#include <synchapi.h>
#include <iomanip>
using namespace std;
class Appoinment {
	void drawExam() {
		cout << "1. �κ� ���ð�" <<
			endl << "2. �κ� �ܼ���缱�Կ�" <<
			endl << "3. �˷����� �Ǻ� ����" << //
			endl << "4. �˷����� ���� �׿�" << //
			endl << "5. �๰ ����" <<
			endl << "6. ���� �� ��⵵" <<
			endl << "7. �İ� ���� ���" <<
			endl << "8. �κ� ��ǻ�� �����Կ�(OMU CT)" <<// 
			endl << "9. �κ� �ڱ�������Կ�(MRI)"<<endl;
	}
	void drawTimeTable() {//�̹� ������ �� �ð��� �����ϴ� �ڵ�� db�� ���� ������� ���ư��� ������
		cout << "----TIME TABLE----" << endl;
		for (int i = 8; i < 18; i++) {//��ħ 8�ú��� ���� 6�ñ��� ��ϴ� ����
			for (int j = 0; j < 60; j += 20) {//20�� �������� ������ ����
				cout << setw(10) << i << " : " << j << endl;
			}
		}
		cout << "------------------" << endl;
	}
public:
	int medicalAppoinment() {
		time_t timer;
		struct tm* t;
		timer = time(NULL);
		t = localtime(&timer);

		ofstream writeFile("Appointment.txt", ios::app);

		Calendar cal(t->tm_year + 1900, t->tm_mon + 1);
		string day;
		system("cls");
		do {
			cal.DrawCalender();
			cout << "������ ���Ͻô� ��¥�� ����ּ���. ���� �޷� ���� �����ôٸ� N �� �޷� ���� �ʹٸ� B" << endl;
			cout << ">> ";
			cin >> day;
			if (day == "N") {
				cal.AddMonth();
			}
			else if (day == "B") {
				cal.MinusMonth();
			}
			system("cls");
		} while (day == "N" || day == "B" || day == "0" || stoi(day)>31);
		int month = cal.month;
		int year = cal.year;
			
		drawTimeTable();
		cout << "������ ���Ͻô� �ð��� ����ּ���. �Է� ���(�ð� ��)" << endl;
		cout << ">> ";
		int time;
		cin >> time;
		int min;
		cin >> min;
		system("cls");

		cout << "����Ȯ���� ���� �̸��� �Է����ֽʽÿ�." << endl;
		cout << ">> ";
		string name;
		cin >> name;
		system("cls");

		cout << "����Ȯ���� ���� ID�� �Է����ֽʽÿ�." << endl;
		cout << ">> ";
		string id;
		cin >> id;
		system("cls");

		if (id != "") {
			if (writeFile.is_open()) {
				writeFile <<id<<" / " << name << " / " << year << " / " << month << " / " << day << "/ " << time << " / " << min << " / " << endl;
				cout << name << "�� " << year << "�� " << month << "�� " << day << "�� " << time << "�� " << min << "�� ����Ϸ� �ϼ̽��ϴ�." << endl << "id��  " << id;
			}
			else {
				std::cout << "������ ã�� �� �����ϴ�!" << std::endl;
			}
			writeFile.close();
			Sleep(2000);
			return 0;
		}
		return 0;
	}

	int my_MedicalAppoinment() {
		cout << "���� ID�� �Է����ֽʽÿ�.(20���� �̸� �������)" << endl;
		cout << ">> ";
		char id[20]="";
		cin >> id;
		system("cls");
		ifstream readFile;
		readFile.open("Appointment.txt");
		if (readFile.is_open()) {
			char lines[100];
			string line;
			cout << line << endl;
			while (getline(readFile, line)) {
				readFile.getline(lines, sizeof(line));
				//char* information = strtok(lines, " / ");
				cout << line << endl;
			}

			cout << "Ȯ���ϼ����� ok�� �Է����ּ���." << endl;
			cout << ">> ";
			string ok;
			cin >> ok;
			if (ok == "ok") {
				readFile.close();
				return 0;
			}
		}
		else {
			std::cout << "������ ã�� �� �����ϴ�!" << std::endl;
			readFile.close();
			return 0;
		}
		return 0;
	}
	int examAppointment() {
		time_t timer;
		struct tm* t;
		timer = time(NULL);
		t = localtime(&timer);
		ofstream writeFile;
		writeFile.open("Appointment.txt", ios::app);
		system("cls");
		drawExam();
		cout << "���Ͻô� �˻縦 ����ּ���." << endl;
		cout << ">> ";
		int examdata;
		cin >> examdata;
		string exam[] = { "�κ� ���ð�", "�κ� �ܼ���缱�Կ�", "�˷����� �Ǻ� ����","�˷����� ���� �׿�","�๰ ����",
		"���� �� ��⵵","�İ� ���� ���","�κ� ��ǻ�� �����Կ�(OMU CT)","�κ� �ڱ�������Կ�(MRI)" };
		string choice_exam = exam[examdata - 1];
		system("cls");

		Calendar cal(t->tm_year, t->tm_mon);
		string day;
		do {
			cal.DrawCalender();
			cout << "������ ���Ͻô� ��¥�� ����ּ���. ���� �޷� ���� �����ôٸ� N �� �޷� ���� �ʹٸ� B" << endl;
			cout << ">> ";
			cin >> day;
			if (day == "N") {
				cal.AddMonth();
			}
			else if (day == "B") {
				cal.MinusMonth();
			}
			system("cls");
		} while (day == "N" || day == "B" || day == "0" || stoi(day) > 31);
		int month = cal.month;
		int year = cal.year;

		drawTimeTable();
		cout << "������ ���Ͻô� �ð��� ����ּ���. �Է� ���(�ð� ��)" << endl;
		cout << ">> ";
		int time;
		cin >> time;
		int min;
		cin >> min;
		system("cls");

		cout << "����Ȯ���� ���� �̸��� �Է����ֽʽÿ�." << endl;
		cout << ">> ";
		string name;
		cin >> name;
		system("cls");

		cout << "����Ȯ���� ���� ID�� �Է����ֽʽÿ�." << endl;
		cout << ">> ";
		string id;
		cin >> id;
		system("cls");

		if (id != "") {
			if (writeFile.is_open()) {
				writeFile << name << " / " << year << " / " << month << " / " << " / " << day << " / " << time << " / " << min << " / " << id << " / " << choice_exam << endl;
				cout << name << "�� " << year << "�� " << month << "�� " << day << "�� " << time << "�� " << min << "�� ����Ϸ� �ϼ̽��ϴ�." << endl << "id : " << id << endl << "�˻� : " << choice_exam << endl;
				writeFile.close();
			}
			else {
				std::cout << "������ ã�� �� �����ϴ�!" << std::endl;
			}
			writeFile.close();
			Sleep(2000);
			return 0;
		}
		return 0;
	}
};