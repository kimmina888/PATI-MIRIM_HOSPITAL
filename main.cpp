#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/SUBSYSTEM:CONSOLE") //콘솔프로그램으로 만들겠다고 명시
#pragma comment(lib, "gdiplus.lib") //gdiplus라이브러리
#include<Windows.h>
#include <conio.h>
#include <gdiplus.h> 
#include<iostream>
#include <iomanip>
#include <fstream>
#include "Appointment.cpp"

using namespace std;
void drawMainMenu() {
	cout << setw(10 )<< "1. 진료 예약" << endl;
	cout << setw(10) << "2. 나의 예약" << endl;
	cout << setw(10) << "3. 검사예약" << endl;
	cout << setw(10) << "4. 프로그램 종류" << endl;
}
void gdi(const wchar_t* filepath) {
	HWND hwnd = GetConsoleWindow(); //콘솔창핸들값 구하기
	HDC hdc = GetDC(hwnd); //핸들값으로 DC구하기
	HDC MemoryDC = CreateCompatibleDC(hdc); //사용할수있는 DC생성

	ULONG_PTR ptr; //Gdi+사용을 위한 포인터객체
	Gdiplus::GdiplusStartupInput in; //gdi+입력값객체
	Gdiplus::GdiplusStartup(&ptr, &in, 0); //시작

	Gdiplus::Bitmap* b = Gdiplus::Bitmap::FromFile(filepath); //파일로부터 비트맵받기
	HBITMAP hBit; //HBITMAP구조체 선언
	b->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBit); 

		HGDIOBJ obj = SelectObject(MemoryDC, hBit); //MemoryDC에다가 비트맵지정
	BITMAP bit = { 0 }; //비트맵크기를 구하기위한 구조체
	GetObject(hBit, sizeof BITMAP, &bit); //비트맵크기구하기위함
	StretchBlt(hdc, 0, 0, bit.bmWidth, bit.bmHeight,
		MemoryDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY); //그리기
	SelectObject(MemoryDC, obj); //밑부분은 메모리누수를 막기위함
	DeleteObject(hBit);
	ReleaseDC(hwnd, MemoryDC);
	DeleteDC(hdc);
	delete b;
}
void Color(int Color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}
void getoxy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
int main(void) {
	system("mode con cols=90 lines = 30 | title Mirim_Hospital");
	system("color F0");
	while (1)
	{
		gdi(L"logo.png");
		Sleep(1000);
		Appoinment ap;
		drawMainMenu();
		int choiceMenu;
		cin >> choiceMenu;
		if (choiceMenu == 1) {
			ap.medicalAppoinment();
			system("cls");
		}
		else if (choiceMenu == 2) {
			ap.my_MedicalAppoinment();
			Sleep(2000);
			system("cls");
		}
		else if (choiceMenu == 3) {
			ap.examAppointment();
			system("cls");
		}
		else if (choiceMenu == 4) {
			return 0;
		}
		else {
			system("cls");
			cout << "잘못된 서비스를 선택하셨습니다." << endl;
			cout << "2초후 메인화면으로 돌아갑니다." << endl;
			Sleep(2000);
			system("cls");
		}
	}
}