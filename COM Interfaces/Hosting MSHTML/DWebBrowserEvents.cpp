// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

#include <IDispIds.h>
#include <exDispId.h>

   // IUnknown

   long __stdcall PDFiumControl::_DWebBrowserEvents2::QueryInterface(REFIID riid,void **ppv) {

   if ( riid == DIID_DWebBrowserEvents2 )
      *ppv = static_cast<_DWebBrowserEvents2 *>(this);
   else
      return pParent -> QueryInterface(riid,ppv);

   AddRef();

   return S_OK;
   }
   unsigned long __stdcall PDFiumControl::_DWebBrowserEvents2::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_DWebBrowserEvents2::Release() { 
   return pParent -> Release();
   }
 
   // IDispatch

   STDMETHODIMP PDFiumControl::_DWebBrowserEvents2::GetTypeInfoCount(UINT * pctinfo) { 
   *pctinfo = 0;
   return S_OK;
   } 

   long __stdcall PDFiumControl::_DWebBrowserEvents2::GetTypeInfo(UINT itinfo,LCID lcid,ITypeInfo **pptinfo) { 
   return E_NOTIMPL;
   } 

   STDMETHODIMP PDFiumControl::_DWebBrowserEvents2::GetIDsOfNames(REFIID riid,OLECHAR** rgszNames,UINT cNames,LCID lcid, DISPID* rgdispid) { 
   return E_NOTIMPL;
   }


   STDMETHODIMP PDFiumControl::_DWebBrowserEvents2::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, 
                                                          WORD wFlags,DISPPARAMS * pDispParams, VARIANT FAR* pvarResult,
                                                          EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr) { 

   switch ( dispidMember ) {

   case DISPID_STATUSTEXTCHANGE:
      break;

   case DISPID_DOWNLOADBEGIN:
      break;

   case DISPID_ONVISIBLE:
      break;

   case DISPID_NAVIGATECOMPLETE:
      break;

   case DISPID_COMMANDSTATECHANGE:  
      pParent -> calcDimensions();
      break;

   case DISPID_DOCUMENTCOMPLETE: {

      if ( pParent -> pIWebBrowserDocument )
         pParent -> pIWebBrowserDocument -> Release();

      pParent -> pIWebBrowserDocument = NULL;

      if ( pParent -> pDocumentElement )
         pParent -> pDocumentElement -> Release();

      pParent -> pDocumentElement = NULL;

      if ( pParent -> pIElementBehaviorFactory )
         delete pParent -> pIElementBehaviorFactory;

      pParent -> pIElementBehaviorFactory = NULL;

      if ( pParent -> pIElementBehavior )
         delete pParent -> pIElementBehavior;

      pParent -> pIElementBehavior = NULL;

      if ( pParent -> pIHTMLPainter )
         delete pParent -> pIHTMLPainter;
      
      pParent -> pIHTMLPainter = NULL;

      IDispatch *pIDispatch = NULL;

      pParent -> pIWebBrowser -> get_Document(&pIDispatch);

      if ( pIDispatch )
         pIDispatch -> QueryInterface(IID_IHTMLDocument3,reinterpret_cast<void **>(&pParent -> pIWebBrowserDocument));

      if ( pParent -> pIWebBrowserDocument ) {

         IHTMLElement *pIHTMLElement = NULL;

         pParent -> pIWebBrowserDocument -> getElementById(L"body",&pIHTMLElement);

         if ( pIHTMLElement ) {

            pParent -> pIElementBehaviorFactory = new _IElementBehaviorFactory(pParent);
            pParent -> pIElementBehavior = new _IElementBehavior(pParent);
            pParent -> pIHTMLPainter = new _IHTMLPainter(pParent);

            pIHTMLElement -> QueryInterface(IID_IHTMLElement2,reinterpret_cast<void **>(&pParent -> pDocumentElement));

            IUnknown *pIUnknown = NULL;

            pParent -> pIElementBehaviorFactory -> QueryInterface(IID_IUnknown,reinterpret_cast<void **>(&pIUnknown));

            VARIANT v;

            V_VT(&v) = VT_UNKNOWN;
            V_UNKNOWN(&v) = pIUnknown;

            HRESULT rc = pParent -> pDocumentElement -> addBehavior(L"Paint",&v,&pParent -> pIElementBehaviorFactory -> dwCookie);

            pIUnknown -> Release();

            pIHTMLElement -> QueryInterface(IID_IHTMLBodyElement,reinterpret_cast<void **>(&pParent -> pIHTMLBodyElement));

            pIHTMLElement -> Release();

            pIHTMLElement = NULL;

            if ( 0 < pParent -> clientRequestedPageNumber ) {

               pParent -> navigatePage(pParent -> clientRequestedPageNumber);

               pParent -> clientRequestedPageNumber = 0;

            }

         } else 

            pIDispatch -> Release();

      } else
         if ( pIDispatch )
            pIDispatch -> Release();

      if ( pParent -> szwPendingPrintDocumentName[0] ) 
         PostMessage(pParent -> hwndSite,WM_PRINT_DOCUMENT,0L,0L);

      if ( NULL == pParent -> hwndExplorer ) {

         pParent -> hwndExplorer = FindWindowWithClass(pParent -> hwndSite,"Internet Explorer_Server");

         explorerObjectMap[pParent -> hwndExplorer] = pParent;

         if ( NULL == nativeExplorerHandler && ! ( NULL == pParent -> hwndExplorer ) ) 
            nativeExplorerHandler = (WNDPROC)SetWindowLongPtr(pParent -> hwndExplorer,GWLP_WNDPROC,(LONG_PTR)explorerHandler);
         else 
            if ( ! ( NULL == pParent -> hwndExplorer ) )
               SetWindowLongPtr(pParent -> hwndExplorer,GWLP_WNDPROC,(LONG_PTR)explorerHandler);

      }

      break;
      }

   default:
      break;

   }

   pParent -> connectionPointContainer.fire_Invoke(dispidMember,riid,lcid,wFlags,pDispParams,pvarResult,pexcepinfo,puArgErr);

   return S_OK;
   }