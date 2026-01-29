#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/ithilien/emyn-arnen/arnen_items.c";

#include <language.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

static object *Orc = allocate(2 + random(3));

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
    set_areadesc("village");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("The valley that continues to the east opens here onto a " +
    "small plain encircled by low hills. On the plain, there is a " +
    "village. A river is coming out of the valley and running southwest. " +
    "To the north, there is a small path entering a bushy thicket.");
    add_item("road",BSN(
    "The road looks like a small farm road. It obviously has not seen " +
    "a lot of trafic in recent years, since it is overgrown with grass " +
    "and even small bushes in a few places."));
    add_item(({"bridge"}), BSN(
    "The road is crossing the small river on a small stone to the " +
    "southeast. The bridge has three low arches and is just broad enough " +
    "for a single carriage to pass it."));
    add_item(({"village", "houses"}), BSN(
    "The village consists of several small stone houses opposite " +
    "a large building built with its back to the hill that " +
    "rises south of the plain."));
    add_item(({"valley"}), BSN(
    "The valley runs around a hill to the east, going southeast " +
    "from here and then turing westward."));
    add_item(({"plain", "small plain"}), BSN(
    "West of here is a small plain, surrounded on all sides by low " +
    "hills. From the southeast, a small valley is leading onto the plain, " +
    "and across the plain, there is another opening between two hills " +
    "where another valley might lead out of the plain."));
    add_hill();
    add_item(({"river", }), BSN(
    "The small river is several feet across and it must be quite deep. " +
    "It is quickly flowing down in the valley from the east, passing " +
    "under the stone bridge and running southwestward."));
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
    add_exit(ITH_DIR + "sforest/path1",   "north", 0, 3);
    add_exit(ITH_DIR + "emyn-arnen/srd3", "southeast", cross_bridge, 3);
    add_exit(ITH_DIR + "emyn-arnen/vrd2", "west", 0, 3);

    reset_room();
}

string
short_desc()
{
    if (areatype == 8)
        return "A road through "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}

public void
reset_room()
{
    clone_npcs(Orc, MORGUL_DIR + "npc/ithil_orc", 60.0, ITH_DIR + "emyn-arnen");
    (Orc - ({ 0 }))->set_random_move(5 + random(6));
}

