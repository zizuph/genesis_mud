/*
 *  /d/Emerald/telberin/dock/sea8.c
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
    set_short("just off the eastern coast of Sparkle");
    set_long("Directly to the west, the mainland of Sparkle rises"
      + " to block out the horizon, its docks visible perhaps a"
      + " mile distant. East, the open ocean beckons.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

