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

    set_long_desc("To the north a long bridge-walk extends, running " +
		  "from tree to tree. To the west, a small bridge-walk " +
		  "runs to the nearest tree. Here is a stairway leading " +
		  "down to a clearing.");
    
    add_exit(TDIR + "bridge_walk10", "north");
    add_exit(TDIR + "bridge_walk11", "west");
    add_exit(TDIR + "clearing3", "down");
}
