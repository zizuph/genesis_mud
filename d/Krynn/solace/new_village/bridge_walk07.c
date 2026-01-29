/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

#include "/d/Krynn/common/herbsearch.h"

object gDoor;

reset_solace_room()
{
    set_searched(random(2));
}

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "bridge_walk03", "north");
    add_exit(TDIR + "bridge_walk08", "south");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

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


