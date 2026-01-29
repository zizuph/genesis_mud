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

    add_exit(TDIR + "platform5", "east");
    add_exit(TDIR + "bridge_walk25", "southwest");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

    reset_solace_room();

    gDoor = clone_object(OBJ + "d_bridge_walk26");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str;

    str = "There is a small house built in this mighty " +
	  "Vallenwood tree, with a ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += " green door leading into it. To the east you can spot a " +
           "platform and extending to the west is the bridge-walk.";

    return str;
}
