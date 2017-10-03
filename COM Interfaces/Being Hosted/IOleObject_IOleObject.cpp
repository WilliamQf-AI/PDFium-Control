
#include "PDFiumControl.h"

   STDMETHODIMP PDFiumControl::_IOleObject::SetClientSite(IOleClientSite *pcs) {

   if ( ! pcs ) {

      if ( pIOleClientSite_MySite )
         pIOleClientSite_MySite -> Release();

      pIOleClientSite_MySite = NULL;

      if ( pIOleInPlaceSite_MySite ) 
         pIOleInPlaceSite_MySite -> Release();

      pIOleInPlaceSite_MySite = NULL;

      if ( pParent -> hwndSite ) {
         DestroyWindow(pParent -> hwndSite);
         pParent -> hwndSite = NULL;
      }

      return S_OK;

   }
 
   if ( pIOleClientSite_MySite )
      pIOleClientSite_MySite -> Release();

   pIOleClientSite_MySite = pcs;
 
   pIOleClientSite_MySite -> AddRef();

   initialize();

   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::GetClientSite(IOleClientSite **pcs) {
   *pcs = pIOleClientSite_MySite;
   pIOleClientSite_MySite -> AddRef();
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::Advise(IAdviseSink *pAdvSink,DWORD *pdwConnection) {
   if ( ! pOleAdviseHolder )
      CreateOleAdviseHolder(&pOleAdviseHolder);
   if ( pOleAdviseHolder)
      pOleAdviseHolder -> Advise(pAdvSink,pdwConnection);
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::Unadvise(DWORD dwConnection) {
   if ( pOleAdviseHolder)
      pOleAdviseHolder -> Unadvise(dwConnection);
   pOleAdviseHolder = NULL;
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::EnumAdvise(IEnumSTATDATA **ppenum) {
   if ( pOleAdviseHolder)
      return pOleAdviseHolder -> EnumAdvise(ppenum);
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::SetExtent(DWORD dwDrawAspect,SIZEL *pSizel) {
   if ( dwDrawAspect != DVASPECT_CONTENT ) 
      return S_OK;
   SIZEL tempSizel;
   RECT rect = {0,0,0,0};
   hiMetricToPixel(pSizel,&tempSizel);
   rect.right = tempSizel.cx;
   rect.bottom = tempSizel.cy;
   SetWindowPos(pParent -> hwndSite,HWND_TOP,0,0,rect.right - rect.left,rect.bottom - rect.top,SWP_NOMOVE);
   memcpy(&containerSize,&tempSizel,sizeof(SIZEL));
   return S_OK;
   }
 
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::GetExtent(DWORD dwDrawAspect,SIZEL *pSizel) {
   memcpy(pSizel,&containerSize,sizeof(SIZEL));
   pixelToHiMetric(pSizel,pSizel);
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::DoVerb(LONG iVerb, LPMSG ,IOleClientSite *pClientSite, LONG,HWND hwndParent,LPCRECT lprcPosRect) {

   switch ( iVerb ) {
   case OLEIVERB_PRIMARY:
   case OLEIVERB_OPEN:
      break;

   case OLEIVERB_PROPERTIES:
//      SendMessage(hwndSite,WM_COMMAND,MAKEWPARAM(ID_SETUP,0),0L);
      break;
 
   case OLEIVERB_UIACTIVATE:
      break;
 
   case OLEIVERB_HIDE:
      ShowWindow(pParent -> hwndSite,SW_HIDE);
      break;
 
   case OLEIVERB_SHOW: 
      pIOleInPlaceObject -> SetObjectRects(lprcPosRect,NULL);
      ShowWindow(pParent -> hwndSite,SW_SHOW);
      break;
 
   case OLEIVERB_INPLACEACTIVATE:
      pIOleInPlaceObject -> SetObjectRects(lprcPosRect,NULL);
      pIOleInPlaceObject -> InPlaceActivate();
      break;
 
   default:
      break;
   }

   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::SetHostNames(LPCOLESTR szContainerApp,LPCOLESTR olestrContainerObject) {
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::Close(DWORD dwOptions) {
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::SetMoniker(DWORD dwMonikerNo,IMoniker *pm) {
   return E_NOTIMPL;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::GetMoniker(DWORD dwAssign,DWORD dwMonikerNo,IMoniker **ppm) {
   return E_NOTIMPL;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::InitFromData(IDataObject *pdo,BOOL fCreation,DWORD dwReserved) {
   return E_NOTIMPL;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::GetClipboardData(DWORD,IDataObject **ppdo) {
   return E_NOTIMPL;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::EnumVerbs(IEnumOLEVERB **ppEnumOleVerb) {
   HRESULT rc = OleRegEnumVerbs(CLSID_PDFiumControl,ppEnumOleVerb);
   return rc;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::Update() {
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::IsUpToDate() {
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::GetUserClassID(CLSID *pclsid) {
   *pclsid = CLSID_PDFiumControl;
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::GetUserType(DWORD dwTypeOfType,LPOLESTR *pszTypeName) {
   return OleRegGetUserType(CLSID_PDFiumControl,dwTypeOfType,pszTypeName);
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::GetMiscStatus(DWORD dwAspect,DWORD *dwStatus) {
   if ( dwAspect == DVASPECT_CONTENT )
      *dwStatus = OLEMISC_ACTIVATEWHENVISIBLE | OLEMISC_SETCLIENTSITEFIRST | 0*OLEMISC_INSIDEOUT | 
                            OLEMISC_CANTLINKINSIDE | OLEMISC_RECOMPOSEONRESIZE | OLEMISC_ALWAYSRUN;
   else
      *dwStatus = 0;
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::SetColorScheme(LOGPALETTE *) {
   return S_OK;
   }
