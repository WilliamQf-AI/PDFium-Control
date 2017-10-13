
#include "PDFiumControl.h"

   PDFiumControl::_IConnectionPoint::_IEnumConnections::_IEnumConnections(_IConnectionPoint *pp) :
      pParent(pp)
   {
   return;
   }


   PDFiumControl::_IConnectionPoint::_IEnumConnections::~_IEnumConnections() {
   return;
   }


   STDMETHODIMP PDFiumControl::_IConnectionPoint::_IEnumConnections::QueryInterface(REFIID riid,void **ppv) {
   *ppv = NULL;
   if ( IID_IEnumConnections == riid )
      *ppv = static_cast<IEnumConnections *>(this);
   else
      return pParent -> QueryInterface(riid,ppv);
   AddRef();
   return S_OK;
   }


   STDMETHODIMP_(ULONG) PDFiumControl::_IConnectionPoint::_IEnumConnections::AddRef() {
   return pParent -> AddRef();
   }

   STDMETHODIMP_(ULONG) PDFiumControl::_IConnectionPoint::_IEnumConnections::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IConnectionPoint::_IEnumConnections::Next(ULONG cReq,CONNECTDATA* paConnections,ULONG* pcEnumerated) {

   ULONG cRet;

   if ( NULL == paConnections ) 
      return E_POINTER;

   for ( cRet = 0; enumeratorIndex < (ULONG)pParent -> CountLiveConnections() && cReq > 0; paConnections++, enumeratorIndex++, cRet++, cReq-- ) 
      *paConnections = pParent -> ConnectionData()[enumeratorIndex];

   if ( ! ( NULL == pcEnumerated ) )
      *pcEnumerated = cRet;

   return 0 == cRet ? S_FALSE : S_OK;
   }


   STDMETHODIMP PDFiumControl::_IConnectionPoint::_IEnumConnections::Skip(ULONG cSkip) {
   if ( ( enumeratorIndex + cSkip ) < (ULONG)pParent -> CountLiveConnections() ) 
      return S_FALSE;
   enumeratorIndex += cSkip;
   return S_OK;
   }



   STDMETHODIMP PDFiumControl::_IConnectionPoint::_IEnumConnections::Reset() {
   enumeratorIndex = 0;
   return S_OK;
   }



   STDMETHODIMP PDFiumControl::_IConnectionPoint::_IEnumConnections::Clone(IEnumConnections** ppIEnum) {

   _IEnumConnections* p = new _IEnumConnections(pParent);

   return p -> QueryInterface(IID_IEnumConnections,(void **)ppIEnum);
   }
