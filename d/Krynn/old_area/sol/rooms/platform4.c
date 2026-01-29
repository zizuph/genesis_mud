/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

create_solace_room()
{
    set_place(PLATFORM);

    set_long_desc("Here is a stairway leading down winding its way " +
		  "in circles around the tall tree. There are also " +
		  "three different bridge-walks extending from here. " +
		  "One is going north and one is going southeast, the " +
		  "last one is going south. Down below you, you can see " +
		  "a small path.");
    
    add_exit(TDIR + "bridge_walk16", "north");
    add_exit(TDIR + "bridge_walk15", "southeast");
    add_exit(TDIR + "bridge_walk21", "south");
    add_exit(TDIR + "clearing2", "down");
}
