
#include "PDFiumControl.h"

   void PDFiumControl::_IOleObject::initialize() {

   if ( pIOleInPlaceSite_MySite )
      pIOleInPlaceSite_MySite -> Release();
 
   pIOleInPlaceSite_MySite = NULL;
 
   pIOleClientSite_MySite -> QueryInterface(IID_IOleInPlaceSite,(void **)&pIOleInPlaceSite_MySite);

   IDispatch* pIDispatch;

   HRESULT rc = pIOleClientSite_MySite -> QueryInterface(IID_IDispatch,reinterpret_cast<void **>(&pIDispatch));

   if ( S_OK == rc ) {
      DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
      VARIANT var = {VT_EMPTY};
      var.vt = VT_BOOL;
      pIDispatch -> Invoke(DISPID_AMBIENT_USERMODE,IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_PROPERTYGET,&dispparamsNoArgs,&var,NULL,NULL);
      pIDispatch -> Release();
      isRunning = (var.bVal == 0 ? false : true);
   } else
      isRunning = true;

   hwndContainer = NULL;

   pIOleInPlaceSite_MySite -> GetWindow(&hwndContainer);

   if ( pParent -> hwndSite ) {
      SetParent(pParent -> hwndSite,hwndContainer);
      return;
   }

   pParent -> Initialize(hwndContainer);

   return;
   }

