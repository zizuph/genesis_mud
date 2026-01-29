/*
 *  /d/Emerald/telberin/dock/sea7.c
 *
 *  This is a travel room between Emerald and Sparkle.
 *
 *  Created August 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict types

inherit "/d/Emerald/std/room";
#include <stdproperties.h>


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room 
 */
public void
create_emerald_room()
{
    set_short("in the open sea off the coast of Sparkle");
    set_long("The open sea spreads out in all directions to the"
      + " north. South, the mainland of Sparkle looms on the"
      + " horizon.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

