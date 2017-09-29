

      class _IOleInPlaceSite;
      class _IOleInPlaceFrame;
      class _IOleDocumentSite;

      // IOleClientSite

      class _IOleClientSite : public IOleClientSite {

      public:

         _IOleClientSite(PDFiumControl *p,_IOleInPlaceSite *pis,_IOleInPlaceFrame *pif) : pParent(p), pIOleInPlaceSite(pis),pIOleInPlaceFrame(pif), refCount(0) {};
         ~_IOleClientSite() {};

         //   IUnknown

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         long _stdcall SaveObject();
         long _stdcall GetMoniker(DWORD,DWORD,IMoniker**);
         long _stdcall GetContainer(IOleContainer**);
         long _stdcall ShowObject();
         long _stdcall OnShowWindow(BOOL);
         long _stdcall RequestNewObjectLayout();

         PDFiumControl *pParent;

         _IOleInPlaceSite *pIOleInPlaceSite;
         _IOleInPlaceFrame *pIOleInPlaceFrame;

         long refCount;

      } * pIOleClientSite_HTML_Host;

      // IOleDocumentSite

      class _IOleDocumentSite : public IOleDocumentSite {

      public:

         _IOleDocumentSite(PDFiumControl *p,_IOleClientSite *pics) : 
                           pParent(p), pIOleClientSite(pics), pIOleDocumentView(NULL), refCount(0) {};
         ~_IOleDocumentSite() { if ( pIOleDocumentView ) pIOleDocumentView -> Release(); };

         //   IUnknown

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         long _stdcall ActivateMe(IOleDocumentView *);

         PDFiumControl *pParent;
         _IOleClientSite *pIOleClientSite;
         IOleDocumentView *pIOleDocumentView;

         long refCount;

      } * pIOleDocumentSite_HTML_Host;


      // IOleInPlaceSiteEx

      class _IOleInPlaceSite : public IOleInPlaceSiteEx {

      public:

         _IOleInPlaceSite(PDFiumControl* pp,_IOleInPlaceFrame *ipf) :
                     pParent(pp), pIOleInPlaceFrame(ipf), refCount(0) {};


         _IOleInPlaceFrame *GetIOleInPlaceFrame() { return pIOleInPlaceFrame; };

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);

      private:

         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         STDMETHOD(GetWindow)(HWND*);
         STDMETHOD(ContextSensitiveHelp)(BOOL);
         STDMETHOD(CanInPlaceActivate)();
         STDMETHOD(OnInPlaceActivate)();
         STDMETHOD(OnUIActivate)();
         STDMETHOD(GetWindowContext)(IOleInPlaceFrame **,IOleInPlaceUIWindow**,RECT* position,RECT* clip,OLEINPLACEFRAMEINFO*);
         STDMETHOD(Scroll)(SIZE);
         STDMETHOD(OnUIDeactivate)(BOOL);
         STDMETHOD(OnInPlaceDeactivate)();
         STDMETHOD(DiscardUndoState)();
         STDMETHOD(DeactivateAndUndo)();
         STDMETHOD(OnPosRectChange)(const RECT*);
         STDMETHOD(OnInPlaceActivateEx)(BOOL *,DWORD);
         STDMETHOD(OnInPlaceDeactivateEx)(BOOL);
         STDMETHOD(RequestUIActivate)();

      protected:

         PDFiumControl *pParent;
         _IOleInPlaceFrame *pIOleInPlaceFrame;

         long refCount;

      } * pIOleInPlaceSite_HTML_Host;

      // IOleInPlaceFrame

      class _IOleInPlaceFrame : public IOleInPlaceFrame {

      public:

         _IOleInPlaceFrame(PDFiumControl *pp,HWND hostWindow) : pParent(pp), hwndHost(hostWindow), refCount(0) {};

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);

         HWND HWNDHost() { return hwndHost; };

      private:

         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         STDMETHOD(GetWindow)(HWND *);
         STDMETHOD(ContextSensitiveHelp)(BOOL);
         STDMETHOD(GetBorder)(RECT *);
         STDMETHOD(RequestBorderSpace)(LPCBORDERWIDTHS);
         STDMETHOD(SetBorderSpace)(LPCBORDERWIDTHS);
         STDMETHOD(SetActiveObject)(IOleInPlaceActiveObject *,LPCOLESTR);
         STDMETHOD(InsertMenus)(HMENU,OLEMENUGROUPWIDTHS *);
         STDMETHOD(SetMenu)(HMENU,HOLEMENU,HWND);
         STDMETHOD(RemoveMenus)(HMENU);
         STDMETHOD(SetStatusText)(LPCOLESTR);
         STDMETHOD(EnableModeless)(BOOL);
         STDMETHOD(TranslateAccelerator)(MSG *,WORD);

      protected:

         PDFiumControl *pParent;
         HWND hwndHost;

         long refCount;

      } * pIOleInPlaceFrame_HTML_Host;