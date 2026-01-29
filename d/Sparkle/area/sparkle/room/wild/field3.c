/* 	field3.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("A large field");
    set_long("\n"+
             "A large open field. Mountains prevent passage west and south.\n"+
             "");

    add_exit("field4","north");
    add_exit("field2","east");

    add_item(({"mountains","field" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
