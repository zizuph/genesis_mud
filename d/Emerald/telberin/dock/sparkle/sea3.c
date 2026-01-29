/*
 *  /d/Emerald/telberin/dock/sea3.c
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
    set_short("upon the waters of the River Telberin");
    set_long("The waters of the River Telberin flow beneath the"
      + " vessel now. To the north, they join with the more placid"
      + " waters of the lake where the city of Telberin can be seen"
      + " as a distant point of light. South, the river opens onto"
      + " the sea.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

