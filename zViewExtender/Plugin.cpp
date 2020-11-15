
// This file added in headers queue
// File: "Sources.h"

namespace NAMESPACE {

  // TO DO
  // Your code ...

  void Game_Entry() {
    PATCH_EXECUTE(
      "MemSet(0x0064F1C7, '90', 0x0064F1F0 - 0x0064F1C7)"
    );


    bool enableInMenu = true;
    Union.GetSysPackOption().Read( enableInMenu, "zViewExtender", "UseCursorInMenu", enableInMenu );
    if( !enableInMenu ) {
      Ivk_Menu_Render.Detach();
      Ivk_Menu_HandleEvent.Detach();
      Ivk_Menu_Enter.Detach();
      Ivk_Menu_Leave.Detach();
    }


    bool enableInDialogs = true;
    Union.GetSysPackOption().Read( enableInDialogs, "zViewExtender", "UseCursorInDialogs", enableInDialogs );
    if( !enableInDialogs ) {
      Ivk_zCViewDialogChoice_BlitText.Detach();
      Ivk_zCViewDialog_StartSelection.Detach();
      Ivk_zCViewDialog_StopSelection.Detach();
      Ivk_zCViewDialogChoice_HandleEvent.Detach();
    }


    bool enableInInventory = true;
    Union.GetSysPackOption().Read( enableInInventory, "zViewExtender", "UseCursorInInventory", enableInInventory );
    if( !enableInInventory ) {
      Ivk_oCItemContainer_HandleEvent.Detach();
      Ivk_oCStealContainer_HandleEvent.Detach();
      Ivk_oCNpcContainer_HandleEvent.Detach();
      Ivk_oCNpcInventory_HandleEvent.Detach();
      Ivk_oCNpcInventory_OpenPassive.Detach();
      Ivk_oCNpcInventory_Close.Detach();
      Ivk_oCItemContainer_Draw.Detach();
      Ivk_oCItem_RenderItem.Detach();
    }
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
  }

  void Game_PostLoop() {
    zCViewCursor::GetCursor()->FrameEnd();
    zCViewCursor::GetCursor()->Render();
  }

  void Game_MenuLoop() {
#if 0
    // Test program
    InitTest();
#endif
    if( !player ) {
      screen->RemoveItem( zCViewCursor::GetCursor() );
      zCViewCursor::GetCursor()->FrameBegin();
      zCViewCursor::GetCursor()->FrameEnd();

      screen->InsertItem( zCViewCursor::GetCursor() );
      zCViewCursor::GetCursor()->Render( false );
    }
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