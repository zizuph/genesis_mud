/*
 *	/d/Gondor/ithilien/emyn-arnen/srd1.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/ithilien/emyn-arnen/arnen_items.c";

#include <language.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("valley between the gentle hills");
    set_area("southern");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("The road is following a bend in the valley from west " +
        "to northeast. North of the road, a small river is running.");
    add_item(({"mountains","mountain","ephel duath"}),BSN(
    "Only the dark tops of the moutains named Ephel Duath appear are " +
    "still visible over the trees to the east."));
    add_item(({"valley"}), BSN(
    "The small valley is running between two gentle hills from the " +
    "northeast to the west. Both a small river and the road are " +
    "following the valley."));
    add_item("road",BSN(
    "The road looks like a small farm road. It obviously has not seen " +
    "a lot of trafic in recent years, since it is overgrown with grass " +
    "and even small bushes in a few places."));
    add_hill();
    add_item(({"river", "rivulets"}), BSN(
    "The small river must be coming from the slopes of the Ephel Duath. " +
    "It is several feet across and it must be quite deep. It is flowing " +
    "quickly westward. From the hill to the north, several small rivulets " +
    "are feeding the river."));
    add_item(({"forest","forests", "glades"}),BSN(
    "The hills are covered with scattered groups of large trees, " +
    "surrounding the trees are thick bushes and shrubs. There are acres " +
    "populous with woodland hyacinths; and hoary ash-trees and giant " +
    "oaks stand in wide glades."));
    add_item(({"bushes", "shrubs", "trees", "oaks", "ash-trees"}), BSN(
    "Unlike in the forests further north, here the trees stand in " +
    "scattered groups of hoary ash-trees and giant oaks, which are " +
    "surrounded by thick growth of gorse and whortleberry, and low tough " +
    "thorns."));
    add_exit(ITH_DIR + "road/sr6", "northeast", 0, 3);
    add_exit(ITH_DIR + "emyn-arnen/srd2", "west", 0, 3);
}

string
short_desc()
{
    if (areatype == 8)
        return "A road in "+LANG_ADDART(areadesc)+" of "+areaname+
            " in "+land;
    return ::short_desc();
}
