// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   HRESULT __stdcall PDFiumControl::QueryInterface(REFIID riid, void** ppv) {

   *ppv = 0;

   if ( IID_IUnknown == riid )
      *ppv = this;
   else
      if ( IID_IPDFiumControl == riid )
         *ppv = static_cast<IPDFiumControl *>(this);

   if ( * ppv ) {
      AddRef();
      return S_OK;
   }

   if ( IID_IConnectionPointContainer == riid ) 
      return connectionPointContainer.QueryInterface(riid,ppv);

   //
   // Hosting MSHTML 
   //

   if ( IID_IOleInPlaceSite == riid )
      return pIOleInPlaceSite_HTML_Host -> QueryInterface(riid,ppv);

   if ( IID_IOleInPlaceSiteEx == riid )
      return pIOleInPlaceSite_HTML_Host -> QueryInterface(riid,ppv);

   if ( IID_IOleDocumentSite == riid ) 
      return pIOleDocumentSite_HTML_Host -> QueryInterface(riid,ppv);

   if ( IID_IOleInPlaceFrame == riid ) 
      return pIOleInPlaceFrame_HTML_Host -> QueryInterface(riid,ppv);

   if ( DIID_DWebBrowserEvents2 == riid )
      return pDWebBrowserEvents_HTML_Host -> QueryInterface(riid,ppv);

   if ( IID_IElementBehaviorFactory == riid )
      return pIElementBehaviorFactory -> QueryInterface(riid,ppv);

   if ( IID_IElementBehavior == riid )
      return pIElementBehavior -> QueryInterface(riid,ppv);

   if ( IID_IHTMLPainter == riid ) 
      return pIHTMLPainter -> QueryInterface(riid,ppv);

   //
   // Mimicking the Adobe Reader interface
   //

   if ( IID_IPDFiumControl_IAcroAXDocShim == riid || IID_IAcroAXDocShim == riid ) {

      if ( NULL == pIAcroAXDocShim )
         pIAcroAXDocShim = new _IAcroAXDocShim(this);

      return pIAcroAXDocShim -> QueryInterface(riid,ppv);

   }

   if ( fromOleObject )
      return E_NOINTERFACE;

   if ( ! pIOleObject )
      pIOleObject = new _IOleObject(this);

   return pIOleObject -> QueryInterface(riid,ppv);
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