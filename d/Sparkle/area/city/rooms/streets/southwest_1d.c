/*
 *  /d/Sparkle/area/city/rooms/streets/southwest_1d.c
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
    set_street(STREET_SOUTHWEST_1);

    add_exit("southwest_1e", "east");
    add_exit("southwest_1c", "south");
} /* create_sparkle */