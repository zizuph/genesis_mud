/*
 *	/d/Gondor/ithilien/emyn-arnen/vrd2.c
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
    set_areadesc("village");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("All the houses of the village seem deserted. Most " +
        "of them are already ruins, and those who are still standing " +
        "show the signs of long neglect and decay.");
    add_item("road",BSN(
    "Here in the village the road once was paved, but even here " +
    "it is overgrown with grass. The main road runs from east, " +
    "leading out of the village, to west. A small branch is " +
    "going south, following the bank of the river."));
    add_item(({"village", "houses", "ruins"}), BSN(
    "The village consists of several small stone houses opposite " +
    "a large building built with its back to the hill that " +
    "rises south of the plain. Just north of here is the entrance " +
    "into one of the house that did not decay into ruins yet."));
    add_item(({"building", "large building", "palace"}), BSN(
    "The large building is almost a small palace. With the back, the " +
    "building leans against the hill that rises south of the village. " +
    "The front stretches " +
    "south of the road for several hundred feet. The entrance seems " +
    "to be further west, though there might be a gate at the end " +
    "of the small way leading south from here."));
    add_item(({"valley"}), BSN(
    "The valley opens to the east, leading out of the village."));
    add_item(({"plain", "small plain"}), BSN(
    "West of here is a small plain, surrounded on all sides by low " +
    "hills. From the southeast, a small valley is leading onto the plain, " +
    "and across the plain, there is another opening between two hills " +
    "where another valley might lead out of the plain."));
    add_hill();
    add_item(({"river", }), BSN(
    "The small river is several feet across and it must be quite deep. " +
    "It is quickly flowing down in the valley from the east, passing " +
    "under a stone bridge southeast of here and running southwestward."));
    add_exit(ITH_DIR + "emyn-arnen/house1", "north", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/vrd1",   "east", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/rrd1",   "south", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/vrd3",   "west", 0, 1);
}

string
short_desc()
{
    if (areatype == 8)
        return "A road through "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}
