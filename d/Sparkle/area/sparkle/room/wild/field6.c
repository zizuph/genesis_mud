/* 	field6.c			Styles.   3 Mar 1993
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
             "A large open field. The stream prevents passage to the west\n"+
             "and south.\n"+
             "");

    add_exit("ruin","north");
    add_exit("bridge_n","east");

    add_item(({"stream" }),
             "Oh it is too wide to jump. Maybe you can find a bridge.\n"+
             "");
    add_item(({"field" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
