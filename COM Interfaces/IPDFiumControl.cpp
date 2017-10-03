
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

   if ( ! pPDFiumDocument_Current )
      return E_UNEXPECTED;
   
   return pPDFiumDocument_Current -> get_PDFPageXPixels(pageNumber,pX);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageXPixelsInView(long pageNumber,long *pX) {

   if ( ! pX )
      return E_POINTER;

   if ( ! pPDFiumDocument_Current )
      return E_UNEXPECTED;
   
   return pPDFiumDocument_Current -> get_PDFPageXPixelsInView(pageNumber,pX);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageYPixels(long pageNumber,long *pY) {

   if ( ! pY )
      return E_POINTER;

   if ( ! pPDFiumDocument_Current )
      return E_UNEXPECTED;
   
   return pPDFiumDocument_Current -> get_PDFPageYPixels(pageNumber,pY);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageYPixelsInView(long pageNumber,long *pY) {

   if ( ! pY )
      return E_POINTER;

   if ( ! pPDFiumDocument_Current )
      return E_UNEXPECTED;
   
   return pPDFiumDocument_Current -> get_PDFPageYPixelsInView(pageNumber,pY);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageWidthPixels(long pageNumber,long *pWidth) {

   if ( ! pWidth )
      return E_POINTER;

   if ( ! pPDFiumDocument_Current )
      return E_UNEXPECTED;
   
   return pPDFiumDocument_Current -> get_PDFPageWidthPixels(pageNumber,pWidth);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageHeightPixels(long pageNumber,long *pHeight) {

   if ( ! pHeight )
      return E_POINTER;

   if ( ! pPDFiumDocument_Current )
      return E_UNEXPECTED;
   
   return pPDFiumDocument_Current -> get_PDFPageHeightPixels(pageNumber,pHeight);
   }


   HRESULT __stdcall PDFiumControl::get_PDFPageXPoints(long pageNumber,long *pX) {

   if ( ! pX )
      return E_POINTER;

   if ( ! pPDFiumDocument_Current )
      return E_UNEXPECTED;
   
   return pPDFiumDocument_Current -> get_PDFPageXPoints(pageNumber,pX);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageYPoints(long pageNumber,long *pY) {

   if ( ! pY )
      return E_POINTER;

   if ( ! pPDFiumDocument_Current )
      return E_UNEXPECTED;
   
   return pPDFiumDocument_Current -> get_PDFPageYPoints(pageNumber,pY);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageWidthPoints(long pageNumber,long *pWidth) {

   if ( ! pWidth )
      return E_POINTER;

   if ( ! pPDFiumDocument_Current )
      return E_UNEXPECTED;
   
   return pPDFiumDocument_Current -> get_PDFPageWidthPoints(pageNumber,pWidth);
   }

   HRESULT __stdcall PDFiumControl::get_PDFPageHeightPoints(long pageNumber,long *pHeight) {

   if ( ! pHeight )
      return E_POINTER;

   if ( ! pPDFiumDocument_Current )
      return E_UNEXPECTED;
   
   return pPDFiumDocument_Current -> get_PDFPageHeightPoints(pageNumber,pHeight);
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
   return pPDFiumDocument_Current -> ConvertPointsToScrollPanePixels(pageNumber,pRect);
   }


   HRESULT __stdcall PDFiumControl::OpenDocument(BSTR pdfFileName,GUID *pIPDFiumDocumentId) {

   if ( ! pIPDFiumDocumentId )
      return E_POINTER;

   char szFileName[MAX_PATH];

   WideCharToMultiByte(CP_ACP,0,pdfFileName,-1,szFileName,MAX_PATH,0,0);

   FPDF_STRING pdfFile(szFileName);

   FPDF_DOCUMENT theDocument = FPDF_LoadDocument(pdfFile,NULL);

   if ( NULL == theDocument )
      return E_FAIL;

   if ( pPDFiumDocument_Current )
      delete pPDFiumDocument_Current;

   pPDFiumDocument_Current = new PDFiumDocument(this,theDocument);

   openedDocuments.push_back(pPDFiumDocument_Current);

   *pIPDFiumDocumentId = *(pPDFiumDocument_Current -> GetId());

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::CloseDocument(GUID *pIPDFiumDocumentId) {

   if ( 0 == openedDocuments.size() )
      return E_FAIL;

   std::list<PDFiumDocument *> toRemove;

   for ( PDFiumDocument *p : openedDocuments ) {
      if ( ( NULL == pIPDFiumDocumentId ) || *(p -> GetId()) == *pIPDFiumDocumentId ) {
         p -> Release();
         if ( p == pPDFiumDocument_Current )
            pPDFiumDocument_Current = NULL;
         toRemove.push_back(p);
         if ( ! ( NULL == pIPDFiumDocumentId ) ) {
            openedDocuments.remove(p);
            return S_OK;
         }
      }
   }

   for ( PDFiumDocument *p : toRemove )
      openedDocuments.remove(p);

   toRemove.clear();

   if ( ! ( NULL == pIPDFiumDocumentId ) )
      return E_FAIL;

   pPDFiumDocument_Current = NULL;

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::FindDocument(GUID *pDocumentId,PDFiumDocument **ppPDFiumDocument) {

   for ( std::list<PDFiumDocument *>::iterator it = openedDocuments.begin(); it != openedDocuments.end(); it++ ) {
      if ( *((*it) -> GetId()) == *pDocumentId ) {
         *ppPDFiumDocument = (*it);
         return S_OK;
      }
   }

   return E_FAIL;
   }


   HRESULT __stdcall PDFiumControl::DisplayDocument(COLORREF passedBackgroundColor,long cxImagePixels,long cyImagePixels,BSTR pdfOrHTMLFileName,long pageNumber) {

   FILE *fDocument = _wfopen(pdfOrHTMLFileName,L"rb");

   if ( NULL == fDocument )
      return E_FAIL;

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

      GUID docId = GUID_NULL;

      OpenDocument(pdfOrHTMLFileName,&docId);

      swprintf_s(szwTemporaryDocumentName,MAX_PATH,L"%ls",_wtempnam(NULL,NULL));

      pPDFiumDocument_Current -> GenerateHTML(backgroundColor,cxPDFWidth,cyPDFHeight,szwTemporaryDocumentName);

      fclose(fDocument);

      documentToLoad = SysAllocString(szwTemporaryDocumentName);

   } else {

      fclose(fDocument);

      documentToLoad = SysAllocString(pdfOrHTMLFileName);

   }

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

   clientRequestedPageNumber = 0;

   if ( 0 == pageNumber || ! isPDF )
      return S_OK;

   clientRequestedPageNumber = pageNumber;

   return S_OK;
   }


   HRESULT __stdcall PDFiumControl::PrintDocument(BSTR documentName,BOOL showPrinterSelection) {

#if 1

   wcscpy_s(szwPendingPrintDocumentName,MAX_PATH,documentName);

   pendingShowPrinterSelection = showPrinterSelection;

   DisplayDocument(0,0,0,documentName,0);

#else
   VARIANT target,vEmpty;

   VariantInit(&vEmpty);
   VariantInit(&target);

   target.vt = VT_BSTR;
   target.bstrVal = L"_self";

   HRESULT rc = pIWebBrowser -> put_AddressBar(VARIANT_TRUE);

   rc = pIWebBrowser -> put_FullScreen(VARIANT_FALSE);

   rc = pIWebBrowser -> Navigate(documentName,&vEmpty,&target,&vEmpty,&vEmpty);

   wcscpy_s(szwPendingPrintDocumentName,MAX_PATH,documentName);

   pendingShowPrinterSelection = showPrinterSelection;

#endif

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
printf("\nhello world");

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


   HRESULT __stdcall PDFiumControl::Cleanup() {

   if ( hwndExplorer ) {
      SetWindowLongPtr(hwndExplorer,GWLP_WNDPROC,(LONG_PTR)nativeExplorerHandler);
      explorerObjectMap.erase(hwndExplorer);
      hwndExplorer = NULL;
   }

   for ( PDFiumDocument *pDocument : openedDocuments ) 
      pDocument -> Release();

   openedDocuments.clear();

   pPDFiumDocument_Current = NULL;

   if ( ( 0 == countInstances ) && ( 0 < pdfiumConfig.version ) ) {
      FPDF_DestroyLibrary();
      memset(&pdfiumConfig,0,sizeof(FPDF_LIBRARY_CONFIG));
   }

   if ( szwTemporaryDocumentName[0] )
      DeleteFile(szwTemporaryDocumentName);

   return S_OK;
   }
