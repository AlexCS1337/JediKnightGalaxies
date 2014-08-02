#include "client.h"
#include "cl_uiapi.h"

#if 0
	// Jedi Knight Galaxies

	case UI_JKG_CHANGEPROTOCOL:
		return 0;

	case UI_SYSCALL_CG:
		currentVM = cgvm;
		return 0;

	case UI_SYSCALL_UI:
		currentVM = uivm;
		return 0;
#endif

/*
====================
CL_ShutdownUI
====================
*/
void CL_ShutdownUI( void ) {
	Key_SetCatcher( Key_GetCatcher( ) & ~KEYCATCH_UI );

	if ( !cls.uiStarted )
		return;

/*
Ghoul2 Insert End
*/
	default:
		Com_Error( ERR_DROP, "Bad UI system trap: %ld", (long int) args[0] );

	}

	return 0;
}

/*
====================
CL_ShutdownUI
====================
*/
void CL_ShutdownUI( qboolean delayFreeVM ) {
	Key_SetCatcher( Key_GetCatcher( ) & ~KEYCATCH_UI );
	cls.uiStarted = qfalse;

	CL_UnbindUI();
}

/*
====================
CL_InitUI
====================
*/

void CL_InitUI( void ) {
	// load the dll
	CL_BindUI();

	// init for this gamestate
	//rww - changed to <= CA_ACTIVE, because that is the state when we did a vid_restart
	//ingame (was just < CA_ACTIVE before, resulting in ingame menus getting wiped and
	//not reloaded on vid restart from ingame menu)
	UIVM_Init( (qboolean)(cls.state >= CA_AUTHORIZING && cls.state <= CA_ACTIVE) );
}

/*
====================
UI_GameCommand

See if the current console command is claimed by the ui
====================
*/
qboolean UI_GameCommand( void ) {
	if ( !cls.uiStarted )
		return qfalse;

	return UIVM_ConsoleCommand( cls.realtime );
}
