
#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::_IOleInPlaceActiveObject::QueryInterface(REFIID riid,void **ppv) {
 
   if ( IID_IOleInPlaceActiveObject == riid )
      *ppv = static_cast<IOleInPlaceActiveObject *>(this); 
   else
      return pParent -> QueryInterface(riid,ppv);

   AddRef();
  
   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IOleInPlaceActiveObject::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IOleInPlaceActiveObject::Release() {
   return pParent -> Release();
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceActiveObject::GetWindow(HWND *pHwnd) {
   *pHwnd = pParent -> pParent -> hwndSite;
   return S_OK;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceActiveObject::ContextSensitiveHelp(BOOL) {
   return E_NOTIMPL;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceActiveObject::TranslateAccelerator(MSG*) { 
   return S_OK;   
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceActiveObject::OnFrameWindowActivate(BOOL) {
   return S_OK;   
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceActiveObject::OnDocWindowActivate(BOOL) { 
   return S_OK;   
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceActiveObject::ResizeBorder(LPCRECT,IOleInPlaceUIWindow *,BOOL) {   
   return S_OK;   
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceActiveObject::EnableModeless(BOOL) {   
   return S_OK;   
   }