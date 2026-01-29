/*
 *  /d/Sparkle/area/city/rooms/temp_pub.c
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

    set_short_extra("You are in a pub");
    set_long_extra("You are inside Gayryn's Prodigal Pub.");

    add_exit("temp_pub_roof", "up");
    add_exit(STREET_DIR + "east_3c", "east");
} /* create_sparkle */