
namespace NAMESPACE {
  enum zEMouseButton {
    zBUTTON_LEFT,
    zBUTTON_MIDDLE,
    zBUTTON_RIGHT
  };
  
  class zCViewInteractive;

  class zCViewCursorVisual : public zCViewAnimated {
    friend class zCViewCursor;
  protected:
    int ActivePointX;
    int ActivePointY;
  public:

    zCViewCursorVisual();
    void SetActivePoint( const int& x, const int& y );
    void GetActivePoint( int& x, int& y );
  };

  class zCViewCursor : public zCView {
    Array<zCViewCursorVisual*> arrBodies;
    Array<zCView*> arrSelectedCollection;
    zCView* TopSelectedView;
    zCViewInteractive* TopSelectedViewInteractive;
    uint VisualIndex;
    int PosX;
    int PosY;
    uint References;
    bool_t LeftPressed,   LeftToggled;
    bool_t MiddlePressed, MiddleToggled;
    bool_t RightPressed,  RightToggled;
    zCView** TopHandleView;

    void OnEnter();
    void OnLeave();
    void OnDown( zEMouseButton button );
    void OnDrag( int oldx, int oldy );
    void OnUp( zEMouseButton button );
  public:

    zCViewCursor();
    virtual ~zCViewCursor();

    void UpdateKeyStates();
    void UpdateInput();
    void ClearInput();
    void ClearSelection();
    void Collect( zCView* view );
    void GetActivePoint( int& px, int& py );
    void GetActivePointPosition( int& px, int& py );
    void GetCursorPosition( int& px, int& py );
    void FrameBegin();
    void FrameEnd();
    void Render();
    void Show();
    void ShowAt( int x, int y );
    void ShowAtCenter();
    void Hide();
    zCViewCursorVisual* GetActiveVisual();
    zCViewCursorVisual* GetDefaultVisual();

    //
    void     SetTopHandleView( zCView*& view );
    zCView*& GetTopHandleView();
    void     ClearTopHandleView();


    zCView* GetTopSelectedView();
    Array<zCView*>& GetTopSelectedCollection();

    // left mouse button
    bool_t IsLeftPressed();
    bool_t IsLeftToggled();

    // middle mouse button
    bool_t IsMiddlePressed();
    bool_t IsMiddleToggled();

    // right mouse button
    bool_t IsRightPressed();
    bool_t IsRightToggled();

    static zCViewCursor* GetCursor();
  };
}