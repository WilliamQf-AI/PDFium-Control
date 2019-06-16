// Copyright 2017, 2018, 2019 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <windows.h>
#include <shlwapi.h>
#include <ShlObj.h>

#include <olectl.h>
#include <stdio.h>

#include "resource.h"

#define DEFINE_DATA

#include "PDFIumControl.h"

#include "PDFIumControl_i.c"
#include "PDFiumControl_IAcroAXDocShim_i.c"

WCHAR OBJECT_NAME[][64] = {L"InnoVisioNate.PDFIumControl",L"InnoVisioNate.PDFiumControlPropertyPage",NULL};

WCHAR OBJECT_NAME_V[][64] = {L"InnoVisioNate.PDFIumControl.1",L"InnoVisioNate.PDFiumControlPropertyPage.1",NULL};

WCHAR OBJECT_DESCRIPTION[][64] = {L"InnoVisioNate PDFium Control Object",L"InnoVisioNate PDFium Control Property Page Object"};

WCHAR OBJECT_VERSION[][8] = {L"1.0",L"1.0"};

CLSID OBJECT_CLSID[] = {CLSID_PDFiumControl,CLSID_PDFiumControlPropertyPage,GUID_NULL};

CLSID OBJECT_LIBID[] = {LIBID_PDFiumControl,LIBID_PDFiumControl};

   extern "C" BOOL WINAPI DllMain(HINSTANCE hI, DWORD dwReason, LPVOID) {

   switch ( dwReason ) {

   case DLL_PROCESS_ATTACH: {

      hModule = reinterpret_cast<HMODULE>(hI);

      GetModuleFileNameW(hModule,szwModuleName,1024);

      ITypeLib *ptLib;

      LoadTypeLib(szwModuleName,&ptLib);

      if ( ptLib )
         ptLib -> GetTypeInfoOfGuid(IID_IPDFiumControl,&pITypeInfo_IPDFiumControl);

      wcscat_s(szwModuleName,MAX_PATH,L"\\2");

      LoadTypeLib(szwModuleName,&ptLib);

      if ( ptLib )
         ptLib -> GetTypeInfoOfGuid(IID_IPDFiumControl_IAcroAXDocShim,&pITypeInfo_IAcroAXDocShim);

      WCHAR *p = wcsrchr(szwModuleName,L'\\');

      *p = L'\0';

      }

      break;
  
   case DLL_PROCESS_DETACH:
      break;
  
   }
  
   return TRUE;
   }


   class Factory : public IClassFactory {
   public:

      Factory(CLSID theObjectId) : myObjectId(theObjectId), refCount(0) {};
      ~Factory() {};
  
      STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
      STDMETHOD_ (ULONG, AddRef)();
      STDMETHOD_ (ULONG, Release)();
      STDMETHOD (CreateInstance)(IUnknown *punkOuter, REFIID riid, void **ppv);
      STDMETHOD (LockServer)(BOOL fLock);
  
   private:
      CLSID myObjectId;
      int refCount;
   };
  
  
   static Factory factory[2] {Factory(CLSID_PDFiumControl), Factory(CLSID_PDFiumControlPropertyPage) };
  
   STDAPI DllCanUnloadNow(void) {
   return S_FALSE;
   }
  
  
  
   STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppObject) {
   *ppObject = NULL;
   if ( rclsid == OBJECT_CLSID[0] ) 
      return factory[0].QueryInterface(riid,ppObject);
   if ( rclsid == OBJECT_CLSID[1] )
      return factory[1].QueryInterface(riid,ppObject);
   return CLASS_E_CLASSNOTAVAILABLE;
   }
  
  
   STDAPI DllRegisterServer() {

   HRESULT rc = S_OK;
   ITypeLib *ptLib;
   HKEY keyHandle,clsidHandle;
   DWORD disposition;
   WCHAR szwTemp[256];
   LPOLESTR oleString;

   rc = LoadTypeLib(szwModuleName,&ptLib);
   rc = RegisterTypeLib(ptLib,szwModuleName,NULL);

   for ( long objIndex = 0; 1; objIndex++ ) {

      if ( GUID_NULL == OBJECT_CLSID[objIndex] )
         break;

      WCHAR szwCLSID[256];

      StringFromCLSID(OBJECT_CLSID[objIndex],&oleString);
      wcscpy_s(szwCLSID,256,oleString);
  
      RegOpenKeyEx(HKEY_CLASSES_ROOT,L"CLSID",0,KEY_CREATE_SUB_KEY,&keyHandle);
  
      RegCreateKeyEx(keyHandle,szwCLSID,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&clsidHandle,&disposition);
      RegSetValueEx(clsidHandle,NULL,0,REG_SZ,(BYTE *)OBJECT_DESCRIPTION[objIndex],2 * (DWORD)wcslen(OBJECT_DESCRIPTION[objIndex]));
  
      RegCreateKeyEx(clsidHandle,L"Control",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)L'\0',2);
  
      RegCreateKeyEx(clsidHandle,L"ProgID",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)OBJECT_NAME_V[objIndex],2 * (DWORD)wcslen(OBJECT_NAME_V[objIndex]));
  
      RegCreateKeyEx(clsidHandle,L"InprocServer",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)szwModuleName,2 * (DWORD)wcslen(szwModuleName));
  
      RegCreateKeyEx(clsidHandle,L"InprocServer32",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)szwModuleName,2 * (DWORD)wcslen(szwModuleName));
//      RegSetValueEx(keyHandle,"ThreadingModel",0,REG_SZ,(BYTE *)"Free",10);
      RegSetValueEx(keyHandle,L"ThreadingModel",0,REG_SZ,(BYTE *)L"Apartment",18);
  
      RegCreateKeyEx(clsidHandle,L"LocalServer",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)szwModuleName,2 * (DWORD)wcslen(szwModuleName));
    
      RegCreateKeyEx(clsidHandle,L"TypeLib",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
          StringFromCLSID(OBJECT_LIBID[objIndex],&oleString);
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)oleString,2 * (DWORD)wcslen(oleString));
        
      RegCreateKeyEx(clsidHandle,L"ToolboxBitmap32",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
//      swprintf_s(szwTemp,"%s, 1",szModuleName);
//      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)szwTemp,strlen(szModuleName));
  
      RegCreateKeyEx(clsidHandle,L"Version",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)OBJECT_VERSION[objIndex],2 * (DWORD)wcslen(OBJECT_VERSION[objIndex]));
  
      RegCreateKeyEx(clsidHandle,L"MiscStatus",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)L"0",4);
  
      RegCreateKeyEx(keyHandle,L"1",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      swprintf_s(szwTemp,256,L"%ld",
                 OLEMISC_ALWAYSRUN |
                 OLEMISC_ACTIVATEWHENVISIBLE | 
                 OLEMISC_RECOMPOSEONRESIZE | 
                 OLEMISC_INSIDEOUT |
                 OLEMISC_SETCLIENTSITEFIRST |
                 OLEMISC_CANTLINKINSIDE );
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)szwTemp,2 * (DWORD)wcslen(szwTemp));
  
      RegCreateKeyEx(HKEY_CLASSES_ROOT,OBJECT_NAME[objIndex],0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegCreateKeyEx(keyHandle,L"CurVer",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)OBJECT_NAME_V[objIndex],2 * (DWORD)wcslen(OBJECT_NAME_V[objIndex]));

      RegCreateKeyEx(HKEY_CLASSES_ROOT,OBJECT_NAME_V[objIndex],0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegCreateKeyEx(keyHandle,L"CLSID",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&keyHandle,&disposition);
      RegSetValueEx(keyHandle,NULL,0,REG_SZ,(BYTE *)szwCLSID,2 * (DWORD)wcslen(szwCLSID));

   }

   return S_OK;
   }
  
  
   STDAPI DllUnregisterServer() {

   HRESULT rc = S_OK;
   HKEY keyHandle;
   WCHAR szwCLSID[256];
   LPOLESTR oleString;
  
   for ( long objIndex = 0; 1; objIndex++ ) {

      if ( GUID_NULL == OBJECT_CLSID[objIndex] )
         break;

      StringFromCLSID(OBJECT_CLSID[objIndex],&oleString);

      wcscpy_s(szwCLSID,256,oleString);
  
      RegOpenKeyEx(HKEY_CLASSES_ROOT,L"CLSID",0,KEY_CREATE_SUB_KEY,&keyHandle);

      rc = SHDeleteKey(keyHandle,szwCLSID);

      rc = SHDeleteKey(HKEY_CLASSES_ROOT,OBJECT_NAME[objIndex]);

      rc = SHDeleteKey(HKEY_CLASSES_ROOT,OBJECT_NAME_V[objIndex]);

   }

   return S_OK;
   }
  
  
   long __stdcall Factory::QueryInterface(REFIID iid, void **ppv) { 
   *ppv = NULL; 
   if ( iid == IID_IUnknown || iid == IID_IClassFactory ) 
      *ppv = this; 
   else 
      return E_NOINTERFACE; 
   AddRef(); 
   return S_OK; 
   } 
  
  
   unsigned long __stdcall Factory::AddRef() { 
   return ++refCount; 
   } 
  
  
   unsigned long __stdcall Factory::Release() { 
   return --refCount;
   } 
  
  
   HRESULT STDMETHODCALLTYPE Factory::CreateInstance(IUnknown *punkOuter, REFIID riid, void **ppv) { 
   HRESULT hres = E_NOINTERFACE;
   *ppv = NULL; 
   if ( myObjectId == OBJECT_CLSID[0] ) {
      PDFiumControl *pef  = new PDFiumControl(punkOuter);
      hres = pef -> QueryInterface(riid,ppv);
      if ( ! *ppv ) 
         delete pef;
      return hres;
   }
   if ( myObjectId == OBJECT_CLSID[1] ) {
      PDFiumControl *pef = new PDFiumControl(punkOuter);
      hres = pef -> GetIOleObject() -> PropertyPage(0) ->  QueryInterface(riid,ppv);
      if ( ! *ppv ) 
         delete pef;
      return hres;
   }
   return hres;
   } 
  
  
   long __stdcall Factory::LockServer(int fLock) { 
   return S_OK; 
   }
