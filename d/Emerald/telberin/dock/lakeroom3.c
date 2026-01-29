/*
 *  /d/Emerald/telberin/dock/lakeroom3.c
 *
 *  This is a travel room between the City of Telberin and
 *  the north shore used by the ferry.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
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
    set_long("You are sailing upon the waters of Lake Telberin."
      + " Just to the north, the shore of the lake is"
      + " visible, nestled beneath the looming forms of the"
      + " Blackwall Mountains, which dominate the horizon in"
      + " that direction.\n");
    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

