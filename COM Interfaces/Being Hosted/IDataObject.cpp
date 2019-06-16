// Copyright 2017, 2018, 2019 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::_IDataObject::QueryInterface(REFIID riid,void **ppv) {
 
   if ( IID_IDataObject == riid )
      *ppv = static_cast<IDataObject *>(this); 
   else
      return pParent -> QueryInterface(riid,ppv);

   AddRef();

   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IDataObject::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IDataObject::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IOleObject::_IDataObject::GetData(FORMATETC *,STGMEDIUM *) {
   return S_OK;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IDataObject::GetDataHere(FORMATETC *,STGMEDIUM *) {
   return E_NOTIMPL;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IDataObject::QueryGetData(FORMATETC *) {
   return E_NOTIMPL;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IDataObject::GetCanonicalFormatEtc(FORMATETC *,FORMATETC *) {
   return E_NOTIMPL;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IDataObject::SetData(FORMATETC *theData,STGMEDIUM *,BOOL) {
   return E_NOTIMPL;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IDataObject::EnumFormatEtc(DWORD,IEnumFORMATETC **) {
   return E_NOTIMPL;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IDataObject::DAdvise(FORMATETC *pFormatEtc,DWORD advf,IAdviseSink *pIAS,DWORD *pdwConnection) {
   if ( ! pParent -> pDataAdviseHolder ) 
      CreateDataAdviseHolder(&pParent -> pDataAdviseHolder);
   if ( pParent -> pDataAdviseHolder )
      pParent -> pDataAdviseHolder -> Advise(static_cast<IDataObject *>(this),pFormatEtc,advf,pIAS,pdwConnection);
   return S_OK;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IDataObject::DUnadvise(DWORD dwConnection) {
   if ( pParent -> pDataAdviseHolder )
      pParent -> pDataAdviseHolder -> Unadvise(dwConnection);
   pParent -> pDataAdviseHolder = NULL;
   return S_OK;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IDataObject::EnumDAdvise(IEnumSTATDATA **) {
   return S_OK;
   }