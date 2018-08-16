// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   HRESULT __stdcall PDFiumControl::put_BackgroundColor(COLORREF color) {
   backgroundColor = color;
   if ( hwndSite )
      InvalidateRect(hwndSite,NULL,TRUE);
   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::get_BackgroundColor(COLORREF *pColor) {
   if ( ! pColor )
      return E_POINTER;
   *pColor = backgroundColor;
   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::put_PDFWidth(long cx) {
   cxPDFWidth = cx;
   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::get_PDFWidth(long *pcx) {
   if ( ! pcx ) 
      return E_POINTER;
   *pcx = cxPDFWidth;
   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::put_PDFHeight(long cy) {
   cyPDFHeight = cy;
   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::get_PDFHeight(long *pcy) {
   if ( ! pcy ) 
      return E_POINTER;
   *pcy = cyPDFHeight;
   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::put_EnableExplorerContextMenu(BOOL doEnable) {
   enableExplorerContextMenu = doEnable;
   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::get_PageCount(long *pPageCount) {

   if ( ! pPageCount )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;

   return pPDFiumDocument -> get_PDFPageCount(pPageCount);
   }


   HRESULT __stdcall PDFiumControl::get_PDFPagesVisible(BSTR *pPagesVisible) {

   if ( ! pPagesVisible )
      return E_POINTER;

   if ( ! pDocumentElement )
      return E_UNEXPECTED;

   *pPagesVisible = SysAllocString(szwPageLabel);

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::get_PDFPageMostVisible(long *pPageNumber ) {
   
   if ( ! pPageNumber )
      return E_POINTER;

   if ( ! pDocumentElement )
      return E_UNEXPECTED;

   *pPageNumber = maxVisiblePage;

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::get_PDFPageXPixels(long pageNumber,long *pX) {

   if ( ! pX )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;
   
   return pPDFiumDocument -> get_PDFPageXPixels(pageNumber,pX);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageXPixelsInView(long pageNumber,long *pX) {

   if ( ! pX )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;
   
   return pPDFiumDocument -> get_PDFPageXPixelsInView(pageNumber,pX);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageYPixels(long pageNumber,long *pY) {

   if ( ! pY )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;
   
   return pPDFiumDocument -> get_PDFPageYPixels(pageNumber,pY);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageYPixelsInView(long pageNumber,long *pY) {

   if ( ! pY )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;
   
   return pPDFiumDocument -> get_PDFPageYPixelsInView(pageNumber,pY);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageWidthPixels(long pageNumber,long *pWidth) {

   if ( ! pWidth )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;
   
   return pPDFiumDocument -> get_PDFPageWidthPixels(pageNumber,pWidth);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageHeightPixels(long pageNumber,long *pHeight) {

   if ( ! pHeight )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;
   
   return pPDFiumDocument -> get_PDFPageHeightPixels(pageNumber,pHeight);
   }


   HRESULT __stdcall PDFiumControl::get_PDFPageXPoints(long pageNumber,long *pX) {

   if ( ! pX )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;
   
   return pPDFiumDocument -> get_PDFPageXPoints(pageNumber,pX);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageYPoints(long pageNumber,long *pY) {

   if ( ! pY )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;
   
   return pPDFiumDocument -> get_PDFPageYPoints(pageNumber,pY);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageWidthPoints(long pageNumber,long *pWidth) {

   if ( ! pWidth )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;
   
   return pPDFiumDocument -> get_PDFPageWidthPoints(pageNumber,pWidth);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageHeightPoints(long pageNumber,long *pHeight) {

   if ( ! pHeight )
      return E_POINTER;

   if ( ! pPDFiumDocument )
      return E_UNEXPECTED;
   
   return pPDFiumDocument -> get_PDFPageHeightPoints(pageNumber,pHeight);
   }

   HRESULT __stdcall PDFiumControl::put_Document(BSTR newDocumentName) {

   szwDocumentName[0] = L'\0';

   if ( newDocumentName && 0 < wcslen(newDocumentName) )
      wcscpy_s(szwDocumentName,1024,newDocumentName);
   else
      return S_OK;

   if ( ! hwndSite )
      return S_OK;

   DisplayDocument(backgroundColor,cxPDFWidth,cyPDFHeight,newDocumentName,0);

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageNumberAtY(long yValue,long seekHeight,long *pPageNumber) {

   if ( ! pPageNumber )
      return E_POINTER;

   *pPageNumber = pageNumberContainingY(yValue,seekHeight);

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::get_Document(BSTR *pDocumentName) {

   if ( ! pDocumentName )
      return E_POINTER;

   if ( szwDocumentName[0] )
      *pDocumentName = SysAllocString(szwDocumentName);
   else
      *pDocumentName = SysAllocString(L"");

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::put_ScrollBarVisible(BOOL setVisible) {

   if ( ! pIHTMLBodyElement )
      return E_UNEXPECTED;

   if ( setVisible )
      pIHTMLBodyElement -> put_scroll(L"yes");
   else
      pIHTMLBodyElement -> put_scroll(L"no");

   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::get_ScrollBarVisible(BOOL *pIsVisible) {

   if ( ! pIsVisible )
      return E_POINTER;

   if ( ! pIHTMLBodyElement )
      return E_UNEXPECTED;

   BSTR bstrIsScroll;

   pIHTMLBodyElement -> get_scroll(&bstrIsScroll);

   if ( 0 == wcscmp(bstrIsScroll,L"no") )
      *pIsVisible = FALSE;
   else
      *pIsVisible = TRUE;
   
   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::ConvertPointsToScrollPanePixels(long pageNumber,RECT *pRect) {
   return pPDFiumDocument -> ConvertPointsToScrollPanePixels(pageNumber,pRect);
   }


   HRESULT __stdcall PDFiumControl::OpenDocument(BSTR pdfFileName) {

   char szFileName[MAX_PATH];

   WideCharToMultiByte(CP_ACP,0,pdfFileName,-1,szFileName,MAX_PATH,0,0);

   FPDF_STRING pdfFile(szFileName);

   FPDF_DOCUMENT theDocument = FPDF_LoadDocument(pdfFile,NULL);

   if ( NULL == theDocument )
      return E_FAIL;

   if ( pPDFiumDocument ) 
      delete pPDFiumDocument;

   pPDFiumDocument = new PDFiumDocument(this,theDocument);

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::CloseDocument() {

   if ( ! pPDFiumDocument )
      return E_FAIL;

   delete pPDFiumDocument;

   pPDFiumDocument = NULL;

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::DisplayDocument(COLORREF passedBackgroundColor,long cxImagePixels,long cyImagePixels,BSTR pdfOrHTMLFileName,long pageNumber) {

   if ( ! pIWebBrowser )
      InitializeMSHTML();

   VARIANT target,vEmpty;

   VariantInit(&vEmpty);
   VariantInit(&target);

   FILE *fDocument = _wfopen(pdfOrHTMLFileName,L"rb");

   if ( NULL == fDocument ) {
      pIWebBrowser -> Navigate(pdfOrHTMLFileName,&vEmpty,&target,&vEmpty,&vEmpty);
      pIOleInPlaceObject_MSHTML -> SetObjectRects(&rcHTMLHost,&rcHTMLHost);
      pIOleObject_MSHTML -> DoVerb(OLEIVERB_SHOW,NULL,pIOleClientSite_HTML_Host,0,hwndSite,&rcHTMLHost);
      return E_FAIL;
   }

   BYTE filePreamble[4];

   int nBytes = (int)fread(filePreamble,1,4,fDocument);

   if ( ! ( 4 == nBytes ) ) {
      fclose(fDocument);
      return E_FAIL;
   }

   if ( szwTemporaryDocumentName[0] )
      DeleteFile(szwTemporaryDocumentName);

   memset(szwTemporaryDocumentName,0,sizeof(szwTemporaryDocumentName));

   backgroundColor = passedBackgroundColor;
   cxPDFWidth = cxImagePixels;
   cyPDFHeight = cyImagePixels;

   szwDocumentName[0] = L'\0';;

   wcscpy_s(szwDocumentName,1024,pdfOrHTMLFileName);

   BSTR documentToLoad = NULL;

   isPDF = FALSE;

   if ( 0 == memcmp(filePreamble,"%PDF",4) ) {

      isPDF = TRUE;

      OpenDocument(pdfOrHTMLFileName);

      swprintf_s(szwTemporaryDocumentName,MAX_PATH,L"%ls",_wtempnam(NULL,NULL));

      pPDFiumDocument -> GenerateHTML(backgroundColor,cxPDFWidth,cyPDFHeight,szwTemporaryDocumentName);

      fclose(fDocument);

      documentToLoad = SysAllocString(szwTemporaryDocumentName);

   } else {

      fclose(fDocument);

      documentToLoad = SysAllocString(pdfOrHTMLFileName);

   }

   target.vt = VT_BSTR;
   target.bstrVal = L"_self";

   HRESULT rc = pIWebBrowser -> put_AddressBar(VARIANT_TRUE);

   rc = pIWebBrowser -> put_FullScreen(VARIANT_FALSE);

   rc = pIWebBrowser -> Navigate(documentToLoad,&vEmpty,&target,&vEmpty,&vEmpty);

   pIOleInPlaceObject_MSHTML -> SetObjectRects(&rcHTMLHost,&rcHTMLHost);

   pIOleObject_MSHTML -> DoVerb(OLEIVERB_SHOW,NULL,pIOleClientSite_HTML_Host,0,hwndSite,&rcHTMLHost);

   SysFreeString(documentToLoad);

   clientRequestedPageNumber = 0;

   if ( 0 == pageNumber || ! isPDF )
      return S_OK;

   clientRequestedPageNumber = pageNumber;

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::ResizePDFDocument(long cxImagePixels,long cyImagePixels) {

   if ( ! isPDF )
      return E_UNEXPECTED;

   if ( szwTemporaryDocumentName[0] )
      DeleteFile(szwTemporaryDocumentName);

   memset(szwTemporaryDocumentName,0,sizeof(szwTemporaryDocumentName));

   cxPDFWidth = cxImagePixels;
   cyPDFHeight = cyImagePixels;

   CloseDocument();
   OpenDocument(szwDocumentName);

   swprintf_s(szwTemporaryDocumentName,MAX_PATH,L"%ls",_wtempnam(NULL,NULL));

   pPDFiumDocument -> GenerateHTML(backgroundColor,cxPDFWidth,cyPDFHeight,szwTemporaryDocumentName);

   BSTR documentToLoad = SysAllocString(szwTemporaryDocumentName);

   VARIANT target,vEmpty;

   VariantInit(&vEmpty);
   VariantInit(&target);

   target.vt = VT_BSTR;
   target.bstrVal = L"_self";

   HRESULT rc = pIWebBrowser -> put_AddressBar(VARIANT_TRUE);

   rc = pIWebBrowser -> put_FullScreen(VARIANT_FALSE);

   rc = pIWebBrowser -> Navigate(documentToLoad,&vEmpty,&target,&vEmpty,&vEmpty);

   pIOleInPlaceObject_MSHTML -> SetObjectRects(&rcHTMLHost,&rcHTMLHost);

   pIOleObject_MSHTML -> DoVerb(OLEIVERB_SHOW,NULL,pIOleClientSite_HTML_Host,0,hwndSite,&rcHTMLHost);

   SysFreeString(documentToLoad);

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::PrintDocument(BSTR documentName,BOOL showPrinterSelection) {

   wcscpy_s(szwPendingPrintDocumentName,MAX_PATH,documentName);

   pendingShowPrinterSelection = showPrinterSelection;

   DisplayDocument(0,0,0,documentName,0);

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::GoToPage(long pageNumber) {

   navigatePage(pageNumber);

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::PrintCurrentDocument(BOOL showPrinterSelection) {

   IDispatch *pIDispatch = NULL;

   pIWebBrowser -> get_Document(&pIDispatch);

   IHTMLDocument2 *pIHTMLDocument2 = NULL;

   pIDispatch -> QueryInterface(IID_IHTMLDocument2,reinterpret_cast<void **>(&pIHTMLDocument2));

   if ( pIHTMLDocument2 ) {

      IOleCommandTarget *pIOleCommandTarget = NULL;

      pIHTMLDocument2 -> QueryInterface(IID_IOleCommandTarget,reinterpret_cast<void **>(&pIOleCommandTarget));

      pIOleCommandTarget -> Exec(&CGID_MSHTML,IDM_PRINT,showPrinterSelection ? OLECMDEXECOPT_PROMPTUSER : OLECMDEXECOPT_DONTPROMPTUSER,NULL,NULL);

      pIOleCommandTarget -> Release();

      pIHTMLDocument2 -> Release();

   } else {

      HRESULT rc = pIWebBrowser -> ExecWB(OLECMDID_PRINT,showPrinterSelection ? OLECMDEXECOPT_PROMPTUSER : OLECMDEXECOPT_DONTPROMPTUSER,NULL,NULL);

   }

   pIDispatch -> Release();

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::get_IsPDF(BOOL *pIsPDF) {
   if ( ! pIsPDF )
      return E_POINTER;
   *pIsPDF = isPDF;
   return S_OK;
   }

   HRESULT __stdcall PDFiumControl::FinalRelease() {

   while ( Release() ) ;

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::Cleanup() {

   if ( hwndExplorer ) {
      SetWindowLongPtr(hwndExplorer,GWLP_WNDPROC,(LONG_PTR)nativeExplorerHandler);
      explorerObjectMap.erase(hwndExplorer);
      hwndExplorer = NULL;
   }

   if ( pPDFiumDocument )
      delete pPDFiumDocument;

   pPDFiumDocument = NULL;

   if ( ( 0 == countInstances ) && ( 0 < pdfiumConfig.version ) ) {
      FPDF_DestroyLibrary();
      memset(&pdfiumConfig,0,sizeof(FPDF_LIBRARY_CONFIG));
   }

   if ( szwTemporaryDocumentName[0] )
      DeleteFile(szwTemporaryDocumentName);

   return S_OK;
   }
