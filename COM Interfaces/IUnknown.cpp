
#include "PDFiumControl.h"

   HRESULT __stdcall PDFiumControl::QueryInterface(REFIID riid, void** ppv) {

   *ppv = 0;

   if ( IID_IUnknown == riid )
      *ppv = this;
   else

   if ( IID_IPDFiumControl == riid )
      *ppv = static_cast<IPDFiumControl *>(this);
   else

   if ( IID_IConnectionPointContainer == riid ) 
      *ppv = static_cast<IConnectionPointContainer *>(&connectionPointContainer);
   else

   //
   // Hosting MSHTML 
   //

   if ( IID_IOleInPlaceSite == riid )
      *ppv = static_cast<IOleInPlaceSite *>(pIOleInPlaceSite_HTML_Host);
   else

   if ( IID_IOleInPlaceSiteEx == riid )
      *ppv = static_cast<IOleInPlaceSiteEx *>(pIOleInPlaceSite_HTML_Host);
   else

   if ( IID_IOleDocumentSite == riid ) 
      *ppv = static_cast<IOleDocumentSite *>(pIOleDocumentSite_HTML_Host);
   else

   if ( IID_IOleInPlaceFrame == riid ) 
      *ppv = static_cast<IOleInPlaceFrame *>(pIOleInPlaceFrame_HTML_Host);
   else

   if ( riid == DIID_DWebBrowserEvents2 )
      return pDWebBrowserEvents_HTML_Host -> QueryInterface(riid,ppv);
   else

   //
   // Mimicking the Adobe Reader interface
   //

   if ( IID_IPDFiumControl_IAcroAXDocShim == riid || IID_IAcroAXDocShim == riid ) {
      if ( NULL == pIAcroAXDocShim )
         pIAcroAXDocShim = new _IAcroAXDocShim(this);
      return pIAcroAXDocShim -> QueryInterface(riid,ppv);
   } else {

      if ( fromOleObject )
         return E_NOINTERFACE;

      if ( ! pIOleObject )
         pIOleObject = new _IOleObject(this);

      return pIOleObject -> QueryInterface(riid,ppv);

   }

   AddRef();

   return S_OK;
   }


   ULONG __stdcall PDFiumControl::AddRef() {
   return refCount++;
   }


   ULONG __stdcall PDFiumControl::Release() { 
   if ( --refCount == 0 ) {
      delete this;
      return 0;
   }
   return refCount;
   }