
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
  connections = new CONNECTDATA[countConnections];
  memset(connections, 0, countConnections * sizeof(CONNECTDATA));
  return;
  };


  PDFiumControl::_IConnectionPoint::~_IConnectionPoint() {
  for ( int k = 0; k < countConnections; k++ ) 
     if ( connections[k].pUnk ) connections[k].pUnk -> Release();
  delete [] connections;
  return;
  }


  HRESULT PDFiumControl::_IConnectionPoint::QueryInterface(REFIID riid,void **ppv) {
  return pParent -> QueryInterface(riid,ppv);
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
  return pParent -> QueryInterface(IID_IConnectionPointContainer,(void **)ppCPC);
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

   int freeSlot;

   *pdwCookie = 0;

   freeSlot = getSlot();

   pISink -> AddRef();

   connections[freeSlot].pUnk = pISink;
   connections[freeSlot].dwCookie = nextCookie;

   *pdwCookie = nextCookie++;

   countLiveConnections++;

   return S_OK;
   }


  STDMETHODIMP PDFiumControl::_IConnectionPoint::Unadvise(DWORD dwCookie) {

  if ( 0 == dwCookie ) return E_INVALIDARG;

  int slot;

  slot = findSlot(dwCookie);

  if ( slot == -1 ) return CONNECT_E_NOCONNECTION;

  if ( connections[slot].pUnk ) connections[slot].pUnk -> Release();

  connections[slot].dwCookie = 0;

  countLiveConnections--;

  return S_OK;
  }

  STDMETHODIMP PDFiumControl::_IConnectionPoint::EnumConnections(IEnumConnections **ppEnum) {
  CONNECTDATA *tempConnections;
  int i,j;

  *ppEnum = NULL;

  if ( countLiveConnections == 0 ) return OLE_E_NOCONNECTION;

  tempConnections = new CONNECTDATA[countLiveConnections];

  for ( i = 0, j = 0; i < countConnections && j < countLiveConnections; i++) {

    if ( 0 != connections[i].dwCookie ) {
      tempConnections[j].pUnk = (IUnknown *)connections[i].pUnk;
      tempConnections[j].dwCookie = connections[i].dwCookie;
      j++;
    }
  }

  _IEnumerateConnections *p = new _IEnumerateConnections(this,countLiveConnections,tempConnections,0);
  p -> QueryInterface(IID_IEnumConnections,(void **)ppEnum);

  delete [] tempConnections;

  return S_OK;
  }


  int PDFiumControl::_IConnectionPoint::getSlot() {
  CONNECTDATA* moreConnections;
  int i;
  i = findSlot(0);
  if ( i > -1 ) return i;
  moreConnections = new CONNECTDATA[countConnections + ALLOC_CONNECTIONS];
  memset( moreConnections, 0, sizeof(CONNECTDATA) * (countConnections + ALLOC_CONNECTIONS));
  memcpy( moreConnections, connections, sizeof(CONNECTDATA) * countConnections);
  delete [] connections;
  connections = moreConnections;
  countConnections += ALLOC_CONNECTIONS;
  return countConnections - ALLOC_CONNECTIONS;
  }


  int PDFiumControl::_IConnectionPoint::findSlot(DWORD dwCookie) {
  for ( int i = 0; i < countConnections; i++ )
     if ( dwCookie == connections[i].dwCookie ) return i;
  return -1;
  }