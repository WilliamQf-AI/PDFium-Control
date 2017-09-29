
#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleClientSite::QueryInterface(REFIID riid,void **ppv) {

   if ( ! ppv )
      return E_POINTER;

   *ppv = NULL;

   if ( IID_IUnknown == riid ) 
      *ppv = static_cast<IUnknown *>(this);
   else

   if ( IID_IOleClientSite == riid ) 
      *ppv = static_cast<IOleClientSite *>(this);
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();

   return S_OK;
   }

   unsigned long __stdcall PDFiumControl::_IOleClientSite::AddRef() {
   return ++refCount;
   }

   unsigned long __stdcall PDFiumControl::_IOleClientSite::Release() {
   return --refCount;
   }


   HRESULT PDFiumControl::_IOleClientSite::SaveObject() {
   return S_OK;
   }

   
   HRESULT PDFiumControl::_IOleClientSite::GetMoniker(DWORD,DWORD,IMoniker**) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleClientSite::GetContainer(IOleContainer **) {
   return E_NOTIMPL;
   }


   HRESULT PDFiumControl::_IOleClientSite::ShowObject() {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleClientSite::OnShowWindow(BOOL) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleClientSite::RequestNewObjectLayout() {
   return S_OK;
   }
