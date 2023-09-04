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
	//CComBSTR tmp("Wow, ");
	//tmp.Append(key);
	//*result = tmp;

	//CComBSTR tmp;
	//tmp.Append(key);

	//_bstr_t bstrWrapper;
	//bstrWrapper.Assign(key);
	//WideCharToMultiByte(CP_UTF8, 0, &key[0], (int)bstrWrapper.length(), NULL, 0, NULL, NULL);
	//unsigned char* test = bstrWrapper;

	//CP_UTF8, 0, wcsString, -1,NULL, 0, NULL, NULL

	//unsigned char* b = {};

	// Declaration
	//unsigned char szBuff[100];
	//BSTR bstrVal = NULL;
	//WideCharToMultiByte(CP_UTF8, 0, &tmp[0], (int)tmp.Length(), NULL, 0, NULL, NULL);
	//strcpy(tmp, "codeguru.com");
	//bstrVal = _com_util::ConvertStringToBSTR(szBuff);



	// Free the allocation on variable bstrVal
	//::SysFreeString(bstrVal);

	//std::string keyStr;
	//keyStr.append(key) //.BSTRToArray(b); // cast from string to unsigned char*



	std::string keyString = ConvertBSTRToMBS(key);
	unsigned char keyChar[448];

	memcpy(&keyChar, &keyString, sizeof(keyString));


	unsigned char keyDefault[] = "Whatever it says, it is just some code.";

	Blowfish blowfish;
	blowfish.SetKey(keyChar, sizeof(keyDefault));

	// Input/Output length must be a multiple of the block length (64bit)
	unsigned char text[64] = "Hello World Plain Text! Hello World Plain Text! WOW!!! :)";

	blowfish.Encrypt(text, text, sizeof(text));
	//printf_s("Encrypted: %s", text);

	blowfish.Decrypt(text, text, sizeof(text));
	//printf_s("Decrypted: %s", text);

	//blowfish.Encrypt(text, text, sizeof(text));
	//printf_s("Encrypted: %s", text);

	//blowfish.Decrypt(text, text, sizeof(text));
	//printf_s("Decrypted: %s", text);

	//CComBSTR tmp("Wow, ");
	//tmp.Append(text);
	//* result = WideCharToMultiByte(text);



	// Declaration
	//WCHAR wszBuff[50];
	//BSTR bstrVal = NULL;

	// Convert from WCHAR to BSTR
	//wcscpy_s(wszBuff, L"{ text }");
	//bstrVal = ::SysAllocString(wszBuff);

	// Some code

	std::string resultStr;
	memcpy(&resultStr, &text, sizeof(text));


	*result = ConvertMBSToBSTR(resultStr);

	// Free the allocation on variable bstrVal
	//::SysFreeString(bstrVal);



	// Debug
	//printf("Component says: received key %s\n", keyDefault);

	return S_OK;
}


STDMETHODIMP CATLCryptXiObject::Test(LONG x, LONG* y)
{
	*y = x + 3;

	return S_OK;
}
