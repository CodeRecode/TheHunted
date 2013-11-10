//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include <stdio.h>

#include <cdll_client_int.h>

#include "mutationmenu.h"

#include <vgui/IScheme.h>
#include <vgui/ILocalize.h>
#include <vgui/ISurface.h>
#include <KeyValues.h>
#include <vgui_controls/ImageList.h>
#include <filesystem.h>

#include <vgui_controls/TextEntry.h>
#include <vgui_controls/Button.h>
#include <vgui_controls/Panel.h>

#include "cdll_util.h"
#include "IGameUIFuncs.h" // for key bindings
#ifndef _XBOX
extern IGameUIFuncs *gameuifuncs; // for key binding details
#endif
#include <game/client/iviewport.h>

#include <stdlib.h> // MAX_PATH define

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

using namespace vgui;

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CMutationMenu::CMutationMenu(IViewPort *pViewPort) : Frame(NULL, PANEL_CLASS)
{
	m_pViewPort = pViewPort;

	// initialize dialog
	SetTitle("", true);

	// load the new scheme early!!
	SetScheme("ClientScheme");
	SetMoveable(false);
	SetSizeable(false);

	// hide the system buttons
	SetTitleBarVisible( false );
	SetProportional(true);


	LoadControlSettings( "Resource/UI/MutationMenu.res" );
}

//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
CMutationMenu::~CMutationMenu()
{
}

MouseOverPanelButton* CMutationMenu::CreateNewMouseOverPanelButton(EditablePanel *panel)
{ 
	return new MouseOverPanelButton(this, "MouseOverPanelButton", panel);
}

Panel *CMutationMenu::CreateControlByName(const char *controlName)
{
	return BaseClass::CreateControlByName( controlName );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CMutationMenu::Reset()
{
}

//-----------------------------------------------------------------------------
// Purpose: Called when the user picks a mutation
//-----------------------------------------------------------------------------
void CMutationMenu::OnCommand( const char *command )
{
	if ( Q_stricmp( command, "vguicancel" ) )
	{
		engine->ClientCmd( const_cast<char *>( command ) );
	}

	Close();

	gViewPortInterface->ShowBackGround( false );

	BaseClass::OnCommand( command );
}

//-----------------------------------------------------------------------------
// Purpose: shows the class menu
//-----------------------------------------------------------------------------
void CMutationMenu::ShowPanel(bool bShow)
{
	if ( bShow )
	{
		Activate();
		SetMouseInputEnabled( true );
	}
	else
	{
		SetVisible( false );
		SetMouseInputEnabled( false );
	}
	
	m_pViewPort->ShowBackGround( bShow );
}

//-----------------------------------------------------------------------------
// Purpose: Sets the text of a control by name
//-----------------------------------------------------------------------------
void CMutationMenu::SetLabelText(const char *textEntryName, const char *text)
{
	Label *entry = dynamic_cast<Label *>(FindChildByName(textEntryName));
	if (entry)
	{
		entry->SetText(text);
	}
}

//-----------------------------------------------------------------------------
// Purpose: Sets the visibility of a button by name
//-----------------------------------------------------------------------------
void CMutationMenu::SetVisibleButton(const char *textEntryName, bool state)
{
	Button *entry = dynamic_cast<Button *>(FindChildByName(textEntryName));
	if (entry)
	{
		entry->SetVisible(state);
	}
}


void CMutationMenu::SetData(KeyValues *data)
{
}

void CMutationMenu::OnKeyCodePressed(KeyCode code) 
{
	BaseClass::OnKeyCodePressed( code );
}