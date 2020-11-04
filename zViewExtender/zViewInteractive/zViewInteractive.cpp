
namespace NAMESPACE {
  zCViewInteractive::zCViewInteractive() : zCViewAnimated() {
    EventEnter = Null;
    EventLeave = Null;
    EventDown  = Null;
    EventDrag  = Null;
    EventUp    = Null;
    EventLoop  = Null;
  }

  zCViewInteractive::zCViewInteractive( int a0, int a1, int a2, int a3, zTviewID a4 ) : zCViewAnimated( a0, a1, a2, a3, a4 ) {
    EventEnter = Null;
    EventLeave = Null;
    EventDown  = Null;
    EventDrag  = Null;
    EventUp    = Null;
    EventLoop  = Null;
  }

  void zCViewInteractive::InitFunctions(
    zTViewInteractiveEventMovement enter,
    zTViewInteractiveEventMovement leave,
    zTViewInteractiveEventToggled  down,
    zTViewInteractiveEventMovement drag,
    zTViewInteractiveEventToggled  up,
    zTViewInteractiveEventMovement loop
  ) {
    EventEnter = enter;
    EventLeave = leave;
    EventDown  = down;
    EventDrag  = drag;
    EventUp    = up;
    EventLoop  = loop;
  }

  bool_t zCViewInteractive::IsSelected() {
    zCViewCursor* cursor = zCViewCursor::GetCursor();
    return cursor && cursor->GetTopSelectedView() == this;
  }

  bool_t zCViewInteractive::IsActive() {
    return Active;
  }

  zCViewInteractive::~zCViewInteractive() {
    // TO DO remove from cursor view list
  }
}