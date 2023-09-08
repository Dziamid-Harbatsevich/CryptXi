// ATLCryptXiObject.cpp : Implementation of CATLCryptXiObject

#include "pch.h"
#include "ATLCryptXiObject.h"
#include <string>
#include <comdef.h>
#include "cryptxi_helper.h"

#include <iostream>

// CATLCryptXiObject

STDMETHODIMP CATLCryptXiObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IATLCryptXiObject
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void charToUCharArray(unsigned char** text, char* nstring, size_t charByteSize) {
	unsigned char* result = new unsigned char[charByteSize + 1];
	//unsigned char result[2 + (2 * charByteSize)] = {};
	// unsigned_char_arr[i]= static_cast<unsigned char>(char_arr[i]);

	std::cout << "charToUCharArray.text = " << text << std::endl;
	std::cout << "charToUCharArray.nstring = " << nstring << std::endl;
	std::cout << "charToUCharArray.sizeof(text) = " << sizeof(text) << std::endl;
	std::cout << "charToUCharArray.sizeof(nstring) = " << sizeof(nstring) << std::endl;
	

	for (int i = 0; i < charByteSize + 1; i++)
	{
		//std::cout << "nstring[i] = " << nstring[i] << std::endl;

		result[i] = static_cast<unsigned char>(nstring[i]);

		//std::cout << "result[i] = " << result[i] << std::endl;
	}

	std::cout << "charToUCharArray end result = " << result << std::endl;
	memcpy(*text, result, charByteSize + 1);
	delete[] result;
	std::cout << "charToUCharArray end *text = " << *text << std::endl;
}

STDMETHODIMP CATLCryptXiObject::SetKey(BSTR key, BSTR* result)
{
	
	CComBSTR tmp(key);
	size_t keyByteSize = tmp.ByteLength();
	printf_s("CComBSTR(key).ByteLength): %d\n", keyByteSize);


	//////////////////////////////
	//allocate the array
	//int** arr = new int* [row];
	//for (int i = 0; i < row; i++)
	//	arr[i] = new int[col];
	char* nstring = new char[keyByteSize];

	// Convert to a char*
	//const size_t newsize = 100;
	//char nstring[newsize];
	CW2A tmpstr1(tmp);
	//strcpy_s(nstring, tmpstr1);
	strcpy_s(nstring, keyByteSize, tmpstr1);
	//strcat_s(nstring, " (char *)");
	std::cout << "(char *)nstring = " << nstring << std::endl;
	printf_s("sizeof(nstring): %d\n", sizeof(nstring));

	//// Convert to a wchar_t*
	//wchar_t wcstring[newsize];
	//wcscpy_s(wcstring, tmp);
	//wcscat_s(wcstring, L" (wchar_t *)");
	//std::wcout << wcstring << std::endl;
	//printf_s("sizeof(wcstring): %d\n", sizeof(wcstring));

	//// Convert to a _bstr_t
	//_bstr_t bstrt(tmp);
	//bstrt += " (_bstr_t)";
	//std::cout << bstrt << std::endl;
	//printf_s("sizeof(bstrt): %d\n", sizeof(bstrt));

	// Convert to a CString
	//CString cstring(tmp);
	//cstring += " (CString)";
	//std::cout << cstring << std::endl;

	// Convert to a basic_string
	//wstring basicstring(tmp);
	//basicstring += L" (basic_string)";
	//std::wcout << basicstring << std::endl;    // Convert to a System::String
	//String^ systemstring = gcnew String(tmp);
	//systemstring += " (System::String)";
	//Console::WriteLine("{0}", systemstring);
	//delete systemstring;



	////////////////////////////

	//std::string str = tmp.PtrToStringBSTR();

	//char arr[str.length() + 1];

	//strcpy(arr, str.c_str());
	//std::cout << "String to char array conversion:\n";
	//for (int i = 0; i < str.length(); i++)
	//	std::cout << arr[i];

	///////////////////////////

	////BSTR bstr = SysAllocString(L"This is a basic string which encoded in UTF-16!!ɏ");
	//int len = WideCharToMultiByte(CP_UTF8, 0, key, -1, NULL, 0, NULL, NULL);
	//SAFEARRAYBOUND bound;
	//bound.cElements = len;
	//bound.lLbound = 0;
	//SAFEARRAY* sa = SafeArrayCreate(VT_UI1, 1, &bound);
	//char* safeBuf = nullptr;
	//if (len > 0) {
	//	SafeArrayAccessData(sa, (void**)&safeBuf);
	//	WideCharToMultiByte(CP_UTF8, 0, key, -1, safeBuf, len, NULL, NULL);
	//	std::cout << "Byte Array: " << safeBuf << std::endl;
	//	SafeArrayUnaccessData(sa);
	//}
	//SafeArrayDestroy(sa);
	////SysFreeString(bstr);

	//printf_s("safeBuf: %s\n", safeBuf);
	//printf_s("sizeof(safeBuf): %d\n", sizeof(safeBuf));

	///////////////////////////

	//BSTR bstr = SysAllocString(L"This is a basic string which encoded in UTF-16!!");
	//int len = WideCharToMultiByte(CP_UTF8, 0, bstr, -1, NULL, 0, NULL, NULL);
	//SAFEARRAYBOUND bound;
	//bound.cElements = len;
	//bound.lLbound = 0;
	//SAFEARRAY* sa = SafeArrayCreate(VT_UI1, 1, &bound);
	//char* testCharArr = nullptr;
	//if (len > 0) {
	//	SafeArrayAccessData(sa, (void**)&testCharArr);
	//	WideCharToMultiByte(CP_UTF8, 0, bstr, -1, testCharArr, len, NULL, NULL);
	//	//cout << "Byte Array: " << testCharArr << std::endl;
	//	SafeArrayUnaccessData(sa);
	//}
	//SafeArrayDestroy(sa);
	//SysFreeString(bstr);

	//std::cout << "String testCharArr by char:\n";
	//for (int i = 0; i < sizeof(testCharArr) / sizeof(testCharArr)[0]; i++)
	//{
	//	std::cout << testCharArr[i] << std::endl;
	//}

	//std::cout << "String testCharArr by byte:\n";
	//for (int i = 0; i < sizeof(testCharArr); i++)
	//{
	//	std::cout << testCharArr[i] << std::endl;
	//}

	///////////////////////////


	//size_t size = sizeof(unsigned char*);
	//printf_s("sizeof(unsigned char*): %d\n", size);
	//size = sizeof(unsigned char);
	//printf_s("sizeof(unsigned char): %d\n", size);

	//HRESULT BSTRToArray(LPSAFEARRAY * ppArray) throw();
	//HRESULT ArrayToBSTR(const SAFEARRAY * pSrc) throw();
	//char* keyCharArr = (char*)key;
	//unsigned char* uKeyCharArr = (unsigned char*)key;
	//unsigned const char* cuKeyCharArr = (unsigned const char*)key;
	//printf_s("BSTR key: %S\n", key);
	//printf_s("BSTR keyCharArr: %S\n", keyCharArr);
	//printf_s("BSTR cuKeyCharArr: %S\n", cuKeyCharArr);


	//const size_t newsize = (tmp.Length() + 1) * 2;
	//char* nstring = (char*)key;
	//unsigned char keyUser[sizeof(key)];
	//memcpy(&keyUser, &key, sizeof(key));

	//std::cout << *keyUser << std::endl;
	//printf_s("keyUser: %s\n", keyUser);

	Blowfish blowfish;
	unsigned char keyDefault[] = "somekey";
	blowfish.SetKey(keyDefault, sizeof(keyDefault));

	// Input/Output length must be a multiple of the block length (64bit)
	//unsigned char text[448];
	//memcpy(&text, &cuKeyCharArr, sizeof(cuKeyCharArr));
	//printf_s("sizeof(cuKeyCharArr): %d\n", sizeof(cuKeyCharArr));
	//unsigned char text[] = "Hello World Plain Text Inside ATL! :)";
	//unsigned char* text = (unsigned char*)nstring;
	//unsigned char text[1 + sizeof(nstring) / sizeof(nstring)[0]];
	
	std::cout << "sizeof(nstring) / sizeof(nstring)[0] = " << keyByteSize << std::endl;
	//unsigned char** ptrText = (unsigned char**)malloc((sizeof(nstring) / sizeof(nstring)[0]) * sizeof(unsigned char));
	unsigned char* text = (unsigned char*)malloc(keyByteSize * sizeof(unsigned char));
	charToUCharArray(&text, nstring, keyByteSize);
	//unsigned char* text = *ptrText;
	//unsigned char* text = reinterpret_cast<unsigned char*>(memory_buffer);
	std::cout << "unsigned char* text = " << text << std::endl;
	std::cout << "sizeof(text) = " << sizeof(text) << std::endl;

	unsigned char* ucBufText = new unsigned char[keyByteSize];
	blowfish.Encrypt(ucBufText, reinterpret_cast<const unsigned char*>(text), keyByteSize);
	//blowfish.Encrypt(text, text, sizeof(text));
	printf_s("Encrypted: %s\n", ucBufText);
	std::cout << "Encrypted = " << ucBufText << std::endl;
	printf_s("Encrypted strlen((char*)ucBufText): %d\n", strlen((char*)ucBufText));

	blowfish.Decrypt(ucBufText, ucBufText, keyByteSize);
	printf_s("Decrypted: %s\n", ucBufText);
	std::cout << "Decrypted = " << ucBufText << std::endl;
	printf_s("Decrypted strlen((char*)text): %d\n", strlen((char*)ucBufText));

	// Convert unsigned char* string to a CComBSTR string.
	CComBSTR newResult;


	_bstr_t bstrt(ucBufText);
	newResult.Append((LPCSTR)ucBufText);
	
	printf("Component::SetKey() says: %S\n", newResult);

	delete[] nstring;
	free(text);
	delete[] ucBufText;

	*result = newResult;

	return S_OK;
}


STDMETHODIMP CATLCryptXiObject::Encrypt(BSTR PlainText, BSTR* EncryptedText)
{
	//unsigned const char* cuPlainCharArr = (const unsigned char*)PlainText;

	Blowfish blowfish;
	unsigned char keyDefault[] = "somekey";
	blowfish.SetKey(keyDefault, sizeof(keyDefault));

	unsigned char cuPlainCharArr[] = "Hello World Plain Text Inside ATL! :)";
	unsigned char encrypted[448];

	blowfish.Encrypt(encrypted, cuPlainCharArr, sizeof(cuPlainCharArr));

	// Convert unsigned char* string to a CComBSTR string.
	CComBSTR newResult;
	newResult.Append((char*)encrypted);
	*EncryptedText = newResult;

	return S_OK;
}


STDMETHODIMP CATLCryptXiObject::Decrypt(BSTR EncryptedText, BSTR* DecryptedText)
{
	//unsigned const char* cuEncryptedCharArr = (const unsigned char*)EncryptedText;

	Blowfish blowfish;
	unsigned char keyDefault[] = "somekey";
	blowfish.SetKey(keyDefault, sizeof(keyDefault));

	unsigned char cuEncryptedCharArr[] = "WH,♂#Φû*⌐g{íâs╜↕)≤µ\8§·VΣ^╞eè╪ÉL! :)";
	unsigned char plain[448];

	blowfish.Decrypt(plain, cuEncryptedCharArr, sizeof(cuEncryptedCharArr));
	//printf_s("Decrypted in Decrypt(): %s\n", plain);

	// Convert unsigned char* string to a CComBSTR string.
	CComBSTR newResult;
	newResult.Append((char*)plain);
	*DecryptedText = newResult;

	return S_OK;
}
