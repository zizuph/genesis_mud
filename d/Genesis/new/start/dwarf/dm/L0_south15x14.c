/*
 * Written by Nuf.
 * /d/Genesis/nuf/startloc/dm/L0_south15x14.c
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
    set_short("Passageway in the depths of the mountain");
    set_long("The walls here are a smooth, but a bit worn down. "+
             "The rugged floor is cold and the ceiling reveals "+
             "the many years it's seen.\n" );
    add_item( ({"wall", "walls"}), "The walls are worn down "+
              "yet smooth.\n" );
    add_item( ({"floor"}), "Cold and dark, the floor is rugged "+
              "and there are small pools of water on it it.\n" );
    add_item( "ceiling", "A very ill maintained ceiling, likely "+
              "to break at any year now.\n" );

    /* Exits */
    add_exit( MOUNTAIN + "L0_south14x13.c", "northwest" );

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
