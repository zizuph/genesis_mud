/* /d/Gondor/guilds/defenders/rooms/h1_2.c
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

    add_exit(DEF_GUILDDIR + "rooms/h1_1",   "west");
	add_exit(DEF_GUILDDIR + "rooms/s1", "north");
	add_exit(DEF_GUILDDIR + "rooms/h1_3",   "east");
	add_exit(DEF_GUILDDIR + "rooms/h1_4", "south");
	
	add_item(({"stuff", "more stuff"}), "stuff.\n");

    reset_room();
}


void
reset_room()
{
   
}

