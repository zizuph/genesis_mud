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

    add_exit(TDIR + "platform1", "east");
    add_exit(TDIR + "bridge_walk17", "south");
    add_exit(TDIR + "bridge_walk19", "southwest");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");
}

public string
my_desc()
{
    string str, people;

    str = "Here three different bridge-walks join together. They " +
          "extend to the east, south and to the southwest. " +
	  "When looking down you can see a narrow path winding " +
	  "between the trees. The limbs of the mighty trees " +
     "intertwine and form a thick canopy. Looking down, you " +
	  "see a small road";

    if (people = get_living(({TDIR + "small_road2"})))
        str += ", walking along the small road you can see " + people;

    return str + ".";
}
