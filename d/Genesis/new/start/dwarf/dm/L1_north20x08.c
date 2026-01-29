/*
 * Written by Nuf.
 * /d/Genesis/nuf/startloc/dm/L1_tunnel20x08.c
 */

#pragma strict_types

#include "mountain.h"

inherit STD_MOUNTAIN_ROOM;

#include <stdproperties.h>

/* Prototypes */
public void create_mountain_room();

/* Defines */

/* Function name: create_mountain_room
 * Purpose      : set up the room
 */
public void
create_mountain_room()
{
    set_short("Tunnel in the depth of the mountain");
    set_long("The walls here are a little bit worn down. "+
             "The light shed from the torches cuts through "+
             "the darkness easily. The floor is cold and somewhat "+
             "rugged. The tunnel leads south into a shaft and "+
	     "east. A narrow crack leads northeast.\n" );
    add_item( ({"wall", "walls"}), "The walls are worn down "+
              "and has some cracks in it.\n" );
    add_item( ({"floor"}), "Cold and dark, the floor is rugged "+
              "and there are various articles lying about.\n" );
    add_item( ({"crack", "cracks"}), "The cracks looks more "+
              "the result of years of scraping.\n" );
    add_item( ({"torch", "torches", "light"}), "The light "+
              "that is shed from the torches around you "+
              "makes you able to see a little further than "+
              "just your feet.\n" );
 
    /* Exits */
    add_exit( MOUNTAIN + "L1_north19x09.c", "southwest");

    /* Properties */
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
}




