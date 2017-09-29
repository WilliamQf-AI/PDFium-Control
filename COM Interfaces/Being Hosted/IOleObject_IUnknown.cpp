
#include "PDFiumControl.h"

   long __stdcall PDFiumControl::_IOleObject::QueryInterface(REFIID riid,void **ppv) {
 
   *ppv = NULL;

   if ( IID_IUnknown == riid )
      *ppv = static_cast<IUnknown *>(this);

   if ( IID_IOleObject == riid )
      *ppv = static_cast<IOleObject *>(this); 

   if ( *ppv ) {
      AddRef();
      return S_OK;
   }

   if ( IID_IQuickActivate == riid )
      return pIQuickActivate -> QueryInterface(riid,ppv);

   if ( IID_IDataObject == riid )
      return pIDataObject -> QueryInterface(riid,ppv);

   if ( IID_IOleControl == riid ) 
      return pIOleControl -> QueryInterface(riid,ppv);

   if ( IID_IOleInPlaceObject == riid )
      return pIOleInPlaceObject -> QueryInterface(riid,ppv);

   if ( IID_IOleInPlaceActiveObject == riid )
      return pIOleInPlaceActiveObject -> QueryInterface(riid,ppv);

   if ( IID_IProvideClassInfo == riid )
      return pIProvideClassInfo2 -> QueryInterface(riid,ppv);

   if ( IID_IProvideClassInfo2 == riid )
      return pIProvideClassInfo2 -> QueryInterface(riid,ppv);

   if ( IID_IViewObject == riid )
      return pIViewObjectEx -> QueryInterface(riid,ppv);

   if ( IID_IViewObject2 == riid )
      return pIViewObjectEx -> QueryInterface(riid,ppv);

   if ( IID_IViewObjectEx == riid )
      return pIViewObjectEx -> QueryInterface(riid,ppv);

   if ( IID_IRunnableObject == riid )
      return pIRunnableObject -> QueryInterface(riid,ppv);

   if ( IID_ISpecifyPropertyPages == riid )
      return pISpecifyPropertyPages -> QueryInterface(riid,ppv);

   if ( IID_IPersistStreamInit == riid )
      return pIPersistStreamInit -> QueryInterface(riid,ppv);

   if ( IID_IPersistStorage == riid )
      return pIPersistStorage -> QueryInterface(riid,ppv);

   fromOleObject = true;

   HRESULT rc = pParent -> QueryInterface(riid,ppv);

   fromOleObject = false;

   return rc;
   }

   unsigned long __stdcall PDFiumControl::_IOleObject::AddRef() {
   return ++refCount;
   }
 
   unsigned long __stdcall PDFiumControl::_IOleObject::Release() {
   if ( 1 == refCount ) {
      delete this;
      return 0;
   }
   return --refCount;
   }
