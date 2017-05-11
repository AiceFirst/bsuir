
#include "main.h"

/*
�������� ����. ����� ���, ��� ���������, ���������� ������� ������������ test123 � �������

ReadAce(); ���������� ������� ����������
����� ����������� ����� ��� ��� test123 � ������� ����� � ��������� (��������� ����� � ���������)
ReadAce(); ���������� ������� ����������
�������� ������� ��� (��� ��, ��� �� ��������� �� ������� ����)
ReadAce(); ���������� ������� ����������


����!!! �����!!! �������� ������ ���, ������� � �������� ��� ���������� ������������� �������
��� ���������� ��-�� ������������� �������� ��� (��� ��������� ������ � ������� DACL)
*/

int main()
{
	ReadAce();
		
	wchar_t wchDirName[248] = L"test";       // ��� ��������
	wchar_t wchUserName[UNLEN] = L"test123";    // ��� ������������

	ACL *lpOldDacl;    // ��������� �� ������ DACL
	ACL *lpNewDacl;    // ��������� �� ����� DACL
	LPVOID lpAce;      // ��������� �� ������� ACE

	DWORD dwDaclLength = 0;        // ����� DACL
	DWORD dwSdLength = 0;          // ����� SD
	DWORD dwSidLength = 0;         // ����� SID
	DWORD dwLengthOfDomainName = 0;    // ����� ����� ������

	PSID lpSid = NULL;             // ��������� �� ����������� SID
	LPTSTR lpDomainName = NULL;    // ��������� �� ��� ������

	SID_NAME_USE typeOfSid;        // ��� ������� ������

	SECURITY_DESCRIPTOR *lpSd = NULL;  // ����� ����������� ������������
	SECURITY_DESCRIPTOR sdAbsoluteSd;  // ���������� ������ SD
	BOOL bDaclPresent;             // ������� ����������� ������ DACL
	BOOL bDaclDefaulted;           // ������� ������ DACL �� ���������

	DWORD dwRetCode;   // ��� ��������

	// �������� ����� ����������� ������������
	if (!GetFileSecurity(
		wchDirName,    // ��� �����
		DACL_SECURITY_INFORMATION,   // �������� DACL
		lpSd,          // ����� ����������� ������������
		0,             // ���������� ����� ������
		&dwSdLength))  // ����� ��� ��������� �����
	{
		dwRetCode = GetLastError();

		if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
			// ������������ ������ ��� ������
			lpSd = (SECURITY_DESCRIPTOR*) new char[dwSdLength];
		else
		{
			// ������� �� ���������
			printf("Get file security failed.\n");
			printf("Error code: %d\n", dwRetCode);

			return dwRetCode;
		}
	}

	// ������ ���������� ������������
	if (!GetFileSecurity(
		wchDirName,    // ��� �����
		DACL_SECURITY_INFORMATION,   // �������� DACL
		lpSd,          // ����� ����������� ������������
		dwSdLength,    // ����� ������
		&dwSdLength))  // ����� ��� ��������� �����
	{
		dwRetCode = GetLastError();
		printf("Get file security failed.\n");
		printf("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	// ���������� ����� SID ������������
	if (!LookupAccountName(
		NULL,          // ���� ��� �� ��������� ����������
		wchUserName,   // ��� ������������
		NULL,          // ���������� ����� SID
		&dwSidLength,  // ����� SID
		NULL,          // ���������� ��� ������
		&dwLengthOfDomainName,     // ����� ����� ������
		&typeOfSid))   // ��� ������� ������
	{
		dwRetCode = GetLastError();

		if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
		{
			// ������������ ������ ��� SID
			lpSid = (SID*) new char[dwSidLength];
			lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
		}
		else
		{
			// ������� �� ���������
			printf("Lookup account name failed.\n");
			printf("Error code: %d\n", dwRetCode);

			return dwRetCode;
		}
	}

	// ���������� SID
	if (!LookupAccountName(
		NULL,          // ���� ��� �� ��������� ����������
		wchUserName,   // ��� ������������
		lpSid,         // ��������� �� SID
		&dwSidLength,  // ����� SID
		lpDomainName,  // ��������� �� ��� ������
		&dwLengthOfDomainName,   // ����� ����� ������
		&typeOfSid))   // ��� ������� ������
	{
		dwRetCode = GetLastError();

		printf("Lookup account name failed.\n");
		printf("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	// �������� ������ DACL �� ����������� ������������
	if (!GetSecurityDescriptorDacl(
		lpSd,              // ����� ����������� ������������
		&bDaclPresent,     // ������� ����������� ������ DACL
		&lpOldDacl,        // ����� ��������� �� DACL
		&bDaclDefaulted))  // ������� ������ DACL �� ���������
	{
		dwRetCode = GetLastError();
		printf("Get security descriptor DACL failed.\n");
		printf("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	// ���������� ����� ������ DACL
	dwDaclLength = lpOldDacl->AclSize +
		sizeof(ACCESS_ALLOWED_ACE)-sizeof(DWORD)+dwSidLength;

	// ������������ ������ ��� ����� DACL
	lpNewDacl = (ACL*)new char[dwDaclLength];

	// �������������� ����� DACL
	if (!InitializeAcl(
		lpNewDacl,       // ����� DACL
		dwDaclLength,    // ����� DACL
		ACL_REVISION))   // ������ DACL
	{
		dwRetCode = GetLastError();

		printf("Lookup account name failed.\n");
		printf("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	// ��������� ������ ������� � ����� DACL
	if (!AddAccessAllowedAce(
		lpNewDacl,       // ����� DACL
		ACL_REVISION,    // ������ DACL
		FILE_WRITE_DATA | FILE_READ_DATA,  // ��������� ������ ��������
		lpSid))          // ����� SID
	{
		dwRetCode = GetLastError();
		perror("Add access allowed ace failed.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	// �������� ����� ������� ACE � ������ ������ DACL
	if (!GetAce(
		lpOldDacl,     // ����� ������� DACL
		0,             // ���� ������ �������
		&lpAce))       // ����� ������� ��������
	{
		dwRetCode = GetLastError();

		printf("Get ace failed.\n");
		printf("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	// ������������ �������� �� ������� DACL � ����� DACL
	if (bDaclPresent)
	{	
		if (!AddAce(
			lpNewDacl,       // ����� ������ DACL
			ACL_REVISION,    // ������ DACL
			MAXDWORD,        // ��������� � ����� ������
			lpAce,           // ����� ������� DACL
			lpOldDacl->AclSize - sizeof(ACL)))  // ����� ������� DACL
		{
			dwRetCode = GetLastError();
			perror("Add access allowed ace failed.\n");
			printf("The last error code: %u\n", dwRetCode);

			return dwRetCode;
		}
	}

	// ��������� ������������� DACL
	if (!IsValidAcl(lpNewDacl))
	{
		dwRetCode = GetLastError();
		perror("The new ACL is invalid.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	// ������� ����� ���������� ������������ � ���������� �����
	if (!InitializeSecurityDescriptor(
		&sdAbsoluteSd,       // ����� ��������� SD
		SECURITY_DESCRIPTOR_REVISION))
	{
		dwRetCode = GetLastError();
		perror("Initialize security descriptor failed.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	// ������������� DACL  � ����� ���������� ������������
	if (!SetSecurityDescriptorDacl(
		&sdAbsoluteSd,   // ����� ����������� ������������
		TRUE,            // DACL ������������
		lpNewDacl,       // ��������� �� DACL
		FALSE))          // DACL �� ����� �� ���������
	{
		dwRetCode = GetLastError();
		perror("Set security descriptor DACL failed.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	// ��������� ��������� ����������� ������������
	if (!IsValidSecurityDescriptor(&sdAbsoluteSd))
	{
		dwRetCode = GetLastError();
		perror("Security descriptor is invalid.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}
	// ������������� ����� ���������� ������������
	if (!SetFileSecurity(
		wchDirName,        // ��� �����
		DACL_SECURITY_INFORMATION,     // ������������� DACL
		&sdAbsoluteSd))    // ����� ����������� ������������
	{
		dwRetCode = GetLastError();
		printf("Set file security failed.\n");
		printf("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	ReadAce();

	DeleteAce(lpNewDacl, 0);

	// ��������� ������������� DACL
	if (!IsValidAcl(lpNewDacl))
	{
		dwRetCode = GetLastError();
		perror("The new ACL is invalid.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	// ������� ����� ���������� ������������ � ���������� �����
	if (!InitializeSecurityDescriptor(
		&sdAbsoluteSd,       // ����� ��������� SD
		SECURITY_DESCRIPTOR_REVISION))
	{
		dwRetCode = GetLastError();
		perror("Initialize security descriptor failed.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	// ������������� DACL  � ����� ���������� ������������
	if (!SetSecurityDescriptorDacl(
		&sdAbsoluteSd,   // ����� ����������� ������������
		TRUE,            // DACL ������������
		lpNewDacl,       // ��������� �� DACL
		FALSE))          // DACL �� ����� �� ���������
	{
		dwRetCode = GetLastError();
		perror("Set security descriptor DACL failed.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	// ��������� ��������� ����������� ������������
	if (!IsValidSecurityDescriptor(&sdAbsoluteSd))
	{
		dwRetCode = GetLastError();
		perror("Security descriptor is invalid.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}
	// ������������� ����� ���������� ������������
	if (!SetFileSecurity(
		wchDirName,        // ��� �����
		DACL_SECURITY_INFORMATION,     // ������������� DACL
		&sdAbsoluteSd))    // ����� ����������� ������������
	{
		dwRetCode = GetLastError();
		printf("Set file security failed.\n");
		printf("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	ReadAce();

	// ����������� ������
	delete[] lpSd;
	delete[] lpSid;
	delete[] lpDomainName;
	delete[] lpNewDacl;

	return 0;
}


int ReadAce()
{
	setlocale(0, "");

	system("cls");
	LPCWSTR fname = L"test";

	//fname = L"C:\\windows";

	wcout << "file:" << fname << "\n";

	PSECURITY_DESCRIPTOR psd = NULL;
	PACL pdacl;
	ACL_SIZE_INFORMATION aclSize = { 0 };
	PSID sidowner = NULL;
	PSID sidgroup = NULL;


	ULONG result = GetNamedSecurityInfo(fname
		, SE_FILE_OBJECT
		, OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION
		, &sidowner
		, &sidgroup
		, &pdacl
		, NULL
		, &psd); 

	//if (result != ERROR_SUCCESS){ return NULL; }

	wchar_t oname[256];
	wchar_t asd[4] = L"���";
	DWORD namelen;
	wchar_t* doname = new TCHAR[512];
	DWORD domainnamelen;
	SID_NAME_USE peUse;
	ACCESS_ALLOWED_ACE* ace;

 	LookupAccountSid(NULL, sidowner, oname, &namelen, doname, &domainnamelen, &peUse);

	wcout << "Owner: " << doname << " " << oname << " ";

	LookupAccountSid(NULL, sidgroup, oname, &namelen, doname, &domainnamelen, &peUse);
	wcout << "Group: " << doname << "/" << oname << "\n";

	wcout << "\n\n\n::DACL::" << "\n";
	SID *sid;
	unsigned long i, mask;
	char *stringsid;

	for (int i = 0; i<(*pdacl).AceCount; i++) {
		int c = 1;
		BOOL b = GetAce(pdacl, i, (PVOID*)&ace);

		//SID *sid = (SID *) ace->SidStart;
		if (((ACCESS_ALLOWED_ACE *)ace)->Header.AceType == ACCESS_ALLOWED_ACE_TYPE) {

			sid = (SID *)&((ACCESS_ALLOWED_ACE *)ace)->SidStart;
			LookupAccountSid(NULL, sid, oname, &namelen, doname, &domainnamelen, &peUse);
			wcout << "SID: " << doname << "/" << oname << "\n";
			mask = ((ACCESS_ALLOWED_ACE *)ace)->Mask;
		}
		else if (((ACCESS_DENIED_ACE *)ace)->Header.AceType == ACCESS_DENIED_ACE_TYPE) {
			sid = (SID *)&((ACCESS_DENIED_ACE *)ace)->SidStart;
			LookupAccountSid(NULL, sid, oname, &namelen, doname, &domainnamelen, &peUse);
			wcout << "SID: " << doname << "/" << oname << "\n";
			mask = ((ACCESS_DENIED_ACE *)ace)->Mask;
		}
		else printf("Other ACE\n");

		wcout << "ACE: mask:" << ace->Mask << " sidStart:" << ace->SidStart << " header type=" << (ace->Header.AceType ? "deny" : "allow") << " header flags=" << ace->Header.AceFlags << "\n";
		if (DELETE & ace->Mask) {
			wcout << " DELETE" << "\n";
		}
		if (FILE_GENERIC_READ & ace->Mask) {
			wcout << " FILE_GENERIC_READ" << "\n";
		}
		if (FILE_GENERIC_WRITE & ace->Mask) {
			wcout << " FILE_GENERIC_WRITE" << "\n";
		}
		if (FILE_GENERIC_EXECUTE & ace->Mask) {
			wcout << " FILE_GENERIC_EXECUTE" << "\n";
		}
		if (GENERIC_READ & ace->Mask) {
			wcout << " GENERIC_READ" << "\n";
		}
		if (GENERIC_WRITE & ace->Mask) {
			wcout << " GENERIC_WRITE" << "\n";
		}
		if (GENERIC_EXECUTE & ace->Mask) {
			wcout << " GENERIC_EXECUTE" << "\n";
		}
		if (GENERIC_ALL & ace->Mask) {
			wcout << " GENERIC_ALL" << "\n";
		}
		if (READ_CONTROL & ace->Mask) {
			wcout << " READ_CONTROL" << "\n";
		}
		if (WRITE_DAC & ace->Mask) {
			wcout << " WRITE_DAC" << "\n";
		}
		if (WRITE_OWNER & ace->Mask) {
			wcout << " WRITE_OWNER" << "\n";
		}
		if (SYNCHRONIZE & ace->Mask) {
			wcout << " SYNCHRONIZE" << "\n";
		}
		wcout << "\n";
	}
	/*
	SECURITY_DESCRIPTOR* p1 = (SECURITY_DESCRIPTOR*)psd;

	wcout << "\n\n\n::SECURITY_DESCRIPTOR_CONTROL::" << "\n";

	SECURITY_DESCRIPTOR_CONTROL ctrl = (*p1).Control;
	if (SE_OWNER_DEFAULTED & ctrl) {
		wcout << " SE_OWNER_DEFAULTED" << "\n";
	}
	if (SE_DACL_PRESENT & ctrl) {
		wcout << " SE_DACL_PRESENT" << "\n";
	}
	if (SE_DACL_DEFAULTED & ctrl) {
		wcout << " SE_DACL_DEFAULTED" << "\n";
	}
	if (SE_SACL_PRESENT & ctrl) {
		wcout << " SE_SACL_PRESENT" << "\n";
	}
	if (SE_SACL_DEFAULTED & ctrl) {
		wcout << " SE_SACL_DEFAULTED" << "\n";
	}
	if (SE_DACL_AUTO_INHERIT_REQ & ctrl) {
		wcout << " SE_DACL_AUTO_INHERIT_REQ" << "\n";
	}
	if (SE_SACL_AUTO_INHERIT_REQ & ctrl) {
		wcout << " SE_SACL_AUTO_INHERIT_REQ" << "\n";
	}
	if (SE_SACL_AUTO_INHERITED & ctrl) {
		wcout << " SE_SACL_AUTO_INHERITED" << "\n";
	}
	if (SE_DACL_PROTECTED & ctrl) {
		wcout << " SE_DACL_PROTECTED" << "\n";
	}
	if (SE_SACL_PROTECTED & ctrl) {
		wcout << " SE_SACL_PROTECTED" << "\n";
	}
	if (SE_RM_CONTROL_VALID & ctrl) {
		wcout << " SE_RM_CONTROL_VALID" << "\n";
	}
	if (SE_SELF_RELATIVE & ctrl) {
		wcout << " SE_SELF_RELATIVE" << "\n";
	}*/

	LocalFree(psd);
	LocalFree(sidowner);
	//LocalFree(pdacl);
	system("pause");
	return 0;
}