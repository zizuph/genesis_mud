#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * The Minstrel Guild Headquarters: The Performance Hall.
 * Cedric 2/93
 */

int
check_enter()
{
    if (MEMBER(TP()))
	return 0;
    else
	TP()->catch_msg(("That way lies the inner sanctum of the Minstrels; "
	+ "only the initiated may pass.\n"));
    return 1;
}

void 
create_room() 
{
    set_short("The Auditorium of the Minstrels"); 
    set_long("A cozy performance hall where the Minstrels may display "
    + "their skills for all to see. Right now the hall is quiet, but "
    + "come back later; the Guildmaster has plans for this place!\n");

    add_exit(GUILD+"courtyard", "north"); 
    add_exit(GUILD+"tower_mundane", "southeast"); 
    add_exit(GUILD+"office", "southwest", "@@check_enter");
    add_prop(ROOM_I_INSIDE, 1);
}
