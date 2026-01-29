/* /d/Gondor/guilds/defenders/rooms/lookout_outside.c
 *
 * Defenders, guildhall.
 *
 * Nerull, 2016
 *
 */

#include <stdproperties.h>
#include "defs.h";
#include "../guild.h";

inherit DEF_STD_ROOM;


/*
 * Function name: create_def_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_def_room()
{
	set_short("Some room");
	set_long("This is a room.\n");

	// Outdoor location
	add_prop(ROOM_I_INSIDE, 0);

	add_exit(DEF_GUILDDIR + "rooms/lookout", "down");
	
	add_item(({"stuff", "more stuff"}), "stuff.\n");

    reset_room();
}


void
reset_room()
{
   
}

