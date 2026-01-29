/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM2;

create_solace_room()
{
    set_place(EASTROAD);

    set_long_desc("The East road twists and turns here, cutting through " +
		  "the vallenwoods. The road continues east and west. To " +
		  "the south a small path leads up to a big vallenwood with " +
		  "a stairway leading up. The canopy overhead forms a " +
		  "protective shield from the outside world. Above you " +
		  "is a wooden bridge-walk.");

    add_exit(TDIR + "east_road3", "east");
    add_exit(TDIR + "clearing3", "south");
    add_exit(TDIR + "east_road1", "west");
}


