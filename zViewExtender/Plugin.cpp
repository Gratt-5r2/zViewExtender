
// This file added in headers queue
// File: "Sources.h"

namespace NAMESPACE {

  // TO DO
  // Your code ...

  void Game_Entry() {
  }

  void Game_Init() {
    RECT rect;
    GetWindowRect( hWndApp, &rect );
    ClipCursor( &rect );
  }

  void Game_Exit() {
  }

  void Game_PreLoop() {
    zCViewCursor::GetCursor()->FrameBegin();
  }

  void Game_Loop() {
    InventoryTest();
    /*auto& inv = player->inventory2;
    screen->Print( 1000, 1000, "selectedItem: " + A inv.selectedItem );
    screen->Print( 1000, 1100, "offset: " + A inv.offset );
    screen->Print( 1000, 1200, "drawItemMax: " + A inv.drawItemMax );
    screen->Print( 1000, 1300, "itemListMode: " + A inv.itemListMode );
    screen->Print( 1000, 1400, "frame: " + A inv.frame );
    screen->Print( 1000, 1500, "right: " + A inv.right );
    screen->Print( 1000, 1600, "ownList: " + A inv.ownList );
    screen->Print( 1000, 1700, "prepared: " + A inv.prepared );
    screen->Print( 1000, 1800, "passive: " + A inv.passive );
    screen->Print( 1000, 1900, "m_bManipulateItemsDisabled: " + A inv.m_bManipulateItemsDisabled );
    screen->Print( 1000, 2000, "m_bCanTransferMoreThanOneItem: " + A inv.m_bCanTransferMoreThanOneItem );
    screen->Print( 1000, 2100, "packAbility: " + A inv.packAbility );
    screen->Print( 1000, 2200, "invnr: " + A inv.invnr );*/


  }

  void Game_PostLoop() {
    zCViewCursor::GetCursor()->FrameEnd();
    zCViewCursor::GetCursor()->Render();
  }




  zCViewInteractive* button3;

  bool RedClick( zCViewInteractive* button, zCViewCursor* cursor, zEMouseButton mouse ) {
    button3->InsertBack( "RED" );
    return true;
  }

  bool GreenClick( zCViewInteractive* button, zCViewCursor* cursor, zEMouseButton mouse ) {
    button3->InsertBack( "GREEN" );
    return true;
  }

  bool BlueClick( zCViewInteractive* button, zCViewCursor* cursor, zEMouseButton mouse ) {
    button3->InsertBack( "BLUE" );
    return true;
  }

  bool BlueDrag( zCViewInteractive* button, zCViewCursor* cursor ) {
    button3->InsertBack( "BLUE" );
    return true;
  }

  bool ShapedIn( zCViewInteractive* button, zCViewCursor* cursor ) {
    button3->InsertBack( "YELLOW" );
    return true;
  }

  bool ShapedOut( zCViewInteractive* button, zCViewCursor* cursor ) {
    button3->InsertBack( "BLUE" );
    return true;
  }



  void Game_MenuLoop() {

    if( !player ) {
      screen->RemoveItem( zCViewCursor::GetCursor() );
      zCViewCursor::GetCursor()->FrameBegin();
      zCViewCursor::GetCursor()->FrameEnd();

      screen->InsertItem( zCViewCursor::GetCursor() );
      zCViewCursor::GetCursor()->Render( false );
    }

    return;

    static zCViewShaped* viewShaped;
    static zCViewShaped* viewShaped2;
    static zCView* viewTest;
    if( !viewTest ) {
      int x, y;
      ogame->viewport->vsizey += 5;


      viewTest = new zCView();
      viewTest->SetSize( 8192, 8192 );
      viewTest->InsertBack( "BLACK" );
      screen->InsertItem( viewTest );


      zCViewInteractive* button1 = new zCViewInteractive();
      zCViewInteractive* button2 = new zCViewInteractive();
                         button3 = new zCViewInteractive();
      screen->InsertItem( button1 );
      screen->InsertItem( button2 );
      screen->InsertItem( button3 );

      button1->SetSize( zPixelX( 30 ), zPixelY( 30 ) );
      button2->SetSize( zPixelX( 30 ), zPixelY( 30 ) );
      button3->SetSize( zPixelX( 30 ), zPixelY( 30 ) );
      button1->SetPos( 100, 100 );
      button2->SetPos( 6000, 100 );
      button3->SetPos( 3500, 5500 );

      button1->InsertBack( "RED" );
      button2->InsertBack( "GREEN" );
      button3->InsertBack( "BLUE" );

      button1->InitFunctions( Null, Null, RedClick,   Null,     Null, Null );
      button2->InitFunctions( Null, Null, GreenClick, Null,     Null, Null );
      button3->InitFunctions( Null, Null, BlueClick,  BlueDrag, Null, Null );

      viewShaped  = new zCViewShaped();
      viewShaped2 = new zCViewShaped();

      screen->InsertItem( viewShaped );
      //viewShaped->InsertItem( viewShaped2 );

      viewShaped->InsertBack( "STARTSCREEN" );
      viewShaped2->InsertBack( "LOADSCREEN" );

      viewShaped->alphafunc = zRND_ALPHA_FUNC_BLEND;
      viewShaped->SetTransparency( 150 );
      /*viewShaped->InsertVertex( zVEC2( 0.0f,    0.0f    ), zVEC2( 0.0f, 0.0f ) );
      viewShaped->InsertVertex( zVEC2( 8192.0f, 0.0f    ), zVEC2( 1.0f, 0.0f ) );
      viewShaped->InsertVertex( zVEC2( 4096.0f, 4096.0f ), zVEC2( 0.5f, 1.0f ) );*/

      viewShaped->SetSize( zPixelX( 500 ), zPixelY( 500 ) );
      viewShaped2->SetSize( 2048, 2048 );
      viewShaped->SetPos( 4096 - zPixelX( 250 ), 4096 - zPixelY( 250 ) );
      viewShaped2->SetPos( 4096 - 1024, 4096 - 1024 );
      //viewShaped->InsertVertex( zVEC2( 0.0f, 0.0f ) );
      //viewShaped->InsertVertex( zVEC2( 8192.0f, 0.0f ) );
      //viewShaped->InsertVertex( zVEC2( 4096.0f, 4096.0f ) );

      viewShaped->CreateBoxShape( 0, 8192.0f );
      viewShaped2->CreateBoxShape( 0, 8192.0f );
      //viewShaped->CreateRoundShape( 4096, 4096, 6 );
      //viewShaped->RotateUV( 45 );
      //viewShaped->CreateFlatUV();
      viewShaped->InitFunctions( ShapedIn, ShapedOut, Null, BlueDrag, Null, Null );


      //viewShaped->RotateShape( -45 );
      zVEC2 virtualScale = viewShaped->GetVirtualScale();
      //viewShaped->MoveShape( zVEC2( -100, 0 ) );
      //viewShaped->ScaleShape( zVEC2( 1.5f, 1.5f ), 0.0f, 45 );
    }

    /*position[VX] = 4096;
    position[VY] = 4096;*/


    /*if( zMouseKeyPressed( Mid ) )
      viewShaped->RotateUV( ztimer->frameTimeFloat * 0.7f, pivot );
    else
      viewShaped->MoveUV( zVEC2( 10, 0 ) + ztimer->frameTimeFloat );*/


    // Получить координаты курсора и спроецировать их
    // в локальные координаты объекта zCViewShaped
    int px, py;
    zCViewCursor::GetCursor()->GetCursorPosition( px, py );
    zVEC2 pivot = viewShaped->PixelToVirtual( zVEC2( zVirtualX( px ), zVirtualY( py ) ) );

    // Поворачивать объект на 0.5 и
    // противодействовать UV на -0.5
    


    if( zKeyPressed( KEY_NUMPAD1 ) )
      viewShaped->MoveUV( zVEC2( 100.0f, 0.0f ) * ztimer->frameTimeFloat );

    if( zKeyPressed( KEY_NUMPAD2 ) ) {
      viewShaped->RotateShape( ztimer->frameTimeFloat * 0.5f, pivot );
      viewShaped->RotateUV( ztimer->frameTimeFloat * -0.5f, pivot );
    }
    
    if( zKeyPressed( KEY_NUMPAD3 ) )
      viewShaped->ScaleUV( zVEC2( 1.000f, 1.001f ), pivot, 45 );




    if( zKeyPressed( KEY_NUMPAD4 ) )
      viewShaped->MoveShape( zVEC2( 100.0f, 0.0f ) * ztimer->frameTimeFloat );

    if( zKeyPressed( KEY_NUMPAD5 ) ) {
      viewShaped->RotateShape( ztimer->frameTimeFloat * 0.5f, pivot );
      viewShaped->RotateUV( ztimer->frameTimeFloat * -0.5f, pivot );
    }

    if( zKeyPressed( KEY_NUMPAD6 ) )
      viewShaped->ScaleShape( zVEC2( 1.000f, 1.001f ), pivot, 45 );


    //viewShaped->Line( px - 100, py - 100, px + 100, py + 100, GFX_RED );
    //viewShaped->Line( px - 100, py + 100, px + 100, py - 100, GFX_RED );
    //cmd << position[VX] << "   " << position[VY] << endl;
  }

  void Game_SaveBegin() {
  }

  void Game_SaveEnd() {
  }

  void LoadBegin() {
  }

  void LoadEnd() {
  }

  void Game_LoadBegin_NewGame() {
    LoadBegin();
  }

  void Game_LoadEnd_NewGame() {
    LoadEnd();
  }

  void Game_LoadBegin_SaveGame() {
    LoadBegin();
  }

  void Game_LoadEnd_SaveGame() {
    LoadEnd();
  }

  void Game_LoadBegin_ChangeLevel() {
    LoadBegin();
  }

  void Game_LoadEnd_ChangeLevel() {
    LoadEnd();
  }

  void Game_LoadBegin_Trigger() {
  }
  
  void Game_LoadEnd_Trigger() {
  }

  void Game_Pause() {
  }

  void Game_Unpause() {
  }

  void Game_DefineExternals() {
  }

  // A multiplatform application reference.
  // please disable unused functions.
  // write 'false' in 'Enabled' macro.
#define AppDefault True
  CApplication* lpApplication = !CHECK_THIS_ENGINE ? Null : CApplication::CreateRefApplication(
    Enabled( AppDefault ) Game_Entry,
    Enabled( AppDefault ) Game_Init,
    Enabled( AppDefault ) Game_Exit,
    Enabled( AppDefault ) Game_PreLoop,
    Enabled( AppDefault ) Game_Loop,
    Enabled( AppDefault ) Game_PostLoop,
    Enabled( AppDefault ) Game_MenuLoop,
    Enabled( AppDefault ) Game_SaveBegin,
    Enabled( AppDefault ) Game_SaveEnd,
    Enabled( AppDefault ) Game_LoadBegin_NewGame,
    Enabled( AppDefault ) Game_LoadEnd_NewGame,
    Enabled( AppDefault ) Game_LoadBegin_SaveGame,
    Enabled( AppDefault ) Game_LoadEnd_SaveGame,
    Enabled( AppDefault ) Game_LoadBegin_ChangeLevel,
    Enabled( AppDefault ) Game_LoadEnd_ChangeLevel,
    Enabled( AppDefault ) Game_LoadBegin_Trigger,
    Enabled( AppDefault ) Game_LoadEnd_Trigger,
    Enabled( AppDefault ) Game_Pause,
    Enabled( AppDefault ) Game_Unpause,
    Enabled( AppDefault ) Game_DefineExternals
  );
}