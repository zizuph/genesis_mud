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

    set_long_desc("The bridge-walk continues to the north and south. " +
		  "The mighty trees form a thick canopy overhead, " +
		  "protecting the citizens from the harsh outside world.");

    add_exit(TDIR + "bridge_walk08", "north");
    add_exit(TDIR + "bridge_walk10", "south");

    reset_solace_room();
}




