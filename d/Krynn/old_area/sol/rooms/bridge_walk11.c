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

    set_long_desc("At this tree, three bridge-walks join together. " +
		  "They extend to the east, southwest and northwest. " +
		  "The mighty tree forms a thick canopy overhead.");

    add_exit(TDIR + "platform3", "east");
    add_exit(TDIR + "bridge_walk14", "southwest");
    add_exit(TDIR + "bridge_walk12", "northwest");

    reset_solace_room();
}
