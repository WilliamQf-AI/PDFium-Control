
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

#if 0
      if ( pParent -> pIElementBehaviorFactory )
         delete pParent -> pIElementBehaviorFactory;

      pParent -> pIElementBehaviorFactory = NULL;

      if ( pParent -> pIElementBehavior )
         delete pParent -> pIElementBehavior;

      pParent -> pIElementBehavior = NULL;

      if ( pParent -> pIHTMLPainter )
         delete pParent -> pIHTMLPainter;
      
      pParent -> pIHTMLPainter = NULL;

#endif

      IDispatch *pIDispatch = NULL;

      pParent -> pIWebBrowser -> get_Document(&pIDispatch);

      if ( pIDispatch )
         pIDispatch -> QueryInterface(IID_IHTMLDocument3,reinterpret_cast<void **>(&pParent -> pIWebBrowserDocument));

      if ( pParent -> pIWebBrowserDocument ) {

         IHTMLElement *pIHTMLElement = NULL;

         pParent -> pIWebBrowserDocument -> getElementById(L"body",&pIHTMLElement);

         if ( pIHTMLElement ) {

#if 0
            pParent -> pIElementBehaviorFactory = new _IElementBehaviorFactory(pParent);
            pParent -> pIElementBehavior = new _IElementBehavior(pParent);
            pParent -> pIHTMLPainter = new _IHTMLPainter(pParent);
#endif

            pIHTMLElement -> QueryInterface(IID_IHTMLElement2,reinterpret_cast<void **>(&pParent -> pDocumentElement));

#if 0
            IUnknown *pIUnknown = NULL;

            pParent -> pIElementBehaviorFactory -> QueryInterface(IID_IUnknown,reinterpret_cast<void **>(&pIUnknown));

            VARIANT v;

            V_VT(&v) = VT_UNKNOWN;
            V_UNKNOWN(&v) = pIUnknown;

            HRESULT rc = pParent -> pDocumentElement -> addBehavior(L"Paint",&v,&pParent -> pIElementBehaviorFactory -> dwCookie);

            pIUnknown -> Release();
#endif

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

#if 0
      pParent -> ignoreDocumentOpenInWebBrowser = false;

      if ( ! pParent -> ignoreDocumentOpenProcessingSteps )
         PostMessage(hwndMainFrame,WM_DOCUMENT_IS_OPENED,0L,0L);
      else
         pParent -> ignoreDocumentOpenProcessingSteps = false;
#endif

      break;
      }

   default:
      break;

   }

   pParent -> connectionPointContainer.fire_Invoke(dispidMember,riid,lcid,wFlags,pDispParams,pvarResult,pexcepinfo,puArgErr);

   return S_OK;
   }