/*
 *	/d/Gondor/ithilien/emyn-arnen/vrd5.c
 *
 *	Coded by Olorin.
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
    set_areadesc("village");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("The road is leading out of the hamlet to the west, "
      + "where it follows a small river into a valley between two "
      + "low hills. To the east stand deserted and ruined houses "
      + "north of the road, and a large stone building south of it.");
    add_item(({"road", "track"}), BSN(
        "In the village the road once was paved, but here it has never "
      + "been more than a track on the bank of the river, though it looks "
      + "as if it once was used by heavy carriages. You imagine that "
      + "long ago farmers used this track to bring their crops to the "
      + "Anduin."));
    add_item(({"village", "hamlet", "houses", "ruins"}), BSN(
        "The village consists of several small stone houses opposite "
      + "a large building built with its back to the hill that "
      + "rises south of the village. Most of the smaller houses are "
      + "standing north of a small square northeast of here."));
    add_item(({"building", "large building", "palace"}), BSN(
        "The large building is almost a small palace. With the back, the "
      + "building leans against the hill that rises south of the village. "
      + "The front stretches south of the road for dozens of yards. "
      + "The entrance must be further to the east."));
    add_item(({"plain", "small plain", "valley", }), BSN(
        "The hamlet is built onto a small plain, surrounded on all sides "
      + "by the gentle hills of Emyn Arnen. A small valley is leading west "
      + "towards the Anduin. The road and the river are following the valley."));
    add_hill();
    add_item(({"river"}), BSN(
        "Further west, the river can be seen running westwards south of the "
      + "road. The large building to the south is still blocking the view "
      + "so it is impossible to say where the river is coming from."));
    
    add_exit(ITH_DIR + "emyn-arnen/vrd4", "east", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/vrd6", "west", 0, 3);
}

public string
short_desc()
{
    if (areatype == 8)
        return "A road through "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}
