/*
 *	/d/Gondor/ithilien/sforest/thicket1.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 6-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("small clearing");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("ash");
    set_extraline("Thick growth of gorse and whortleberry, and low tough thorns " +
    "surround the small clearing on all sides except to the east where a road " +
    "is visible. Out of the bushes a few hoary ash-trees raise their stems " +
    "and slender crowns. Small paths through the thicket go southwest and northwest. ");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),BS(
    "The mountains named Ephel Duath appear to be dark grey from here. "+
    "You judge the mountains to be between 5000 to 7000 feet tall, "+
    "and you guess they are several kilometers away now.\n"));
    add_item("road",BS(
    "The long straight road runs south towards Harad, Gondor's old enemy " +
    "in the South. It has been made in a long lost time, and it is in " +
    "bad repair. But the handiwork of the Men of old can still be seen in its " +
    "straight sure flight and level course. \n"));
    add_item(({"bush","bushes","thicket","gorse","whortleberry","thorns"}), BSN(
    "The thick thorny undergrowth prevents passage in almost all directions. " +
    "Only to the east, there is a large gap in the bushes, leading " +
    "onto the road, and to the northwest and southwest, narrow paths " +
    "wind through the thicket of gorse and whortleberry. "));
    add_item(({"clearing","glade"}), BSN(
    "The small clearing within the thicket of bushes and thorns was " +
    "recently created by a large fire. The ground is still covered with " +
    "ashes and burned wood. "));
    add_item(({"ashes","wood","ground"}), BSN(
    "The ground is covered with ashes and burned wood from trees and " +
    "bushes. Someone must have made a large fire here rather recently. "));
    add_item(({"forest","woods"}), BSN(
    "To the west, the thicket goes over into a large forest with " +
    "large glades between groups of hoary ash-trees and ancient oaks. "));

    set_up_herbs( ({ HERB_DIR + "astaldo", HERB_DIR + "garlic", 
		     HERB_DIR + "oregano", HERB_DIR + "red_pepper", 
		     HERB_DIR + "thyme", }),
		  ({ "forest","ground","field","flowers","forest"}), 3);
    add_exit(ITH_DIR + "road/sr3",         "east",      0, 3);
    add_exit(ITH_DIR + "sforest/thicket4", "southwest", 0, 2);
    add_exit(ITH_DIR + "sforest/thicket2", "northwest", 0, 1);
}
