
#pragma once

   // IOleObject 

   class _IOleObject : public IOleObject {

   public:

      _IOleObject(PDFiumControl *pp);
      ~_IOleObject();

      STDMETHOD(QueryInterface)(REFIID riid,void **ppv);
      STDMETHOD_ (ULONG, AddRef)();
      STDMETHOD_ (ULONG, Release)();

      IPropertyPage *PropertyPage(long index) { return static_cast<IPropertyPage *>(pIPropertyPage[index]); };

   private:

      STDMETHOD(SetClientSite)(IOleClientSite *pClientSite);
      STDMETHOD(GetClientSite)(IOleClientSite **ppCLientSite);
      STDMETHOD(SetHostNames)(LPCOLESTR szContainerApp,LPCOLESTR szContainerObj);
      STDMETHOD(Close)(DWORD dwSaveOption);
      STDMETHOD(SetMoniker)(DWORD dwWhichMoniker, IMoniker *pmk);
      STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker,IMoniker **ppmk);
      STDMETHOD(InitFromData)(IDataObject *pDataObject,BOOL fCreation,DWORD dwReserved);
      STDMETHOD(GetClipboardData)(DWORD dwReserved,IDataObject **ppDataObject);
      STDMETHOD(DoVerb)(LONG iVerb,LPMSG lpmsg,IOleClientSite *pActiveSite,LONG lindex,HWND hwndParent,LPCRECT lprcPosRect);
      STDMETHOD(EnumVerbs)(IEnumOLEVERB **ppenumOleVerb);
      STDMETHOD(Update)();
      STDMETHOD(IsUpToDate)();
      STDMETHOD(GetUserClassID)(CLSID * pClsid);
      STDMETHOD(GetUserType)(DWORD dwFormOfType, LPOLESTR *pszUserType);
      STDMETHOD(SetExtent)(DWORD dwDrawAspect, LPSIZEL lpsizel);
      STDMETHOD(GetExtent)(DWORD dwDrawAspect, LPSIZEL lpsizel);
     
      STDMETHOD(Advise)(IAdviseSink *pAdvSink, DWORD * pdwConnection);
      STDMETHOD(Unadvise)(DWORD dwConnection);
      STDMETHOD(EnumAdvise)(IEnumSTATDATA **ppenumAdvise);
      STDMETHOD(GetMiscStatus)(DWORD dwAspect, DWORD * pdwStatus);        
     
      STDMETHOD(SetColorScheme)(LPLOGPALETTE lpLogpal);

      PDFiumControl *pParent;

      long refCount;

      // IDataObject

      class _IDataObject : public IDataObject {

      public:

         _IDataObject(_IOleObject *pp) : pParent(pp) {};
         ~_IDataObject() {};

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

      private:

         // IDataObject

         STDMETHOD(GetData)(FORMATETC *,STGMEDIUM *);
         STDMETHOD(GetDataHere)(FORMATETC *,STGMEDIUM *);
         STDMETHOD(QueryGetData)(FORMATETC *);
         STDMETHOD(GetCanonicalFormatEtc)(FORMATETC *,FORMATETC *);
         STDMETHOD(SetData)(FORMATETC *,STGMEDIUM *,BOOL);
         STDMETHOD(EnumFormatEtc)(DWORD,IEnumFORMATETC **);
         STDMETHOD(DAdvise)(FORMATETC *,DWORD,IAdviseSink *,DWORD *);
         STDMETHOD(DUnadvise)(DWORD);
         STDMETHOD(EnumDAdvise)(IEnumSTATDATA **);

         _IOleObject *pParent;

      } *pIDataObject{NULL};

      // IOleControl

      class _IOleControl : public IOleControl {

      public:

         _IOleControl(_IOleObject *pp) : pParent(pp) {};
         ~_IOleControl() {};

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

      private:
     
         STDMETHOD(GetControlInfo)(CONTROLINFO *);
         STDMETHOD(OnMnemonic)(MSG *);
         STDMETHOD(OnAmbientPropertyChange)(long);
         STDMETHOD(FreezeEvents)(int);

         _IOleObject *pParent;

      } *pIOleControl{NULL};

      // IOleInPlaceObject

      class _IOleInPlaceObject : public IOleInPlaceObject {

      public:

         _IOleInPlaceObject(_IOleObject *pp) : pParent(pp) {};
         ~_IOleInPlaceObject() {};

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         // IOleWindow
   
         STDMETHOD (GetWindow)(HWND *);
         STDMETHOD (ContextSensitiveHelp)(BOOL);

         // IOleInPlaceObject

         STDMETHOD (InPlaceActivate)();
         STDMETHOD (InPlaceDeactivate)();
         STDMETHOD (UIDeactivate)();
         STDMETHOD (SetObjectRects)(LPCRECT,LPCRECT);
         STDMETHOD (ReactivateAndUndo)();

      private:

         _IOleObject *pParent;

      } *pIOleInPlaceObject{NULL};

      // IOleInPlaceActiveObject

      class _IOleInPlaceActiveObject : public IOleInPlaceActiveObject {

      public:

         _IOleInPlaceActiveObject(_IOleObject *pp) : pParent(pp) {};
         ~_IOleInPlaceActiveObject() {};

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

      private:

         // IOleWindow
   
         STDMETHOD (GetWindow)(HWND *);
         STDMETHOD (ContextSensitiveHelp)(BOOL);

         // IOleInPlaceActiveObject

         STDMETHOD(TranslateAccelerator)(LPMSG);
         STDMETHOD(OnFrameWindowActivate)(BOOL);
         STDMETHOD(OnDocWindowActivate)(BOOL);
         STDMETHOD(ResizeBorder)(LPCRECT ,IOleInPlaceUIWindow *,BOOL);
         STDMETHOD(EnableModeless)(BOOL);

      private:

         _IOleObject *pParent;

      } *pIOleInPlaceActiveObject{NULL};


      class _IProvideClassInfo2 : public IProvideClassInfo2 {
      public:

         _IProvideClassInfo2(_IOleObject *pp) : pParent(pp) {};
         ~_IProvideClassInfo2() {};

         STDMETHOD(QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         // IProvideClassInfo

         STDMETHOD(GetClassInfo)(ITypeInfo **);

         // IProvideClassInfo2

         STDMETHOD(GetGUID)(DWORD,GUID *);

      private:

         _IOleObject *pParent;

      } *pIProvideClassInfo2{NULL};

      class _IQuickActivate : public IQuickActivate {
      public:

         _IQuickActivate(_IOleObject *pp) : pParent(pp) {};
         ~_IQuickActivate() {};

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

        //  IQuickActivate

        STDMETHOD(QuickActivate)(QACONTAINER* pQAContainer,QACONTROL* pQAControl);
        STDMETHOD(SetContentExtent)(SIZEL* pSizel);
        STDMETHOD(GetContentExtent)(SIZEL* pSizel);

      private:
   
         _IOleObject* pParent;

      } *pIQuickActivate{NULL};

      class _IViewObjectEx : public IViewObjectEx {
      public:

         _IViewObjectEx(_IOleObject *pp) : pParent(pp) {};
         ~_IViewObjectEx() {};

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         // IViewObject

         STDMETHOD (Draw)(unsigned long,long,void *,DVTARGETDEVICE *,HDC,HDC,const struct _RECTL *,const struct _RECTL *,int (__stdcall *)(ULONG_PTR),ULONG_PTR);
         STDMETHOD (GetColorSet)(DWORD,long,void *,DVTARGETDEVICE *,HDC,LOGPALETTE **);
         STDMETHOD (Freeze)(DWORD,long,void *,DWORD *);
         STDMETHOD (Unfreeze)(DWORD);
         STDMETHOD (SetAdvise)(DWORD,DWORD,IAdviseSink *);
         STDMETHOD (GetAdvise)(DWORD *,DWORD *,IAdviseSink **);

         // IViewObject2

         STDMETHOD (GetExtent)(unsigned long,long,DVTARGETDEVICE *,struct tagSIZE *);

         // IViewObjectEx

         STDMETHOD (GetRect)(DWORD dwAspect,RECTL *);
         STDMETHOD (GetViewStatus)(DWORD *);
         STDMETHOD (QueryHitPoint)(DWORD dwAspect,const struct tagRECT *pRectBounds,POINT ptlHit,long lCloseHint,DWORD *dwHitResult);
         STDMETHOD (QueryHitRect)(DWORD dwAspect,const struct tagRECT *pRectBounds,const struct tagRECT *rctHit,long lCloseHint,DWORD *dwHitResult);
         STDMETHOD (GetNaturalExtent)(DWORD dwExtent,LONG lIndex,DVTARGETDEVICE *ptd,HDC hicTargetDev,DVEXTENTINFO *extentInfo,SIZEL *);

      private:
   
         _IOleObject *pParent;

      } *pIViewObjectEx{NULL};

      class _IRunnableObject : public IRunnableObject {

      public:

         _IRunnableObject(_IOleObject *pp) : pParent(pp) {};
         ~_IRunnableObject() {};

         // IUnknown

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         // IRunnableObject

         STDMETHOD (GetRunningClass)(CLSID *);
         STDMETHOD (Run)(LPBC);
         int __stdcall IsRunning(void);
         STDMETHOD (LockRunning)(BOOL,BOOL);
         STDMETHOD (SetContainedObject)(BOOL);

      private:
   
         _IOleObject *pParent;

      } *pIRunnableObject{NULL};


      class _ISpecifyPropertyPages : public ISpecifyPropertyPages {

      public:

         _ISpecifyPropertyPages(_IOleObject *p) : pParent(p) {};
         ~_ISpecifyPropertyPages() {};

         // IUnknown

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         // ISpecifyPropertyPages

         STDMETHOD(GetPages)(CAUUID *pPages);

      private:

         _IOleObject *pParent;

      } *pISpecifyPropertyPages{NULL};

      class _IPropertyPage : public IPropertyPage {
      public:

         _IPropertyPage(_IOleObject *p,CLSID clsid) : pParent(p),theCLSID(clsid) {};
         ~_IPropertyPage() {};

         // IUnknown

         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();

         // IPropertyPage

      private:

         STDMETHOD(SetPageSite)(IPropertyPageSite *pPageSite);
         STDMETHOD(Activate)(HWND hWndParent, LPCRECT prc, BOOL fModal);
         STDMETHOD(Deactivate)();
         STDMETHOD(GetPageInfo)(PROPPAGEINFO *pPageInfo);
         STDMETHOD(SetObjects)(ULONG cObjects, IUnknown **ppUnk);
         STDMETHOD(Show)(UINT nCmdShow);
         STDMETHOD(Move)(LPCRECT prc);
         STDMETHOD(IsPageDirty)();
         STDMETHOD(Apply)();
         STDMETHOD(Help)(LPCOLESTR pszHelpDir);
         STDMETHOD(TranslateAccelerator)(LPMSG pMsg);

         _IOleObject *pParent;
         CLSID theCLSID;

      } *pIPropertyPage[1] {NULL};

      class _IPersistStreamInit : public IPersistStreamInit {

      public:
 
         _IPersistStreamInit(_IOleObject *pp) : pParent(pp) {};
         ~_IPersistStreamInit() {};
 
         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();
 
         STDMETHOD(GetClassID)(CLSID *);
 
//      IPersistStream
 
         STDMETHOD(GetSizeMax)(ULARGE_INTEGER *);
         STDMETHOD(IsDirty)();
         STDMETHOD(Load)(IStream *);
         STDMETHOD(Save)(IStream *,int);
 
 //      IPersistStreamInit
 
         STDMETHOD(InitNew)();

     private:
 
         _IOleObject *pParent;
 
      } * pIPersistStreamInit{NULL};
 
      class _IPersistStorage : public IPersistStorage {

      public:
 
         _IPersistStorage(_IOleObject *pp) : pParent(pp), noScribble(true) {};
         ~_IPersistStorage() { };
 
         STDMETHOD (QueryInterface)(REFIID riid,void **ppv);
         STDMETHOD_ (ULONG, AddRef)();
         STDMETHOD_ (ULONG, Release)();
 
         STDMETHOD(GetClassID)(CLSID *);
         STDMETHOD(IsDirty)();
         STDMETHOD(InitNew)(IStorage *);
         STDMETHOD(Load)(IStorage *);
         STDMETHOD(Save)(IStorage *,BOOL);
         STDMETHOD(SaveCompleted)(IStorage *);
         STDMETHOD(HandsOffStorage)();
 
      private:
 
         _IOleObject *pParent;

         boolean noScribble;
 
      } *pIPersistStorage{NULL};

   private:

      void initialize();

      //
      // Items necessary for being hosted.
      //
      IOleAdviseHolder *pOleAdviseHolder;
      IDataAdviseHolder *pDataAdviseHolder;

      IAdviseSink *pViewAdviseSink;
      DWORD adviseSink_dwAspect,adviseSink_advf;
      DWORD dwViewAdviseSinkConnection;

      IOleClientSite *pIOleClientSite_MySite;
      IOleInPlaceSite *pIOleInPlaceSite_MySite;

      HWND hwndContainer;

      HWND hwndPropertyPage;

      SIZEL containerSize;

      bool isRunning;

      static LRESULT CALLBACK propertiesHandler(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

   } *pIOleObject{NULL};