/*
 *	/d/Gondor/rohan/isengard/isenroad4.c
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 *  5-Jan-2002, Alto: Exit to new Isengard.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("barren waste");
    set_area("central");
    set_areaname("the Isengard Valley");
    set_land("Misty Mountains");
    set_extraline("The road leads up to the Gates of Isengard to the north, and "+
    "south it leads along the west bank of the River Isen. Beyond the Circle "+
    "of Isengard the dark pinnacle of Orthanc rises, 500 feet tall. "+
    "Foul fumes seem to rise from within Isengard, and the area that "+
      "the road runs through is but a treeless waste.");
    add_item(({"pinnacle","castle","orthanc","Orthanc"}),
    "You don't see much of it here, because of the dark fumes rising from\n"+
    "within the perimeter wall around it, but it rises more than 500 feet\n"+
    "above the ground, and is carved out of pitch black rock.\n");
    add_item(({"circle","isengard",}),
    "The Circle of Isengard is the wall surrounding the Castle Orthanc. The\n"+
    "wall is more than a hundred feet high, its outer surface sheer.\n");
    add_exit(ISEN_DIR + "igard/exterior/status_room",  "north", 0, 3);
    add_exit(ISEN_DIR + "isenroad/isenroad3", "south", 0, 3);
}

