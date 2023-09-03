// ATLCryptXiObject.cpp : Implementation of CATLCryptXiObject

#include "pch.h"
#include "ATLCryptXiObject.h"


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
	// TODO: Add your implementation code here
	// TODO: Add your implementation code here
	//CComBSTR tmp("Wow, ");
	//tmp.Append(key);
	//*result = tmp;



	unsigned char keyDefault[] = "Whatever it says, it is just some code.";

	Blowfish blowfish;
	blowfish.SetKey(keyDefault, sizeof(keyDefault));

	// Input/Output length must be a multiple of the block length (64bit)
	unsigned char text[64] = "Hello World Plain Text! Hello World Plain Text! WOW!!! :)";

	blowfish.Encrypt(text, text, sizeof(text));
	printf_s("Encrypted: %s", text);

	blowfish.Decrypt(text, text, sizeof(text));
	printf_s("Decrypted: %s", text);

	blowfish.Encrypt(text, text, sizeof(text));
	printf_s("Encrypted: %s", text);

	blowfish.Decrypt(text, text, sizeof(text));
	printf_s("Decrypted: %s", text);



	// Debug
	printf("Component says: received key %s\n", keyDefault);

	return S_OK;
}


STDMETHODIMP CATLCryptXiObject::Test(LONG x, LONG* y)
{
	// TODO: Add your implementation code here
	*y = x + 3;

	return S_OK;
}
