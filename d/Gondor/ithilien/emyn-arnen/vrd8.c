/*
 *	/d/Gondor/ithilien/emyn-arnen/vrd8.c
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
    set_extraline("The track comes to a sudden end in front of a dike made " 
    + "from large rocks here. The only way out is back to the southeast.");
    add_item(({"road", "track"}), BSN(
      "The track looks as if it once was used by heavy carriages. "
    + "Before the dike was erected here, it must have led further west "
    + "through the valley, but now it ends here."));
    add_hill();
    add_item(({"river"}), BSN(
      "The river is running westwards through a narrow opening in the dike. "
    + "The already swift current becomes a rushing torrent as it gushes "
    + "through the narrow cleft."));
    add_item(({"dike", "cleft"}), BSN(
      "The dike was made from large rocks swiftly heaped up one on the other. "
    + "On top of the large rocks many smaller ones and gravel were thrown. "
    + "If someone were foolish enough to climb the dike, this rubble would "
    + "slide down and bury the climber."));
    add_item(({"valley", }), BSN(
      "A small valley between low hills to the northeast and the southwest. "
    + "The river is following the valley to the northwest towards the "
    + "Anduin. The road probably once followed the valley, too, but now it "
    + "ends here at the dike."));
    
    add_exit(ITH_DIR + "emyn-arnen/vrd7", "southeast", 0, 3);

    add_cmd_item( ({ "dike", "rocks", }), "climb", 
	"Uuuuhh! You don't dare. Go and find a few orcs if you want to kill yourself!\n");
}

string
short_desc()
{
    if (areatype == 8)
        return "A dirt track in "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}

public int
do_swim(string str)
{
    if (strlen(str))
        return 0;

    write("Uuuuhh! You don't dare. Go and find a few orcs if you want to kill yourself!\n");
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_swim,  "swim");
}

