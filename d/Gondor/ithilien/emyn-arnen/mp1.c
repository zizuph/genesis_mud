/*
 *	/d/Gondor/ithilien/emyn-arnen/mp1.c
 *
 *	Coded by Olorin
 *
 *	Modification log:
 *	27-Jan-1997, Olorin:	Changed inheritance.
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
    set_areadesc("small hamlet");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("The houses of the hamlet are north and east of here. "
        + "To the south, a road is running from west to east. Beyond the "
        + "street stands a large stone building.");
    add_item("road",BSN(
      "The road runs from east to west between the market place "
    + "to the north and the large building to the south."));
    add_item(({"village", "hamlet", "houses", "ruins"}), BSN(
      "The village consists of several small stone houses. Most of "
    + "them are north and east of the market place, but they either " 
    + "look deserted and in bad repair or are ruins."));
    add_item(({"building", "large building", "palace"}), BSN(
      "The large building is almost a small palace. With the back, the "
    + "building leans against the hill that rises south of the village. "
    + "The front stretches south of the road for dozens of yards."));
    add_item(({"plain", "small plain"}), BSN(
      "The hamlet is built onto a small plain, surrounded on all sides "
    + "by the gentle hills of Emyn Arnen. The largest hill is rising "
    + "to the south, behind the large stone building."));
    add_hill();
    add_item(({"square", "market place", "small square"}), BSN(
      "The market place is a small square north of the road running through "
    + "the hamlet. Once the people living in Emyn Arnen probably traded here "
    + "in the products of their fair country. Most of the houses of the "
    + "hamlet are northwest of the market place."));
    add_exit(ITH_DIR + "emyn-arnen/ruin1",  "northwest", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/house2", "north", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/mp2",    "east",  0, 1);
    add_exit(ITH_DIR + "emyn-arnen/vrd4",   "south", 0, 1);
}

private string
short_desc()
{
    if (areatype == 8)
        return "A market place in "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}
