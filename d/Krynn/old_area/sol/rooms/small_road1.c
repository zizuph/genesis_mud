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
    set_place(SMALLROAD);

    set_long_desc("At the edge of the road stands a huge vallenwood " +
		  "with a staircase leading up to a platform in the " +
		  "tree. The road continues to the east and west, " +
		  "to the east you spot the Main road.");

    add_exit(TDIR + "small_road2", "west");
    add_exit(TDIR + "main_road4", "east");
    add_exit(TDIR + "platform1", "up");
}



