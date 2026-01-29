/*
 *	/d/Gondor/ithilien/emyn-arnen/ruin1.c
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
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_area_room()
{
    string *herbs;

    set_areatype(8);
    set_areadesc("small hamlet");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("All that is left of this building are the foundations "
      + "and half of the northwest wall. The door into the house once "
      + "was to the southeast, where the doorstep is still visible.");
    add_item(({"village", "hamlet", "houses", "ruins"}), BSN(
        "The village consists of several small stone houses. Most of "
      + "them are north and east of the market place, but they either " 
      + "look deserted and in bad repair or are ruins."));
    add_item(({"building", "ruin", "house", }), BSN(
        "The building obviously was destroyed by fire. The foundations "
      + "and the remnants of the northwest wall are black and charred. "
      + "Of the interior of the house nothing is left."));
    add_item(({"northwest wall", "remnants", "wall", "walls", "foundations", }), BSN(
        "The remnants of the northwest wall and the foundations are all "
      + "that is left of the building. They are charred and covered with "
      + "soot from the fire that destroyed the house."));
    add_item(({"floor", "ground", }), BSN(
        "Wind and weather have left nothing of the floor of the building. "
      + "Plants have reclaimed the space, and grass, flowers, and even "
      + "small bushes are growing here in the ruined building."));
    add_item(({"flowers", "plants", "grass", "bushes", }), BSN(
        "Grass, flowers, and even small bushes are growing inside the ruin. "
      + "Even though Ithilien is lying under the Shadow of Mordor and "
      + "the villages are deserted, plants of all kind are still flourishing "
      + "in this fair land."));
    add_item(({"plain", "small plain"}), BSN(
        "The hamlet is built onto a small plain, surrounded on all sides "
      + "by the gentle hills of Emyn Arnen. The largest hill is rising "
      + "to the south, behind the large stone building."));
    add_hill();
    add_item(({"square", "market place", "small square"}), BSN(
        "The market place is to the south of the building. It is a small "
      + "square between the road to the south and the houses of the "
      + "north of it."));
    add_exit(ITH_DIR + "emyn-arnen/mp1", "southeast", 0, 1);

    herbs = HERB_MASTER->query_herbs( ({ "garden", "meadow", "subtropical", }) );
    set_up_herbs( ({ HERB_DIR + "red_pepper",
		     ONE_OF_LIST_WITH_SEED(herbs, 650698),
		     ONE_OF_LIST_WITH_SEED(herbs,  66857),
		     ONE_OF_LIST_WITH_SEED(herbs, 384825), }),
		  ({ "ground","field","bushes","forest"}), 3);
}

string
short_desc()
{
    if (areatype == 8)
        return "A ruined building in "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}
