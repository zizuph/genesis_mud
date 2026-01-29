/* cv/room1.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";

inherit VAMPIRES_STD_ROOM;


/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    add_prop(ROOM_I_INSIDE, 1);
	set_short("crevice");
	set_long(""
        +"" 
        +""
        +""
		+".\n");
    
	add_item(({"stone", "volcanic stone", "basalt", "basaltic stone"}),
       "The stone appears to be a basalt made when magma cooled. It is  "+
       "dark with a hint of warmth.\n");
    add_item(({"crystal", "crystals", "opening"}),
        "Small crystals can be seen along the edges of openings that "+
        "were broken between this crevice and a larger void beyond.\n"); 		
    add_exit("room16", "east");
	add_exit("room13", "west");
    add_exit("post",   "north");
    
    reset_faerun_room();

}
