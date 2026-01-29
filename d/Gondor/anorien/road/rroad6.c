/*
 *	/d/Gondor/anorien/road/rroad6.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("grassy field");
    set_areatype(8);
    set_area("southeastern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_extraline("To the west you see the stone wall of Rammas Echor, and to "+
    "the east is the river Anduin, and the green forests of Ithilien beyond. "+
    "Further north along the road you see some ruins. The road continues "+
    "south along the river.");
    add_item("ruins", "These are the ruins of Osgiliath, the ancient " +
	     "capital of Gondor.\n");
    add_item("wall","The stone wall is strong and tall, and you guess the best\n"+
	     "way of passing it would be through a gate.\n");
    add_item("forest","You gaze across the river for a while, daydreaming about\n"+
	     "the lovely green forests of Ithilien.\n");
    add_exit(ANO_DIR + "road/rroad7", "north", 0, 2);
    add_exit(ANO_DIR + "road/rroad5", "south", 0, 2);
}
