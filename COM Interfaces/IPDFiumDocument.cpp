// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

#define NORMALIZE_PAGE_NUMBER(pn)   \
   long pageIndex = pn;             \
   if ( 0 == pageIndex ) {          \
      pParent -> calcDimensions();  \
      pageIndex = pParent -> maxVisiblePage;    \
   }                                            \
   if ( pageIndex > pageCount || 1 > pageIndex )\
      return E_FAIL;                            \
   pageIndex--;

   HRESULT __stdcall PDFiumControl::PDFiumDocument::QueryInterface(REFIID riid, void** ppv) {

   *ppv = 0;

   if ( IID_IUnknown == riid )
      *ppv = this;
   else

   //
   //NTC: 09-21-2017: I don't think there is any reason to expose this interface.
   //
#if 0
   if ( IID_IPDFiumDocument == riid )
      *ppv = static_cast<IPDFiumDocument *>(this);
   else
#endif

      return pParent -> QueryInterface(riid,ppv);

   AddRef();

   return S_OK;
   }


   ULONG __stdcall PDFiumControl::PDFiumDocument::AddRef() {
   return refCount++;
   }


   ULONG __stdcall PDFiumControl::PDFiumDocument::Release() { 
   if ( --refCount == 0 ) {
      delete this;
      return 0;
   }
   return refCount;
   }


   HRESULT __stdcall PDFiumControl::PDFiumDocument::GenerateHTML(COLORREF backgroundColor,long cxImage,long cyImage,BSTR htmlFileName) {

   FILE *fOutput = _wfopen(htmlFileName,L"wt");

   if ( NULL == fOutput )
      return E_FAIL;

   char *p = strchr(szHTMLHeader,'%');

   *p = '\0';

   fprintf(fOutput,szHTMLHeader);

   fprintf(fOutput,"#%02x%02x%02x",GetRValue(backgroundColor),GetGValue(backgroundColor),GetBValue(backgroundColor));

   fprintf(fOutput,strchr(p + 1,'%') + 1);

   *p = '%';

   RECT rc;
   rc.left = 0;
   rc.top = 0;
   rc.right = cxImage;
   rc.bottom = cyImage;

   HBRUSH white = CreateSolidBrush(RGB(255,255,255));

   pageCount = FPDF_GetPageCount(pDocumentObject);

   for ( int k = 0; k < pageCount; k++ ) {

      FPDF_PAGE pPage = FPDF_LoadPage(pDocumentObject,k);

      POINTL *pPDFDimensions = new POINTL();

      pPDFDimensions -> x = (long)FPDF_GetPageWidth(pPage);

      pPDFDimensions -> y = (long)FPDF_GetPageHeight(pPage);

      pagePDFDimensions[k] = pPDFDimensions;

      POINTL *pPixelDimensions = new POINTL();

      pPixelDimensions -> x = 0;
      pPixelDimensions -> y = 0;

      pagePDFLocations[k] = pPixelDimensions;

      pPixelDimensions = new POINTL();

      pagePixelDimensions[k] = pPixelDimensions;

      POINTL *pPixelLocation = new POINTL();

      pPixelLocation -> x = 0;
      pPixelLocation -> y = 0;

      pagePixelLocations[k] = pPixelLocation;

      HDC hdcDesktop = GetDC(HWND_DESKTOP);

      HDC hdc = CreateCompatibleDC(hdcDesktop);

      HBITMAP hBitmap = CreateBitmap(cxImage,cyImage,1,GetDeviceCaps(hdcDesktop,BITSPIXEL),NULL);

      SelectObject(hdc,hBitmap);

      FillRect(hdc,&rc,white);

      FPDF_RenderPage(hdc,pPage,0,0,cxImage,cyImage,0,0);

      WCHAR *pszwImageFile = new WCHAR[MAX_PATH];

      wcscpy_s(pszwImageFile,MAX_PATH,_wtempnam(NULL,NULL));

      SaveBitmapFile(hdc,hBitmap,pszwImageFile);

      imageFiles.push_back(pszwImageFile);

      DeleteObject(hBitmap);

      DeleteDC(hdc);

      ReleaseDC(HWND_DESKTOP,hdcDesktop);

      fprintf(fOutput,szHTMLPage,k + 1,k + 1,pszwImageFile);

   }

   fprintf(fOutput,szHTMLFooter);

   fclose(fOutput);

   DeleteObject(white);

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageCount(long *pCount) {
   if ( ! pCount )
      return E_POINTER;
   *pCount = pageCount;
   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageXPixels(long pageNumber,long *pX) {

   if ( ! pX )
      return E_POINTER;
   
   NORMALIZE_PAGE_NUMBER(pageNumber)

   *pX = pagePixelLocations[pageIndex] -> x;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageXPixelsInView(long pageNumber,long *pX) {

   if ( ! pX )
      return E_POINTER;

   NORMALIZE_PAGE_NUMBER(pageNumber)

   if ( pParent -> isInView(pagePixelLocations[pageIndex] -> y,pagePixelDimensions[pageIndex] -> y) )
      *pX = pagePixelLocations[pageIndex] -> x;
   else
      *pX = COORDINATE_NOT_IN_VIEW;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::put_PDFPageXPixels(long pageNumber,long x) {

   NORMALIZE_PAGE_NUMBER(pageNumber)

   pagePixelLocations[pageIndex] -> x = x;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageYPixels(long pageNumber,long *pY) {

   if ( ! pY )
      return E_POINTER;

   NORMALIZE_PAGE_NUMBER(pageNumber)

   *pY = pagePixelLocations[pageIndex] -> y;

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageYPixelsInView(long pageNumber,long *pY) {

   if ( ! pY )
      return E_POINTER;

   NORMALIZE_PAGE_NUMBER(pageNumber)

   if ( pParent -> isInView(pagePixelLocations[pageIndex] -> y,pagePixelDimensions[pageIndex] -> y) )
      *pY = pagePixelLocations[pageIndex] -> y - pParent -> ScrollTop();
   else
      *pY = COORDINATE_NOT_IN_VIEW;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::put_PDFPageYPixels(long pageNumber,long y) {

   NORMALIZE_PAGE_NUMBER(pageNumber)

   pagePixelLocations[pageIndex] -> y = y;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageWidthPixels(long pageNumber,long *pWidth) {

   if ( ! pWidth )
      return E_POINTER;

   NORMALIZE_PAGE_NUMBER(pageNumber)

   *pWidth = pagePixelDimensions[pageIndex] -> x;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::put_PDFPageWidthPixels(long pageNumber,long cx) {

   NORMALIZE_PAGE_NUMBER(pageNumber)

   pagePixelDimensions[pageIndex] -> x = cx;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageHeightPixels(long pageNumber,long *pHeight) {

   if ( ! pHeight )
      return E_POINTER;

   NORMALIZE_PAGE_NUMBER(pageNumber)

   *pHeight = pagePixelDimensions[pageIndex] -> y;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::put_PDFPageHeightPixels(long pageNumber,long cy) {

   NORMALIZE_PAGE_NUMBER(pageNumber)

   pagePixelDimensions[pageIndex] -> y = cy;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageXPoints(long pageNumber,long *pX) {

   if ( ! pX )
      return E_POINTER;

   NORMALIZE_PAGE_NUMBER(pageNumber)

   *pX = pagePDFLocations[pageIndex] -> x;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::put_PDFPageXPoints(long pageNumber,long x) {

   NORMALIZE_PAGE_NUMBER(pageNumber)

   pagePDFLocations[pageIndex] -> x = x;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageYPoints(long pageNumber,long *pY) {

   if ( ! pY )
      return E_POINTER;

   NORMALIZE_PAGE_NUMBER(pageNumber)

   *pY = pagePDFLocations[pageIndex] -> y;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::put_PDFPageYPoints(long pageNumber,long y) {

   NORMALIZE_PAGE_NUMBER(pageNumber)

   pagePDFLocations[pageIndex] -> y = y;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageWidthPoints(long pageNumber,long *pWidth) {

   if ( ! pWidth )
      return E_POINTER;

   NORMALIZE_PAGE_NUMBER(pageNumber)

   *pWidth = pagePDFDimensions[pageIndex] -> x;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::put_PDFPageWidthPoints(long pageNumber,long cx) {

   NORMALIZE_PAGE_NUMBER(pageNumber)

   pagePDFDimensions[pageIndex] -> x = cx;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::get_PDFPageHeightPoints(long pageNumber,long *pHeight) {

   if ( ! pHeight )
      return E_POINTER;

   NORMALIZE_PAGE_NUMBER(pageNumber)

   *pHeight = pagePDFDimensions[pageIndex] -> y;

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::PDFiumDocument::put_PDFPageHeightPoints(long pageNumber,long cy) {

   NORMALIZE_PAGE_NUMBER(pageNumber)

   pagePDFDimensions[pageIndex] -> y = cy;

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::PDFiumDocument::ConvertPointsToScrollPanePixels(long pageNumber,RECT *pRect) {

   NORMALIZE_PAGE_NUMBER(pageNumber)

   long x = pagePixelLocations[pageIndex] -> x;
   long y = pagePixelLocations[pageIndex] -> y;
   long cy = pagePixelDimensions[pageIndex] -> y;

   long pointsX = pagePDFLocations[pageIndex] -> x;
   long pointsY = pagePDFLocations[pageIndex] -> y;

   double scalePointsToPixels = (double)pagePixelDimensions[pageIndex] -> y / (double)pagePDFDimensions[pageIndex] -> y;

   long cxTarget = pRect -> right - pRect -> left;
   long cyTarget = pRect -> top - pRect -> bottom;
   long pointsTop = pagePDFDimensions[pageIndex] -> y - pRect -> top;

   pRect -> left = x + (long)((double)pRect -> left * scalePointsToPixels);
   pRect -> top = y + (long)((double)pointsTop * scalePointsToPixels);
   pRect -> right = pRect -> left + (long)((double)cxTarget * scalePointsToPixels);
   pRect -> bottom = pRect -> top + (long)((double)cyTarget * scalePointsToPixels);

   return S_OK;

   }
