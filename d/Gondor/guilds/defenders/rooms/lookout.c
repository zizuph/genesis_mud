/* /d/Gondor/guilds/defenders/rooms/lookout.c
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

	add_exit(DEF_GUILDDIR + "rooms/temple", "north");
	add_exit(DEF_GUILDDIR + "rooms/lookout_outside", "up");
	
	add_item(({"stuff", "more stuff"}), "stuff.\n");

    reset_room();
}


void
reset_room()
{
   
}

