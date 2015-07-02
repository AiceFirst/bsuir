#include "main.h"

/*
HANDLE CreateThread(
	LPSECURITY_ATTRIBUTES lpThreadAttributes, // �������� ������
	DWORD dwStackSize, // ������ ����� ������ � ������
	LPTHREAD_START_ROUTINE lpStartAddress,// ����� ����������� �������
	LPVOID lpParameter,// ����� ���������
	DWORD dwCreationFlags,// ����� �������� ������
	LPDWORD lpThreadId// ������������� ������
);

DWORD WINAPI ThreadProc (LPVOID lpParameters); //�������� ��� �������, ����������� � ������
*/

int n = 0;

int main(int argc, char *argv[])
{
	int inc = 10;
	HANDLE hThread;
	DWORD IDThread;
	cout << "n = " << n << endl;
	hThread = CreateThread(NULL, 0, Add, (void*)inc, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();
	// ���� ���� ����� Add �������� ������
	WaitForSingleObject(hThread, INFINITE);
	// ��������� ���������� ������ Add
	CloseHandle(hThread);
	cout << "n = " << n << endl;

	system("pause");
	return 0;
}

DWORD WINAPI Add(LPVOID iNum)
{
	cout << "Thread is started." << endl;
	n += (int)iNum;
	cout << "Thread is finished." << endl;
	return 0;
}