
#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::_IRunnableObject::QueryInterface(REFIID riid,void **ppv) {

   if ( IID_IRunnableObject == riid )
      *ppv = static_cast<IRunnableObject *>(this); 
   else
      return pParent -> QueryInterface(riid,ppv);
   
   AddRef();
   return S_OK;
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IRunnableObject::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IRunnableObject::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IOleObject::_IRunnableObject::GetRunningClass(CLSID *pcid) {
   *pcid = CLSID_PDFiumControl;
   return E_UNEXPECTED;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IRunnableObject::Run(LPBC pBindingContext) { 
   return S_OK; 
   }

   int __stdcall PDFiumControl::_IOleObject::_IRunnableObject::IsRunning() { 
   return 1; 
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IRunnableObject::LockRunning(BOOL,BOOL) { 
   return S_OK; 
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IRunnableObject::SetContainedObject(BOOL) { 
   return S_OK; 
   }

