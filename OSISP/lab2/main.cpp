#include "main.h"

/*
BOOL CreateProcess(
	LPCTSTR lpApplicationName, // ��� ������������ ������
	LPTSTR lpCommandLine, // ��������� ������
	LPSECURITY_ATTRIBUTES lpProcessAttributes, // �������� ������ ��������
	LPSECURITY_ATTRIBUTES lpThreadAttributes, // �������� ������ ������
	BOOL bInheritHandle, // ����������� �� ����������
	DWORD dwCreationFlags, // ����� �������� ��������
	LPVOID lpEnvironment, // ���� ����� ����� ���������
	LPCTSTR lpCurrentDirectory, // ������� �������
	LPSTARTUPINFO lpStartUpInfo, // ��� �������� ����
	LPPROCESS_INFORMATION lpProcessInformation // ���������� � ��������

);
*/

int main(int argc, char *argv[])
{
	const wchar_t lpszAppName[17] = L"test_process.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	// ������� ����� ���������� �������
	if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
	{
		cout << "The new process is not created.\n";
		system("pause");
		return 0;
	}
	cout << "The new process is created.\n";
	// ���� ���������� ���������� �������
	WaitForSingleObject(piApp.hProcess, INFINITE);
	// ��������� ����������� ����� �������� � ������� ��������
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	cout << "Process closed.\n";
	system("pause");
	return 0;
}