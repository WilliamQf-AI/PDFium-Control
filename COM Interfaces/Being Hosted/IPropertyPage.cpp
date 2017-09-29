
#include "PDFiumControl.h"

   //
   //NTC: 09-13-2017: The disabled code in this file is left in place to demonstrate how property pages can be
   // implemented in COM. The original code is from another project of mine that implements 3 property pages.
   //

   static bool okayToSave = false;

   long __stdcall PDFiumControl::_IOleObject::_IPropertyPage::QueryInterface(REFIID riid,void **ppv) {
   *ppv = NULL;
   if ( riid == IID_IPropertyPage )
      *ppv = static_cast<IPropertyPage *>(this);
   else
      return pParent -> QueryInterface(riid,ppv);
   AddRef(); 
   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IPropertyPage::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IPropertyPage::Release() {
   return pParent -> Release();
   }
 
 
   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::SetPageSite(IPropertyPageSite *pPageSite) {
   return S_OK;
   }

   
   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::Activate(HWND hwndParent,const RECT *pRect,BOOL doModal) {

#if 0
   if ( 0 == nativePropertySheetFrameHandlerRefCount ) {
      hwndPropertySheetFrame = GetParent(hwndParent);
      nativePropertySheetFrameHandler = (WNDPROC)SetWindowLongPtr(hwndPropertySheetFrame,GWLP_WNDPROC,(ULONG_PTR)propertySheetFrameHandler);
   }

   nativePropertySheetFrameHandlerRefCount++;
#endif

   if ( CLSID_PDFiumControlPropertyPage == theCLSID ) {
      if ( pParent -> hwndPropertyPage )
         DestroyWindow(pParent -> hwndPropertyPage);
      pParent -> hwndPropertyPage = CreateDialogParam(hModule,MAKEINTRESOURCE(IDDIALOG_PROPERTIES),hwndParent,(DLGPROC)PDFiumControl::_IOleObject::propertiesHandler,(ULONG_PTR)pParent);
      SetWindowPos(pParent -> hwndPropertyPage,HWND_TOP,pRect -> left,pRect -> top,pRect -> right - pRect -> left,pRect -> bottom - pRect -> top,SWP_SHOWWINDOW);
      return S_OK;
   }

   return S_OK;
   }


   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::Deactivate() {

   if ( CLSID_PDFiumControlPropertyPage == theCLSID ) {
      if ( pParent -> hwndPropertyPage ) {
         DestroyWindow(pParent -> hwndPropertyPage);
         pParent -> hwndPropertyPage = NULL;
      }
   }

   return S_OK;
   }



   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::GetPageInfo(PROPPAGEINFO *pPageInfo) {

   memset(pPageInfo,0,sizeof(PROPPAGEINFO));

   pPageInfo -> cb = sizeof(PROPPAGEINFO);

   pPageInfo -> pszTitle = (BSTR)CoTaskMemAlloc(128);

   pPageInfo -> pszDocString = NULL;

   memset(pPageInfo -> pszTitle,0,128);

   if ( CLSID_PDFiumControlPropertyPage == theCLSID ) {
      MultiByteToWideChar(CP_ACP,0,"PDFium Control Properties",-1,(BSTR)pPageInfo -> pszTitle,128);
      pPageInfo -> size.cx = 256 + 128 + 64;
      pPageInfo -> size.cy = 256 + 128;
   }

   return S_OK;
   }


   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::SetObjects(ULONG cObjects,IUnknown** pUnk) {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::Show(UINT cmdShow) {

   if ( CLSID_PDFiumControlPropertyPage == theCLSID )
      ShowWindow(pParent -> hwndPropertyPage,cmdShow);

   return S_OK;
   }


   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::Move(const RECT *prc) {

   if ( CLSID_PDFiumControlPropertyPage == theCLSID )
      SetWindowPos(pParent -> hwndPropertyPage,HWND_TOP,prc -> left,prc -> top, prc -> right - prc -> left,prc -> bottom - prc -> top,0L);

   return S_OK;
   }


   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::IsPageDirty() {
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::Apply() {

#if 0
   pParent -> fire_PropertyChanged();

   if ( ! okayToSave )
      return S_OK;

   okayToSave = false;

   PSHNOTIFY notify = {0};

   notify.hdr.code = PSN_APPLY;
   notify.lParam = 1L;

//   if ( CLSID_PhabletSignaturePadPropertyPage == theCLSID ) 
      SendMessage(pParent -> hwndPropertyPage,WM_NOTIFY,0L,(LPARAM)&notify);

//   if ( CLSID_PhabletSignaturePadRuntimePropertyPage == theCLSID ) 
      SendMessage(pParent -> hwndRuntimePropertyPage,WM_NOTIFY,0L,(LPARAM)&notify);

//   if ( CLSID_PhabletSignaturePadDocumentationPropertyPage == theCLSID ) 
      SendMessage(pParent -> hwndDocumentationPropertyPage,WM_NOTIFY,0L,(LPARAM)&notify);
#endif
   return S_OK;
   }


   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::Help(LPCOLESTR pszHelpDir) {
   return E_FAIL;
   }


   HRESULT PDFiumControl::_IOleObject::_IPropertyPage::TranslateAccelerator(MSG* pMsg) {
   return S_FALSE;
   }

//
//NTC: 02-08-2012. This is a total bullshit hack that is necessary because the MS documentation
// cannot bother to say anywhere how on earth to tell if the user pressed OK, or Cancel - as if
// nobody would ever want to know this absolutely obvious thing to need to know !?!
//
#if 0
   LRESULT CALLBACK PDFiumControl::_IOleObject::propertySheetFrameHandler(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
   if ( msg == WM_COMMAND ) {
      switch ( LOWORD(wParam ) ) {
      case IDOK:
         okayToSave = true;
         break;
      case IDCANCEL:
         okayToSave = false;
         break;
      }
   }
   return CallWindowProc(nativePropertySheetFrameHandler,hwnd,msg,wParam,lParam);
   }
 #endif