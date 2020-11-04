
namespace NAMESPACE {
  HOOK Ivk_Menu_Render      AS( &zCMenu::Render,      &zCMenu::Render_Union );
  HOOK Ivk_Menu_HandleEvent AS( &zCMenu::HandleEvent, &zCMenu::HandleEvent_Union );
  HOOK Ivk_Menu_Enter       AS( &zCMenu::ScreenInit,  &zCMenu::ScreenInit_Union );
  HOOK Ivk_Menu_Leave       AS( &zCMenu::ScreenDone,  &zCMenu::ScreenDone_Union );



  void oCMenuSavegame::UpdateThumbPic_Union() {
    int oldSelSlot = m_selSlot;
    if( m_mainSel >= 0 && m_mainSel < m_listItems.GetNumInList() ) {
      m_selSlotItemIndex = m_mainSel;
      m_selSlot = GetMenuItemSlotNr( m_listItems[m_mainSel] );
    }
    if( oldSelSlot != m_selSlot )
      HandleSlotChange( oldSelSlot );
  }



  void zCMenu::Render_Union() {
    zCViewCursor* cursor = zCViewCursor::GetCursor();

    if( cursor ) {
      static int oldx, oldy, x, y;
      cursor->GetPixelPos( x, y );

      if( oldx != x || oldy != y ) {

        oldx = x;
        oldy = y;
        zCView* frontView = screen->GetTopView( x, y );

        if( frontView ) {
          for( int i = 0; i < m_listItems.GetNum(); i++ ) {
            if( m_listItems[i]->m_pInnerWindow == frontView ) {

              zCMenuItem* activeItem = GetActiveItem();
              if( activeItem != m_listItems[i] ) {
                SetActiveItem( m_listItems[i] );

                if( m_listItems[i] == GetActiveItem() ) {
                  zCSoundFX* sfx = zsound->LoadSoundFX( "MOUSE_SELECT.WAV" );
                  if( sfx ) {
                    zsound->PlaySound( sfx, 1 );
                    sfx->Release();
                  }
                }

                oCMenuSavegame* menuSavegame = dynamic_cast<oCMenuSavegame*>( this );
                if( menuSavegame )
                  menuSavegame->UpdateThumbPic_Union();
              }
            }
          }
        }
      }
    }

    return THISCALL( Ivk_Menu_Render )();
  }



  int zCMenu::HandleEvent_Union( int key ) {
    cmd << key << endl;

    if( m_mainSel != -1 ) {
      zCViewCursor* cursor = zCViewCursor::GetCursor(); 

      if( cursor ) {
        if( key == MOUSE_WHEELDOWN || key == MOUSE_WHEELDOWN_G1 ) {
          zCSoundFX* sfx = zsound->LoadSoundFX( "MOUSE_SCROLL.WAV" );
          if( sfx ) {
            zsound->PlaySound( sfx, 1 );
            sfx->Release();
          }

          return THISCALL( Ivk_Menu_HandleEvent )( KEY_LEFT );
        }
        else if( key == MOUSE_WHEELUP || key == MOUSE_WHEELUP_G1 ) {
          zCSoundFX* sfx = zsound->LoadSoundFX( "MOUSE_SCROLL.WAV" );
          if( sfx ) {
            zsound->PlaySound( sfx, 1 );
            sfx->Release();
          }

          return THISCALL( Ivk_Menu_HandleEvent )( KEY_RIGHT );
        }
      
        if( key == MOUSE_BUTTONLEFT ) {

          zCSoundFX* sfx = zsound->LoadSoundFX( "MOUSE_CLICK.WAV" );
          if( sfx ) {
            zsound->PlaySound( sfx, 1 );
            sfx->Release();
          }

          int x, y;
          cursor->GetPixelPos( x, y );
          zCView* menuItem = screen->GetTopView( x, y );
      
          if( menuItem ) {
            for( int i = 0; i < m_listItems.GetNum(); i++ ) {
            
              if( GetActiveItem()->m_pInnerWindow == menuItem ) {
                SetActiveItem( m_listItems[i] );
                return THISCALL( Ivk_Menu_HandleEvent )( key );
              }
            }
          }
          return True;
        }

        if( key == MOUSE_BUTTONRIGHT ) {
          zCSoundFX* sfx = zsound->LoadSoundFX( "MOUSE_BACK.WAV" );
          if( sfx ) {
            zsound->PlaySound( sfx, 1 );
            sfx->Release();
          }
        }
      }
    }
    return THISCALL( Ivk_Menu_HandleEvent )( key );
  }



  static bool_t s_lastMenuIsMain = True;

  void zCMenu::ScreenInit_Union() {
    bool_t thisMenuIsMain = name == "MENU_MAIN";

    if( thisMenuIsMain && s_lastMenuIsMain )
      zCViewCursor::GetCursor()->ShowAtCenter();
    else
      zCViewCursor::GetCursor()->Show();

    THISCALL( Ivk_Menu_Enter )();
  }



  void zCMenu::ScreenDone_Union() {
    THISCALL( Ivk_Menu_Leave )();
    zCViewCursor::GetCursor()->Hide();
    
    s_lastMenuIsMain = name == "MENU_MAIN";
  }
}