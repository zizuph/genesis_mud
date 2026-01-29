/* 	field4.c			Styles.   3 Mar 1993
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
             "A large open field. Mountains prevent passage west\n"+
             "and the muddy ground makes it hard to reach the pond to\n"+
             "the northeast.\n"+
             "");

    add_exit("field8","north");
    add_exit("field3","south");
    add_exit("field5","east");

    add_item(({"mountains","field" }),
             "");
    add_item(({"ground","mud" }),
             "The ground is very muddy due to the nearby pond.\n"+
             "");
    add_item(({"pond" }),
             "A very nice little pond. With a few ducks it would be perfect.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
