
namespace NAMESPACE {
  typedef bool( __cdecl* zTViewInteractiveEventMovement )( zCViewInteractive*, zCViewCursor* );
  typedef bool( __cdecl* zTViewInteractiveEventToggled )( zCViewInteractive*, zCViewCursor*, zEMouseButton );

  class zCViewInteractive : public zCViewAnimated {
    friend class zCViewCursor;
  public:

    uint CursorVisualIndex;
    zTViewInteractiveEventMovement EventEnter;
    zTViewInteractiveEventMovement EventLeave;
    zTViewInteractiveEventToggled  EventDown;
    zTViewInteractiveEventMovement EventDrag;
    zTViewInteractiveEventToggled  EventUp;
    zTViewInteractiveEventMovement EventLoop;

    zCViewInteractive();
    zCViewInteractive( int a0, int a1, int a2, int a3, zTviewID a4 = zTviewID::VIEW_ITEM );
    void InitFunctions(
      zTViewInteractiveEventMovement enter,
      zTViewInteractiveEventMovement leave,
      zTViewInteractiveEventToggled  down,
      zTViewInteractiveEventMovement drag,
      zTViewInteractiveEventToggled  up,
      zTViewInteractiveEventMovement loop
      );

    bool_t IsSelected();
    virtual ~zCViewInteractive();
  };
}