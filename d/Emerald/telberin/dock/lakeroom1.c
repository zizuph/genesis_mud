/*
 *  /d/Emerald/telberin/dock/lakeroom1.c
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
    set_long("You are sailing upon the waters of Lake Telberin,"
      + " just a ways north of the city itself, which is clearly"
      + " in view.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

