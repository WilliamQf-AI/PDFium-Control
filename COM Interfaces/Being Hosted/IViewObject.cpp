
#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::_IViewObjectEx::QueryInterface(REFIID riid,void **ppv) {

   *ppv = NULL;

   if ( IID_IViewObject == riid )
      *ppv = static_cast<IViewObject *>(this);
   else

   if ( IID_IViewObject2 == riid )
      *ppv = static_cast<IViewObject2 *>(this);
   else

   if ( IID_IViewObjectEx == riid )
      *ppv = static_cast<IViewObjectEx *>(this);
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();
   return S_OK;
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IViewObjectEx::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IViewObjectEx::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::Draw(DWORD dvAspect,long index,void *pvAspect,DVTARGETDEVICE *ptd,
                          HDC hicTarget,HDC hdcDraw,const struct _RECTL *pRectClient,
                          const struct _RECTL *rectlMetaFile,int (__stdcall *cancelFunction)(ULONG_PTR),ULONG_PTR cancelParameter) {
 
   if ( dvAspect != DVASPECT_CONTENT )
      return S_OK;

   if ( pRectClient ) {

      RECT rcResult;

      memcpy(&rcResult,pRectClient,sizeof(RECT));

      double aspectRatio = 835.0 / 366.0;

      double thisAspect = (double)(pRectClient -> right - pRectClient -> left) / (double) (pRectClient -> bottom - pRectClient -> top);

      if ( thisAspect < aspectRatio ) {

         long cx = (rcResult.right - rcResult.left);

         rcResult.left = (rcResult.right + rcResult.left) / 2 - cx / 2;
         rcResult.right = rcResult.left + cx;

         long cy = (long)((double)cx / aspectRatio);

         rcResult.top = (rcResult.bottom + rcResult.top) / 2 - cy / 2;
         rcResult.bottom = rcResult.top + cy;

      } else {

         long cy = (rcResult.bottom - rcResult.top);

         rcResult.top = (rcResult.bottom + rcResult.top) / 2 - cy / 2;
         rcResult.bottom = rcResult.top + cy;

         long cx = (long)((double)cy * aspectRatio);

         rcResult.left = (rcResult.left + rcResult.right) / 2 - cx / 2;
         rcResult.right = rcResult.left + cx;

      }

#if 0
      HDC hdcSource = CreateCompatibleDC(NULL);
      HANDLE hBitmap = LoadImage(hModule,MAKEINTRESOURCE(IDBITMAP_BACKGROUND),IMAGE_BITMAP,0,0,0L);
      HANDLE oldObject = SelectObject(hdcSource,hBitmap);
      StretchBlt(hdcDraw,rcResult.left,rcResult.top,rcResult.right - rcResult.left,rcResult.bottom - rcResult.top,hdcSource,0,0,835,366,SRCCOPY);
      DeleteObject(hBitmap);
      DeleteDC(hdcSource);
#endif

   } else {

#if 0
      IDispatch* pIDispatch;
   	DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
      VARIANT var = {VT_EMPTY};
      GVariantClear(&var);
      var.vt = VT_BOOL;
      pParent -> pIOleClientSite -> QueryInterface(IID_IDispatch,reinterpret_cast<void**>(&pIDispatch));
      pIDispatch -> Invoke(DISPID_AMBIENT_USERMODE,IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_PROPERTYGET,&dispparamsNoArgs,&var,NULL,NULL);
      pIDispatch -> Release();
      if ( var.bVal ) {
         ShowWindow(pParent -> hwndOleObject,SW_HIDE);
         return S_OK;
      }
#endif

   }
 
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::GetColorSet(DWORD,long,void *,DVTARGETDEVICE *,HDC,LOGPALETTE **) {
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::Freeze(DWORD,long,void *,DWORD *) {
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::Unfreeze(DWORD) {
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::SetAdvise(DWORD dwAspect,DWORD advf,IAdviseSink *pAdvise) {
   if ( ! pAdvise ) {
      if ( pParent -> pViewAdviseSink ) 
         pParent -> pViewAdviseSink -> Release();
      pParent -> pViewAdviseSink = NULL;
      return S_OK;
   }
   pParent -> pViewAdviseSink = pAdvise;
   pParent -> adviseSink_dwAspect = dwAspect;
   pParent -> adviseSink_advf = advf;
   pAdvise -> AddRef();
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::GetAdvise(DWORD *pdwAspect,DWORD *padvf,IAdviseSink **ppAdvise) {
   if ( pParent -> pViewAdviseSink == NULL ) {
      if ( padvf ) *padvf = 0;
      if ( pdwAspect ) *pdwAspect = 0;
      if ( ppAdvise ) *ppAdvise = NULL; 
      return S_OK;
   }
   if ( ppAdvise ) {
      *ppAdvise = pParent -> pViewAdviseSink;
      pParent -> pViewAdviseSink -> AddRef();
   }      
   if ( pdwAspect ) *pdwAspect = pParent -> adviseSink_dwAspect;
   if ( padvf ) *padvf = pParent -> adviseSink_advf;
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::GetExtent(unsigned long,long,DVTARGETDEVICE *,struct tagSIZE *s) {
   s -> cx = pParent -> containerSize.cx;
   s -> cy = pParent -> containerSize.cy;
   pixelsToHiMetric(s,s);
   return S_OK;
   }
 
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::GetRect(DWORD dwAspect,RECTL *pRectl){
   return S_OK; 
   }
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::GetViewStatus(DWORD *dwViewStatus){ 
   *dwViewStatus = VIEWSTATUS_OPAQUE;
   return S_OK; 
   }
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::QueryHitPoint(DWORD dwAspect,const struct tagRECT *pRectBounds,POINT ptlHit,long lCloseHint,DWORD *dwHitResult){
   return S_OK; 
   }
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::QueryHitRect(DWORD dwAspect,const struct tagRECT *pRectBounds,const struct tagRECT *rctHit,long lCloseHint,DWORD *dwHitResult){  
   return S_OK; 
   }
 
   STDMETHODIMP PDFiumControl::_IOleObject::_IViewObjectEx::GetNaturalExtent(DWORD dwExtent,LONG lIndex,DVTARGETDEVICE *ptd,HDC hicTargetDev,DVEXTENTINFO *extentInfo,SIZEL *){ 
   return S_OK;
   }


