// Copyright 2017, 2018, 2019 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::_IPersistStorage::QueryInterface(REFIID riid,void **ppv) {

   *ppv = NULL;

   if ( IID_IPersistStorage == riid )
      *ppv = static_cast<IPersistStorage *>(this);
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();

   return S_OK;
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IPersistStorage::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IPersistStorage::Release() {
   return pParent -> Release();
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStorage::GetClassID(CLSID *pcid) {
   memcpy(pcid,&CLSID_PDFiumControl,sizeof(GUID));
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStorage::IsDirty() {
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStorage::InitNew(IStorage *pIStorage) {
   pParent -> pParent -> SetDefaults();
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStorage::Load(IStorage *pIStorage) {

   IStream *pIStream = NULL;

   HRESULT hr = pIStorage -> OpenStream(L"PDFiumControl",0,STGM_READ | STGM_SHARE_EXCLUSIVE,0,&pIStream);

   if ( ! ( S_OK == hr ) )
      return E_FAIL;

   hr = pParent -> pIPersistStreamInit -> Load(pIStream);

   pIStream -> Release();

   return hr;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStorage::Save(IStorage *pIStorage,BOOL sameAsLoad) {

   IStream *pIStream;

   HRESULT hr = pIStorage -> DestroyElement(L"PDFiumControl");

   hr = pIStorage -> CreateStream(L"PDFiumControl",STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,0,0,&pIStream);

   noScribble = true;

   hr = pParent -> pIPersistStreamInit -> Save(pIStream,TRUE);

   pIStream -> Release();

   return hr;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStorage::SaveCompleted(IStorage *) {
   noScribble = false;
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStorage::HandsOffStorage() {
   return S_OK;
   }
