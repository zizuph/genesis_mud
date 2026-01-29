/*
 *      /d/Gondor/ithilien/emyn-arnen/vrd6.c
 *
 *      Coded by Olorin.
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance.
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
    set_areadesc("valley between low hills");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("The track is leading from the hamlet east of here "
        + "deeper into the valley to the west. South of the track is the "
        + "bank of a small river.");
    add_item(({"road", "track"}), BSN(
        "The track looks as if it once was used by heavy carriages. "
            + "You imagine that long ago farmers used this track to bring their "
            + "crops to the Anduin."));
    add_item(({"village", "hamlet", "houses", "ruins"}), BSN(
        "The village consists of several small stone houses opposite "
            + "a large building built with its back to the hill that "
            + "rises south of the village. Most of the smaller houses are "
            + "standing north of a small square northeast of here."));
    add_item(({"building", "large building", "palace"}), BSN(
        "The large building is almost a small palace. With the back, the "
            + "building leans against the hill that rises south of the village. "
            + "Under the west wall of the building, the river is coming out of "
            + "a culvert."));
    add_item(({"plain", "small plain", "valley", }), BSN(
        "The hamlet is built onto a small plain, surrounded on all sides "
            + "by the gentle hills of Emyn Arnen. A small valley is leading west "
            + "towards the Anduin. The road and the river are following the valley."));
    add_hill();
    add_item(({"river"}), BSN(
        "The river is coming with a swift current out of a culvert under "
            + "the large building. It then continues south of the track into "
            + "the valley, running towards the Anduin."));
    add_item(({"culvert"}), BSN(
        "The culvert opens like a dark gaping mouth under the western wall of "
            + "the large building."));
    
    add_exit(ITH_DIR + "emyn-arnen/vrd5",  "east",  0, 3);
    add_exit(ITH_DIR + "emyn-arnen/bank2", "south", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/vrd7",  "west",  0, 3);
}

string
short_desc()
{
    if (areatype == 8)
        return "A dirt track in "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}
