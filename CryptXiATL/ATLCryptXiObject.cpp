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
	printf_s("key in SetKey(): %S\n", key);

	CComBSTR tmp;
	tmp.Append(key);

	printf_s("tmp.Append(key) in SetKey(): %S\n", tmp);

	unsigned char* keyUser = {};

	printf_s("unsigned char* keyUser in SetKey(): %S\n", keyUser);

	memcpy(&keyUser, &tmp, sizeof(tmp));

	printf_s("memcpy() in SetKey(): %S\n", keyUser);

	VarUI1FromStr((LPCOLESTR)key, LOCALE_USER_DEFAULT, 0, keyUser);
	//HRESULT VarUI1FromStr(
	//	[in]  LPCOLESTR strIn,
	//	[in]  LCID      lcid,
	//	[in]  ULONG     dwFlags,
	//	[out] BYTE * pbOut
	//);

	//std::string strPacket = W2A(*packet);
	//unsigned char* pBuffer = new unsigned char[strPacket.length() + 1];
	//memset(pBuffer, 0, strPacket.length() + 1);
	//memcpy(pBuffer, strPacket.c_str(), strPacket.length() + 1);

	printf_s("keyUser in SetKey(): %S\n", keyUser);

	//unsigned char keyDefault[] = "Whatever it says, it is just some code.";

	Blowfish blowfish;
	blowfish.SetKey(keyUser, sizeof(keyUser));

	//// Input/Output length must be a multiple of the block length (64bit)
	unsigned char text[256] = "Hello World! Wow!";
	//strcpy(&text, &keyUser);
	//memcpy(&text, &text, sizeof(keyUser));

	blowfish.Encrypt(text, keyUser, sizeof(text));
	printf_s("Encrypted: %S\n", text);

	blowfish.Decrypt(text, text, sizeof(text));
	printf_s("Decrypted: %S\n", text);

	// Convert a _bstr_t string to a CComBSTR string.
	CComBSTR newResult((BSTR)text);
	//unsigned char* text = text;

	//CComBSTR res;
	//res.Append((char*)text);

	*result = newResult;

	return S_OK;
}


STDMETHODIMP CATLCryptXiObject::Encrypt(BSTR PlainText, BSTR* EncryptedText)
{
	unsigned char plain[256] = {};
	memcpy(&plain, &PlainText, sizeof(PlainText));

	//printf_s("plain in Encrypt(): %s\n", plain);

	unsigned char keyDefault[] = "Whatever it says, it is just some code.";
	Blowfish blowfish;
	blowfish.SetKey(keyDefault, sizeof(keyDefault));

	unsigned char encrypted[256] = {};
	blowfish.Encrypt(encrypted, plain, sizeof(plain));
	//printf_s("Encrypted in Encrypt(): %s\n", encrypted);

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

	unsigned char keyDefault[] = "Whatever it says, it is just some code.";
	Blowfish blowfish;
	blowfish.SetKey(keyDefault, sizeof(keyDefault));

	unsigned char plain[256] = {};
	blowfish.Decrypt(plain, encrypted, sizeof(encrypted));
	//printf_s("Decrypted in Decrypt(): %s\n", plain);

	// Convert a _bstr_t string to a CComBSTR string.
	CComBSTR newResult((char*)plain);

	*DecryptedText = newResult;

	return S_OK;
}
