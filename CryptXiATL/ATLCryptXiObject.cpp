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

static void charToUCharArray(unsigned char** input, char* nstring, size_t charByteSize)
{
	unsigned char* result = new unsigned char[charByteSize + 1];
	for (int i = 0; i < charByteSize + 1; i++)
	{
		result[i] = static_cast<unsigned char>(nstring[i]);
	}
	memcpy(*input, result, charByteSize + 1);
	delete[] result;
}

static void castInput(BSTR* key, unsigned char** input, size_t inputByteSize)
{
	CComBSTR tmp(*key);
	char* nstring = new char[inputByteSize];
	CW2A tmpCW2A(tmp);
	strcpy_s(nstring, inputByteSize, tmpCW2A);
	charToUCharArray(input, nstring, inputByteSize);
	delete[] nstring;
}

STDMETHODIMP CATLCryptXiObject::SetKey(BSTR key, BSTR* result)
{
	size_t inputByteSize = SysStringByteLen(key);
	unsigned char* input = (unsigned char*)malloc(inputByteSize * sizeof(unsigned char));
	castInput(&key, &input, inputByteSize);

	blowfish.SetKey(input, sizeof(input));

	// Convert unsigned char* array to a CComBSTR.
	CComBSTR newResult;
	newResult.Append((LPCSTR)input);

	// Debug
	//std::cout << "Component::SetKey() says: " << (LPCSTR)ucBufText << std::endl;

	free(input);
	*result = newResult;

	return S_OK;
}

STDMETHODIMP CATLCryptXiObject::Encrypt(BSTR plainText, BSTR* encrypted)
{
	size_t inputByteSize = SysStringByteLen(plainText);
	unsigned char* input = (unsigned char*)malloc(inputByteSize * sizeof(unsigned char));
	castInput(&plainText, &input, inputByteSize);

	unsigned char* ucBufText = new unsigned char[inputByteSize * sizeof(unsigned char)];
	blowfish.Encrypt(ucBufText, reinterpret_cast<const unsigned char*>(input), inputByteSize);

	// Convert unsigned char* array to a CComBSTR.
	CComBSTR newResult;
	newResult.Append((LPCSTR)ucBufText);

	// Debug
	std::cout << "Component::Encrypt() says: " << (LPCSTR)ucBufText << std::endl;

	free(input);
	delete[] ucBufText;

	*encrypted = newResult;

	return S_OK;
}


STDMETHODIMP CATLCryptXiObject::Decrypt(BSTR encrypted, BSTR* decrypted)
{
	size_t inputByteSize = SysStringByteLen(encrypted);
	unsigned char* input = (unsigned char*)malloc(inputByteSize * sizeof(unsigned char));
	castInput(&encrypted, &input, inputByteSize);

	unsigned char* ucBufText = new unsigned char[inputByteSize * sizeof(unsigned char)];
	blowfish.Decrypt(ucBufText, reinterpret_cast<const unsigned char*>(input), inputByteSize);

	// Convert unsigned char* array to a CComBSTR.
	CComBSTR newResult;
	newResult.Append((LPCSTR)ucBufText);

	// Debug
	std::cout << "Component::Decrypt() ucBufText says: " << (LPCSTR)ucBufText << std::endl;

	free(input);
	delete[] ucBufText;

	*decrypted = newResult;

	return S_OK;
}
