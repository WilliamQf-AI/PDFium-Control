// Copyright 2017, 2018, 2019 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IHTMLPainter::QueryInterface(REFIID riid,void **ppv) {
 
   if ( IID_IHTMLPainter == riid )
      *ppv = static_cast<IHTMLPainter *>(this);  
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();
  
   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IHTMLPainter::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IHTMLPainter::Release() {
   return pParent -> Release();
   }

   STDMETHODIMP PDFiumControl::_IHTMLPainter::Draw(RECT rcBounds,RECT rcUpdate,LONG lDrawFlags,HDC hdc,LPVOID pvDrawObject) {

   pParent -> connectionPointContainer.fire_Paint(hdc,&rcBounds);

   return S_OK;
   }


   STDMETHODIMP PDFiumControl::_IHTMLPainter::OnResize(SIZE size) {
   
   pParent -> connectionPointContainer.fire_Size(&size);

   return S_OK;
   }


   STDMETHODIMP PDFiumControl::_IHTMLPainter::GetPainterInfo(HTML_PAINTER_INFO *pInfo) {

   pInfo -> lFlags = HTMLPAINTER_OPAQUE | HTMLPAINTER_SUPPORTS_XFORM;
   pInfo -> lZOrder = HTMLPAINT_ZORDER_WINDOW_TOP;
   memset(&pInfo -> rcExpand,0,sizeof(RECT));
   memset(&pInfo -> iidDrawObject,0,sizeof(IID));
   
   return S_OK;
   }


   STDMETHODIMP PDFiumControl::_IHTMLPainter::HitTestPoint(POINT pt,BOOL *pbHit,LONG *plPartID) {
   return S_OK;
   }

