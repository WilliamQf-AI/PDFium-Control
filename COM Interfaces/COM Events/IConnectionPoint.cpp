
#include "PDFiumControl.h"

#define ALLOC_CONNECTIONS  16

  PDFiumControl::_IConnectionPoint::_IConnectionPoint(PDFiumControl *pp,REFIID theInterface) : 
     pParent(pp), 
     adviseSink(0),
     nextCookie(400),
     countLiveConnections(0),
     eventsInterfaceId(theInterface),
     countConnections(ALLOC_CONNECTIONS)
   { 
   pConnections = new CONNECTDATA[countConnections];
   memset(pConnections, 0, countConnections * sizeof(CONNECTDATA));
   pEnumConnections = new PDFiumControl::_IConnectionPoint::_IEnumConnections(this);
   return;
   }


   PDFiumControl::_IConnectionPoint::~_IConnectionPoint() {
   for ( int k = 0; k < countConnections; k++ ) 
      if ( pConnections[k].pUnk ) 
         pConnections[k].pUnk -> Release();
   delete [] pConnections;
   return;
   }


   HRESULT PDFiumControl::_IConnectionPoint::QueryInterface(REFIID riid,void **ppv) {
   *ppv = NULL;
   if ( IID_IConnectionPoint == riid ) 
      *ppv = static_cast<IConnectionPoint *>(this);
   else
      return pParent -> QueryInterface(riid,ppv);
   AddRef();
   return S_OK;
   }


   STDMETHODIMP_(ULONG) PDFiumControl::_IConnectionPoint::AddRef() {
   return pParent -> AddRef();
   }

   STDMETHODIMP_(ULONG) PDFiumControl::_IConnectionPoint::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IConnectionPoint::GetConnectionInterface(IID *pIID) {
   if ( NULL == pIID ) 
      return E_POINTER;
   *pIID = eventsInterfaceId;
   return S_OK;
   }


   STDMETHODIMP PDFiumControl::_IConnectionPoint::GetConnectionPointContainer(IConnectionPointContainer **ppCPC) {
   return QueryInterface(IID_IConnectionPointContainer,(void **)ppCPC);
   }


   STDMETHODIMP PDFiumControl::_IConnectionPoint::Advise(IUnknown *pUnkSink,DWORD *pdwCookie) {

   HRESULT hr;
   IUnknown* pISink = 0;

   hr = pUnkSink -> QueryInterface(eventsInterfaceId,(void **)&pISink);

   if ( E_NOINTERFACE == hr ) 
      return CONNECT_E_NOCONNECTION;

   if ( ! SUCCEEDED(hr) ) 
      return hr;

   if ( ! pISink ) 
      return CONNECT_E_CANNOTCONNECT;

   int freeSlot = getSlot();

   pISink -> AddRef();

   pConnections[freeSlot].pUnk = pISink;

   pConnections[freeSlot].dwCookie = nextCookie;

   *pdwCookie = nextCookie++;

   countLiveConnections++;

   return S_OK;
   }


   STDMETHODIMP PDFiumControl::_IConnectionPoint::Unadvise(DWORD dwCookie) {

   if ( 0 == dwCookie ) 
      return E_INVALIDARG;

   int slot = findSlot(dwCookie);

   if ( -1 == slot ) 
      return CONNECT_E_NOCONNECTION;

   if ( pConnections[slot].pUnk ) 
      pConnections[slot].pUnk -> Release();

   pConnections[slot].pUnk = NULL;

   pConnections[slot].dwCookie = 0;

   countLiveConnections--;

   return S_OK;
   }


   STDMETHODIMP PDFiumControl::_IConnectionPoint::EnumConnections(IEnumConnections **ppEnum) {

   *ppEnum = NULL;

   if ( 0 == countLiveConnections ) 
      return OLE_E_NOCONNECTION;

   pEnumConnections -> Reset();

   pEnumConnections -> QueryInterface(IID_IEnumConnections,(void **)ppEnum);

   return S_OK;
   }


   int PDFiumControl::_IConnectionPoint::getSlot() {

   CONNECTDATA *pMoreConnections;

   int k = findSlot(0);

   if ( -1 < k ) 
      return k;

   pMoreConnections = new CONNECTDATA[countConnections + ALLOC_CONNECTIONS];

   memset( pMoreConnections, 0, sizeof(CONNECTDATA) * (countConnections + ALLOC_CONNECTIONS));

   memcpy( pMoreConnections, pConnections, sizeof(CONNECTDATA) * countConnections);

   delete [] pConnections;

   pConnections = pMoreConnections;

   countConnections += ALLOC_CONNECTIONS;

   return countConnections - ALLOC_CONNECTIONS;
   }


   int PDFiumControl::_IConnectionPoint::findSlot(DWORD dwCookie) {
   for ( int k = 0; k < countConnections; k++ )
      if ( dwCookie == pConnections[k].dwCookie ) 
         return k;
   return -1;
   }