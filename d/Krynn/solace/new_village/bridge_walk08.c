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

    set_long_desc("The limbs of nearby trees intertwine to " +
                  "form a thick canopy overhead. The bridge-walk " +
		  "extends to the north and south.");

    add_exit(TDIR + "bridge_walk07", "north");
    add_exit(TDIR + "bridge_walk09", "south");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");
}
