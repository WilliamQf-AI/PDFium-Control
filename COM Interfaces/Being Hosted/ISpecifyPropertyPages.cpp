// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::_ISpecifyPropertyPages::QueryInterface(REFIID riid,void **ppv) {

   *ppv = NULL; 

   if ( riid == IID_ISpecifyPropertyPages )
      *ppv = static_cast<ISpecifyPropertyPages *>(this);
   else
 
      return pParent -> QueryInterface(riid,ppv);
 
   AddRef();
   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_ISpecifyPropertyPages::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_ISpecifyPropertyPages::Release() {
   return pParent -> Release();
   }


   HRESULT PDFiumControl::_IOleObject::_ISpecifyPropertyPages::GetPages(CAUUID *pCAUUID) {

   if ( ! pCAUUID )
      return E_POINTER;

   pCAUUID -> cElems = 1;

   pCAUUID -> pElems = reinterpret_cast<GUID *>(CoTaskMemAlloc(pCAUUID -> cElems * sizeof(GUID)));

   memset(pCAUUID -> pElems,0,pCAUUID -> cElems * sizeof(GUID));

   pCAUUID -> pElems[0] = CLSID_PDFiumControlPropertyPage;


   return S_OK;
   }