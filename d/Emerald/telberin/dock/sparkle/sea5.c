/*
 *  /d/Emerald/telberin/dock/sea5.c
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
    set_short("in the open sea off the coast of Emerald");
    set_long("The shores of Emerald are visible in the distance to"
      + " the north, surrounded by the vast open waters of the sea"
      + " in all other directions.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

