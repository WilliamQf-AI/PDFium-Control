// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"


   long __stdcall PDFiumControl::_IOleObject::_IQuickActivate::QueryInterface(REFIID riid,void **ppv) {
 
   if ( IID_IQuickActivate == riid )
      *ppv = static_cast<IQuickActivate *>(this); 
   else
      return pParent -> QueryInterface(riid,ppv);
   AddRef();
   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IQuickActivate::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IQuickActivate::Release() {
   return pParent -> Release();
   }


   HRESULT PDFiumControl::_IOleObject::_IQuickActivate::QuickActivate(QACONTAINER* qaContainer,QACONTROL* qaControl) {

   DWORD dwDummy;

   pParent -> Advise(qaContainer -> pAdviseSink,&dwDummy);

   if ( qaContainer -> pAdviseSink )
      pParent -> pIViewObjectEx -> SetAdvise(DVASPECT_CONTENT,0,qaContainer -> pAdviseSink);

   qaControl -> cbSize = sizeof(QACONTROL);

   qaControl -> dwPointerActivationPolicy = 0xFFFF;

   pParent -> pIViewObjectEx -> GetViewStatus(&qaControl -> dwViewStatus);

   pParent -> GetMiscStatus(DVASPECT_CONTENT, &qaControl -> dwMiscStatus);

   pParent -> pIOleClientSite_MySite = qaContainer -> pClientSite;

   if ( pParent -> pIOleClientSite_MySite )
      pParent -> pIOleClientSite_MySite -> AddRef();

   return S_OK;
   }


   HRESULT PDFiumControl::_IOleObject::_IQuickActivate::SetContentExtent(SIZEL* pSizel) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleObject::_IQuickActivate::GetContentExtent(SIZEL* pSizel) {
   return S_OK;
   }