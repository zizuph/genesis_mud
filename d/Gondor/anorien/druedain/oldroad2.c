/*
 *	/d/Gondor/anorien/druedain/oldroad2.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 4-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

public string  check_tracking();

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("forgotten road");
    set_area("south");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("soft, light green");
    set_treetype("tall, grey");
    set_forest_density(11);
    set_extraline("All around you there are more grey trees all " +
        "sheltering this piece of forgotten road in the Druedain Forest " +
        "in southern Anorien. The undergrowth of the forest makes it " +
        "hard to see where the old road once went, but it seems to " +
        "continue south and northwest."+check_tracking());
    add_item("road", 
	"The ancient wagon-trail is covered by the undergrowth of the forest.\n");
    add_exit(DRUEDAIN_DIR + "forest2",     "north",     test_loc,   2, 1);
    add_exit(DRUEDAIN_DIR + "oldroad3",    "south",     test_track, 2, 0);
    add_exit(DRUEDAIN_DIR + "rangerpath1", "west",      test_track, 2, 1);
    add_exit(DRUEDAIN_DIR + "oldroad1",    "northwest", test_track, 2, 0);
}

public string
check_tracking()
{
    if (TP->query_skill(SS_AWARENESS) > forest_density)
	return " You also notice an old path leading west.";
    else return "";
}

