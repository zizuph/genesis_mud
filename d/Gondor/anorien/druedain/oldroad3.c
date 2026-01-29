/*
 *	/d/Gondor/anorien/druedain/oldroad3.c
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

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("forgotten road");
    set_area("south");
    set_areaname("the Druedain Forest");
    set_land("Anorien");
    set_grass("soft, light green");
    set_treetype("tall, grey");
    set_forest_density(10);
    set_extraline("All around you there are more grey trees all " +
        "sheltering this forgotten track or road. You hear the soft wind " +
        "blowing through the branches however, and this makes you feel " +
        "somewhat safe. The overgrown road seems to lead north.");
    add_item("road", BSN("All the grass and moss that grow everywhere " +
        "make it hard to see where the road goes. You can only see it " +
        "continue north, while it seems to end here."));
    add_item("trees", BSN("The trees here are tall and grey, and their " +
        "long branches stretching out above do not let much light down " +
        "to the ground."));
    add_exit(DRUEDAIN_DIR + "oldroad2", "north", test_track, 2, 0);
    add_exit(DRUEDAIN_DIR + "forest3",  "east",  test_track, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest14", "south", test_track, 2, 1);
}
