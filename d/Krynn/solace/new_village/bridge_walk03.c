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

    set_long_desc("There is a rather small house cradled in the "+
		  "branches of the nearest tree.  It must " +
		  "be an offical place since it is obviously lacking " +
		  "a door. There are three bridge-walks here leading " +
		  "south, west and southwest. There are wooden stairs " +
		  "leading north into the house. Above your head you can " +
		  "see a thick canopy formed by the treelimbs.");

    add_exit(HOUSE + "questmaster", "north");
    add_exit(TDIR + "bridge_walk07", "south");
    add_exit(TDIR + "bridge_walk02", "southwest");
    add_exit(TDIR + "bridge_walk04", "west");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

    reset_solace_room();

}
