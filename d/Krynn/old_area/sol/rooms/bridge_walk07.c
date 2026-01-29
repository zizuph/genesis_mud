/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

object gDoor;

RESETROOM

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "bridge_walk03", "north");
    add_exit(TDIR + "bridge_walk08", "south");

    reset_solace_room();

    gDoor = clone_object(OBJ + "d_bridge_walk07");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str;

    str = "The bridge-walk you are on extends to the north and " +
          "far to the south. A building is located in the tree " +
	  "with a green ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += " door leading into it. The limbs of the mighty tree you are " +
           "standing beside mesh to form a thick canopy overhead.";

    return str;
}


