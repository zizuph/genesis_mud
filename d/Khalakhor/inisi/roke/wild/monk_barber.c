/*
 * monk_barber.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

void
create_room()
{
    set_short("small, musty room");

/*
    set_long("This is the Barber's shop. If he is here, perhaps you " +
             "can convince him to shave your head, if you are a monk.\n");
*/
    set_long("You are in a small, musty, poorly lit room.\n");

    add_prop(ROOM_I_INSIDE, 1);
    /*add_prop(ROOM_M_NO_ATTACK,
      "You can not do that while on Sacred ground.\n");*/
    add_exit("monk_entr", "east");
}
