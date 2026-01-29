/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

RESETROOM

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("The wooden bridge-walk extends in three different " +
		  "directions, to the north, northeast and to the south.");

    add_exit(TDIR + "bridge_walk18", "north");
    add_exit(TDIR + "platform1", "northeast");
    add_exit(TDIR + "bridge_walk16", "south");

    reset_solace_room();
}

