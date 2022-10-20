// ScopedHelper.h: interface for the CScopedHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCOPEDHELPER_H__0FF7EF44_E5CF_48B3_BD93_EFCFCDEDDE74__INCLUDED_)
#define AFX_SCOPEDHELPER_H__0FF7EF44_E5CF_48B3_BD93_EFCFCDEDDE74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScopedHandle  
{
public:
    CScopedHandle(): m_handle(INVALID_HANDLE_VALUE) {}
    explicit CScopedHandle(HANDLE h): m_handle(h) {};
    virtual ~CScopedHandle(){
        if (NULL != m_handle && INVALID_HANDLE_VALUE != m_handle)
            CloseHandle(m_handle);
    };

    HANDLE get() {return m_handle;}
private:
    CScopedHandle(const CScopedHandle&);
    CScopedHandle& operator = (const CScopedHandle&);
    HANDLE m_handle;
};

class CScopedVirtualAlloc
{
public:
    CScopedVirtualAlloc(HANDLE hprocess, void* addr, size_t size, UINT32 alloctype, UINT32 flprotect)
        : m_processhandle(hprocess),
        m_ptr(VirtualAllocEx(hprocess, addr, size, alloctype, flprotect)){
    };
    virtual ~CScopedVirtualAlloc(){
        if (NULL != m_ptr)
            VirtualFreeEx(m_processhandle, m_ptr, 0, MEM_RELEASE);
    };
    
    void* get() {return m_ptr;}
private:
    CScopedVirtualAlloc();
    CScopedVirtualAlloc(const CScopedVirtualAlloc&);
    CScopedVirtualAlloc& operator = (const CScopedVirtualAlloc&);
    HANDLE m_processhandle;
    void* m_ptr;
};

class ScopedVirtualProtect
{
public:
    ScopedVirtualProtect(void* addr, size_t size, UINT32 protect)
        :m_addr(addr), m_size(size), m_oldprotect(0), protectok(false){
        protectok = VirtualProtect(addr, size, protect, (DWORD*)&m_oldprotect);
    }
    ~ScopedVirtualProtect(){
        if (protectok)
            VirtualProtect(m_addr, m_size, m_oldprotect, (DWORD*)&m_oldprotect);
    }
private:
    BOOL protectok;
    void* m_addr;
    size_t m_size;
    UINT32 m_oldprotect;
};

#endif // !defined(AFX_SCOPEDHELPER_H__0FF7EF44_E5CF_48B3_BD93_EFCFCDEDDE74__INCLUDED_)
