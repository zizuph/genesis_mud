/* 	field2.c			Styles.   3 Mar 1993
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
             "A large open field. It extends in all directions but south\n"+
             "where you can see a low mountain ridge.\n"+
             "");

    add_exit("field5","north");
    add_exit("field3","west");
    add_exit("field1","east");

    add_item(({"mountain","mountains","mountain ridge","ridge" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
