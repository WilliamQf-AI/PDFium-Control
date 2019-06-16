// Copyright 2017, 2018, 2019 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::_IOleControl::QueryInterface(REFIID riid,void **ppv) {
   if ( IID_IOleControl == riid )
      *ppv = static_cast<IOleControl *>(this); 
   else
      return pParent -> QueryInterface(riid,ppv);
   AddRef();
   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IOleControl::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IOleControl::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IOleObject::_IOleControl::GetControlInfo(CONTROLINFO *pci) {
   if ( ! pci )
      return E_POINTER;
   pci -> cb = sizeof(CONTROLINFO);
   pci -> cAccel = 0;
   pci -> dwFlags = CTRLINFO_EATS_ESCAPE;
   return S_OK;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleControl::OnMnemonic(MSG *) {
   return S_FALSE;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleControl::OnAmbientPropertyChange(long propertyId) {
   return S_OK;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleControl::FreezeEvents(int) {
   return S_OK;
   }