#include "stdafx.h"
#include <string>
#include <algorithm>
#include <windows.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#define ADDIN_API __declspec(dllexport)

typedef struct tagDEBUGHELPER
{
    DWORD dwVersion;
    HRESULT(WINAPI *ReadDebuggeeMemory)(struct tagDEBUGHELPER *pThis, DWORD dwAddr, DWORD nWant, VOID* pWhere, DWORD *nGot);
    // from here only when dwVersion >= 0x20000
    DWORDLONG(WINAPI *GetRealAddress)(struct tagDEBUGHELPER *pThis);
    HRESULT(WINAPI *ReadDebuggeeMemoryEx)(struct tagDEBUGHELPER *pThis, DWORDLONG qwAddr, DWORD nWant, VOID* pWhere, DWORD *nGot);
    int (WINAPI *GetProcessorType)(struct tagDEBUGHELPER *pThis);
} DEBUGHELPER;

typedef HRESULT(WINAPI *CUSTOMVIEWER)(DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t max, DWORD reserved);

extern "C" ADDIN_API HRESULT BoostUuidFormatter(DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t max, DWORD reserved);

ADDIN_API HRESULT BoostUuidFormatter(DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t max, DWORD reserved)
{
    char uuid_data[16];
    DWORD bytesRead;
    HRESULT hr = pHelper->ReadDebuggeeMemoryEx(pHelper, pHelper->GetRealAddress(pHelper), sizeof(uuid_data), &uuid_data, &bytesRead);
    if (FAILED(hr))
        return hr;

    boost::uuids::uuid uuid;
    memcpy(&uuid, uuid_data, std::min<DWORD>(bytesRead, 16));
    std::string str = "{" + boost::uuids::to_string(uuid) + "}";
    sprintf_s(pResult, max, str.c_str());
    return S_OK;
}
