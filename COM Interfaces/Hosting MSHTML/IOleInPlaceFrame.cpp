
#include "PDFiumControl.h"


   long __stdcall PDFiumControl::_IOleInPlaceFrame::QueryInterface(REFIID riid,void **ppv) {

   if ( ! ppv )
      return E_POINTER;

   *ppv = NULL;

   if ( IID_IUnknown == riid ) 
      *ppv = static_cast<IUnknown *>(this);
   else

   if ( IID_IOleInPlaceFrame == riid ) 
      *ppv = static_cast<IOleInPlaceFrame *>(this);
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();

   return S_OK;
   }
   unsigned long __stdcall PDFiumControl::_IOleInPlaceFrame::AddRef() {
   return ++refCount;
   }
   unsigned long __stdcall PDFiumControl::_IOleInPlaceFrame::Release() {
   return --refCount;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::GetWindow(HWND *gwh) {
   *gwh = hwndHost;
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::ContextSensitiveHelp(BOOL) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::GetBorder(RECT *) {
   return INPLACE_E_NOTOOLSPACE;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::RequestBorderSpace(LPCBORDERWIDTHS) {
   return INPLACE_E_NOTOOLSPACE;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::SetBorderSpace(LPCBORDERWIDTHS pBorderWidths) {
   return S_OK ;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::SetActiveObject(IOleInPlaceActiveObject *pObj,LPCOLESTR) {

   if ( pParent -> pIOleInPlaceActiveObject_HTML )
      pParent -> pIOleInPlaceActiveObject_HTML -> Release();

   pParent -> pIOleInPlaceActiveObject_HTML = NULL;

   pParent -> pIOleInPlaceActiveObject_HTML = pObj;

   if ( pObj )
      pParent -> pIOleInPlaceActiveObject_HTML -> AddRef();

   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::InsertMenus(HMENU,LPOLEMENUGROUPWIDTHS) {
   return E_UNEXPECTED;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::RemoveMenus(HMENU) {
   return E_UNEXPECTED;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::SetMenu(HMENU,HOLEMENU,HWND) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::SetStatusText(LPCOLESTR) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::EnableModeless(BOOL) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::TranslateAccelerator(MSG *,WORD) {
   return S_FALSE;
   }