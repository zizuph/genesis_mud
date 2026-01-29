/*
 *  /d/Emerald/telberin/dock/sea6.c
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
    set_short("in the vast waters of the open sea");
    set_long("You are sailing the vast waters of the open sea. In all"
      + " directions, as far as the eye can see, the ocean stretches to"
      + " the distant horizon.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

