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

    add_exit(TDIR + "bridge_walk26", "northeast");
    add_exit(TDIR + "adv_guild", "southeast");
    add_exit(TDIR + "platform8", "southwest");

    add_item("sign", "The sign has 'The House of Adventurers' written with " +
	     "large letters all over it.\n");

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

    str = "There is a stairway leading southeast into a large " +
          "building. The building has a large sign above the " +
	  "doorway that reads 'The House of Adventurers'. To the " +
	  "southwest, you can see a platform and the bridge-walk " +
	  "extends to the northeast. The thick canopy overhead " +
	  "makes a good protection against the outside world. Looking " +
	  "down, you see a small road twisting its way around the trees";

    if (people = get_living(({TDIR + "small_road6"})))
        str += ", walking along the small road you can see " + people;

    return str + ".";
}




