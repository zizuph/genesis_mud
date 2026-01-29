/*
 *  /d/Emerald/telberin/dock/lakeroom2.c
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
      + " The ferry is probably about halfway between the city"
      + " and the north shore of the lake now, making is way"
      + " carefully through the water.\n");
    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
} /* create_emerald_room */

