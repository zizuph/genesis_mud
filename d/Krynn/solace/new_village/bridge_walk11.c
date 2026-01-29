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

    set_long_desc("At this tree, three bridge-walks join together. " +
		  "They extend to the east, southwest and northwest. " +
		  "The mighty tree forms a thick canopy overhead.");

    add_exit(TDIR + "platform3", "east");
    add_exit(TDIR + "bridge_walk14", "southwest");
    add_exit(TDIR + "bridge_walk12", "northwest");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

    reset_solace_room();
}
