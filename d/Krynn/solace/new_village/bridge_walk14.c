/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

#include "/d/Krynn/common/herbsearch.h"

reset_solace_room()
{
    set_searched(random(2));
}

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "bridge_walk11", "northeast");
    add_exit(TDIR + "post_office", "south");
    add_exit(TDIR + "bridge_walk15", "west");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

    reset_solace_room();
}

public string
my_desc()
{
    string str, people;

    str = "To the south a small stairway leads into the local " +
	  "post office. The bridge-walk runs northeast and west " +
	  "from here. The limbs of the mighty trees intertwine " +
	  "overhead, forming a thick canopy. Looking down you " +
	  "can see the Solace Main road.";

    if ((people = get_living(({TDIR + "main_road7"}))))
        str += " You can see " + people + " walking along the road below " +
	       "you.";

    return str;
}
