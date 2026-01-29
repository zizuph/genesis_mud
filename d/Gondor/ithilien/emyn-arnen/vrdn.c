/*
 *	/d/Gondor/ithilien/emyn-arnen/vrdn.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
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
    set_areadesc("hamlet");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("To the south, the road is leading to the market "
    + "place of the hamlet. On all other sides are deserted houses "
    + "or ruins.");
    add_item("road",BSN(
      "The road once was paved, but now it is overgrown with grass. "
    + "The road is leading south to the market place."));
    add_item(({"houses", "house", "ruin", "ruins", }), BSN(
      "To the north and northeast, one can enter deserted "
    + "houses that show the signs of long neglect and decay. Of the "
    + "houses that once stood to the east and northwest, only ruins "
    + "remain."));
    add_item(({"village", "hamlet", }), BSN(
      "The village consists of several small stone houses opposite "
    + "a large building built with its back to the hill that "
    + "rises south of the village. Most of the smaller houses are "
    + "standing here north of the market place."));
    add_item(({"building", "large building", "palace"}), BSN(
      "The large building is almost a small palace. With the back, the "
    + "building leans against the hill that rises south of the village. "
    + "The front stretches south of the road for dozens of yards. "
    + "The entrance seems to be a bit further west."));
    add_item(({"plain", "small plain"}), BSN(
      "The hamlet is built onto a small plain, surrounded on all sides "
    + "by the gentle hills of Emyn Arnen. The largest hill is rising "
    + "to the south, behind the large stone building."));
    add_hill();
    add_item(({"square", "market place", "small square"}), BSN(
      "South of hjere is a small square. This was probably once the "
    + "market place where the people living in Emyn Arnen traded in the "
    + "products of their fair country. Most of the house of the hamlet "
    + "are here north of the market place."));
    add_exit(ITH_DIR + "emyn-arnen/house3", "north",     0, 1);
    add_exit(ITH_DIR + "emyn-arnen/house4", "northeast", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/ruin3",  "east",      0, 1);
    add_exit(ITH_DIR + "emyn-arnen/mp2",    "south",     0, 1);
    add_exit(ITH_DIR + "emyn-arnen/ruin2",  "northwest", 0, 1);
}

string
short_desc()
{
    if (areatype == 8)
        return "A road through "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}
