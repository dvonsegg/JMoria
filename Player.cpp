// Player.cpp
//
// implementation of the Player

#include "Player.h"
#include "Tileset.h"
#include "Game.h"
#include "Dungeon.h"
#include "DisplayText.h"

extern CGame *g_pGame;

/*#define TEMPSTUFF
#ifdef TEMPSTUFF
#include "DisplayText.h"
#include "Dungeon.h"

extern CDisplayText *msgs;
extern CDungeon *theDungeon;
#endif
/**/
void CPlayer::Init()
{
	// Initialize all the player stuff, baby.
	//m_TileSet = new CTileset("JMoriaTiles256x256.png", 32, 32 );
	m_TileSet = new CTileset("Resources/Courier.png", 32, 32 );

	// This will likely get moved somewhere else. --Jimbo
	SpawnPlayer();
}

bool CPlayer::Update(float fCurTime)
{
	return true;
}

void CPlayer::Draw()
{
	Uint8 player_tile = '@' - ' ' - 1;//TileIDs[TILE_IDX_PLAYER] - ' ' - 1;
	JVector vSize(1,1);

	PreDraw();
	m_TileSet->DrawTile( player_tile, m_vPos, vSize, true );
	PostDraw();
}

void CPlayer::PreDraw()
{
	g_pGame->GetDungeon()->PreDraw();
}

void CPlayer::PostDraw()
{
	g_pGame->GetDungeon()->PostDraw();
}

JResult CPlayer::SpawnPlayer()
{
	bool bPlayerSpawned = false;
	printf("Trying to spawn player...");
	JVector vTryPos;
	while( !bPlayerSpawned )
	{
		vTryPos.Init( (float)Util::GetRandom(0, DUNG_WIDTH-1), (float)Util::GetRandom(0, DUNG_HEIGHT-1) );

		//printf("Trying to spawn player at <%.2f %.2f>...\n", vTryPos.x, vTryPos.y);
		//g_pGame->GetMsgs()->Printf( "Trying to spawn player at <%.2f %.2f>...\n", vTryPos.x, vTryPos.y );

		// try changing this to "iswalkable" -- might need to move that to dungeon. --Jimbo
		if( g_pGame->GetDungeon()->IsWalkable(vTryPos) == DUNG_COLL_NO_COLLISION )
		{
			m_vPos = vTryPos;
			bPlayerSpawned = true;
			printf("Success!\n");
			//g_pGame->GetMsgs()->Printf( "Success!\n" );
		}
	}

	return JSUCCESS;
}