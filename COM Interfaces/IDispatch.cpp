// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   // IDispatch

   STDMETHODIMP PDFiumControl::GetTypeInfoCount(UINT * pctinfo) { 
   *pctinfo = 1;
   return S_OK;
   } 


   long __stdcall PDFiumControl::GetTypeInfo(UINT itinfo,LCID lcid,ITypeInfo **pptinfo) { 

   *pptinfo = NULL; 

   if ( itinfo != 0 ) 
      return DISP_E_BADINDEX; 

   if ( ! pITypeInfo_IPDFiumControl ) {

   }

   *pptinfo = pITypeInfo_IPDFiumControl;

   pITypeInfo_IPDFiumControl -> AddRef();

   return S_OK; 
   } 
 

   STDMETHODIMP PDFiumControl::GetIDsOfNames(REFIID riid,OLECHAR** rgszNames,UINT cNames,LCID lcid, DISPID* rgdispid) { 
   return DispGetIDsOfNames(pITypeInfo_IPDFiumControl, rgszNames, cNames, rgdispid); 
   }


   STDMETHODIMP PDFiumControl::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, 
                                                                        WORD wFlags,DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult,
                                                                         EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr) {
   IDispatch *ppv;
   QueryInterface(IID_IDispatch,reinterpret_cast<void**>(&ppv));
   HRESULT hr = pITypeInfo_IPDFiumControl -> Invoke(ppv,dispidMember,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr);
   ppv -> Release();
   return hr;
   }

