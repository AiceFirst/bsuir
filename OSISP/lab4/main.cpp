#include "main.h"

/*
DWORD WaitForSingleObject(
	HANDLE hHandle, // ���������� �������
	DWORD dwMilliseconds // �������� �������� � �������������
);

DWORD WaitForMultipleObjects(
	DWORD nCount, // ���������� ��������
	CONST HANDLE *lpHandles, // ������ ������������ ��������
	BOOL bWaitAll, // ����� ��������
	DWORD dwMilliseconds // �������� �������� � �������������
);

HANDLE CreateMutex(
	LPSECURITY_ATTRIBUTES lpMutexAttributes, // �������� ������
	BOOL bInitialOwner, // ��������� �������� ��������
	LPCTSTR lpName // ��� ��������
);

BOOL ReleaseMutex(
	HANDLE hMutex // ���������� ��������
);
*/
HANDLE hMutex;

int main(int argc, char *argv[])
{
	HANDLE hThread[2];
	DWORD IDThread1, IDThread2;

	int id = 1;

	//hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"DemoMutex");
	hMutex = CreateMutex(NULL, FALSE, L"MyMutex");
	if (hMutex == NULL)
	{
		cout << "Open mutex failed." << endl;
		cout << "Press any key to exit." << endl;
		system("pause");
		return GetLastError();
	}

	hThread[0] = CreateThread(NULL, 0, Thread, (void*)id, 0, &IDThread1);
	if (hThread[0] == NULL)
		return GetLastError();

	id++;
	
	hThread[1] = CreateThread(NULL, 0, Thread, (void*)id, 0, &IDThread2);
	if (hThread[1] == NULL)
		return GetLastError();
	
	//���� ���������� ���� ���������
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	// ��������� ���������� �������
	CloseHandle(hMutex);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	system("pause");
	return 0;
}

DWORD WINAPI Thread(LPVOID iNum)
{
	for (int i = 0; i < 10; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);

		cout << "thread " << (int)iNum << endl;

		ReleaseMutex(hMutex);
	}
	return 0;
}