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

    set_long_desc("Here is a stairway leading down winding around the " +
		  "mighty trunk to a narrow path. Above your head the " +
		  "limbs of the tree mesh to form a thick canopy. " +
		  "Bridge-walks are extending to the southeast and to " +
		  "the west.");
    
    add_exit(TDIR + "bridge_walk06", "southeast");
    add_exit(TDIR + "bridge_walk26", "west");
    add_exit(TDIR + "small_road4", "down");
}
