/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM2;

RESETROOM

create_solace_room()
{
    set_place(MAINROAD);

    set_long_desc("The Main road stretches north and south among the " +
		  "huge vallenwoods. The limbs of the trees intertwine " +
		  "above you, providing a protective canopy from the " +
		  "harsh outside world.");

    add_exit(TDIR + "intersection", "north");
    add_exit(TDIR + "main_road7", "south");

    reset_solace_room();
}


