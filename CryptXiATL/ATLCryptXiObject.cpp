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

	Blowfish blowfish;
	unsigned char keyDefault[] = "somekey";
	blowfish.SetKey(keyDefault, sizeof(keyDefault));

	// Input/Output length must be a multiple of the block length (64bit)
	//unsigned char text[448];
	//memcpy(&text, &cuKeyCharArr, sizeof(cuKeyCharArr));
	//printf_s("sizeof(cuKeyCharArr): %d\n", sizeof(cuKeyCharArr));
	unsigned char text[] = "Hello World Plain Text Inside ATL! :)";

	//blowfish.Encrypt(text, reinterpret_cast<const unsigned char*>(cuKeyCharArr), sizeof(cuKeyCharArr));
	blowfish.Encrypt(text, text, sizeof(text));
	printf_s("Encrypted: %s\n", text);

	blowfish.Decrypt(text, text, sizeof(text));
	printf_s("Decrypted: %s\n", text);

	// Convert unsigned char* string to a CComBSTR string.
	CComBSTR newResult;
	newResult.Append((char*)text);
	*result = newResult;

	printf("Component::SetKey() says: %S\n", *result);


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
