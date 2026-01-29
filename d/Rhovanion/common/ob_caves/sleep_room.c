/*
 * sleep_room.c
 * A place to store the player while he's sleeping.
 * Written by Trenix@Genesis, 8-17-93
 *
 */

inherit "/std/room";
#include <stdproperties.h>

void
create_room()
{
    set_short("");
    set_long("");
    add_prop(OBJ_I_LIGHT,5);
    add_prop(ROOM_I_LIGHT,5);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_I_INSIDE,1);
}

init()
{
    ::init();
}

/* EOF */
