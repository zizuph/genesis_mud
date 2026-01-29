/*
 *	/d/Gondor/ithilien/emyn-arnen/vrd3.c
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
    set_extraline("North of the road is a small square, probably once "
    + "the market place of this hamlet. To the south stands the "
    + "impressive front of the large stone building, continuing "
    + "east and west for dozens of yards.");
    add_item("road",BSN(
      "Here in the village the road once was paved, but even here "
    + "it is overgrown with grass. The road runs from east to west "
    + "between the market place to the north and the large building "
    + "to the south."));
    add_item(({"village", "hamlet", "houses", "ruins"}), BSN(
      "The village consists of several small stone houses opposite "
    + "a large building built with its back to the hill that "
    + "rises south of the village. Most of the smaller houses are "
    + "standing north of the market place."));
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
      "North of the road is a small square. This was probably once the "
    + "market place where the people living in Emyn Arnen traded in the "
    + "products of their fair country. Most of the house of the hamlet "
    + "are north of the market place."));
    add_exit(ITH_DIR + "emyn-arnen/mp2",  "north", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/vrd2", "east",  0, 1);
    add_exit(ITH_DIR + "emyn-arnen/vrd4", "west",  0, 1);
}

string
short_desc()
{
    if (areatype == 8)
        return "A road through "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}

