/*
 * Written by Nuf.
 * /d/Genesis/nuf/startloc/dm/L0_tunnel14x12.c
 */

#pragma strict_types

#include "mountain.h"

inherit STD_MOUNTAIN_ROOM;

#include <stdproperties.h>

/* Prototypes */
public void create_mountain_room();
public void reset_room();

/* Defines */

/* Function name: create_mountain_room
 * Purpose      : set up the room
 */
public void
create_mountain_room()
{
    set_short("Intersection in the depths of the mountain");
    set_long("The walls here are still smooth. The light shed "+
             "from the torches barely makes way through the "+
             "compact darkness. The floor is cold and somewhat "+
             "rugged, and small drops keep falling down on "+
             "the it from the ceiling. The tunnel continues "+
             "to the west and to the east and narrows off to "+
             "north and south.\n" );
    add_item( ({"drop", "drops"}), "Small drops trickle down "+
              "from the ceiling, they seem to be clear.\n" );
    add_item( ({"wall", "walls"}), "The walls are smooth and "+
              "moisture has begun to condensate and trickle "+
              "down a few very fine cracks.\n" );
    add_item( ({"floor"}), "Cold and dark, the floor is rugged "+
              "and small pools of water has formed.\n" );
    add_item( ({"pool", "pools", "water pools", "water pool"}),
              "The pools are small and filled with clear "+
              "water.\n" );
    add_item( "moisture", "Fine moisture on the walls.\n" );
    add_item( ({"crack", "cracks"}), "A few very fine cracks, "+
              "in some of them clear water trickles down.\n" );
    add_item( ({"torch", "torches", "light"}), "The light "+
              "that is shed from the torches around you barely "+
              "makes you able to see your feet.\n" );

    /* Exits */
    add_exit( MOUNTAIN + "L0_north14x11.c", "north" );
    add_exit( MOUNTAIN + "L0_tunnel16x12.c", "east" );
    add_exit( MOUNTAIN + "L0_south14x13.c", "south" );
    add_exit( MOUNTAIN + "L0_tunnel12x12.c", "west" );

    /* Properties */
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
}

/* Function name: reset_room
 * Purpose      : resets the room
 */
public void
reset_room()
{
    ::reset_room();
}
