/*
 *  /d/Sparkle/area/city/rooms/streets/north_b.c
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
    set_quadrant("north");
    set_street(STREET_NORTH);

    add_exit("north_c", "north");
    add_exit("north_a", "south");
} /* create_sparkle */