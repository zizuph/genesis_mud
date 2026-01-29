/* 	field5.c			Styles.   3 Mar 1993
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
             "Out on a large field.\n"+
             "The field stretches out in all directions but a stream prevents you\n"+
             "from going north or east.\n"+
             "");

    add_exit("field4","west");
    add_exit("field2","south");

    add_item(({"field" }),
             "");
    add_item(({"stream" }),
             "Oh, it's definitively too wide to jump.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
