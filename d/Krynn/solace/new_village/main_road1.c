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

    set_long_desc("You are at the begining of the Solace Main road. The " +
		  "road twists and turns among the huge vallenwoods. The " +
		  "road continues to the southwest, and to the north a " +
		  "forest lane starts.");

    add_exit(C_FOREST, "north");
    add_exit(TDIR + "main_road2", "southwest");
}


