//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
//
//
#include "cbase.h"
#include "hud.h"
#include "hud_macros.h"
#include "view.h"

#include "iclientmode.h"

#include <KeyValues.h>
#include <vgui/ISurface.h>
#include <vgui/ISystem.h>
#include <vgui_controls/AnimationController.h>

#include <vgui/ILocalize.h>

using namespace vgui;

#include "hudelement.h"
#include "hud_basetimer.h"

#include "hl2mp_gamerules.h"

#include "convar.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Purpose: Health panel
//-----------------------------------------------------------------------------
class CHudRoundTimer : public CHudElement, public CHudBaseTimer
{
	DECLARE_CLASS_SIMPLE( CHudRoundTimer, CHudBaseTimer );

public:
	CHudRoundTimer( const char *pElementName );
	virtual void Init( void );
	virtual void VidInit( void );
	virtual void Reset( void );
	virtual void OnThink();
};	

DECLARE_HUDELEMENT( CHudRoundTimer );

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CHudRoundTimer::CHudRoundTimer( const char *pElementName ) : CHudElement( pElementName ), CHudBaseTimer(NULL, "HudRoundTimer")
{
	SetHiddenBits( HIDEHUD_HEALTH | HIDEHUD_PLAYERDEAD );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudRoundTimer::Init()
{
	Reset();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudRoundTimer::Reset()
{
	SetSeconds(0);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudRoundTimer::VidInit()
{
	Reset();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudRoundTimer::OnThink()
{
	CHL2MPRules* gameRules = dynamic_cast< CHL2MPRules* >(g_pGameRules);
	int roundSecondsLeft = gameRules->GetRoundRemainingTime();
	if ( roundSecondsLeft < 0 )
		roundSecondsLeft = 0;
	SetSeconds(roundSecondsLeft);
}