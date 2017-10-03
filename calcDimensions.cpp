
#include "PDFiumControl.h"

   void PDFiumControl::calcDimensions() {

   if ( ! pDocumentElement )
      return;

   memset(szwPageLabel,0,sizeof(szwPageLabel));

   pDocumentElement -> get_scrollTop(&scrollTop);

   pDocumentElement -> get_scrollHeight(&scrollHeight);

   RECT rcClient;

   GetWindowRect(hwndSite,&rcClient);

   cyClient = rcClient.bottom - rcClient.top;

   long amountVisible = 0;
   long maxAmountVisible = 0;

   maxVisiblePage = -1;

   long currentPDFPageCount = 0;

   pPDFiumDocument_Current -> get_PDFPageCount(&currentPDFPageCount);

   for ( int k = 0; k < currentPDFPageCount; k++ ) {

      IHTMLElement *pIHTMLElement = NULL;

      WCHAR szwId[32];

      swprintf_s(szwId,32,L"page%d",k + 1);

      pIWebBrowserDocument -> getElementById(szwId,&pIHTMLElement);

      if ( NULL == pIHTMLElement )
         continue;

      long x,y,cx,cy;

      pIHTMLElement -> get_offsetTop(&y);

      pIHTMLElement -> get_offsetHeight(&cy);

      pIHTMLElement -> get_offsetLeft(&x);

      pIHTMLElement -> get_offsetWidth(&cx);

      pPDFiumDocument_Current -> put_PDFPageXPixels(k + 1,x);
      pPDFiumDocument_Current -> put_PDFPageYPixels(k + 1,y);
      pPDFiumDocument_Current -> put_PDFPageWidthPixels(k + 1,cx);
      pPDFiumDocument_Current -> put_PDFPageHeightPixels(k + 1,cy);

      long cxPoints,cyPoints;

      pPDFiumDocument_Current -> get_PDFPageWidthPoints(k + 1,&cxPoints);

      pPDFiumDocument_Current -> get_PDFPageHeightPoints(k + 1,&cyPoints);

      double scalePixelsToPoints = (double)cxPoints / (double) cx;

      pPDFiumDocument_Current -> put_PDFPageXPoints(k + 1,(long)((double)x * scalePixelsToPoints));

      scalePixelsToPoints = (double)cyPoints / (double) cy;

      pPDFiumDocument_Current -> put_PDFPageYPoints(k + 1,(long)((double)y * scalePixelsToPoints));

      if ( isInView(y,cy) ) {

         swprintf_s(&szwPageLabel[wcslen(szwPageLabel)],512 - wcslen(szwPageLabel),L"%d,",k + 1);

         amountVisible = cy;

         if ( y < scrollTop ) 
            amountVisible -= scrollTop - y;

         if ( amountVisible > cyClient )
            amountVisible -= amountVisible - cyClient;

         if ( amountVisible > maxAmountVisible ) {
            maxAmountVisible = amountVisible;
            maxVisiblePage = k + 1;
         }

      }

      pIHTMLElement -> Release();

   }

   if ( 0 < wcslen(szwPageLabel) && L',' == szwPageLabel[wcslen(szwPageLabel) - 1] )
      szwPageLabel[wcslen(szwPageLabel) - 1] = L'\0';

   return;
   }

   long PDFiumControl::pageNumberContainingY(long yValue,long seekHeight) {

   if ( ! pDocumentElement )
      return 0;

   RECT rcClient;
   GetWindowRect(hwndSite,&rcClient);

   cyClient = rcClient.bottom - rcClient.top;

   pDocumentElement -> get_scrollTop(&scrollTop);

   pDocumentElement -> get_scrollHeight(&scrollHeight);

   long currentPDFPageCount = 0;

   pPDFiumDocument_Current -> get_PDFPageCount(&currentPDFPageCount);

   long values[] = {yValue,yValue + seekHeight};

   for ( int j = 0; j < 2; j++ ) {

      for ( int k = 0; k < currentPDFPageCount; k++ ) {

         IHTMLElement *pIHTMLElement = NULL;

         WCHAR szwId[32];

         swprintf_s(szwId,32,L"page%d",k + 1);

         pIWebBrowserDocument -> getElementById(szwId,&pIHTMLElement);

         if ( NULL == pIHTMLElement )
            continue;

         long x,y,cx,cy;

         pIHTMLElement -> get_offsetTop(&y);

         pIHTMLElement -> get_offsetHeight(&cy);

         pIHTMLElement -> get_offsetLeft(&x);

         pIHTMLElement -> get_offsetWidth(&cx);

         pIHTMLElement -> Release();

         if ( isInView(y,cy) ) {

            if ( y > scrollTop )
               y -= scrollTop;
            else
               y = 0;

            if ( y < values[j] && y + cy > values[j] )
               return k + 1;

         }

      }

   }

   return 0;
   }

   bool PDFiumControl::isInView(long y,long cy) {
   return ( y > scrollTop || y + cy > scrollTop ) && y < scrollTop + cyClient;
   }


   void PDFiumControl::navigatePage(long pageNumber) {

   if ( ! pIWebBrowserDocument ) {
      clientRequestedPageNumber = pageNumber;
      SetTimer(hwndSite,IDTIMER_GOTO_PAGE,TIMER_GOTO_PAGE_DURATION,NULL);
      return;
   }

   WCHAR szwId[32];

   IHTMLElement *pIHTMLElement;

   swprintf_s(szwId,32,L"pageAnchor%d",pageNumber);

   pIWebBrowserDocument -> getElementById(szwId,&pIHTMLElement);

   if ( ! pIHTMLElement ) 
      return;

   VARIANT v;

   V_VT(&v) = VT_BOOL;
   V_BOOL(&v) = TRUE;

   pIHTMLElement -> scrollIntoView(v);

   pIHTMLElement -> Release();

   return;
   }
