#include "../Header/Main.h"

//int currLevel;
static AEGfxVertexList* bMesh;
static AEGfxTexture* bTex;

/******************************************************************************/
/*!
\brief
	This function serves as the "Load" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectLoad()
{
	bTex = AEGfxTextureLoad("./BinFiles/Resources/Textures/menuArrow.png");
	AE_ASSERT_MESG(bTex, "Failed to create button texture.");
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Initialize" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectInit()
{
	currTag = 0;
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-20.0f, -20.0f, 0x00FF00FF, 0.0f, 1.0f,
		20.0f, -20.0f, 0x00FFFF00, 1.0f, 1.0f,
		-20.0f, 20.0f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		20.0f, -20.0f, 0x00FFFFFF, 1.0f, 1.0f,
		20.0f, 20.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-20.0f, 20.0f, 0x00FFFFFF, 0.0f, 0.0f);

	bMesh = AEGfxMeshEnd();
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Update" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectUpdate()
{
	if (AEInputCheckTriggered(AEVK_UP))
	{
		currTag--;

		if (currTag <= 0)
			currTag = 0;
	}

	if (AEInputCheckTriggered(AEVK_DOWN))
	{
		currTag++;

		if (currTag >= 3)
			currTag = 3;

	}


	if (AEInputCheckReleased(AEVK_RETURN))
	{
		switch (currTag)
		{
		case 0:
			gGameStateNext = GS_LEVEL1;
			break;
		case 1:
			gGameStateNext = GS_LEVEL2;
			break;
		case 2:
			gGameStateNext = GS_LEVEL3;
			break;
		case 3:
			gGameStateNext = GS_MAINMENU;
			break;
		}
	}
	
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Draw" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectDraw()
{
	char buffer[1024];

	switch (currTag)
	{
	case 0:
		RenderButton(0, bTex, bMesh);
		break;
	case 1:
		RenderButton(-0.15f, bTex, bMesh);
		break;
	case 2:
		RenderButton(-0.3f, bTex, bMesh);
		break;
	case 3:
		RenderButton(-0.45f, bTex, bMesh);
		break;
	}

	sprintf_s(buffer, "LEVEL SELECTION");
	AEGfxPrint(font, buffer, -0.3f, 0.3f, 2, 255, 255, 255);

	sprintf_s(buffer, "LEVEL 1");
	AEGfxPrint(font, buffer, -0.1f, 0, 1.25f, 255, 255, 255);

	sprintf_s(buffer, "LEVEL 2");
	AEGfxPrint(font, buffer, -0.1f, -0.15f, 1.25f, 255, 255, 255);

	sprintf_s(buffer, "LEVEL 3");
	AEGfxPrint(font, buffer, -0.1f, -0.3f, 1.25f, 255, 255, 255);

	sprintf_s(buffer, "RETURN");
	AEGfxPrint(font, buffer, -0.1f, -0.45f, 1.25f, 255, 255, 255);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);

}

/******************************************************************************/
/*!
\brief
	This function serves as the "Free" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectFree()
{
	//FreeMeshes();
	AEGfxMeshFree(bMesh);
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Unload" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectUnload()
{
	//UnloadTextures();
	AEGfxTextureUnload(bTex);
}