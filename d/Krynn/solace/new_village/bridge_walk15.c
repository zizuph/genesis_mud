/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

#include "/d/Krynn/common/herbsearch.h"

object gCitizen, gDoor;

reset_solace_room()
{
    set_searched(random(2));

    if (!gCitizen)
        (gCitizen = clone_object(NPC + "citizen"))->move(TO);
}

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "bridge_walk14", "east");
    add_exit(TDIR + "platform4", "northwest");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

    reset_solace_room();

    gDoor = clone_object(OBJ + "d_bridge_walk15");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str;

    str = "You stand before of a small family residence that has " +
          "been built in a mighty vallenwood tree. The brown door leading " +
	  "into the house is ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += ". The bridge-walk extends to the east and to the northwest " +
           "from here. The trees form a thick canopy overhead.";

    return str;
}
