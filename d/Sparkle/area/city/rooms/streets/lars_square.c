/*
 *  /d/Sparkle/area/city/rooms/streets/lars_square.c
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
    set_quadrant("east");
    set_street("Lars Square");
    set_square(1);

    add_exit("east_3b", "east");
    
    room_add_object(CITY_DIR + "auction/obj/tent", 1);
} /* create_sparkle */
