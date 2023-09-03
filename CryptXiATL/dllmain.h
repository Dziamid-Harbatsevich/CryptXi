// dllmain.h : Declaration of module class.

class CCryptXiATLModule : public ATL::CAtlDllModuleT< CCryptXiATLModule >
{
public :
	DECLARE_LIBID(LIBID_CryptXiATLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CRYPTXIATL, "{134ebb80-1e1f-4efa-b1fc-67c95420c81e}")
};

extern class CCryptXiATLModule _AtlModule;
