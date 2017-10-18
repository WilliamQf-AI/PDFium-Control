// Copyright 2017 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PDFiumControl.h"

   std::list<WCHAR *> PDFiumControl::PDFiumDocument::imageFiles;

   PDFiumControl::PDFiumDocument::PDFiumDocument(PDFiumControl *pp,FPDF_DOCUMENT pDoc) : 
      refCount(1), pParent(pp), pDocumentObject(pDoc), pagePDFDimensions(), pagePDFLocations(), pagePixelDimensions(), pagePixelLocations()
   {

   return;
   };


   PDFiumControl::PDFiumDocument::~PDFiumDocument() {

   if ( pDocumentObject ) 
      FPDF_CloseDocument(pDocumentObject);

   for ( WCHAR *pFileName : imageFiles ) {
      DeleteFile(pFileName);
      delete [] pFileName;
   }

   imageFiles.clear();

   for ( std::pair<int,POINTL *> p : pagePDFDimensions )
      delete p.second;

   pagePDFDimensions.clear();

   for ( std::pair<int,POINTL *> p : pagePDFLocations )
      delete p.second;

   pagePDFLocations.clear();

   for ( std::pair<int,POINTL *> p : pagePixelDimensions )
      delete p.second;

   pagePixelDimensions.clear();

   for ( std::pair<int,POINTL *> p : pagePixelLocations )
      delete p.second;

   pagePixelLocations.clear();

   return;
   }