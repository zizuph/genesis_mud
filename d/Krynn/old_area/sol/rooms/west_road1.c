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
    set_place(WESTROAD);

    set_long_desc("To the east the West road intersects with the Main road. " +
		  "The West road is a broad road that winds west further " +
		  "into the dense forest. To the south of you is the " +
		  "town square. The thick canopy overhead will give a " +
             "good shelter against any bad weather.");

    add_exit(TDIR + "west_road2", "west");
    add_exit(TDIR + "intersection", "east");
    add_exit(TDIR + "square", "south");
}


