// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IElementBehavior::QueryInterface(REFIID riid,void **ppv) {
 
   if ( IID_IElementBehavior == riid )
      *ppv = static_cast<IElementBehavior *>(this); 
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();
  
   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IElementBehavior::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IElementBehavior::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IElementBehavior::Init(IElementBehaviorSite *pBehaviorSite) {
   if ( pIHTMLPaintSite )
      pIHTMLPaintSite -> Release();
   pBehaviorSite -> QueryInterface(IID_IHTMLPaintSite,reinterpret_cast<void **>(&pIHTMLPaintSite));
   return S_OK;
   }


   STDMETHODIMP PDFiumControl::_IElementBehavior::Notify(long theEvent,VARIANT *pVar) {
   return S_OK;
   }


   STDMETHODIMP PDFiumControl::_IElementBehavior::Detach() {
   return S_OK;
   }

