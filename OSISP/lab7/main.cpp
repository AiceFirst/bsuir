#include "main.h"

/*

LONG RegCreateKeyEx(
HKEY hKey,		// ���������� ��������� �����
LPCTSTR lpSubKey,	// ����� ����� ��������
DWORD Reserved,	// ���������������
LPTSTR lpClass,	// ����� ������ ������
DWORD dwOptions,	// ���� ������ �����
REGSAM samDesired,	// �������� ������ ������������
LPSECURITY_ATTRIBUTES lpSecurityAttributes,	// ����� ���������
// ����� ������������
PHKEY phkResult,	// ����� ������ ��� ��������� �����
LPDWORD lpdwDisposition 	// ����� ������ ������������ ��������
);

LONG RegSetValueEx(
HKEY hKey,		// ���������� �����
LPCTSTR lpValueName,// ����� ����� ���������������� ��������
DWORD Reserved,	// ���������������
DWORD dwType,	// ��� ������
CONST BYTE *lpData,	// ����� ������ ��� ���������
DWORD cbData		// ������ ������
);

LONG RegOpenKeyEx(
HKEY hKey,	// ���������� ���������� �����
LPCTSTR lpSubKey,	// ����� ����� ������������ ��������
DWORD ulOptions,	// ���������������
REGSAM samDesired,	// ����� ������� ������������
PHKEY phkResult 	// ����� ����������� ��������� �����
);

LONG RegQueryValueEx(
HKEY hKey,		// ���������� �����
LPTSTR lpValueName,	// ����� ����� ��������
LPDWORD lpReserved,	// ���������������
LPDWORD lpType,	// ����� ���������� ��� ���� ��������
LPBYTE lpData,	// ����� ������ ��� ������
LPDWORD lpcbData 	// ����� ���������� ��� ������ ������ ������
);

LONG RegDeleteValue(
HKEY hKey,	// ���������� �����
LPCTSTR lpValueName 	// ����� ����� ��������
);

LONG WINAPI RegDeleteKeyValue(
_In_      HKEY hKey,
_In_opt_  LPCTSTR lpSubKey,
_In_opt_  LPCTSTR lpValueName
);
*/

int main(int argc, char *argv[])
{
	HKEY hKey;
	DWORD test1 = 1;
	wchar_t test2[5] = L"test";
	//������� ������ Magic � HKEY_CURRENT_USER\\SOFTWARE\\Magic
	if (!RegCreateKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Magic", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL))
	{
		//���� ��� ������, ������� ��� �������� MyKey
		if (RegSetValueEx(hKey, L"MyKey1", 0, REG_DWORD, (LPBYTE)&test1, sizeof(DWORD)))
		{
			cout << "error RegSetValueEx1\n";
			return GetLastError();
		}

		if (RegSetValueEx(hKey, L"MyKey2", 0, REG_SZ, (LPBYTE)&test2, sizeof(test2)))
		{
			cout << "error RegSetValueEx2\n";
			return GetLastError();
		}
	}
	else
	{
		cout << "error RegCreateKeyEx\n";
		return GetLastError();
	}
	//��������� ����
	RegCloseKey(hKey);

	cout << "HKEY_CURRENT_USER\\SOFTWARE\\Magic created" << endl;
	system("pause");
	
	if (!RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Magic", 0, KEY_READ, &hKey))
	{

		DWORD pvData = { 0 };
		DWORD pcbData = sizeof (pvData);
		if (RegGetValue(hKey, NULL, L"MyKey1", RRF_RT_REG_DWORD, 0, &pvData, &pcbData))
		{
			cout << "error RegGetValue\n";
			return GetLastError();
		}
		cout << "MyKey1: " << pvData << endl;

		char cData[5] = { 0 };
		DWORD bufSize = sizeof cData;
		
		if (RegGetValueA(hKey, NULL, "MyKey2", RRF_RT_REG_SZ, 0, &cData, &bufSize))
		{
			cout << "error RegGetValue\n";
			return GetLastError();
		}
		cout << "MyKey2: " << cData << endl;
	}
	else
	{
		cout << "error RegOpenKeyEx\n";
		return GetLastError();
	}
	//��������� ���� �������
	RegCloseKey(hKey);

	system("pause");
	
	if (!RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE", 0, KEY_READ, &hKey))
	{
		if (RegDeleteKeyValue(hKey, L"Magic", L"MyKey1"))
		{
			cout << "error RegDeleteKeyValue\n" << GetLastError();
			return GetLastError();
		}

	}
	else
	{
		cout << "error RegOpenKeyEx\n";
		return GetLastError();
	}
	//��������� ���� �������
	RegCloseKey(hKey);

	cout << "HKEY_CURRENT_USER\\SOFTWARE\\Magic\\Mykey1 deleted" << endl;
	system("pause");

	if (!RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE", 0, KEY_READ, &hKey))
	{
		if (RegDeleteKey(hKey, L"Magic"))
		{
			cout << "error RegDeleteValue\n" << GetLastError();
			return GetLastError();
		}
	}
	else
	{
		cout << "error RegOpenKeyEx\n";
		return GetLastError();
	}
	
	cout << "HKEY_CURRENT_USER\\SOFTWARE\\Magic deleted" << endl;
	system("pause");

	return 0;
}