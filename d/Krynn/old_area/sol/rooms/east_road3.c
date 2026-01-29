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

    set_long_desc("The East road splits here, the road continues to the " +
		  "east and west, but there is also a road leading " +
		  "southeast. The thick canopy overhead makes a good " +
		  "protection against the outside world.");

    add_exit(C_WILD, "east");
    add_exit(TDIR + "east_road4", "southeast");
    add_exit(TDIR + "east_road2", "west");
}


