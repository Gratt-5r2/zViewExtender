
namespace NAMESPACE {
  bool32 zCView::IsOnBounds( const int& x, const int& y ) {
    zCViewAnimated* animated = dynamic_cast<zCViewAnimated*>( this );
    if( animated )
      return animated->IsOnBounds( x, y );

    return
      x > pposx && x < pposx + psizex &&
      y > pposy && y < pposy + psizey;
  }



  zCView* zCView::GetTopView( const int& x, const int& y ) {
    zCView* child = childs.root;
    zCView* frontView = IsOnBounds( x, y ) ? this : Null;
    while( child ) {

      zCView* view = child->GetTopView( x, y );
      if( view )
        frontView = view;

      child = child->next;
    }

    return frontView;
  }



  void zCView::ShowBounds( const zCOLOR& color ) {
    screen->Line(
      zPixelX( pposx ),
      zPixelY( pposy ),
      zPixelX( pposx + psizex ),
      zPixelY( pposy ),
      color
    );

    screen->Line(
      zPixelX( pposx + psizex ),
      zPixelY( pposy ),
      zPixelX( pposx + psizex ),
      zPixelY( pposy + psizey ),
      color
    );

    screen->Line(
      zPixelX( pposx + psizex ),
      zPixelY( pposy + psizey ),
      zPixelX( pposx ),
      zPixelY( pposy + psizey ),
      color
    );

    screen->Line(
      zPixelX( pposx ),
      zPixelY( pposy + psizey ),
      zPixelX( pposx ),
      zPixelY( pposy ),
      color
    );
  }
}