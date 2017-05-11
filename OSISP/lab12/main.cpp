#include "main.h"

/*
http://wm-help.net/books-online/book/59464.html

������ ������ ������ �������
�� ���������� ���� ���

*/
int main(int argc, char *argv[])
{

	MEMORYSTATUS ms = { sizeof(ms) };
	GlobalMemoryStatus(&ms);

	cout << "TotalPhys     " << ms.dwTotalPhys / 1024 /1024 << "mB" << endl; //����� ����� ���� ������ (�����������) ������
	cout << "AvailPhys     " << ms.dwAvailPhys / 1024 / 1024 << "mB" << endl; //��������� ���� ������ ������.
	cout << "TotalPageFile " << ms.dwTotalPageFile / 1024 / 1024 << "mB" << endl; //������������ ���������� ������, ������� ����� ����������� � ���������� ����� (������) �� ������� ����� (������)
	cout << "AvailPageFile " << ms.dwAvailPageFile / 1024 / 1024 << "mB" << endl; //����� �������� � ����� ���� �� ������ ������ ��������.
	cout << "TotalVirtual  " << ms.dwTotalVirtual / 1024 / 1024 << "mB" << endl; //����� ������ ���� ������, ���������� ��� �������� �������� ������������ ��������
	cout << "AvailVirtual  " << ms.dwAvailVirtual / 1024 / 1024 << "mB" << endl << endl; // ������ ���������� ��������� �������� ����


	PINT pvMem = (PINT)VirtualAlloc(NULL, 1 * 1024 * 1024,  MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	//����������� �������� ����������� ������ � ���������� �� �� ���������� ������
	pvMem[0] = 123;
	cout << pvMem[0] << endl;

	VirtualFree(pvMem, 0, MEM_RELEASE);

	system("pause");
	return 0;
}