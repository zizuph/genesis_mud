/*
 *  /d/Emerald/telberin/dock/sea4.c
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
    set_short("upon turbulent waters off the coast of Emerald");
    set_long("The water has become turbulent here where Lake Telberin"
      + " empties into the sea. The ship is just now off the coast of"
      + " Emerald, with open water to the south, and the channels of"
      + " the lake to the north.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

