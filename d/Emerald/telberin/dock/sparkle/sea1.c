/*
 *  /d/Emerald/telberin/dock/sea1.c
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
    set_short("upon the waters of Lake Telberin");
    set_long("You are sailing upon the waters of Lake Telberin,"
      + " west now of the city itself, which is visible in the"
      + " distance off the side of the ship.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

