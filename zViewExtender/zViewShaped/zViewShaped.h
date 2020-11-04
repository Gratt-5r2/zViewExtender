// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE {
  class zCViewShaped : public zCViewInteractive {
  protected:
    zTBBox2D BBox;
    Array<zTRndSimpleVertex> Vertexes;
    Array<zTRndSimpleVertex> Modified;
    zMAT3 TrafoShape;
    zMAT3 TrafoUV;
    bool_t UseParentTrafo;

    virtual bool_t IsOnBounds( int x, int y );
  public:
    zVEC2 PixelToVirtual( const zVEC2& point );
    zVEC2 VirtualToPixel( const zVEC2& point );
    zVEC2 GetVirtualScale();
    
    zCViewShaped();
    Array<zTRndSimpleVertex>& GetVertexes();
    void GetShapeBounds( zVEC2& min, zVEC2& max );
    void CreateFlatUV();
    void CreateBoxShape( const zVEC2& min, const zVEC2& max );
    void CreateRoundShape( const zVEC2& center, const float& radius, const uint& edges );

    void MoveShape( const zVEC2& direction );
    void RotateShape( const float& angle, const zVEC2& pivot = 4096.0f );
    void ScaleShape( const zVEC2& direction, const zVEC2& pivot, const float& angle = 0.0f );

    void MoveUV( const zVEC2& direction );
    void RotateUV( const float& angle, const zVEC2& pivot = 4096.0f );
    void ScaleUV( const zVEC2& direction, const zVEC2& pivot = 0.0f, const float& angle = 0.0f );

    void MoveUVLocal( const zVEC2& direction );
    void RotateUVLocal( const float& angle, const zVEC2& pivot = 4096.0f );
    void ScaleUVLocal( const zVEC2& direction, const zVEC2& pivot = 0.0f, const float& angle = 0.0f );

    virtual void InsertVertex( const zVEC2& point );
    virtual void InsertVertex( const zVEC2& point, const zVEC2& uv );
    virtual void Blit();
  };
}