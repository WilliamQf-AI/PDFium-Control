
#include "PDFiumControl.h"


   PDFiumControl::_IConnectionPointContainer::_IConnectionPointContainer(PDFiumControl *pp) : 
     pParent(pp)
   { 
   return;
   }

   PDFiumControl::_IConnectionPointContainer::~_IConnectionPointContainer() {
   return;
   }


   HRESULT PDFiumControl::_IConnectionPointContainer::QueryInterface(REFIID riid,void **ppv) {
   return pParent -> QueryInterface(riid,ppv);
   }


   STDMETHODIMP_(ULONG) PDFiumControl::_IConnectionPointContainer::AddRef() {
   return pParent -> AddRef();
   }

   STDMETHODIMP_(ULONG) PDFiumControl::_IConnectionPointContainer::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IConnectionPointContainer::EnumConnectionPoints(IEnumConnectionPoints **ppEnum) {

   _IConnectionPoint *pConnectionPoints[3];

   *ppEnum = NULL;
 
   if ( pParent -> pEnumConnectionPoints ) 
      delete pParent -> pEnumConnectionPoints;
 
   pConnectionPoints[0] = &pParent -> connectionPoint_IPropertyNotifySink;

   pConnectionPoints[1] = &pParent -> connectionPoint_DWebBrowserEvents2;

   pConnectionPoints[2] = &pParent -> connectionPoint_IPDFiumControlEvents;

   pParent -> pEnumConnectionPoints = new _IEnumConnectionPoints(pParent,pConnectionPoints,2);
 
   return pParent -> pEnumConnectionPoints -> QueryInterface(IID_IEnumConnectionPoints,(void **)ppEnum);
   }
 
 
   STDMETHODIMP PDFiumControl::_IConnectionPointContainer::FindConnectionPoint(REFIID riid,IConnectionPoint **ppCP) {

   *ppCP = NULL;

   if ( IID_IPropertyNotifySink == riid ) {
      *ppCP = static_cast<IConnectionPoint *>(&pParent -> connectionPoint_IPropertyNotifySink);
      pParent -> connectionPoint_IPropertyNotifySink.AddRef();
      return S_OK;
   }

   if ( DIID_DWebBrowserEvents2 == riid ) {
      *ppCP = static_cast<IConnectionPoint *>(&pParent -> connectionPoint_DWebBrowserEvents2);
      pParent -> connectionPoint_DWebBrowserEvents2.AddRef();
      return S_OK;
   }

   if ( IID_IPDFiumControlEvents == riid ) {
      *ppCP = static_cast<IConnectionPoint *>(&pParent -> connectionPoint_IPDFiumControlEvents);
      pParent -> connectionPoint_IPDFiumControlEvents.AddRef();
      return S_OK;
   }

   return CONNECT_E_NOCONNECTION;
   }

   // IPropertyNotifySink

   void PDFiumControl::_IConnectionPointContainer::fire_PropertyChanged() {
   IEnumConnections* pIEnum;
   CONNECTDATA connectData;
   pParent -> connectionPoint_IPropertyNotifySink.EnumConnections(&pIEnum);
   if ( ! pIEnum ) return;
   while ( 1 ) {
      if ( pIEnum -> Next(1, &connectData, NULL) ) break;
      IPropertyNotifySink *pClient = reinterpret_cast<IPropertyNotifySink *>(connectData.pUnk);
      pClient -> OnChanged(DISPID_UNKNOWN);
   }
   static_cast<IUnknown*>(pIEnum) -> Release();
   return;
   }

   // DWebBrowserEvents2

   void PDFiumControl::_IConnectionPointContainer::fire_Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,DISPPARAMS * pDispParams, VARIANT FAR* pvarResult,EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr) {
   IEnumConnections* pIEnum;
   CONNECTDATA connectData;
   pParent -> connectionPoint_DWebBrowserEvents2.EnumConnections(&pIEnum);
   if ( ! pIEnum ) return;
   while ( 1 ) {
      if ( pIEnum -> Next(1, &connectData, NULL) ) break;
      DWebBrowserEvents2 *pClient = reinterpret_cast<DWebBrowserEvents2 *>(connectData.pUnk);
      pClient -> Invoke(dispidMember,riid,lcid,wFlags,pDispParams,pvarResult,pexcepinfo,puArgErr);
   }
   static_cast<IUnknown*>(pIEnum) -> Release();
   return;
   }

   // IPDFiumControlEvents

   void PDFiumControl::_IConnectionPointContainer::fire_MouseMessage(UINT msg,WPARAM wParam,LPARAM lParam) {
   IEnumConnections* pIEnum = NULL;
   CONNECTDATA connectData;
   pParent -> connectionPoint_IPDFiumControlEvents.EnumConnections(&pIEnum);
   if ( ! pIEnum ) return;
   while ( 1 ) {
      if ( pIEnum -> Next(1, &connectData, NULL) ) break;
      IPDFiumControlEvents *pClient = reinterpret_cast<IPDFiumControlEvents *>(connectData.pUnk);
      pClient -> MouseMessage(msg,wParam,lParam);
   }
   static_cast<IUnknown*>(pIEnum) -> Release();
   return;
   }

   void PDFiumControl::_IConnectionPointContainer::fire_Size(SIZE *pSize) {
   IEnumConnections* pIEnum = NULL;
   CONNECTDATA connectData;
   pParent -> connectionPoint_IPDFiumControlEvents.EnumConnections(&pIEnum);
   if ( ! pIEnum ) return;
   while ( 1 ) {
      if ( pIEnum -> Next(1, &connectData, NULL) ) break;
      IPDFiumControlEvents *pClient = reinterpret_cast<IPDFiumControlEvents *>(connectData.pUnk);
      pClient -> Size(pSize);
   }
   static_cast<IUnknown*>(pIEnum) -> Release();
   return;
   }

   void PDFiumControl::_IConnectionPointContainer::fire_Paint(HDC hdc,RECT *prcUpdate) {
   IEnumConnections* pIEnum = NULL;
   CONNECTDATA connectData;
   pParent -> connectionPoint_IPDFiumControlEvents.EnumConnections(&pIEnum);
   if ( ! pIEnum ) return;
   while ( 1 ) {
      if ( pIEnum -> Next(1, &connectData, NULL) ) break;
      IPDFiumControlEvents *pClient = reinterpret_cast<IPDFiumControlEvents *>(connectData.pUnk);
      pClient -> Paint(hdc,prcUpdate);
   }
   static_cast<IUnknown*>(pIEnum) -> Release();
   return;
   }