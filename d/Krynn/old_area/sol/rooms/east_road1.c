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
    set_place(EASTROAD);

    set_long_desc("To the west the East road intersects with the Main road. " +
		  "The road winds on east through the forest. The dense " +
		  "forest foliage lines the edges of the road.");

    add_exit(TDIR + "east_road2", "east");
    add_exit(TDIR + "intersection", "west");
}


