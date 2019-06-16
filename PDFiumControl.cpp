// Copyright 2017, 2018, 2019 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   long PDFiumControl::countInstances = 0;
   FPDF_LIBRARY_CONFIG PDFiumControl::pdfiumConfig = {0};
   std::map<HWND,PDFiumControl *> PDFiumControl::explorerObjectMap;
   WNDPROC PDFiumControl::nativeExplorerHandler = NULL;

   PDFiumControl::PDFiumControl(IUnknown *pUnkOuter) :

      connectionPointContainer(this),
      connectionPoint_IPropertyNotifySink(this,IID_IPropertyNotifySink),
      connectionPoint_DWebBrowserEvents2(this,DIID_DWebBrowserEvents2),
      connectionPoint_IPDFiumControlEvents(this,IID_IPDFiumControlEvents),

      isPDF(FALSE),

      refCount(0)
   {

   countInstances++;

   if ( 0 == pdfiumConfig.version ) {

      pdfiumConfig.version = 2;
      pdfiumConfig.m_pUserFontPaths = NULL;
      pdfiumConfig.m_pIsolate = NULL;
      pdfiumConfig.m_v8EmbedderSlot = 0;
      FPDF_InitLibraryWithConfig(&pdfiumConfig);

      HRSRC hResource = FindResource(hModule,MAKEINTRESOURCE(IDITEM_HTML_HEADER),RT_RCDATA);
      BYTE *pResource = (BYTE *)LockResource(LoadResource(hModule,hResource));
      int n = SizeofResource(hModule,hResource);

      memcpy((BYTE *)szHTMLHeader,pResource,min(1024,n));

      hResource = FindResource(hModule,MAKEINTRESOURCE(IDITEM_HTML_PAGE),RT_RCDATA);
      pResource = (BYTE *)LockResource(LoadResource(hModule,hResource));
      n = SizeofResource(hModule,hResource);

      memcpy((BYTE *)szHTMLPage,pResource,min(512,n));

      hResource = FindResource(hModule,MAKEINTRESOURCE(IDITEM_HTML_FOOTER),RT_RCDATA);
      pResource = (BYTE *)LockResource(LoadResource(hModule,hResource));
      n = SizeofResource(hModule,hResource);

      memcpy((BYTE *)szHTMLFooter,pResource,min(512,n));

   }

   memset(szwTemporaryDocumentName,0,sizeof(szwTemporaryDocumentName));
   memset(szwPendingPrintDocumentName,0,sizeof(szwPendingPrintDocumentName));

   SetDefaults();

   return;
   }


   PDFiumControl::~PDFiumControl() {

   countInstances--;

   Cleanup();

   ReleaseMSHTML();

   if ( pIOleObject )
      delete pIOleObject;

   pIOleObject = NULL;

   return;
   }


   void PDFiumControl::InitializeMSHTML() {

   HWND hwndContainer = NULL;

   if ( pIOleObject -> pIOleInPlaceSite_MySite )
      pIOleObject -> pIOleInPlaceSite_MySite -> Release();
 
   pIOleObject -> pIOleInPlaceSite_MySite = NULL;
 
   pIOleObject -> pIOleClientSite_MySite -> QueryInterface(IID_IOleInPlaceSite,(void **)&pIOleObject -> pIOleInPlaceSite_MySite);

   pIOleObject -> pIOleInPlaceSite_MySite -> GetWindow(&hwndContainer);

   GetClientRect(hwndContainer,&rcHTMLHost);

   if ( hwndSite ) {
      SetParent(hwndSite,hwndContainer);
      return;
   }

   IDispatch* pIDispatch;

   HRESULT rc = pIOleObject -> pIOleClientSite_MySite -> QueryInterface(IID_IDispatch,reinterpret_cast<void **>(&pIDispatch));

   if ( S_OK == rc ) {
      DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
      VARIANT var = {VT_EMPTY};
      var.vt = VT_BOOL;
      pIDispatch -> Invoke(DISPID_AMBIENT_USERMODE,IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_PROPERTYGET,&dispparamsNoArgs,&var,NULL,NULL);
      pIDispatch -> Release();
      pIOleObject -> isRunning = (var.bVal == 0 ? false : true);
   } else
      pIOleObject -> isRunning = true;

   WNDCLASS gClass;
   
   memset(&gClass,0,sizeof(WNDCLASS));
   gClass.style = CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW;
   gClass.lpfnWndProc = siteHandler;
   gClass.cbClsExtra = 32;
   gClass.cbWndExtra = 32;
   gClass.hInstance = hModule;
   gClass.hIcon = NULL;
   gClass.hCursor = NULL;
   gClass.hbrBackground = 0;
   gClass.lpszMenuName = NULL;
   gClass.lpszClassName = L"PDFiumControl";
  
   RegisterClass(&gClass);

   hwndSite = CreateWindowEx(0L,L"PDFiumControl",L"",WS_CHILD | WS_VISIBLE,0,0,rcHTMLHost.right - rcHTMLHost.left,rcHTMLHost.bottom - rcHTMLHost.top,hwndContainer,NULL,hModule,(void *)this);

   pIOleInPlaceFrame_HTML_Host = new _IOleInPlaceFrame(this,hwndSite);
   pIOleInPlaceSite_HTML_Host = new _IOleInPlaceSite(this,pIOleInPlaceFrame_HTML_Host);
   pIOleClientSite_HTML_Host = new _IOleClientSite(this,pIOleInPlaceSite_HTML_Host,pIOleInPlaceFrame_HTML_Host);
   pIOleDocumentSite_HTML_Host = new _IOleDocumentSite(this,pIOleClientSite_HTML_Host);

   rc = CoCreateInstance(CLSID_WebBrowser,NULL,CLSCTX_INPROC_SERVER,IID_IWebBrowser2,reinterpret_cast<void **>(&pIWebBrowser));

   if ( S_OK != rc ) {
      MessageBox(NULL,L"The PDFium Control needs to use the Microsoft IE embedded ActiveX Control\n\n"
                        L"This component is part of Microsoft Internet Explorer.\n\n"
                        L"Is IE Installed on your system ?",L"Error!",MB_ICONEXCLAMATION);
      return;
   }

   rc = pIWebBrowser -> put_Resizable(TRUE);

   pIWebBrowser -> put_RegisterAsDropTarget(TRUE);

   pIWebBrowser -> QueryInterface(IID_IOleObject,reinterpret_cast<void **>(&pIOleObject_MSHTML));

   pIOleObject_MSHTML -> QueryInterface(IID_IOleInPlaceObject,reinterpret_cast<void **>(&pIOleInPlaceObject_MSHTML));

   pIOleObject_MSHTML -> SetClientSite(pIOleClientSite_HTML_Host);

   pDWebBrowserEvents_HTML_Host = new _DWebBrowserEvents2(this);

   IUnknown *pIUnknown = NULL;

   pDWebBrowserEvents_HTML_Host -> QueryInterface(IID_IUnknown,reinterpret_cast<void **>(&pIUnknown));

   IConnectionPointContainer *pIConnectionPointContainer = NULL;

   pIWebBrowser -> QueryInterface(IID_IConnectionPointContainer,reinterpret_cast<void**>(&pIConnectionPointContainer));

   if ( pIConnectionPointContainer ) {
      pIConnectionPointContainer -> FindConnectionPoint(DIID_DWebBrowserEvents2,&pIConnectionPoint_MSHTML);
      if ( pIConnectionPoint_MSHTML ) 
         pIConnectionPoint_MSHTML -> Advise(pIUnknown,&connectionCookie_MSHTML);
      pIConnectionPointContainer -> Release();
   }

   pIUnknown -> Release();

   return;
   }

   void PDFiumControl::ReleaseMSHTML() {

   if ( pIElementBehaviorFactory )
      delete pIElementBehaviorFactory;

   pIElementBehaviorFactory = NULL;

   if ( pIElementBehavior )
      delete pIElementBehavior;

   pIElementBehavior = NULL;

   if ( pIHTMLPainter )
      delete pIHTMLPainter;
   
   pIHTMLPainter = NULL;

   if ( pIHTMLBodyElement )
      pIHTMLBodyElement -> Release();

   pIHTMLBodyElement = NULL;

   if ( pIWebBrowserDocument )
      pIWebBrowserDocument -> Release();

   pIWebBrowserDocument = NULL;

   if ( pDocumentElement ) 
      pDocumentElement -> Release();

   pDocumentElement = NULL;

   if ( pIConnectionPoint_MSHTML ) {
      pIConnectionPoint_MSHTML -> Unadvise(connectionCookie_MSHTML);
      pIConnectionPoint_MSHTML -> Release();
      pIConnectionPoint_MSHTML = NULL;
   }

   if ( pIOleObject_MSHTML ) {
      pIOleObject_MSHTML -> SetClientSite(NULL);
      pIOleObject_MSHTML -> Release();
      pIOleObject_MSHTML = NULL;
   }

   if ( pIOleInPlaceObject_MSHTML ) {
      pIOleInPlaceObject_MSHTML -> Release();
      pIOleInPlaceObject_MSHTML = NULL;
   }

   if ( pIOleInPlaceActiveObject_MSHTML ) {
      pIOleInPlaceActiveObject_MSHTML -> Release();
      pIOleInPlaceActiveObject_MSHTML = NULL;
   }

   if ( pIWebBrowser ) {
      pIWebBrowser -> Release();
      pIWebBrowser = NULL;
   }

   return;
   }

   void PDFiumControl::SetDefaults() {

   LOGBRUSH logBrush;
   GetObject(GetSysColorBrush(COLOR_APPWORKSPACE),sizeof(LOGBRUSH),&logBrush);
   backgroundColor = logBrush.lbColor;

   cxPDFWidth = 0;
   cyPDFHeight = 0;

   szwDocumentName[0] = L'\0';

   return;
   }


   void SaveBitmapFile(HDC hdcSource,HBITMAP hBitmap,WCHAR *pszwFileName) {

   BITMAP bitMap;

   GetObject(hBitmap,sizeof(BITMAP),&bitMap);

   long colorTableSize = (long)sizeof(RGBQUAD) * ( 1 << (bitMap.bmPlanes * bitMap.bmBitsPixel) );

   long entireSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize;

   BYTE *pBuffer = new BYTE[entireSize];

   memset(pBuffer,0,entireSize * sizeof(BYTE));

   BITMAPFILEHEADER *pBitmapFileHeader = (BITMAPFILEHEADER *)pBuffer;

   BITMAPINFO *pBitmapInfo = (BITMAPINFO *)(pBuffer + sizeof(BITMAPFILEHEADER));

   BITMAPINFOHEADER *pBitmapInfoHeader = &(pBitmapInfo -> bmiHeader);
   
   pBitmapInfoHeader -> biSize = sizeof(BITMAPINFOHEADER); 
   pBitmapInfoHeader -> biWidth = bitMap.bmWidth;
   pBitmapInfoHeader -> biHeight = bitMap.bmHeight;
   pBitmapInfoHeader -> biPlanes = bitMap.bmPlanes; 
   pBitmapInfoHeader -> biBitCount = bitMap.bmBitsPixel;
   pBitmapInfoHeader -> biCompression = BI_RGB;
   if ( 1 == bitMap.bmBitsPixel ) {
      pBitmapInfoHeader -> biClrUsed = 2;
      pBitmapInfoHeader -> biClrImportant = 2;
   } else {
      pBitmapInfoHeader -> biClrUsed = 0;
      pBitmapInfoHeader -> biClrImportant = 0;
   }

   pBitmapInfoHeader -> biSizeImage = bitMap.bmHeight * ((bitMap.bmWidth * bitMap.bmPlanes * bitMap.bmBitsPixel + 31) & ~31) / 8 ;

   BYTE *pBits = new BYTE[pBitmapInfoHeader -> biSizeImage];

   memset(pBits,0,pBitmapInfoHeader -> biSizeImage);

   long rc = GetDIBits(hdcSource,hBitmap,0,bitMap.bmHeight,pBits,pBitmapInfo,DIB_RGB_COLORS);

   pBitmapFileHeader -> bfType = 0x4d42;

   pBitmapFileHeader -> bfSize = entireSize + pBitmapInfoHeader -> biSizeImage;

   pBitmapFileHeader -> bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize;

   FILE *fBitmap = _wfopen(pszwFileName,L"wb");

   fwrite(pBitmapFileHeader,sizeof(BITMAPFILEHEADER),1,fBitmap);

   fwrite(pBitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,fBitmap);

   fwrite(pBitmapInfo -> bmiColors,colorTableSize,1,fBitmap);

   fwrite(pBits,pBitmapInfoHeader -> biSizeImage,1,fBitmap);

   fclose(fBitmap);

   delete [] pBuffer;
   delete [] pBits;

   return;
   }
