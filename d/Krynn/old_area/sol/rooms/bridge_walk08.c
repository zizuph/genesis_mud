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
    set_place(BRIDGEWALK);

    set_long_desc("The limbs of nearby trees intertwine to " +
                  "form a thick canopy overhead. The bridge-walk " +
		  "extends to the north and south.");

    add_exit(TDIR + "bridge_walk07", "north");
    add_exit(TDIR + "bridge_walk09", "south");
}
