/*
 * monk_barber.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

void
create_room()
{
    set_short("barbershop");

    set_long("This is the Barber's shop. If he is here, perhaps you " +
             "can convince him to shave your head, if you are a monk.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_exit("monk_entr", "east");
}
