/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

inherit ROAD_BASE;

object hobbit;

void
create_road_room()
{
    set_areadesc("hillside");
    set_area("track");
    set_areaname("the hill");
    set_land("Bree");

    add_my_desc("The track runs north and southwest across the " +
        "meadow, and disappears as it dips into a valley. Birds " +
        "dart about and the grass rustles with movement of animals " +
        "nearby. There is a small shack off the track hidden in a " +
        "cluster of trees.\n");

    add_item(({"shanty", "shack"}),
        "It is a rather shabby looking shack, hidden in a cluster " +
        "of trees and looking rather old. The shack seems out of " +
        "place up here on the hill and away from travellers.\n");

    set_add_hilltop();
    reset_shire_room();

    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
 
    set_search_places(({"bush","bushes","trees", "flowers"}));
//    add_herb_file(GONDOR_HERB_DIR + "athelas");

    add_exit(TOWN_DIR + "shack", "north");
    add_exit(ROAD_DIR + "broad14", "southwest");
}

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(hobbit))
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(CITIZEN);
        hobbit->set_power(100);
        hobbit->move(TO);
        hobbit->set_restrain_path("/d/Shire/bree");
        hobbit->set_random_move(2);
    }
}
