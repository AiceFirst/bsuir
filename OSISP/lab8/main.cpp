 #include "main.h"


int main(int argc, char *argv[])
{
	/*
	1L ���������� � ������ �����, �� ������ �� ���������
	2L ����� ��������� ������� ��������
	*/
	PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2L);
	system("pause");

	return 0;
}