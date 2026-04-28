#ifndef __DXGI_H__
#define __DXGI_H__

#include <objbase.h>

// DXGI Status Codes
#define DXGI_STATUS_OCCLUDED                     0x087A0001
#define DXGI_ERROR_NOT_FOUND                    0x887A0002
#define DXGI_ERROR_INVALID_CALL                 0x887A0001

// DXGI Format
typedef enum DXGI_FORMAT {
    DXGI_FORMAT_UNKNOWN = 0,
} DXGI_FORMAT;

// DXGI Mode Description
typedef struct DXGI_MODE_DESC {
    UINT Width;
    UINT Height;
    DXGI_FORMAT Format;
} DXGI_MODE_DESC;

// DXGI Adapter Description
typedef struct DXGI_ADAPTER_DESC {
    WCHAR Description[128];
    UINT VendorId;
    UINT DeviceId;
    UINT SubSysId;
    UINT Revision;
    SIZE_T DedicatedVideoMemory;
    SIZE_T DedicatedSystemMemory;
    SIZE_T SharedSystemMemory;
    LUID AdapterLuid;
} DXGI_ADAPTER_DESC;

// Forward declarations
typedef struct IDXGIAdapter IDXGIAdapter;
typedef struct IDXGIFactory IDXGIFactory;

// IDXGIAdapter vtable
typedef struct IDXGIAdapterVtbl {
    HRESULT (*QueryInterface)(IDXGIAdapter* This, REFIID riid, void** ppvObject);
    ULONG (*AddRef)(IDXGIAdapter* This);
    ULONG (*Release)(IDXGIAdapter* This);
    HRESULT (*SetPrivateData)(IDXGIAdapter* This, REFGUID Name, UINT DataSize, const void* pData);
    HRESULT (*SetPrivateDataInterface)(IDXGIAdapter* This, REFGUID Name, const IUnknown* pUnknown);
    HRESULT (*GetPrivateData)(IDXGIAdapter* This, REFGUID Name, UINT* pDataSize, void* pData);
    HRESULT (*GetParent)(IDXGIAdapter* This, REFIID riid, void** ppParent);
    HRESULT (*EnumOutputs)(IDXGIAdapter* This, UINT Output, void** ppOutput);
    HRESULT (*GetDesc)(IDXGIAdapter* This, DXGI_ADAPTER_DESC* pDesc);
    HRESULT (*CheckInterfaceSupport)(IDXGIAdapter* This, REFGUID InterfaceName, UINT* pUMDVersion);
} IDXGIAdapterVtbl;

struct IDXGIAdapter {
    const IDXGIAdapterVtbl* lpVtbl;
};

// IDXGIFactory vtable
typedef struct IDXGIFactoryVtbl {
    HRESULT (*QueryInterface)(IDXGIFactory* This, REFIID riid, void** ppvObject);
    ULONG (*AddRef)(IDXGIFactory* This);
    ULONG (*Release)(IDXGIFactory* This);
    HRESULT (*SetPrivateData)(IDXGIFactory* This, REFGUID Name, UINT DataSize, const void* pData);
    HRESULT (*SetPrivateDataInterface)(IDXGIFactory* This, REFGUID Name, const IUnknown* pUnknown);
    HRESULT (*GetPrivateData)(IDXGIFactory* This, REFGUID Name, UINT* pDataSize, void* pData);
    HRESULT (*GetParent)(IDXGIFactory* This, REFIID riid, void** ppParent);
    HRESULT (*EnumAdapters)(IDXGIFactory* This, UINT Adapter, IDXGIAdapter** ppAdapter);
    HRESULT (*MakeWindowAssociation)(IDXGIFactory* This, HWND WindowHandle, UINT Flags);
    HRESULT (*GetWindowAssociation)(IDXGIFactory* This, HWND* pWindowHandle);
    HRESULT (*CreateSwapChain)(IDXGIFactory* This, IUnknown* pDevice, void* pDesc, void** ppSwapChain);
    HRESULT (*CreateSoftwareAdapter)(IDXGIFactory* This, HMODULE Module, IDXGIAdapter** ppAdapter);
} IDXGIFactoryVtbl;

struct IDXGIFactory {
    const IDXGIFactoryVtbl* lpVtbl;
};

// DXGI function declarations
HRESULT WINAPI CreateDXGIFactory(REFIID riid, void** ppFactory);

// Stub implementation for CreateDXGIFactory
HRESULT WINAPI CreateDXGIFactory(REFIID riid, void** ppFactory) {
    // Return E_NOTIMPL to indicate not implemented
    return 0x80004001; // E_NOTIMPL
}

#endif // __DXGI_H__
