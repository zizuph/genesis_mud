/*
 *  /d/Sparkle/area/city/rooms/streets/southwest_2a.c
 *
 *  These are the city streets of Sparkle. Refer to outdoor_room.c for
 *  functionality.
 *
 *  Created February 2008, by Cooper Sherry (Gorboth)
 *    - Much credit and thanks to Styles for his inspirational city
 *      design concepts.
 */
#pragma strict_types

#include "../../defs.h"
inherit ROOMS_DIR + "outdoor_room";


/* Prototpyes */
public void        create_sparkle();


/*
 * Function name:        create_sparkle
 * Description  :        set up the room with area presets
 */
public void
create_sparkle()
{
    set_quadrant("southwest");
    set_street(STREET_SOUTHWEST_2);

    add_exit("southwest_2b", "north");
    add_exit("south_1e", "east");
} /* create_sparkle */