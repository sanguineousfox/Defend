#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include <aclapi.h>

int GetCurrentUserSid(PSID* pSID)
{
	const int MAX_NAME = 256;
	DWORD i, dwSize = 0;
	HANDLE hToken;
	PTOKEN_USER user;
	TOKEN_INFORMATION_CLASS TokenClass = TokenUser;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_READ | TOKEN_QUERY, &hToken))
		return GetLastError();

	if (!GetTokenInformation(hToken, TokenClass, NULL, 0, &dwSize))
	{
		DWORD dwResult = GetLastError();
		if (dwResult != ERROR_INSUFFICIENT_BUFFER)
		{
			return FALSE;
		}
	}

	user = (PTOKEN_USER)LocalAlloc(GPTR, dwSize);
	if (!GetTokenInformation(hToken, TokenClass, user, dwSize, &dwSize))
	{
		return FALSE;
	}

	DWORD dw_sid_len = GetLengthSid(user->User.Sid);
	*pSID = (SID*)LocalAlloc(GPTR, dw_sid_len);
	CopySid(dw_sid_len, *pSID, user->User.Sid);
	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hFile;
	EXPLICIT_ACCESS EA[2];
	PSID EveryoneSID = NULL, CurrentUserSID = NULL;
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
	SID_IDENTIFIER_AUTHORITY SIDAuthCU = SECURITY_NT_AUTHORITY;
	PACL pACL = NULL;
	DWORD dwRes, dwDisposition;
	PSECURITY_DESCRIPTOR pSD = NULL;
	SECURITY_ATTRIBUTES SA;
	LONG lRes;
	HKEY hkSub = NULL;

	ZeroMemory(&EA, 2 * sizeof(EXPLICIT_ACCESS));

	AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &EveryoneSID);
	EA[0].grfAccessPermissions = GENERIC_READ;
	EA[0].grfAccessMode = SET_ACCESS;
	EA[0].grfInheritance = NO_INHERITANCE;
	EA[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	EA[0].Trustee.ptstrName = (LPTSTR)EveryoneSID;

	GetCurrentUserSid(&CurrentUserSID);
	EA[1].grfAccessPermissions = GENERIC_ALL;
	EA[1].grfAccessMode = SET_ACCESS;
	EA[1].grfInheritance = NO_INHERITANCE;
	EA[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	EA[1].Trustee.ptstrName = (LPTSTR)CurrentUserSID;

	dwRes = SetEntriesInAcl(2, EA, NULL, &pACL);
	pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION);
	if (!SetSecurityDescriptorDacl(pSD, TRUE, pACL, FALSE))
		std::cout << "SetSecurityDescriptorDacl Error" << GetLastError() << std::endl;

	SA.nLength = sizeof(SECURITY_ATTRIBUTES);
	SA.lpSecurityDescriptor = pSD;
	SA.bInheritHandle = FALSE;

	lRes = RegCreateKeyEx(HKEY_CURRENT_USER, L"Key", 0, 0, 0, KEY_ALL_ACCESS, &SA, &hkSub, &dwDisposition);

	hFile = CreateFile(L"D:\\TEST.txt", GENERIC_READ, 0, &SA, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile)
		std::cout << "Не удалось создать файл." << std::endl;
	else
		std::cout << "Файл с требуемыми атрибутами создан." << std::endl;

Cleanup:

	if (EveryoneSID)
		FreeSid(EveryoneSID);
	if (CurrentUserSID)
		FreeSid(CurrentUserSID);
	if (pACL)
		LocalFree(pACL);
	if (pSD)
		LocalFree(pSD);
	if (hkSub)
		RegCloseKey(hkSub);

	return 0;
}