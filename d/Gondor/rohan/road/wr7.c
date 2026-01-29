/*
 *	/d/Gondor/rohan/road/wr7.c
 *
 *	Coded by Gus (?), 1992
 *
 *	Modification log:
 *	 1996, Olorin:	Changed inheritance,
 *			general revision,
 *			add blackrider.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

#define BLACK_RIDER_ROOM	"/d/Gondor/morgul/blackrider"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("green foothill");
    set_area("eastern");
    set_areaname("the Gap of Rohan");
    set_land("Rohan");
    set_extraline("The Great West Road reaches the Fords of Isen to "
      + "the west, and runs southeast skirting the foot of the "
      + "Thrihyrne, towards the Hornburg. The foothills in the Gap of "
      + "Rohan stretch out north, east and south. Further north one "
      + "can see the south end of the Misty Mountains.");
    add_exit(ROH_DIR + "road/wr6", "southeast", 0, 5);
    add_exit(DUN_DIR+"ford/f01",   "west",      0, 5);

    FIX_EUID
    (ROH_DIR + "plains/e14")->load_me();
    (ROH_DIR + "plains/l10")->load_me();
    BLACK_RIDER_ROOM->load_me();
}

