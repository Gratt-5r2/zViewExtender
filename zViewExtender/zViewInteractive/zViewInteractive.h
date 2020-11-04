
namespace NAMESPACE {
  typedef bool( __cdecl* zTViewInteractiveEventMovement )( zCViewInteractive*, zCViewCursor* );
  typedef bool( __cdecl* zTViewInteractiveEventToggled )( zCViewInteractive*, zCViewCursor*, zEMouseButton );

  class zCViewInteractive : public zCViewAnimated {
    friend class zCViewCursor;
  protected:
    bool_t Active;

    zTViewInteractiveEventMovement EventEnter;
    zTViewInteractiveEventMovement EventLeave;
    zTViewInteractiveEventToggled  EventDown;
    zTViewInteractiveEventMovement EventDrag;
    zTViewInteractiveEventToggled  EventUp;
    zTViewInteractiveEventMovement EventLoop;
  public:

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
    bool_t IsActive();

    virtual ~zCViewInteractive();
  };
}