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

STDMETHODIMP CATLCryptXiObject::SetKey(BSTR key, BSTR* result)
{
	//HRESULT BSTRToArray(LPSAFEARRAY * ppArray) throw();
	//HRESULT ArrayToBSTR(const SAFEARRAY * pSrc) throw();
	char* keyCharArr = (char*)key;
	unsigned const char* cuKeyCharArr = (const unsigned char*)key;
	printf_s("BSTR key: %S\n", key);
	printf_s("BSTR keyCharArr: %S\n", keyCharArr);
	printf_s("BSTR cuKeyCharArr: %S\n", cuKeyCharArr);


	//const size_t newsize = (tmp.Length() + 1) * 2;
	//char* nstring = (char*)key;
	//unsigned char keyUser[sizeof(key)];
	//memcpy(&keyUser, &key, sizeof(key));

	//std::cout << *keyUser << std::endl;
	//printf_s("keyUser: %s\n", keyUser);

	unsigned char keyDefault[] = "Whatever it says, it is just some code.";
	Blowfish blowfish;
	blowfish.SetKey(keyDefault, sizeof(keyDefault));

	// Input/Output length must be a multiple of the block length (64bit)
	unsigned char text[448];
	//memcpy(&text, &cuKeyCharArr, sizeof(cuKeyCharArr));
	//printf_s("sizeof(cuKeyCharArr): %d\n", sizeof(cuKeyCharArr));
	//unsigned char text[] = "Hello World Plain Text! Hello World Plain Text! WOW!!! :)";

	//blowfish.Encrypt(text, reinterpret_cast<const unsigned char*>(cuKeyCharArr), sizeof(cuKeyCharArr));
	blowfish.Encrypt(text, cuKeyCharArr, sizeof(cuKeyCharArr));
	printf_s("Encrypted: %s\n", text);

	blowfish.Decrypt(text, text, sizeof(text));
	printf_s("Decrypted: %s\n", text);

	// Convert a _bstr_t string to a CComBSTR string.
	CComBSTR newResult;
	newResult.Append((char*)text);
	*result = newResult;

	printf("Component::SetKey() says: %S\n", *result);


	return S_OK;
}


STDMETHODIMP CATLCryptXiObject::Encrypt(BSTR PlainText, BSTR* EncryptedText)
{
	unsigned char* plain = {};
	memcpy(&plain, &PlainText, sizeof(PlainText));

	//char* testText = "Hello from Encrypt()!";
	//plain = (unsigned char*)PlainText;
	//memcpy(&plain, &testText, sizeof(testText));

	printf_s("plain in Encrypt(): %s\n", plain);

	Blowfish blowfish;
	unsigned char keyDefault[] = "somekey!";
	blowfish.SetKey(keyDefault, sizeof(keyDefault));

	unsigned char* encrypted = {};
	blowfish.Encrypt(encrypted, plain, sizeof(encrypted));
	printf_s("Encrypted in Encrypt(): %s\n", encrypted);

	blowfish.Decrypt(plain, encrypted, sizeof(plain));
	printf_s("Decrypted in Encrypt(): %s\n", plain);

	// Convert a _bstr_t string to a CComBSTR string.
	CComBSTR newResult((char*)encrypted);

	*EncryptedText = newResult;

	return S_OK;
}


STDMETHODIMP CATLCryptXiObject::Decrypt(BSTR EncryptedText, BSTR* DecryptedText)
{
	/*CComBSTR tmp;
	tmp.Append(EncryptedText);*/
	unsigned char* encrypted = {};
	memcpy(&encrypted, &EncryptedText, sizeof(EncryptedText));

	printf_s("plain in encrypted: %s\n", encrypted);

	Blowfish blowfish;

	unsigned char keyDefault[] = "somekey";
	blowfish.SetKey(keyDefault, sizeof(keyDefault));

	unsigned char plain[256] = {};

	blowfish.Encrypt(encrypted, plain, sizeof(plain));
	printf_s("Encrypted in Encrypt(): %s\n", encrypted);

	//blowfish.Decrypt(plain, encrypted, sizeof(encrypted));
	//printf_s("Decrypted in Decrypt(): %s\n", plain);

	// Convert a _bstr_t string to a CComBSTR string.
	CComBSTR newResult((char*)plain);

	*DecryptedText = newResult;

	return S_OK;
}
