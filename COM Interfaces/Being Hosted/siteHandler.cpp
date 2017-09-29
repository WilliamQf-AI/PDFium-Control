
#include "PDFiumControl.h"

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
      if ( p -> pIOleInPlaceObject_HTML ) 
         p -> pIOleInPlaceObject_HTML -> SetObjectRects(&p -> rcHTMLHost,&p -> rcHTMLHost);
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
