// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <windows.h>
#include <objbase.h>
#include <ShlObj.h>
#include <objsafe.h>

#include <msHTML.h>
#include <MsHtmcid.h>
#include <mshtmhst.h>

#include <list>
#include <map>

#include "resource.h"

#include "utilities.h"

#include "pdfium\fpdfview.h"

#include "PDFiumControl_i.h"

#include "PDFiumControl_IAcroAXDocShim_i.h"

#define COORDINATE_NOT_IN_VIEW -32768

extern "C" const GUID __declspec(selectany) IID_IAcroAXDocShim = {0x3b813ce7,0x7c10,0x4f84,{0xad,0x06,0x9d,0xf7,0x6d,0x97,0xa9,0xaa}};

   class PDFiumControl : public IPDFiumControl {

   public:

      PDFiumControl(IUnknown *pUnkOuter);

      ~PDFiumControl();

      // IUnknown

      STDMETHOD(QueryInterface)(REFIID riid,void **ppv);

      STDMETHOD_ (ULONG, AddRef)();
      STDMETHOD_ (ULONG, Release)();

      // IDispatch

      STDMETHOD(GetTypeInfoCount)(UINT *pctinfo);
      STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo **pptinfo);
      STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgdispid);
      STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pdispparams, VARIANT *pvarResult, EXCEPINFO *pexcepinfo, UINT *puArgErr);

      void InitializeMSHTML();

      void ReleaseMSHTML();

      void SetDefaults();

      bool isInView(long x,long cx);

      long ScrollTop() { return scrollTop; };

   private:

      // IPDFiumControl

      STDMETHOD(put_BackgroundColor)(COLORREF color);
      STDMETHOD(get_BackgroundColor)(COLORREF *pColor);

      STDMETHOD(put_PDFWidth)(long cxPDFWidth);
      STDMETHOD(get_PDFWidth)(long *pcxPDFWidth);

      STDMETHOD(put_PDFHeight)(long cyPDFHeight);
      STDMETHOD(get_PDFHeight)(long *pcyPDFHeight);

      STDMETHOD(put_EnableExplorerContextMenu)(BOOL doEnable);

      STDMETHOD(get_PageCount)(long *pPageCount);

      STDMETHOD(get_PDFPagesVisible)(BSTR *pPagesVisible);

      STDMETHOD(get_PDFPageMostVisible)(long *pPageNumber);

      STDMETHOD(get_PDFPageXPixels)(long pageNumber,long *pX);

      STDMETHOD(get_PDFPageXPixelsInView)(long pageNumber,long *pX);

      STDMETHOD(get_PDFPageYPixels)(long pageNumber,long *pY);

      STDMETHOD(get_PDFPageYPixelsInView)(long pageNumber,long *pY);

      STDMETHOD(get_PDFPageWidthPixels)(long pageNumber,long *pWidth);

      STDMETHOD(get_PDFPageHeightPixels)(long pageNumber,long *pHeight);

      STDMETHOD(get_PDFPageXPoints)(long pageNumber,long *pX);

      STDMETHOD(get_PDFPageYPoints)(long pageNumber,long *pY);

      STDMETHOD(get_PDFPageWidthPoints)(long pageNumber,long *pWidth);

      STDMETHOD(get_PDFPageHeightPoints)(long pageNumber,long *pHeight);

      STDMETHOD(get_PDFPageNumberAtY)(long yValue,long seekHeight,long *pPageNumber);

      STDMETHOD(put_Document)(BSTR documentName);
      STDMETHOD(get_Document)(BSTR *pDocumentName);

      STDMETHOD(get_IsPDF)(BOOL *);

      STDMETHOD(put_ScrollBarVisible)(BOOL);

      STDMETHOD(get_ScrollBarVisible)(BOOL *);

      STDMETHOD(ConvertPointsToScrollPanePixels)(long pageNumber,RECT *pRect);

      STDMETHOD(OpenDocument)(BSTR pdfFileName);

      STDMETHOD(CloseDocument)();

      STDMETHOD(DisplayDocument)(COLORREF backgroundColor,long cxImagePixels,long cyImagePixels,BSTR pdfOrHTMLFileName,long pageNumber);

      STDMETHOD(GoToPage)(long pageNumber);

      STDMETHOD(PrintCurrentDocument)(BOOL showPrinterSelection);

      STDMETHOD(PrintDocument)(BSTR documentName,BOOL showPrinterSelection);

      STDMETHOD(FinalRelease)();

      STDMETHOD(Cleanup)();

   //
   //NTC: 09-21-2017: I don't think there is any reason to expose this interface.
   //
   // class PDFiumDocument : public IPDFiumDocument {
      class PDFiumDocument : public IUnknown {

      public:

         PDFiumDocument(PDFiumControl *pp,FPDF_DOCUMENT pDoc);

         ~PDFiumDocument();

         // IUnknown

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);

         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         // IPDFiumDocument

         STDMETHOD(GenerateHTML)(COLORREF backgroundColor,long cxImage,long cyImage,BSTR htmlFileName);

         STDMETHOD(get_PDFPageCount)(long *pCount);

         STDMETHOD(get_PDFPageXPixels)(long pageNumber,long *pX);
         STDMETHOD(put_PDFPageXPixels)(long pageNumber,long x);

         STDMETHOD(get_PDFPageXPixelsInView)(long pageNumber,long *pX);

         STDMETHOD(get_PDFPageYPixels)(long pageNumber,long *pY);
         STDMETHOD(put_PDFPageYPixels)(long pageNumber,long y);

         STDMETHOD(get_PDFPageYPixelsInView)(long pageNumber,long *pY);

         STDMETHOD(get_PDFPageWidthPixels)(long pageNumber,long *pWidth);
         STDMETHOD(put_PDFPageWidthPixels)(long pageNumber,long cx);

         STDMETHOD(get_PDFPageHeightPixels)(long pageNumber,long *pHeight);
         STDMETHOD(put_PDFPageHeightPixels)(long pageNumber,long cy);

         STDMETHOD(get_PDFPageXPoints)(long pageNumber,long *pX);
         STDMETHOD(put_PDFPageXPoints)(long pageNumber,long x);

         STDMETHOD(get_PDFPageYPoints)(long pageNumber,long *pY);
         STDMETHOD(put_PDFPageYPoints)(long pageNumber,long cy);

         STDMETHOD(get_PDFPageWidthPoints)(long pageNumber,long *pWidth);
         STDMETHOD(put_PDFPageWidthPoints)(long pageNumber,long cx);

         STDMETHOD(get_PDFPageHeightPoints)(long pageNumber,long *pHeight);
         STDMETHOD(put_PDFPageHeightPoints)(long pageNumber,long cy);

         STDMETHOD(ConvertPointsToScrollPanePixels)(long pageNumber,RECT *pRect);


      private:
   
         PDFiumControl *pParent{NULL};
         FPDF_DOCUMENT pDocumentObject{NULL};
         UINT refCount{0};

         int pageCount{0};

         std::map<long,POINTL *> pagePDFDimensions;
         std::map<long,POINTL *> pagePDFLocations;
         std::map<long,POINTL *> pagePixelDimensions;
         std::map<long,POINTL *> pagePixelLocations;

         static std::list<WCHAR *> imageFiles;

      };

      // IPDFiumControl_IAcroAXDocShim

      //
      //NTC: 09-13-2017: See the note in the PDFiumControl_IAcroAXDocShim.odl file. The Adobe reader's interface
      // is declared here (not completely), but the implementation is just stubbed out (see IAcroAXDocShim.cpp).
      // If someone completed that implementation, then changed the object CLSID to that of the Reader's version
      // this object could service existing Reader implementations without even re-compile of the client(s).
      //

      class _IAcroAXDocShim : public IPDFiumControl_IAcroAXDocShim {

      public:

         _IAcroAXDocShim(PDFiumControl *pp) : pParent(pp) {};

         // IUnknown

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);

         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         // IDispatch

         STDMETHOD(GetTypeInfoCount)(UINT *pctinfo);
         STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo **pptinfo);
         STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgdispid);
         STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pdispparams, VARIANT *pvarResult, EXCEPINFO *pexcepinfo, UINT *puArgErr);

         // IAcroAXDocShim

         STDMETHOD(put_src)(BSTR sourceDocument);
         STDMETHOD(get_src)(BSTR *pSourceDocument);

/*
         STDMETHOD(put_messageHandler)(VARIANT messageHandler);
         STDMETHOD(get_messageHandler)(VARIANT *pMessageHandler);
*/

         VARIANT_BOOL __stdcall LoadFile(BSTR fileName );
         STDMETHOD(setShowToolbar)(VARIANT_BOOL On);
         STDMETHOD(gotoFirstPage)();
         STDMETHOD(gotoLastPage)();
         STDMETHOD(gotoNextPage)();
         STDMETHOD(gotoPreviousPage)();
         STDMETHOD(setCurrentPage)(long n );
         STDMETHOD(goForwardStack)();
         STDMETHOD(goBackwardStack)();
         STDMETHOD(setPageMode)(BSTR pageMode);
         STDMETHOD(setLayoutMode)(BSTR layoutMode);
         STDMETHOD(setNamedDest)(BSTR namedDest);
         STDMETHOD(Print)();
         STDMETHOD(printWithDialog)();
         STDMETHOD(setZoom)(float percent);
         STDMETHOD(setZoomScroll)(float percent,float left,float top);
         STDMETHOD(setView)(BSTR viewMode);
         STDMETHOD(setViewScroll)(BSTR viewMode,float offset );
         STDMETHOD(setViewRect)(float left,float top,float width,float height);
         STDMETHOD(printPages)(long from,long to);
         STDMETHOD(printPagesFit)(long from,long to,VARIANT_BOOL shrinkToFit);
         STDMETHOD(printAll)();
         STDMETHOD(printAllFit)(VARIANT_BOOL shrinkToFit);
         STDMETHOD(setShowScrollbars)(VARIANT_BOOL On);
/*
         VARIANT GetVersions();
*/
         STDMETHOD(setCurrentHightlight)(long a,long b,long c,long d);
         STDMETHOD(setCurrentHighlight)(long a,long b,long c,long d);

      private:

         PDFiumControl *pParent{NULL};

         ULONG refCount{0};

      } *pIAcroAXDocShim{NULL};

      //      IConnectionPointContainer

      struct _IConnectionPointContainer : public IConnectionPointContainer {

      public:

         _IConnectionPointContainer(PDFiumControl *pp);

         ~_IConnectionPointContainer();

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         STDMETHOD(FindConnectionPoint)(REFIID riid,IConnectionPoint **);
         STDMETHOD(EnumConnectionPoints)(IEnumConnectionPoints **);

         // IPropertyNotifySinc

         void fire_PropertyChanged();

         // IPDFiumControlEvents

         void fire_MouseMessage(UINT msg,WPARAM wParam,LPARAM lParam);

         void fire_Size(SIZE *pSize);

         void fire_Paint(HDC hdc,RECT *pRcUpdate);

         // DWebBrowserEvents2

         void fire_Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pdispparams, VARIANT *pvarResult, EXCEPINFO *pexcepinfo, UINT *puArgErr);

      private:

         PDFiumControl *pParent;

      } connectionPointContainer;

      struct _IConnectionPoint : IConnectionPoint {

      public:

         _IConnectionPoint(PDFiumControl *pp,REFIID eventsInterfaceId);
	      ~_IConnectionPoint();

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         STDMETHOD (GetConnectionInterface)(IID *);
         STDMETHOD (GetConnectionPointContainer)(IConnectionPointContainer **ppCPC);
         STDMETHOD (Advise)(IUnknown *pUnk,DWORD *pdwCookie);
         STDMETHOD (Unadvise)(DWORD);
         STDMETHOD (EnumConnections)(IEnumConnections **ppEnum);

         IUnknown *AdviseSink() { return adviseSink; };

         int CountLiveConnections() { return countLiveConnections; };

         CONNECTDATA *ConnectionData() { return pConnections; };

         struct _IEnumConnections : public IEnumConnections {

         public:

            _IEnumConnections(_IConnectionPoint *pParent);
            ~_IEnumConnections();

            STDMETHOD(QueryInterface)(REFIID, void **);
            STDMETHODIMP_(ULONG) AddRef();
            STDMETHODIMP_(ULONG) Release();
            STDMETHOD(Next)(ULONG, CONNECTDATA*, ULONG*);
            STDMETHOD(Skip)(ULONG);
            STDMETHOD(Reset)();
            STDMETHOD(Clone)(IEnumConnections**);

         private:

            _IConnectionPoint *pParent{NULL};
            ULONG enumeratorIndex{0};

            } *pEnumConnections{NULL};

      private:

         int getSlot();
         int findSlot(DWORD dwCookie);

	      IUnknown *adviseSink{NULL};
	      PDFiumControl *pParent{NULL};
         DWORD nextCookie{400};
	      int countConnections{0};
         int countLiveConnections{0};

         CONNECTDATA *pConnections{NULL};

         IID eventsInterfaceId;

      } connectionPoint_IPropertyNotifySink,connectionPoint_DWebBrowserEvents2,connectionPoint_IPDFiumControlEvents;

	   struct _IEnumConnectionPoints : IEnumConnectionPoints {

	   public:

	      _IEnumConnectionPoints(PDFiumControl *pp,_IConnectionPoint **,int connectionPointCount);

         ~_IEnumConnectionPoints();

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

 	      STDMETHOD (Next)(ULONG cConnections,IConnectionPoint **rgpcn,ULONG *pcFetched);
         STDMETHOD (Skip)(ULONG cConnections);
         STDMETHOD (Reset)();
         STDMETHOD (Clone)(IEnumConnectionPoints **);

      private:

         int cpCount,enumeratorIndex;
		   PDFiumControl *pParent;
		   _IConnectionPoint **connectionPoints;

      } *pEnumConnectionPoints{NULL};


#ifdef EMBEDDED_OBJECT_EMBEDDER_CLASS
#undef EMBEDDED_OBJECT_EMBEDDER_CLASS
#endif
#define EMBEDDED_OBJECT_EMBEDDER_CLASS PDFiumControl

#include "interfacesToSupportAnEmbeddedObject.h"

      //
      // Objects Used to host an ActiveX control
      //

      // DWebBrowserEvents2

      class _DWebBrowserEvents2 : public DWebBrowserEvents2 {

      public:

         _DWebBrowserEvents2(PDFiumControl *pp) : pParent(pp) {};

         //   IUnknown

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHODIMP_(ULONG) AddRef();
         STDMETHODIMP_(ULONG) Release();

         // IDispatch

         STDMETHOD(GetTypeInfoCount)(UINT *pctinfo);
         STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo **pptinfo);
         STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgdispid);
         STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pdispparams, VARIANT *pvarResult, EXCEPINFO *pexcepinfo, UINT *puArgErr);

      private:

         PDFiumControl *pParent;

      } *pDWebBrowserEvents_HTML_Host{NULL};

      // IElementBehaviorFactory

      class _IElementBehaviorFactory : public IElementBehaviorFactory  {

      public:

         _IElementBehaviorFactory(PDFiumControl * pp) : pParent(pp), dwCookie(0), pIElementBehaviorSite(NULL) {};

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);

         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         STDMETHOD(FindBehavior)(BSTR bstrBehavior,BSTR bstrBehaviorUrl,IElementBehaviorSite *pSite,IElementBehavior **ppBehavior);

         long dwCookie;

         IElementBehaviorSite *pIElementBehaviorSite;

      private:

         PDFiumControl *pParent;

      } * pIElementBehaviorFactory{NULL};

      // IElementBehavior

      class _IElementBehavior : public IElementBehavior {

      public:

         _IElementBehavior(PDFiumControl *pp) : pParent(pp), pIHTMLPaintSite(NULL) {};
         ~_IElementBehavior() { if ( pIHTMLPaintSite ) pIHTMLPaintSite -> Release(); };

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         STDMETHOD(Init)(IElementBehaviorSite *pBehaviorSite);
         STDMETHOD(Notify)(long event,VARIANT *pVar);
         STDMETHOD(Detach)();

         IHTMLPaintSite *pIHTMLPaintSite;

      private:

         PDFiumControl *pParent;

      } * pIElementBehavior{NULL};


      // IHTMLPainter

      class _IHTMLPainter : public IHTMLPainter {

      public:

         _IHTMLPainter(PDFiumControl *pp) : pParent(pp) {};

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

      private:

         STDMETHOD(Draw)(RECT rcBounds,RECT rcUpdate,LONG lDrawFlags,HDC hdc,LPVOID pvDrawObject);
         STDMETHOD(OnResize)(SIZE size);
         STDMETHOD(GetPainterInfo)(HTML_PAINTER_INFO *pInfo);
         STDMETHOD(HitTestPoint)(POINT pt,BOOL *pbHit,LONG *plPartID);

         PDFiumControl *pParent{NULL};

      } * pIHTMLPainter{NULL};

#include "COM Interfaces\Being Hosted\OleObject.h"

   public:

      _IOleObject *GetIOleObject() { if ( NULL == pIOleObject ) pIOleObject = new _IOleObject(this); return pIOleObject; };

      void calcDimensions();

      long pageNumberContainingY(long yValue,long seekHeight);

      void navigatePage(long pageNumber);

   private:

      //
      // Objects used to host MSHTML
      //

      IOleInPlaceObject *pIOleInPlaceObject_MSHTML{NULL};
      IOleObject *pIOleObject_MSHTML{NULL};
      IOleInPlaceActiveObject *pIOleInPlaceActiveObject_MSHTML{NULL};

      IConnectionPoint *pIConnectionPoint_MSHTML{NULL};
      DWORD connectionCookie_MSHTML{0L};

      HWND hwndExplorer{NULL};

      //
      // End of objects used to host MSHTML
      //

      //
      // Object Used to be a MSHTML client
      //

      IWebBrowser2 *pIWebBrowser{NULL};
      IHTMLDocument3 *pIWebBrowserDocument{NULL};
      IHTMLElement2 *pDocumentElement{NULL};
      IHTMLBodyElement *pIHTMLBodyElement{NULL};

      RECT rcHTMLHost{0,0,0,0};

      //
      // Objects necessary for being hosted
      //

      HWND hwndSite{NULL};

      //
      // PDFiumControl Properties
      //

      BYTE propertiesStart{0xFF};
      COLORREF backgroundColor{0};
      long cxPDFWidth{0};
      long cyPDFHeight{0};
      WCHAR szwDocumentName[1024];
      BOOL enableExplorerContextMenu{TRUE};
      BYTE propertiesEnd{0xFF};

      long scrollTop{0};
      long scrollHeight{0};
      long cyClient{0};

      PDFiumDocument *pPDFiumDocument{NULL};

      long maxVisiblePage{0};
      long clientRequestedPageNumber{0};

      WCHAR szwPageLabel[512]{0};
     
      WCHAR szwTemporaryDocumentName[MAX_PATH];
      WCHAR szwPendingPrintDocumentName[MAX_PATH];
      BOOL pendingShowPrinterSelection{FALSE};

      HANDLE hSemaphore_DocumentLoaded{NULL};

      BOOL isPDF;

      ULONG refCount;

      static std::map<HWND,PDFiumControl *> explorerObjectMap;

      static long countInstances;

      static FPDF_LIBRARY_CONFIG pdfiumConfig;

      static WNDPROC nativeExplorerHandler;

      static LRESULT CALLBACK siteHandler(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
      static LRESULT CALLBACK explorerHandler(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

   };

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

   MIDL_DEFINE_GUID(CLSID,CLSID_PDFiumControlPropertyPage,0xB5FF6E92,0xF84E,0x432C,0xAA,0xCB,0x09,0x82,0xC9,0x40,0xE5,0x36);

   void SaveBitmapFile(HDC hdcSource,HBITMAP hBitmap,WCHAR *pszwFileName);

#ifdef DEFINE_DATA

   HMODULE hModule;
   WCHAR szwModuleName[MAX_PATH];
   ITypeInfo *pITypeInfo_IAcroAXDocShim;
   ITypeInfo *pITypeInfo_IPDFiumControl = NULL;

   char szHTMLHeader[1024];
   char szHTMLPage[512];
   char szHTMLFooter[512];

   bool fromOleObject = false;

#else

   extern HMODULE hModule;
   extern WCHAR szwModuleName[];
   extern ITypeInfo *pITypeInfo_IAcroAXDocShim;
   extern ITypeInfo *pITypeInfo_IPDFiumControl;

   extern char szHTMLHeader[];
   extern char szHTMLPage[];
   extern char szHTMLFooter[];

   extern bool fromOleObject;

#endif