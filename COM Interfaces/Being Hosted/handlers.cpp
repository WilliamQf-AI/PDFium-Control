// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

#include <windowsx.h>

   LRESULT CALLBACK PDFiumControl::siteHandler(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {

   PDFiumControl *p = (PDFiumControl *)GetWindowLongPtr(hwnd,GWLP_USERDATA);

   switch ( msg ) {
   case WM_CREATE: {
      CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
      SetWindowLongPtr(hwnd,GWLP_USERDATA,(ULONG_PTR)pcs -> lpCreateParams);
      }
      break;

   case WM_PAINT: {
      PAINTSTRUCT ps = {0};
      BeginPaint(hwnd,&ps);
      HBRUSH hBrush = CreateSolidBrush(p -> backgroundColor);
      //FillRect(ps.hdc,&ps.rcPaint,hBrush);
      DeleteObject(hBrush);
      EndPaint(hwnd,&ps);
      break;
      }

   case WM_SIZE:
      p -> rcHTMLHost.top = 0;
      p -> rcHTMLHost.left = 0;
      p -> rcHTMLHost.right = LOWORD(lParam);
      p -> rcHTMLHost.bottom = HIWORD(lParam);
      if ( p -> pIOleInPlaceObject_MSHTML ) 
         p -> pIOleInPlaceObject_MSHTML -> SetObjectRects(&p -> rcHTMLHost,&p -> rcHTMLHost);
      p -> calcDimensions();
      break;

   case WM_TIMER: 
      if ( IDTIMER_GOTO_PAGE == wParam ) {
         KillTimer(hwnd,IDTIMER_GOTO_PAGE);
         p -> navigatePage(p -> clientRequestedPageNumber);
      }
      break;

   case WM_PRINT_DOCUMENT: {
      p -> PrintCurrentDocument(p -> pendingShowPrinterSelection);
      p -> szwPendingPrintDocumentName[0] = L'\0';
      }
      break;

   default:
      break;

   }

   return DefWindowProc(hwnd,msg,wParam,lParam);
   }


   LRESULT CALLBACK PDFiumControl::explorerHandler(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {

   if ( WM_MOUSEFIRST <= msg && WM_MOUSELAST >= msg ) {
      PDFiumControl *p = explorerObjectMap[hwnd];
      if ( p ) {

         POINT ptlTranslate{0,0};

         RECT rcWindow;
         GetWindowRect(p -> hwndExplorer,&rcWindow);

         ptlTranslate.x = GET_X_LPARAM(lParam);
         ptlTranslate.y = GET_Y_LPARAM(lParam);

         ClientToScreen(hwnd,&ptlTranslate);

         ptlTranslate.x -= rcWindow.left;
         ptlTranslate.y -= rcWindow.top;

         p -> connectionPointContainer.fire_MouseMessage(msg,wParam,MAKELPARAM(ptlTranslate.x,ptlTranslate.y));

         if ( WM_RBUTTONDOWN <= msg && WM_RBUTTONDBLCLK >= msg ) {
            if ( ! p -> enableExplorerContextMenu )
               return (LRESULT)FALSE;
         }
      }
   }

   if ( WM_DESTROY == msg )
      explorerObjectMap.erase(hwnd);

   return nativeExplorerHandler(hwnd,msg,wParam,lParam);
   }