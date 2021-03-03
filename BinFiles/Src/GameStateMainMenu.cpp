#include "../Header/Main.h"

s8 font;	// font id of the font

// Meshes & Textures 
AEGfxTexture* buttonTex;
AEGfxVertexList* buttonMesh;
AEGfxTexture* dpLogo;
AEMtx33 logoScale;
AEGfxVertexList* logoMesh;


mPos mousePos;

f64 menuTime;


/******************************************************************************/
/*!
\brief
	This function serves as the "Load" function of this state
*/
/******************************************************************************/
void GameStateMainMenuLoad()
{
	// Load font for game 
	if (firstTime == true)
	{
		font = AEGfxCreateFont("./BinFiles/Resources/Fonts/Arial Italic.ttf", 20);

		buttonTex = AEGfxTextureLoad("./BinFiles/Resources/Textures/menuArrow.png");
		AE_ASSERT_MESG(buttonTex, "Failed to create button texture.");
		
		dpLogo = AEGfxTextureLoad("./BinFiles/Resources/Textures/DigiPen_RED.png");
		AE_ASSERT_MESG(dpLogo, "Failed to create dplogo texture.");

		firstTime = false;
	}
	else
	{
		buttonTex = AEGfxTextureLoad("./BinFiles/Resources/Textures/menuArrow.png");
		AE_ASSERT_MESG(buttonTex, "Failed to create button texture.");
	}
	
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Initialize" function of this state
*/
/******************************************************************************/
void GameStateMainMenuInit()
{	
	AEMtx33Scale(&logoScale, 5, 5);

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

	//AEGfxTriAdd(
	//	-80.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
	//	80.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
	//	-80.0f, 30.0f, 0x0000FFFF, 0.0f, 0.0f);

	//AEGfxTriAdd(
	//	80.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
	//	80.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
	//	-80.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh2

	buttonMesh = AEGfxMeshEnd();
	//AE_ASSERT_MESG(buttonMesh, "Failed to create mesh 2!!");

	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-90.0f, -25.0f, 0x00FF00FF, 0.0f, 1.0f,
		90.0f, -25.0f, 0x00FFFF00, 1.0f, 1.0f,
		-90.0f, 25.0f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		90.0f, -25.0f, 0x00FFFFFF, 1.0f, 1.0f,
		90.0f, 25.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-90.0f, 25.0f, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh2

	logoMesh = AEGfxMeshEnd();
	//AE_ASSERT_MESG(logoMesh, "Failed to create mesh 2!!");
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Update" function of this state
*/
/******************************************************************************/
void GameStateMainMenuUpdate()
{
	menuTime += AEFrameRateControllerGetFrameTime();
	if (menuTime > 3 && firstTime == false)
	//if (menuTime > 0 && first == false)
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
			if (currTag >= 5)
				currTag = 5;
		}

		if (AEInputCheckReleased(AEVK_RETURN))
		{
			switch (currTag)
			{
			case PLAY:
				gGameStateNext = GS_LEVEL1;
				break;
			case LEVEL:
				gGameStateNext = GS_LEVELSELECT;
				break;
			case QUIT:
				gGameStateNext = GS_QUIT;
				break;
			case CREDITS:
				gGameStateNext = GS_CREDITS;
				break;
			case HELP:
				//gGameStateNext = GS_HELP;
				break;
			case SETTINGS:
				gGameStateNext = GS_SETTINGS;
				break;
			}
		}
	}

	// to-do: menu-ing with mouse

}

/******************************************************************************/
/*!
\brief
	This function serves as the "Draw" function of this state
*/
/******************************************************************************/
void GameStateMainMenuDraw()
{
	if (menuTime < 3)
	{
	/*	AEGfxSetTransform(logoScale.m);
		RenderButton(0.0f, dpLogo, logoMesh);*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetPosition(0, 0);
		AEGfxTextureSet(dpLogo, 0, 0);
		AEGfxSetTransparency(1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);

		AEGfxSetTransform(logoScale.m);
		AEGfxMeshDraw(logoMesh, AE_GFX_MDM_TRIANGLES);
	}
	else
	{
		char strBuffer[1024];
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);

		switch (currTag)
		{
		case PLAY:
			RenderButton(0, buttonTex, buttonMesh);
			break;

		case LEVEL:
			RenderButton(-0.15f, buttonTex, buttonMesh);
			break;
		case SETTINGS:
			RenderButton(-0.3f, buttonTex, buttonMesh);
			break;
		case CREDITS:
			RenderButton(-0.45f, buttonTex, buttonMesh);
			break;
		case HELP:
			RenderButton(-0.6f, buttonTex, buttonMesh);
			break;
		case QUIT:
			RenderButton(-0.75f, buttonTex, buttonMesh);
			break;
		}

		sprintf_s(strBuffer, "Astrocats");
		AEGfxPrint(font, strBuffer, -0.1f, 0.3f, 2, 255, 255, 255);

		sprintf_s(strBuffer, "PLAY");
		AEGfxPrint(font, strBuffer, -0.1f, 0, 1.25f, 255, 255, 255);

		sprintf_s(strBuffer, "LEVEL SELECT");
		AEGfxPrint(font, strBuffer, -0.1f, -0.15f, 1.25f, 255, 255, 255);

		sprintf_s(strBuffer, "SETTINGS");
		AEGfxPrint(font, strBuffer, -0.1f, -0.3f, 1.25f, 255, 255, 255);

		sprintf_s(strBuffer, "CREDITS");
		AEGfxPrint(font, strBuffer, -0.1f, -0.45f, 1.25f, 255, 255, 255);

		sprintf_s(strBuffer, "HELP");
		AEGfxPrint(font, strBuffer, -0.1f, -0.6f, 1.25f, 255, 255, 255);

		sprintf_s(strBuffer, "QUIT");
		AEGfxPrint(font, strBuffer, -0.1f, -0.75f, 1.25f, 255, 255, 255);

		AEGfxSetBlendMode(AE_GFX_BM_NONE);
	}
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Free" function of this state
*/
/******************************************************************************/
void GameStateMainMenuFree()
{
	AEGfxMeshFree(buttonMesh);
	AEGfxMeshFree(logoMesh);
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Unload" function of this state
*/
/******************************************************************************/
void GameStateMainMenuUnload()
{
	AEGfxTextureUnload(buttonTex);
	if (firstUnload == true)
	{
		AEGfxTextureUnload(dpLogo);
		firstUnload = false;
	}
}

void RenderButton(float f, AEGfxTexture* tex, AEGfxVertexList* mesh)
{
	float pc = (WIN_HEIGHT / 10) / 2;
	if (f != 0)
	{
		pc *= (f * 10);
	}
	else
	{
		pc = 0;
	}

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetPosition(-120, pc + 10);
	AEGfxTextureSet(tex, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}