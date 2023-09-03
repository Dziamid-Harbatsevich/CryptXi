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
	CComBSTR tmp("Wow, ");
	tmp.Append(key);
	*result = tmp;

	printf("Component::SetKey() says: %S\n", *result);

	return S_OK;
}


STDMETHODIMP CATLCryptXiObject::Test(LONG x, LONG* y)
{
	// TODO: Add your implementation code here
	*y = x + 3;

	return S_OK;
}
