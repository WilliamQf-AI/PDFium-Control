// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   HRESULT __stdcall PDFiumControl::_IAcroAXDocShim::QueryInterface(REFIID riid, void** ppv) {

   *ppv = NULL;

   if ( IID_IUnknown == riid )
      *ppv = this;
   else

   if ( IID_IDispatch == riid )
      *ppv = static_cast<IDispatch *>(this);
   else

   if ( IID_IPDFiumControl_IAcroAXDocShim == riid )
      *ppv = static_cast<PDFiumControl::_IAcroAXDocShim *>(this);
   else

   if ( IID_IAcroAXDocShim == riid )
      *ppv = static_cast<PDFiumControl::_IAcroAXDocShim *>(this);
   else

      return pParent -> QueryInterface(riid,ppv);

   AddRef();

   return S_OK;
   }


   ULONG __stdcall PDFiumControl::_IAcroAXDocShim::AddRef() {
   return refCount++;
   }


   ULONG __stdcall PDFiumControl::_IAcroAXDocShim::Release() { 
   if ( --refCount == 0 ) {
      delete this;
      return 0;
   }
   return refCount;
   }


   // IDispatch

   STDMETHODIMP PDFiumControl::_IAcroAXDocShim::GetTypeInfoCount(UINT * pctinfo) { 
   *pctinfo = 1;
   return S_OK;
   } 


   long __stdcall PDFiumControl::_IAcroAXDocShim::GetTypeInfo(UINT itinfo,LCID lcid,ITypeInfo **pptinfo) { 
   *pptinfo = NULL; 
   if ( itinfo != 0 ) 
      return DISP_E_BADINDEX; 
   *pptinfo = pITypeInfo_IAcroAXDocShim;
   pITypeInfo_IAcroAXDocShim -> AddRef();
   return S_OK; 
   } 
 

   STDMETHODIMP PDFiumControl::_IAcroAXDocShim::GetIDsOfNames(REFIID riid,OLECHAR** rgszNames,UINT cNames,LCID lcid, DISPID* rgdispid) { 
   return DispGetIDsOfNames(pITypeInfo_IAcroAXDocShim,rgszNames,cNames,rgdispid);
   }


   STDMETHODIMP PDFiumControl::_IAcroAXDocShim::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, 
                                                         WORD wFlags,DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult,
                                                            EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr) { 
   return DispInvoke(this,pITypeInfo_IAcroAXDocShim,dispidMember,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr); 
   }


