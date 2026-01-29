/*
 *	/d/Gondor/ithilien/emyn-arnen/vrd7.c
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
    set_areadesc("valley between low hills");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("The track is leading through the valley to a hamlet "
    + "east of here and through a bend northwestwards to the Anduin. "
    + "South of the track is the bank of a small river.");
    add_item(({"road", "track"}), BSN(
      "The track looks as if it once was used by heavy carriages. "
    + "You imagine that long ago farmers used this track to bring their "
    + "crops to the Anduin."));
    add_item(({"village", "hamlet", "houses", "ruins"}), BSN(
      "The hamlet seems to consist of a few houses north of the road "
    + "and a large stone building south of it. From here, one cannot "
    + "make out more."));
    add_item(({"building", "large building", "palace"}), BSN(
      "The large building seems to be almost a small palace. It rises "
    + "south of the hamlet between the road and a hill."));
    add_item(({"plain", "small plain", "valley", }), BSN(
      "The hamlet is built onto a small plain, surrounded on all sides "
    + "by the gentle hills of Emyn Arnen."));
    add_hill();
    add_item(({"river"}), BSN(
      "The river is running northwestwards towards the Anduin south of the "
    + "dirt track."));
    
    add_exit(ITH_DIR + "emyn-arnen/vrd6", "east", 0, 3);
    add_exit(ITH_DIR + "emyn-arnen/bank1", "south", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/vrd8", "northwest", 0, 3);
}

string
short_desc()
{
    if (areatype == 8)
        return "A dirt track in "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}
