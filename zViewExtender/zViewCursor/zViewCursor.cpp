
namespace NAMESPACE {

  CLogger& GetLog() {
    static CLogger* logger = new CLogger( "Cursor.log" );
    return *logger;
  }



  zCViewCursorVisual::zCViewCursorVisual() : zCViewAnimated( 0, 0, 8192, 8192 ) {
    ActivePointX = 0;
    ActivePointY = 0;
  }



  void zCViewCursorVisual::SetActivePoint( const int& x, const int& y ) {
    ActivePointX = x;
    ActivePointY = y;
  }



  void zCViewCursorVisual::GetActivePoint( int& x, int& y ) {
    x = ActivePointX;
    y = ActivePointY;
  }












  static int s_nInterfaceScaleMultiplier = 1;
  


  void zCViewCursor::OnEnter() {
    zCViewInteractive* topInter = TopSelectedViewInteractive;
    if( topInter && topInter->EventEnter )
      topInter->EventEnter( topInter, this );
  }
    


  void zCViewCursor::OnLeave() {
    zCViewInteractive* topInter = TopSelectedViewInteractive;
    if( topInter && topInter->EventLeave )
      topInter->EventLeave( topInter, this );
  }



  void zCViewCursor::OnDown( zEMouseButton button ) {
    zCViewInteractive* topInter = TopSelectedViewInteractive;
    if( topInter && topInter->EventDown )
      topInter->EventDown( topInter, this, button );
  }



  void zCViewCursor::OnDrag( int oldx, int oldy ) {
    if( !IsLeftPressed() && !IsMiddlePressed() && !IsRightPressed() )
      return;

    zCViewInteractive* topInter = TopSelectedViewInteractive;
    if( topInter && topInter->EventDrag ) {

      // move before calling for test
      int movx = zAnx( topInter->owner, zNax( screen, PosX - oldx ) );
      int movy = zAny( topInter->owner, zNay( screen, PosY - oldy ) );
      topInter->Move( movx, movy );

      // restore position after cancel
      if( !topInter->EventDrag( topInter, this ) )
        topInter->Move( -movx, -movy );
    }
  }



  void zCViewCursor::OnUp( zEMouseButton button ) {
    zCViewInteractive* topInter = TopSelectedViewInteractive;
    if( topInter && topInter->EventUp )
      topInter->EventUp( topInter, this, button );
  }



  zCViewCursor::zCViewCursor() : zCView() {
    TopSelectedView = Null;
    TopSelectedViewInteractive = Null;
    VisualIndex = 0;
    References = 0;
    TopHandleView = Null;
  }



  zCViewCursor::~zCViewCursor() { }



  zCView* zCViewCursor::GetTopSelectedView() {
    return TopSelectedView;
  }



  Array<zCView*>& zCViewCursor::GetTopSelectedCollection() {
    return arrSelectedCollection;
  }


  
  void zCViewCursor::UpdateKeyStates() {
    if( LeftPressed && !LeftToggled ) {
      LeftToggled = True;
      OnDown( zBUTTON_LEFT );
    }

    if( MiddlePressed && !MiddleToggled ) {
      MiddleToggled = True;
      OnDown( zBUTTON_MIDDLE );
    }

    if( RightPressed && !RightToggled ) {
      RightToggled = True;
      OnDown( zBUTTON_RIGHT );
    }

    if( !LeftPressed && LeftToggled ) {
      LeftToggled = False;
      OnUp( zBUTTON_LEFT );
    }

    if( !MiddlePressed && MiddleToggled ) {
      MiddleToggled = False;
      OnUp( zBUTTON_MIDDLE );
    }

    if( !RightPressed && RightToggled ) {
      RightToggled = False;
      OnUp( zBUTTON_RIGHT );
    }
  }
  


  void zCViewCursor::UpdateInput() {
    LeftPressed   = zinput->GetMouseButtonPressedLeft();
    MiddlePressed = zinput->GetMouseButtonPressedMid();
    RightPressed  = zinput->GetMouseButtonPressedRight();
    UpdateKeyStates();
  }



  void zCViewCursor::ClearInput() {
    LeftPressed   = False;
    MiddlePressed = False;
    RightPressed  = False;
    UpdateKeyStates();
  }


  
  void zCViewCursor::ClearSelection() {
    if( TopSelectedViewInteractive ) {
      OnLeave();
      TopSelectedViewInteractive = Null;
    }
    arrSelectedCollection.Clear();
  }



  void zCViewCursor::Collect( zCView* view ) {
    int x, y;
    GetActivePointPosition( x, y );
    if( view->IsOnBounds( x, y ) ) {
      arrSelectedCollection += view;
      TopSelectedView = view;
    }
  }



  void zCViewCursor::GetActivePoint( int& px, int& py ) {
    zCViewCursorVisual* visual = GetActiveVisual();
    px = visual->ActivePointX;
    py = visual->ActivePointY;
  }



  void zCViewCursor::GetActivePointPosition( int& px, int& py ) {
    zCViewCursorVisual* visual = GetActiveVisual();
    zVEC2 viewScale            = GetVirtualScale();

    px = PosX - (int)((float)(visual->ActivePointX) * viewScale[VX]);
    py = PosY - (int)((float)(visual->ActivePointY) * viewScale[VY]);
  }



  void zCViewCursor::GetCursorPosition( int& px, int& py ) {
    px = PosX;
    py = PosY;
  }

  void zCViewCursor::FrameBegin() {
    if( References == 0 )
      return;

    UpdateInput();

    RECT clipCursor;
    GetClipCursor( &clipCursor );
    float sx = float(clipCursor.right  - clipCursor.left);
    float sy = float(clipCursor.bottom - clipCursor.top);

    POINT realCursorPos;
    GetCursorPos( &realCursorPos );

    int nOldPosX = PosX;
    int nOldPosY = PosY;
    
    PosX = int( 8192.0f / sx * float( realCursorPos.x - clipCursor.left ) );
    PosY = int( 8192.0f / sy * float( realCursorPos.y - clipCursor.top  ) );

    if( PosX != nOldPosX || PosY != nOldPosY )
      OnDrag( nOldPosX, nOldPosY );

    // ...
  }



  void zCViewCursor::FrameEnd() {
    if( References == 0 )
      return;

    if( IsLeftPressed() || IsMiddlePressed() || IsRightPressed() )
      return;
       
    // 
    zCView* oldTopView = TopSelectedView;
    
    // Clear selected views
    arrSelectedCollection.Clear();
    TopSelectedView = Null;

    TopSelectedView = GetTopHandleView()->GetTopView(
      screen->nax( PosX ),
      screen->nay( PosY )
      );

    if( TopSelectedView == screen )
      TopSelectedView = Null;

    bool_t isNewTop = oldTopView != TopSelectedView;

    if( isNewTop ) {
      if( TopSelectedViewInteractive ) {
        OnLeave();
      }
    }

    TopSelectedViewInteractive = dynamic_cast<zCViewInteractive*>( TopSelectedView );
    if( isNewTop )
      if( TopSelectedViewInteractive )
        OnEnter();
  }



  void zCViewCursor::Render( bool blit ) {
    if( References == 0 ) {
      screen->RemoveItem( this );
      return;
    }

    if( blit )
      ogame->viewport->InsertItem( this );

    this->RemoveItem( GetActiveVisual() );
    this->InsertItem( GetActiveVisual() );

    SetSize(
      zPixelX( 36 * s_nInterfaceScaleMultiplier ),
      zPixelY( 36 * s_nInterfaceScaleMultiplier )
      );

    int ox, oy;
    GetActivePointPosition( ox, oy );
    SetPos( ox, oy );

    if( blit ) {
      GetActiveVisual()->Blit();
      ogame->viewport->RemoveItem( this );
      RemoveItem( GetActiveVisual() );
    }
  }



  void zCViewCursor::Show() {
    References++;
  }



  void zCViewCursor::ShowAt( int x, int y ) {
    if( References == 0 )
      SetCursorPos( x, y );

    Show();
  }



  void zCViewCursor::ShowAtCenter() {
    ShowAt( VID_MAX_XDIM / 2, VID_MAX_YDIM / 2 );
  }
  
  void zCViewCursor::Hide() {
    References--;
    if( References == Invalid )
      References = 0;

    if( References == 0 ) {
      ClearInput();
      ClearSelection();
    }
  }
  


  zCViewCursorVisual* zCViewCursor::GetActiveVisual() {
    if( VisualIndex >= arrBodies.GetNum() )
      return GetDefaultVisual();

    return arrBodies[VisualIndex];
  }
  


  zCViewCursorVisual* zCViewCursor::GetDefaultVisual() {
    static zCViewCursorVisual* s_visual = Null;
    if( !s_visual ) {
      s_visual = new zCViewCursorVisual();
      s_visual->InsertBack( "UNIONDEFAULTCURSOR" );
      s_visual->SetActivePoint( 650, 650 );
    }

    return s_visual;
  }



  bool_t zCViewCursor::IsLeftPressed() {
    return LeftPressed;
  }



  bool_t zCViewCursor::IsLeftToggled() {
    return LeftPressed && !LeftToggled;
  }



  bool_t zCViewCursor::IsMiddlePressed() {
    return MiddlePressed;
  }



  bool_t zCViewCursor::IsMiddleToggled() {
    return MiddlePressed && !MiddleToggled;
  }



  bool_t zCViewCursor::IsRightPressed() {
    return RightPressed;
  }



  bool_t zCViewCursor::IsRightToggled() {
    return RightPressed && !RightToggled;
  }



  inline zCViewCursor* CreateCursor() {
    zCViewCursor* cursor = new zCViewCursor();

    bool s_bInterfaceScaleEnabled;
    Union.GetSysPackOption().Read( s_bInterfaceScaleEnabled, "INTERFACE", "Scale", false );
    if( s_bInterfaceScaleEnabled )
      s_nInterfaceScaleMultiplier = 2;

    return cursor;
  }



  zCViewCursor* zCViewCursor::GetCursor() {
    static zCViewCursor* cursor = CreateCursor();
    return cursor;
  }



  void zCViewCursor::SetTopHandleView( zCView*& view ) {
    TopHandleView = &view;
  }



  zCView*& zCViewCursor::GetTopHandleView() {
    if( TopHandleView == Null )
      return screen;

    return *TopHandleView;
  }



  void zCViewCursor::ClearTopHandleView() {
    TopHandleView = Null;
  }
}