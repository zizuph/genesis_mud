/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/new_village/town_square/local.h"

inherit SOLOUTROOM2;

create_solace_room()
{
    set_place(SMALLROAD);

    set_long_desc("At the edge of the road stands a huge vallenwood " +
		  "with a staircase leading up to a platform in the " +
		  "tree. The road continues to the east and west, " +
		  "to the east you spot the Main road.");

    add_exit(ROOM7, "south");
    add_exit(TDIR + "main_road4", "east");
    add_exit(TDIR + "small_road2", "west");
    add_exit(ROOM6, "southwest");
    add_exit(TDIR + "platform1", "up");
}



