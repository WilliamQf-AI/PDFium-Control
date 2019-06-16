// Copyright 2017, 2018, 2019 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleInPlaceSite::QueryInterface(REFIID riid,void **ppv) {

   if ( ! ppv )
      return E_POINTER;

   *ppv = NULL;

   if ( IID_IOleInPlaceSite == riid ) 
      *ppv = static_cast<IOleInPlaceSite *>(this);
   else

   if ( IID_IOleInPlaceSiteEx == riid ) 
      *ppv = static_cast<IOleInPlaceSiteEx *>(this);
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();

   return S_OK;
   }
   unsigned long __stdcall PDFiumControl::_IOleInPlaceSite::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleInPlaceSite::Release() {
   return pParent -> Release();
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::GetWindow(HWND *gwh) {
   *gwh = pIOleInPlaceFrame -> HWNDHost();
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::ContextSensitiveHelp(BOOL fEnterMode) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::CanInPlaceActivate() {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::OnInPlaceActivate() {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::OnUIActivate() {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::GetWindowContext(IOleInPlaceFrame **ppIOleInPlaceFrame,
                                                                        IOleInPlaceUIWindow **ppIOleInPlaceUIWindow,
                                                                        RECT *pRectPosition,RECT *pRectClip,
                                                                        OLEINPLACEFRAMEINFO *pOleInPlaceFrameInfo) {

   *ppIOleInPlaceFrame = pIOleInPlaceFrame;
   *ppIOleInPlaceUIWindow = static_cast<IOleInPlaceUIWindow *>(pIOleInPlaceFrame);

   RECT rectHost;
   GetWindowRect(pIOleInPlaceFrame -> HWNDHost(),&rectHost);
   rectHost.right = rectHost.right - rectHost.left;
   rectHost.bottom = rectHost.bottom - rectHost.top;
   rectHost.left = 0;
   rectHost.top = 0;

   memcpy(pRectPosition,&rectHost,sizeof(RECT));
   memcpy(pRectClip,pRectPosition,sizeof(RECT));

   memset(pOleInPlaceFrameInfo,0,sizeof(OLEINPLACEFRAMEINFO));

   pOleInPlaceFrameInfo -> cb = sizeof(OLEINPLACEFRAMEINFO);
   pOleInPlaceFrameInfo -> fMDIApp = FALSE;
   pOleInPlaceFrameInfo -> hwndFrame = pIOleInPlaceFrame -> HWNDHost();
   pOleInPlaceFrameInfo -> haccel = NULL;
   pOleInPlaceFrameInfo -> cAccelEntries = NULL;   

   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::Scroll(SIZE) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::OnUIDeactivate(BOOL) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::OnInPlaceDeactivate() {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::DiscardUndoState() {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::DeactivateAndUndo() {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleInPlaceSite::OnPosRectChange(const RECT *pRect) {
   return S_OK;
   }

   HRESULT PDFiumControl::_IOleInPlaceSite::OnInPlaceActivateEx(BOOL *pRedraw,DWORD dwFlags) {
   *pRedraw = FALSE;
   return S_OK;
   }

   HRESULT PDFiumControl::_IOleInPlaceSite::OnInPlaceDeactivateEx(BOOL fNoRedraw) {
   return S_OK;
   }

   HRESULT PDFiumControl::_IOleInPlaceSite::RequestUIActivate() {
   return S_OK;
   }


