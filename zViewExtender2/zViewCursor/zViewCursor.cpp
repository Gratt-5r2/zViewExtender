
namespace NAMESPACE {



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
    References = 0;
    TopHandleView = Null;
    DefaultVisualIndex = 0;
    VisualIndex = 0;
  }



  zCViewCursor::~zCViewCursor() { }



  zCView* zCViewCursor::GetTopSelectedView() {
    return TopSelectedView;
  }



  Array<zCView*>& zCViewCursor::GetTopSelectedCollection() {
    return SelectedCollection;
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
    SelectedCollection.Clear();
  }



  void zCViewCursor::Collect( zCView* view ) {
    int x, y;
    GetActivePointPosition( x, y );
    if( view->IsOnBounds( x, y ) ) {
      SelectedCollection += view;
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
    
    // Pre-render cleaning
    SelectedCollection.Clear();
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



  void zCViewCursor::UpdateVisual() {
    if( TopSelectedViewInteractive && TopSelectedViewInteractive->CursorVisualIndex != Invalid ) {
      if( VisualIndex != TopSelectedViewInteractive->CursorVisualIndex )
        VisualIndex = TopSelectedViewInteractive->CursorVisualIndex;
    }
    else if( VisualIndex != DefaultVisualIndex )
      VisualIndex = DefaultVisualIndex;
  }



  void zCViewCursor::UpdateRect() {
    if( GetForegroundWindow() == hWndApp ) {
      RECT rect;
      GetWindowRect( hWndApp, &rect );
      ClipCursor( &rect );
    }
  }



  void zCViewCursor::Render( bool blit ) {
    if( References == 0 ) {
      screen->RemoveItem( this );
      return;
    }

    // Update cursor image and
    // cursor movement range
    UpdateVisual();
    UpdateRect();

    // Call loop function when the cursor is over an view interactive
    //if( TopSelectedViewInteractive && TopSelectedViewInteractive->EventLoop )
    //  TopSelectedViewInteractive->EventLoop( TopSelectedViewInteractive, this );

    // Place cursor in
    // viewport before blit
    if( blit )
      ogame->viewport->InsertItem( this );

    // Remove old cursor picture and
    // place new cursor picture
    static zCViewCursorVisual* lastVisual = Null;
    if( lastVisual )
      RemoveItem( lastVisual );

    lastVisual = GetActiveVisual();
    InsertItem( lastVisual );

    // Update cursor size and
    // cursor picture position
    SetSize(
      zPixelX( 36 * s_nInterfaceScaleMultiplier ),
      zPixelY( 36 * s_nInterfaceScaleMultiplier )
      );

    int ox, oy;
    GetActivePointPosition( ox, oy );
    SetPos( ox, oy );

    // Blit picture
    if( blit ) {
      lastVisual->Blit();
      ogame->viewport->RemoveItem( this );
      RemoveItem( lastVisual );
    }

    // Post-render cleaning
    SelectedCollection.Clear();
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



  uint zCViewCursor::CreateVisual( const zSTRING& texName, const zVEC2& activePoint, const int& aniFps ) {
    GetDefaultVisual();

    zCViewCursorVisual* visual = new zCViewCursorVisual();
    visual->InsertBack( texName );
    visual->SetActivePoint( activePoint[VX], activePoint[VY] );

    if( aniFps ) {
      visual->SetAnimationEnabled( True );
      visual->SetFps( aniFps );
    }

    uint index = Visuals.GetNum();
    Visuals += visual;
    return index;
  }
  


  zCViewCursorVisual* zCViewCursor::GetActiveVisual() {
    if( VisualIndex >= Visuals.GetNum() )
      return GetDefaultVisual();

    return Visuals[VisualIndex];
  }
  


  zCViewCursorVisual* zCViewCursor::GetDefaultVisual() {
    static zCViewCursorVisual* s_visual = Null;
    if( !s_visual ) {
      s_visual = new zCViewCursorVisual();
      s_visual->InsertBack( "UnionCursorDefault" );
      s_visual->SetActivePoint( 100, 100 );
      Visuals += s_visual;
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