/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/new_village/town_square/local.h"

inherit SOLOUTROOM2;

RESETROOM

create_solace_room()
{
    set_place(MAINROAD);

    set_long_desc("The main road stretches north and south among the " +
		  "huge vallenwoods. The limbs of the trees intertwine " +
		  "above you, providing a protective canopy from the " +
		  "harsh outside world. Above your head is a " +
		  "wooden bridge-walk running from one vallenwood to " +
		  "another.");

    add_exit(TDIR + "main_road4", "north");
    add_exit(TDIR + "intersection", "south");
    add_exit(ROOM7, "west");

    reset_solace_room();
}


