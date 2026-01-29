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
    set_place(WESTROAD);

    set_long_desc("The mighty vallenwood you are standing beside, has " +
		  "a wooden staircase circling the trunk, reaching the " +
		  "ground just a few paces away from you. The West road " +
		  "winds further to the northwest and southeast. There is " +
		  "small road leading deeper into the forest to the " +
		  "northeast.");

    add_exit(ROOM1, "east");
    add_exit(TDIR + "small_road6", "northeast");
    add_exit(TDIR + "west_road7", "northwest");
    add_exit(TDIR + "west_road5", "southeast");
    add_exit(TDIR + "platform8", "up");
}



