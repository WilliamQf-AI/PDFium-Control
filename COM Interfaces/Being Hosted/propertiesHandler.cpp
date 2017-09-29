
#include "PDFiumControl.h"



   LRESULT CALLBACK PDFiumControl::_IOleObject::propertiesHandler(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {

   PDFiumControl::_IOleObject *p = (PDFiumControl::_IOleObject *)GetWindowLongPtr(hwnd,GWLP_USERDATA);

   switch ( msg ) {

   case WM_INITDIALOG: {

      p = reinterpret_cast<PDFiumControl::_IOleObject *>(lParam);

      SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)p);

      }
      break;

   default:
      break;

   }

   return (LRESULT)0;
   }

