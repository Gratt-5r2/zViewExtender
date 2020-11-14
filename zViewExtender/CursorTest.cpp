// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	static zCViewShaped* s_TestShape = Null;



	bool TurnLeft( zCViewInteractive* button, zCViewCursor* cursor, zEMouseButton mouse ) {
		s_TestShape->RotateShape( -5.0f );
		return true;
	}

	bool TurnRight( zCViewInteractive* button, zCViewCursor* cursor, zEMouseButton mouse ) {
		s_TestShape->RotateShape( +5.0f );
		return true;
	}




	uint hand1;
	uint hand2;

	bool ShapeDrag( zCViewInteractive* button, zCViewCursor* cursor ) {
		return true;
	}

	bool ShapeMouseDown( zCViewInteractive* button, zCViewCursor* cursor, zEMouseButton mouse ) {
		s_TestShape->CursorVisualIndex = hand2;
		return true;
	}

	bool ShapeMouseUp( zCViewInteractive* button, zCViewCursor* cursor, zEMouseButton mouse ) {
		s_TestShape->CursorVisualIndex = hand1;
		return true;
	}



	void InitTest() {
		static bool isInit = false;
		if( isInit )
			return;

		hand1 = zCViewCursor::GetCursor()->CreateVisual( "ExampleCursor_Hand1.tga", 4096, 4096 );
		hand2 = zCViewCursor::GetCursor()->CreateVisual( "ExampleCursor_Hand2.tga", 4096, 4096 );

		zCViewInteractive* viewRotateLeft  = new zCViewInteractive();
		screen->InsertItem( viewRotateLeft );
		viewRotateLeft->SetSize( zPixelX( 100 ), zPixelY( 100 ) );
		viewRotateLeft->InsertBack( "RED" );
		viewRotateLeft->SetPos( 300, 4096 );
		viewRotateLeft->EventDown = TurnLeft;


		zCViewInteractive* viewRotateRight = new zCViewInteractive();
		screen->InsertItem( viewRotateRight );
		viewRotateRight->SetSize( zPixelX( 100 ), zPixelY( 100 ) );
		viewRotateRight->InsertBack( "BLUE" );
		viewRotateRight->SetPos( 8192 - 300 - zPixelX( 100 ), 4096 );
		viewRotateRight->EventDown = TurnRight;


		s_TestShape = new zCViewShaped();
		screen->InsertItem( s_TestShape );
		s_TestShape->SetSize( zPixelX( 380 ), zPixelY( 300 ) );
		s_TestShape->CreateRoundShape( 4096, 4096, 10 );
		s_TestShape->InsertBack( "LOADING" );
		s_TestShape->SetPos( 4096 - zPixelX( 190 ), 4096 - zPixelY( 150 ) );
		s_TestShape->EventDrag = ShapeDrag;
		s_TestShape->EventDown = ShapeMouseDown;
		s_TestShape->EventUp = ShapeMouseUp;
		s_TestShape->CursorVisualIndex = hand1;


		isInit = true;
	}
}