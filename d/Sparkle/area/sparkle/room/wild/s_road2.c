/* 	s_road2.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Bright road");
    set_long("\n"+
             "Bright road.\n"+
             "The road runs north to south and a small trail is forking to the east\n"+
             "where it follows a stream towards the sea. A steep hill and some mountains\n"+
             "to your west seem to make passage that way rather difficult.\n"+
             "");

    add_exit ("s_road1","north");
    add_exit ("s_road3","south");
    add_exit ("stream2","east");

    add_item(({"road","trail","stream","sea","hill","mountains","mountain" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

}

