/*
 * Written by Nuf.
 * /d/Genesis/nuf/startloc/dm/L0_shaft18x12.c
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
    set_short("Shaft in the depth of the mountain");
    set_long("The walls here are a little bit worn down. "+
             "The light shed from the torches cuts through "+
             "the darkness easily. The floor is cold and somewhat "+
             "rugged, and there are some articles lying about. "+
             "The shaft narrows into a tunnel in the west and "+
             "continues up.\n" );
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
    add_item( ({"articles", "article"}), "There are screws, "+
              "hammers and tackles lying scattered on the "+
              "floor.\n" );
    add_item( ({"hammers", "screws"}), "Ordinary stuff for "+
              "constructing and maintenance.\n" );
    add_item( ({"tackle", "tackles"}), "Old and worn down "+
              "tackles that can't have been used for ages.\n" );

    /* Exits */
    add_exit( MOUNTAIN + "L0_tunnel17x12.c", "west" );
    add_exit( MOUNTAIN + "L1_shaft18x12.c", "up", 0, 1, -1);

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
