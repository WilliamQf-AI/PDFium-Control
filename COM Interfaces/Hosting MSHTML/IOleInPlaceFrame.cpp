// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleInPlaceFrame::QueryInterface(REFIID riid,void **ppv) {

   if ( ! ppv )
      return E_POINTER;

   *ppv = NULL;

   if ( IID_IOleInPlaceFrame == riid ) 
      *ppv = static_cast<IOleInPlaceFrame *>(this);
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();

   return S_OK;
   }
   unsigned long __stdcall PDFiumControl::_IOleInPlaceFrame::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleInPlaceFrame::Release() {
   return pParent -> Release();
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::GetWindow(HWND *gwh) {
   *gwh = hwndHost;
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::ContextSensitiveHelp(BOOL) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::GetBorder(RECT *) {
   return INPLACE_E_NOTOOLSPACE;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::RequestBorderSpace(LPCBORDERWIDTHS) {
   return INPLACE_E_NOTOOLSPACE;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::SetBorderSpace(LPCBORDERWIDTHS pBorderWidths) {
   return S_OK ;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::SetActiveObject(IOleInPlaceActiveObject *pObj,LPCOLESTR) {

   if ( pParent -> pIOleInPlaceActiveObject_MSHTML )
      pParent -> pIOleInPlaceActiveObject_MSHTML -> Release();

   pParent -> pIOleInPlaceActiveObject_MSHTML = NULL;

   pParent -> pIOleInPlaceActiveObject_MSHTML = pObj;

   if ( pObj )
      pParent -> pIOleInPlaceActiveObject_MSHTML -> AddRef();

   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::InsertMenus(HMENU,LPOLEMENUGROUPWIDTHS) {
   return E_UNEXPECTED;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::RemoveMenus(HMENU) {
   return E_UNEXPECTED;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::SetMenu(HMENU,HOLEMENU,HWND) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::SetStatusText(LPCOLESTR) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::EnableModeless(BOOL) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceFrame::TranslateAccelerator(MSG *,WORD) {
   return S_FALSE;
   }