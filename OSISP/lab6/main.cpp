#include "main.h"

DWORD  __stdcall ThreadUpdate(LPVOID  param);

HANDLE  hTimer = NULL;
BOOL    aborts = FALSE;


int main(int argc, char *argv[])
{
	HANDLE hThread;
	DWORD IDThread;

	LARGE_INTEGER  due;
	ZeroMemory(&due, sizeof(LARGE_INTEGER));
	due.QuadPart = -20000000;   // 2 - ������� ����� ������� �������
	hTimer = CreateWaitableTimer(NULL, FALSE, L"MyTimer");
	if (hTimer == NULL) {
		cout << "error CreateWaitableTimer" << endl;
		return GetLastError();
	}
	if (!SetWaitableTimer(hTimer, &due, 1000, NULL, NULL, 0)) {  // ������ ������ � ���������� 1 -���
		cout << "error SetWaitableTimer" << endl;
		return GetLastError();
	}

	hThread = CreateThread(NULL, 0, Thread, NULL, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();

	while (!GetAsyncKeyState(VK_ESCAPE)); // ����� �� ����������� ���������� ������ ��� ESC

	aborts = FALSE;      // ������� ����� ����� � ����� ��� ����������
	CloseHandle(hThread);
	CancelWaitableTimer(hTimer);
	CloseHandle(hTimer);
	return 0;
}

DWORD WINAPI Thread(LPVOID iNum)
{
	aborts = TRUE;
	while (aborts) {
		if (WaitForSingleObjectEx(hTimer, INFINITE, FALSE) == WAIT_OBJECT_0)
		{
			time_t seconds = time(NULL);
			tm* timeinfo = localtime(&seconds);
			cout << "Current time " << asctime(timeinfo);
		}

	}
	return 0;
}