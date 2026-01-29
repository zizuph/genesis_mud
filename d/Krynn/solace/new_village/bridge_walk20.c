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

    add_exit(TDIR + "bridge_walk19", "north");
    add_exit(TDIR + "platform7", "southwest");

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

    str = "The bridge-walk continues to the north and to the " +
	  "southwest, where it ends in a platform. Looking down " +
	  "you can see the West road";

    if (people = get_living(({TDIR + "west_road3"})))
        str += ", walking along the road you can see " + people;

    return str + ".";
}



