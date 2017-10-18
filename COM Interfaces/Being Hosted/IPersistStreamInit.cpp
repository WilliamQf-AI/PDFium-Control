// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::_IPersistStreamInit::QueryInterface(REFIID riid,void **ppv) {

   *ppv = NULL;

   if ( IID_IPersistStreamInit == riid )
      *ppv = static_cast<IPersistStreamInit *>(this);
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();

   return S_OK;
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IPersistStreamInit::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IPersistStreamInit::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStreamInit::GetClassID(CLSID *pcid) {
   memcpy(pcid,&CLSID_PDFiumControl,sizeof(GUID));
   return S_OK;
   }


   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStreamInit::IsDirty() {
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStreamInit::Load(IStream *pIStream) {
   if ( ! pIStream )
      return E_POINTER;
   ULONG cbRead = offsetof(PDFiumControl,propertiesEnd) - offsetof(PDFiumControl,propertiesStart);
   HRESULT rc = pIStream -> Read(&pParent -> pParent -> propertiesStart,cbRead,&cbRead);
   if ( pParent -> pParent -> hwndSite ) {
      BSTR newDocumentName = SysAllocString(pParent -> pParent -> szwDocumentName);
      pParent -> pParent -> DisplayDocument(pParent -> pParent -> backgroundColor,pParent -> pParent -> cxPDFWidth,pParent -> pParent -> cyPDFHeight,newDocumentName,0);
      SysFreeString(newDocumentName);
   }
   return rc;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStreamInit::Save(IStream *pIStream,BOOL clearDirty) {
   ULONG cbWritten = offsetof(PDFiumControl,propertiesEnd) - offsetof(PDFiumControl,propertiesStart);
   return pIStream -> Write(&pParent -> pParent -> propertiesStart,cbWritten,&cbWritten);
   }


   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStreamInit::GetSizeMax(ULARGE_INTEGER *pb) {
   pb -> QuadPart = offsetof(PDFiumControl,propertiesEnd) - offsetof(PDFiumControl,propertiesStart);
   return S_OK;
   }

 
   STDMETHODIMP PDFiumControl::_IOleObject::_IPersistStreamInit::InitNew() {
   pParent -> pParent -> SetDefaults();
   return S_OK;
   }