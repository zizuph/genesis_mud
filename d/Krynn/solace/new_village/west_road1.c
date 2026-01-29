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

    set_long_desc("To the east the West road intersects with the Main road. " +
		  "The West road is a broad road that winds west further " +
		  "into the dense forest. To the south of you is the " +
		  "town square. The thick canopy overhead will give a " +
             "good shelter against any bad weather.");

    add_exit(ROOM7, "north");
    add_exit(TDIR + "square", "south");
    add_exit(TDIR + "intersection", "east");
    add_exit(TDIR + "west_road2", "west");


}


