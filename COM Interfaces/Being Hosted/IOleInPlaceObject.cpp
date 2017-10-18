// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::_IOleInPlaceObject::QueryInterface(REFIID riid,void **ppv) {
 
   if ( IID_IOleInPlaceObject == riid )
      *ppv = static_cast<IOleInPlaceObject *>(this); 
   else
      return pParent -> QueryInterface(riid,ppv);

   AddRef();
  
   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IOleInPlaceObject::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IOleInPlaceObject::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceObject::GetWindow(HWND *pHwnd) {
   *pHwnd = pParent -> pParent -> hwndSite;
   return S_OK;
   }
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceObject::ContextSensitiveHelp(BOOL) {
   return E_NOTIMPL;
   }
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceObject::InPlaceActivate() {
    if ( pParent -> pIOleInPlaceSite_MySite -> CanInPlaceActivate() != S_OK ) 
      return S_FALSE;
   pParent -> pIOleInPlaceSite_MySite -> OnInPlaceActivate();
   return S_OK;
   }

   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceObject::InPlaceDeactivate() {

//   for ( long k = TIMER_EVENT_MIN_ID; k <= TIMER_EVENT_MAX_ID; k++ )
//      KillTimer(pParent -> hwndSite,k);

   pParent -> pIOleInPlaceSite_MySite -> OnInPlaceDeactivate();

   return S_OK;
   }
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceObject::UIDeactivate() {
   return S_OK;
   }
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceObject::SetObjectRects(LPCRECT pRectPos,LPCRECT pRectClip) {
   if ( ! pRectPos )
      return S_OK;
   SetWindowPos(pParent -> pParent -> hwndSite,HWND_TOP,pRectPos -> left,pRectPos -> top,
                               pRectPos -> right - pRectPos -> left,pRectPos -> bottom - pRectPos -> top,0L);
   if ( ! pParent -> isRunning )
      ShowWindow(pParent -> pParent -> hwndSite,SW_SHOW);
   return S_OK;
   }
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IOleInPlaceObject::ReactivateAndUndo() {
   return S_OK;
   }