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
    set_place(MAINROAD);

    set_long_desc("You stand before the largest vallenwood you have " +
		  "ever seen. It towers up above the rest of the huge " +
		  "vallenwoods and appears to touch the clouds above. " +
		  "When you look up into the vallenwood, you see an " +
		  "extravagantly decorated inn that has been built " +
		  "in and among the limbs of the tree. The Main road " +
		  "continues to the northeast and to the south. There " +
		  "is also a side road leading southwest into a park. " +
		  "A spiral stairway winds down from the inn above, " +
		  "reaching the ground just infront of you.");

    add_exit(TDIR + "main_road1", "northeast");
    add_exit(TDIR + "main_road3", "south");
    add_exit(TDIR + "park1", "southwest");
    add_exit(TDIR + "platform2", "up");
}


