/*
 *  /d/Sparkle/area/city/rooms/temp_pub_roof.c
 *
 *  Just a quick and dirty temp room to test some stuff.
 */
#pragma strict_types

#include "../defs.h"
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
    set_street(STREET_EAST_3);
    set_rooftop(1);

    set_short_extra("You are high above the piers.");
    set_long_extra("You are on the roof of the pub, overlooking the"
      + " bay to the east.");

    add_exit("temp_pub", "down");
} /* create_sparkle */