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
		cout << "1. 부비동 내시경" <<
			endl << "2. 부비동 단순방사선촬영" <<
			endl << "3. 알레르기 피부 반응" << //
			endl << "4. 알레르기 혈액 항원" << //
			endl << "5. 콧물 세포" <<
			endl << "6. 음향 비강 통기도" <<
			endl << "7. 후각 인지 기능" <<
			endl << "8. 부비동 컴퓨터 단층촬영(OMU CT)" <<// 
			endl << "9. 부비동 자기공명영상촬영(MRI)"<<endl;
	}
	void drawTimeTable() {//이미 예약이 된 시간을 제외하는 코드는 db나 파일 입출력이 돌아가면 넣을것
		cout << "----TIME TABLE----" << endl;
		for (int i = 8; i < 18; i++) {//아침 8시부터 저녁 6시까지 운영하는 병원
			for (int j = 0; j < 60; j += 20) {//20분 간격으로 예약을 받음
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
			cout << "예약을 원하시는 날짜를 골라주세요. 다음 달로 가고 싶으시다면 N 전 달로 가고 싶다면 B" << endl;
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
		cout << "예약을 원하시는 시간을 골라주세요. 입력 양식(시간 분)" << endl;
		cout << ">> ";
		int time;
		cin >> time;
		int min;
		cin >> min;
		system("cls");

		cout << "예약확인을 위한 이름을 입력해주십시오." << endl;
		cout << ">> ";
		string name;
		cin >> name;
		system("cls");

		cout << "예약확인을 위한 ID를 입력해주십시오." << endl;
		cout << ">> ";
		string id;
		cin >> id;
		system("cls");

		if (id != "") {
			if (writeFile.is_open()) {
				writeFile <<id<<" / " << name << " / " << year << " / " << month << " / " << day << "/ " << time << " / " << min << " / " << endl;
				cout << name << "님 " << year << "년 " << month << "월 " << day << "일 " << time << "시 " << min << "분 예약완료 하셨습니다." << endl << "id는  " << id;
			}
			else {
				std::cout << "파일을 찾을 수 없습니다!" << std::endl;
			}
			writeFile.close();
			Sleep(2000);
			return 0;
		}
		return 0;
	}

	int my_MedicalAppoinment() {
		cout << "예약 ID를 입력해주십시오.(20글자 미만 영문사용)" << endl;
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

			cout << "확인하셨으면 ok를 입력해주세요." << endl;
			cout << ">> ";
			string ok;
			cin >> ok;
			if (ok == "ok") {
				readFile.close();
				return 0;
			}
		}
		else {
			std::cout << "파일을 찾을 수 없습니다!" << std::endl;
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
		cout << "원하시는 검사를 골라주세요." << endl;
		cout << ">> ";
		int examdata;
		cin >> examdata;
		string exam[] = { "부비동 내시경", "부비동 단순방사선촬영", "알레르기 피부 반응","알레르기 혈액 항원","콧물 세포",
		"음향 비강 통기도","후각 인지 기능","부비동 컴퓨터 단층촬영(OMU CT)","부비동 자기공명영상촬영(MRI)" };
		string choice_exam = exam[examdata - 1];
		system("cls");

		Calendar cal(t->tm_year, t->tm_mon);
		string day;
		do {
			cal.DrawCalender();
			cout << "예약을 원하시는 날짜를 골라주세요. 다음 달로 가고 싶으시다면 N 전 달로 가고 싶다면 B" << endl;
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
		cout << "예약을 원하시는 시간을 골라주세요. 입력 양식(시간 분)" << endl;
		cout << ">> ";
		int time;
		cin >> time;
		int min;
		cin >> min;
		system("cls");

		cout << "예약확인을 위한 이름을 입력해주십시오." << endl;
		cout << ">> ";
		string name;
		cin >> name;
		system("cls");

		cout << "예약확인을 위한 ID를 입력해주십시오." << endl;
		cout << ">> ";
		string id;
		cin >> id;
		system("cls");

		if (id != "") {
			if (writeFile.is_open()) {
				writeFile << name << " / " << year << " / " << month << " / " << " / " << day << " / " << time << " / " << min << " / " << id << " / " << choice_exam << endl;
				cout << name << "님 " << year << "년 " << month << "월 " << day << "일 " << time << "시 " << min << "분 예약완료 하셨습니다." << endl << "id : " << id << endl << "검사 : " << choice_exam << endl;
				writeFile.close();
			}
			else {
				std::cout << "파일을 찾을 수 없습니다!" << std::endl;
			}
			writeFile.close();
			Sleep(2000);
			return 0;
		}
		return 0;
	}
};