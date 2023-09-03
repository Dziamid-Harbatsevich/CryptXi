// ATLCryptXiObject.h : Declaration of the CATLCryptXiObject

#pragma once
#include "resource.h"       // main symbols



#include "CryptXiATL_i.h"
#include "blowfish.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CATLCryptXiObject

class ATL_NO_VTABLE CATLCryptXiObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CATLCryptXiObject, &CLSID_ATLCryptXiObject>,
	public ISupportErrorInfo,
	public IDispatchImpl<IATLCryptXiObject, &IID_IATLCryptXiObject, &LIBID_CryptXiATLLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CATLCryptXiObject()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CATLCryptXiObject)
	COM_INTERFACE_ENTRY(IATLCryptXiObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(SetKey)(BSTR key, BSTR* result);
	STDMETHOD(Test)(LONG x, LONG* y);
};

OBJECT_ENTRY_AUTO(__uuidof(ATLCryptXiObject), CATLCryptXiObject)
