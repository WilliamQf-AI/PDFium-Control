// Copyright 2017, 2018, 2019 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   PDFiumControl::_IOleObject::_IOleObject(PDFiumControl *pp) :

      pParent(pp),

      pIOleControl(NULL),
      pIDataObject(NULL),
      pIOleInPlaceObject(NULL),
      pIOleInPlaceActiveObject(NULL),
      pIViewObjectEx(NULL),
      pIProvideClassInfo2(NULL),
      pIPersistStreamInit(NULL),
      pIPersistStorage(NULL),
      pIQuickActivate(NULL),
      pISpecifyPropertyPages(NULL),
      pIRunnableObject(NULL),

      pOleAdviseHolder(NULL),
      pDataAdviseHolder(NULL),

      pViewAdviseSink(NULL),
      dwViewAdviseSinkConnection(0L),
      adviseSink_dwAspect(0L),
      adviseSink_advf(0L),

      pIOleClientSite_MySite(NULL),
      pIOleInPlaceSite_MySite(NULL),

      hwndContainer(NULL),
      hwndPropertyPage(NULL)

   {

   memset(&containerSize,0,sizeof(containerSize));

   pIOleControl = new _IOleControl(this);
   pIDataObject = new _IDataObject(this);
   pIOleInPlaceObject = new _IOleInPlaceObject(this);
   pIOleInPlaceActiveObject = new _IOleInPlaceActiveObject(this);
   pIProvideClassInfo2 = new _IProvideClassInfo2(this);
   pIViewObjectEx = new _IViewObjectEx(this);
   pIRunnableObject = new _IRunnableObject(this);
   pIPersistStreamInit = new _IPersistStreamInit(this);
   pIPersistStorage = new _IPersistStorage(this);
   pIQuickActivate = new _IQuickActivate(this);
   pISpecifyPropertyPages = new _ISpecifyPropertyPages(this);

   pIPropertyPage[0] = new _IPropertyPage(this,CLSID_PDFiumControlPropertyPage);

   return;
   }


   PDFiumControl::_IOleObject::~_IOleObject() {

   delete pIOleControl;
   delete pIDataObject;
   delete pIOleInPlaceObject;
   delete pIOleInPlaceActiveObject;
   delete pIProvideClassInfo2;
   delete pIViewObjectEx;
   delete pIRunnableObject;
   delete pIPersistStreamInit;
   delete pIPersistStorage;
   delete pIQuickActivate;
   delete pISpecifyPropertyPages;

   delete pIPropertyPage[0];

   return;
   }
