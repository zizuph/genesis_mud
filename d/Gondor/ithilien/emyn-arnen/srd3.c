/*
 *	/d/Gondor/ithilien/emyn-arnen/srd3.c
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

public int
cross_bridge()
{
    write("You cross the small river on the stone bridge.\n");
    return 0;
}

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("valley between the gentle hills");
    set_area("southern");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("The road is following a valley to the east. Northwest " +
        "of here, the valley becomes much wider. The road crossed the small " +
        "river that is running north of the road on a stone bridge there.");
    add_item("road",BSN(
    "The road looks like a small farm road. It obviously has not seen " +
    "a lot of trafic in recent years, since it is overgrown with grass " +
    "and even small bushes in a few places."));
    add_item(({"bridge"}), BSN(
    "The road is crossing the small river on a small stone to the " +
    "northwest. The bridge has three low arches and is just broad enough " +
    "for a single carriage to pass it."));
    add_item(({"valley"}), BSN(
    "Both a small river and the road are following the valley to the " +
    "east. In the other direction, the valley runs to the northwest " +
    "around the foot of the hill to the north, becoming much broader."));
    add_hill();
    add_item(({"river", }), BSN(
    "The small river is several feet across and it must be quite deep. " +
    "It is quickly flowing down from the east, taking a bend here to the " +
    "southwest, and passing under the stone bridge."));
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
    add_exit(ITH_DIR + "emyn-arnen/srd2", "east",                 0, 3);
    add_exit(ITH_DIR + "emyn-arnen/vrd1", "northwest", cross_bridge, 3);
}

string
short_desc()
{
    if (areatype == 8)
        return "A road in "+LANG_ADDART(areadesc)+" of "+areaname+
            " in "+land;
    return ::short_desc();
}

