// Copyright 2017, 2018, 2019 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IElementBehaviorFactory::QueryInterface(REFIID riid,void **ppv) {
 
   if ( IID_IElementBehaviorFactory == riid )
      *ppv = static_cast<IElementBehaviorFactory *>(this); 
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();
  
   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IElementBehaviorFactory::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IElementBehaviorFactory::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IElementBehaviorFactory::FindBehavior(BSTR bstrBehavior,BSTR bstrBehaviorUrl,IElementBehaviorSite *pSite,IElementBehavior **ppBehavior) {
   pParent -> pIElementBehaviorFactory -> pIElementBehaviorSite = pSite;
   if ( ! ppBehavior )
      return E_POINTER;
   *ppBehavior = NULL;
   pParent -> pIElementBehavior -> QueryInterface(IID_IElementBehavior,reinterpret_cast<void **>(ppBehavior));
   return S_OK;
   }

