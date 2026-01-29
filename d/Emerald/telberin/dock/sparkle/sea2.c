/*
 *  /d/Emerald/telberin/dock/sea2.c
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
      + " due south now of the city, which rises from its island"
      + " shores in the far distance.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

