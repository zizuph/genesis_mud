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

    add_exit(TDIR + "bridge_walk09", "north");
    add_exit(TDIR + "platform3", "south");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

    reset_solace_room();

    gDoor = clone_object(OBJ + "d_bridge_walk10");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str, people;

    str = "The bridge-walk stretches out far to the north, while " +
          "to the south it ends at a platform. In this tree some" +
	  "one has built a rather large house with a ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";
 
    str += " brown door. Looking down you can see the East road";

    if (people = get_living(({TDIR + "east_road2"})))
        str += ", walking along the road you can see " + people;

    return str + ".";
}





