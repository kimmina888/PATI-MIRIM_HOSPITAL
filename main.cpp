#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/SUBSYSTEM:CONSOLE") //�ܼ����α׷����� ����ڴٰ� ���
#pragma comment(lib, "gdiplus.lib") //gdiplus���̺귯��
#include<Windows.h>
#include <conio.h>
#include <gdiplus.h> 
#include<iostream>
#include <iomanip>
#include <fstream>
#include "Appointment.cpp"

using namespace std;
void drawMainMenu() {
	cout << setw(10 )<< "1. ���� ����" << endl;
	cout << setw(10) << "2. ���� ����" << endl;
	cout << setw(10) << "3. �˻翹��" << endl;
	cout << setw(10) << "4. ���α׷� ����" << endl;
}
void gdi(const wchar_t* filepath) {
	HWND hwnd = GetConsoleWindow(); //�ܼ�â�ڵ鰪 ���ϱ�
	HDC hdc = GetDC(hwnd); //�ڵ鰪���� DC���ϱ�
	HDC MemoryDC = CreateCompatibleDC(hdc); //����Ҽ��ִ� DC����

	ULONG_PTR ptr; //Gdi+����� ���� �����Ͱ�ü
	Gdiplus::GdiplusStartupInput in; //gdi+�Է°���ü
	Gdiplus::GdiplusStartup(&ptr, &in, 0); //����

	Gdiplus::Bitmap* b = Gdiplus::Bitmap::FromFile(filepath); //���Ϸκ��� ��Ʈ�ʹޱ�
	HBITMAP hBit; //HBITMAP����ü ����
	b->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBit); 

		HGDIOBJ obj = SelectObject(MemoryDC, hBit); //MemoryDC���ٰ� ��Ʈ������
	BITMAP bit = { 0 }; //��Ʈ��ũ�⸦ ���ϱ����� ����ü
	GetObject(hBit, sizeof BITMAP, &bit); //��Ʈ��ũ�ⱸ�ϱ�����
	StretchBlt(hdc, 0, 0, bit.bmWidth, bit.bmHeight,
		MemoryDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY); //�׸���
	SelectObject(MemoryDC, obj); //�غκ��� �޸𸮴����� ��������
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
			cout << "�߸��� ���񽺸� �����ϼ̽��ϴ�." << endl;
			cout << "2���� ����ȭ������ ���ư��ϴ�." << endl;
			Sleep(2000);
			system("cls");
		}
	}
}