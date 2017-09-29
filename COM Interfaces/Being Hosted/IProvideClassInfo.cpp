
#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::_IProvideClassInfo2::QueryInterface(REFIID riid,void **ppv) {
 
   if ( IID_IProvideClassInfo2 == riid )
      *ppv = static_cast<IProvideClassInfo2 *>(this); 
   else

   if ( IID_IProvideClassInfo == riid )
      *ppv = static_cast<IProvideClassInfo *>(this); 
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();
  
   return S_OK; 
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IProvideClassInfo2::AddRef() {
   return pParent -> AddRef();
   }
   unsigned long __stdcall PDFiumControl::_IOleObject::_IProvideClassInfo2::Release() {
   return pParent -> Release();
   }


   STDMETHODIMP PDFiumControl::_IOleObject::_IProvideClassInfo2::GetClassInfo(ITypeInfo **ppITypeInfo) {
   if ( ! ppITypeInfo )
      return E_POINTER;
   ITypeLib *pITypeLib = NULL;
   HRESULT hr = LoadRegTypeLib(LIBID_PDFiumControl,1,0,0,&pITypeLib);
   pITypeLib -> GetTypeInfoOfGuid(CLSID_PDFiumControl,ppITypeInfo);
   pITypeLib -> Release();
   return S_OK;
   }


   STDMETHODIMP PDFiumControl::_IOleObject::_IProvideClassInfo2::GetGUID(DWORD dwKind,GUID *pGuid) {
   if ( dwKind != GUIDKIND_DEFAULT_SOURCE_DISP_IID || ! pGuid ) 
      return E_INVALIDARG;
   *pGuid = CLSID_PDFiumControl;
   return S_OK;
   }
