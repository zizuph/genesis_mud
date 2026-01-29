/*
 *	/d/Gondor/anorien/nimrais/trolls/path2.c
 *
 *	Coded by Elessar, 1992
 *
 *	Modification log:
 *	Olorin:			Added herbs.
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 *      Gwyneth, 10/02/02:      Minor changes
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(5);
    set_areadesc("hillside");
    set_grass("thick");
    set_area("central");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_extraline("A little path runs here, southwards along the ledge in the " +
        "hillside. The hillside rises steeply to the west, and it plummets " +
        "straight into the valley east of the ledge. It seems possible to "+
        "walk down amongst the rocks and boulders here.");
    add_exit(ANO_DIR + "nimrais/trolls/path1",   "down",  0, 4);
    add_exit(ANO_DIR + "nimrais/trolls/outcave", "south", 0, 2);
    add_item("path", "The path is more of a track made by some being that " +
        "has followed the same trail several times. The ground is rocky and " +
        "barren, and the only difference between the track and the ground " +
        "around it is the notably smaller amount of dust on the track.\n");
    add_item("hillside", "The hillside rises above you to the west.\n");
    add_item(({"rocks", "boulders"}), "The ledge is covered with rocks in all " +
        "sizes, and the slope leading down into the valley is full of " +
        "boulders that block the view and are unscalable. Only through a " +
        "small fissure between two of the largest boulders is it possible to " +
        "climb down into the valley.\n");
}

