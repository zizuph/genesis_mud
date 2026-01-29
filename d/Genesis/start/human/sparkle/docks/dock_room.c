/*
 * Filename:    /d/Genesis/start/human/sparkle/docks/dock_room.c
 *
 * Description: This is the standard room used
 *              for the dock rooms (d) in this directory.
 *
 * Copyright (C): 2000-03-01 by Jakob
 */


#include "defs.h"

inherit SPARKLE_ROOM;

/*
 * Function name: create_room()
 * Description:   Will set up the description that holds
 *                for all the hill rooms in this dir.
 * Returns:       Nothing
 */
public void
create_room()
{
	::create_room();
	seteuid(getuid());
	set_short("Sparkle Dock Area");
}
