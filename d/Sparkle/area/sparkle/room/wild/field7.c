/* 	field7.c			Styles.   3 Mar 1993
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
             "Dark road.\n"+
             "You are on a part of the field which suddenly drops into a deep crevice\n"+
             "to the east. You should be careful 'cause a fall might be quite lethal.\n"+
             "South you can see a bridge and further north along the road are the mountains.\n"+
             "");

    add_exit("field11","north");
    add_exit("ruin","west");
    add_exit("bridge_n","south");

    add_item(({"bridge" }),
             "It's too far away to see any details.\n"+
             "");
    add_item(({"crevice" }),
             "You better be careful not to fall down there!\n"+
             "");
    add_item(({"field","mountains" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
