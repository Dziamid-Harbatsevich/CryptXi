// ATLCryptXiObject.cpp : Implementation of CATLCryptXiObject

#include "pch.h"
#include "ATLCryptXiObject.h"
#include <string>
#include <comdef.h>
#include "cryptxi_helper.h"


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
	CComBSTR tmp;
	tmp.Append(key);

	//const size_t newsize = (tmp.Length() + 1) * 2;
	//char* nstring = new char[newsize];
	unsigned char* keyUser = {};
	memcpy(&keyUser, &key, sizeof(key));

	//unsigned char keyDefault[] = "Whatever it says, it is just some code.";

	Blowfish blowfish;
	blowfish.SetKey(keyUser, sizeof(keyUser));

	// Input/Output length must be a multiple of the block length (64bit)
	unsigned char text[64] = "Hello World Plain Text! Hello World Plain Text! WOW!!! :)";

	blowfish.Encrypt(text, text, sizeof(text));
	//printf_s("Encrypted: %s", text);

	blowfish.Decrypt(text, text, sizeof(text));
	//printf_s("Decrypted: %s", text);

	// Convert a _bstr_t string to a CComBSTR string.
	CComBSTR newResult((char*)text);

	*result = newResult;

	return S_OK;
}


STDMETHODIMP CATLCryptXiObject::Test(LONG x, LONG* y)
{
	*y = x + 3;

	return S_OK;
}
