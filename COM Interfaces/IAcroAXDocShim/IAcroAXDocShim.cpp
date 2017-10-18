// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::put_src(BSTR sourceDocument) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::get_src(BSTR *pSourceDocument) { return E_NOTIMPL; }

/*
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::put_messageHandler(VARIANT messageHandler) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::get_messageHandler(VARIANT *pMessageHandler) { return E_NOTIMPL; }
*/

   VARIANT_BOOL PDFiumControl::_IAcroAXDocShim::LoadFile(BSTR fileName ) { return VARIANT_FALSE; }

   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setShowToolbar(VARIANT_BOOL On ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::gotoFirstPage ( ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::gotoLastPage ( ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::gotoNextPage ( ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::gotoPreviousPage ( ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setCurrentPage (long n ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::goForwardStack ( ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::goBackwardStack ( ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setPageMode (BSTR pageMode ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setLayoutMode (BSTR layoutMode ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setNamedDest (BSTR namedDest ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::Print ( ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::printWithDialog ( ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setZoom (float percent ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setZoomScroll (float percent,float left,float top ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setView (BSTR viewMode ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setViewScroll(BSTR viewMode,float offset ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setViewRect (float left,float top,float width,float height ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::printPages (long from,long to ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::printPagesFit (long from,long to,VARIANT_BOOL shrinkToFit ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::printAll ( ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::printAllFit (VARIANT_BOOL shrinkToFit ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setShowScrollbars (VARIANT_BOOL On ) { return E_NOTIMPL; }
/*
   VARIANT __stdcall PDFiumControl::_IAcroAXDocShim::GetVersions() { return ? }
*/

   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setCurrentHightlight (long a,long b,long c,long d ) { return E_NOTIMPL; }
   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::setCurrentHighlight (long a,long b,long c,long d ) { return E_NOTIMPL; }
