/*
 * Written by Nuf.
 * /d/Genesis/nuf/startloc/dm/L0_west10x13.c
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
    set_short("Alcove in the depths of the mountain");
    set_long("The walls here are a smooth, but a bit worn down. "+
             "The floor is cold and somewhat and rugged, and there "+
             "are some old articles lying in one corner.\n" );
    add_item( ({"wall", "walls"}), "The walls are worn down "+
              "and has some cracks in it.\n" );
    add_item( ({"floor"}), "Cold and dark, the floor is rugged "+
              "and there are various articles lying in one corner.\n" );
    add_item( ({"crack", "cracks"}), "The cracks looks more "+
              "the result of years of scraping.\n" );
    add_item( ({"articles", "article"}), "There are some rusty "+
              "needles and old piles of straw lying in one corner.\n" );
    add_item( ({"needle", "needles", "rusty needles", "rusty needle"}),
              "Some rusty rusty and old needles lying in one corner.\n" );

    /* Exits */
    add_exit( MOUNTAIN + "L0_tunnel11x12.c", "northeast" );

    /* Properties */
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
}

/* Function name: reset_room
 * Purpose      : resets the room
 */
public void
reset_room()
{
    ::reset_room();
}
