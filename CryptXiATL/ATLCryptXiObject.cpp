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

	for (int i = 0; i < charByteSize + 1; i++)
	{
		result[i] = static_cast<unsigned char>(nstring[i]);
	}

	memcpy(*text, result, charByteSize + 1);
	delete[] result;
}

STDMETHODIMP CATLCryptXiObject::SetKey(BSTR key, BSTR* result)
{
	CComBSTR tmp(key);
	size_t keyByteSize = tmp.ByteLength();
	char* nstring = new char[keyByteSize];
	CW2A tmpstr1(tmp);
	strcpy_s(nstring, keyByteSize, tmpstr1);

	Blowfish blowfish;
	unsigned char keyDefault[] = "somekey";
	blowfish.SetKey(keyDefault, sizeof(keyDefault));
	
	unsigned char* text = (unsigned char*)malloc(keyByteSize * sizeof(unsigned char));
	charToUCharArray(&text, nstring, keyByteSize);

	unsigned char* ucBufText = new unsigned char[keyByteSize];
	blowfish.Encrypt(ucBufText, reinterpret_cast<const unsigned char*>(text), keyByteSize);

	// Debug
	printf_s("Encrypted: %s\n", ucBufText);
	std::cout << "Encrypted = " << ucBufText << std::endl;
	printf_s("Encrypted strlen((char*)ucBufText): %d\n", strlen((char*)ucBufText));

	blowfish.Decrypt(ucBufText, ucBufText, keyByteSize);

	// Debug
	printf_s("Decrypted: %s\n", ucBufText);
	std::cout << "Decrypted = " << ucBufText << std::endl;
	printf_s("Decrypted strlen((char*)text): %d\n", strlen((char*)ucBufText));

	// Convert unsigned char* array to a CComBSTR.
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
