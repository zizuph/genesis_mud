/*
 *	/d/Gondor/rohan/isengard/isenroad2.c
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("rocky riverbank");
    set_area("northern");
    set_areaname("the Gap of Rohan");
    set_land("Rohan");
    set_extraline("The road leads north into the valley of Isengard at the "+
    "southern limits of the Misty Mountains, following the west side of "+
    "the cold River Isen, and south towards the Fords of the River in "+
    "central parts of the Gap of Rohan. You can see the southmost peaks "+
    "of the Misty Mountains to the north, the plains of the West Emnet "+
    "in Rohan to the east, and the hills of Dunland to the west.");
    add_item("road",BSN(
    "The road is obviously newly repaired, but its foundations seem ancient. "+
    "It runs along the west bank of a river that comes flowing "+
    "calmly out of a valley to the north."));
    add_item(({"river","river isen","isen","Isen"}),BSN(
    "The river flows calmly past east of here, running south from "+
    "out of the valley to the north. There seems to "+
    "be a crossable ford further south."));
    add_item(({"peaks","peak","mountains","mountain","misty mountains"}),BSN(
    "To the north some mist-shrouded mountain peaks stretch for "+
    "the clouds. These are the southmost arms of the Misty Mountains, and "+
    "between them is the valley of Isengard, where the road you are on leads to."));
    add_item("valley",BSN("The valley is nestled between the two southmost arms of "+
    "the Misty Mountains. The River Isen comes flowing out of the valley, and "+
    "along its west bank runs a newly repaired cobblestone road."));
    add_exit(ISEN_DIR + "isenroad/isenroad3", "north", 0, 3);
    add_exit(ISEN_DIR + "isenroad/isenroad1", "south", 0, 3);
}
