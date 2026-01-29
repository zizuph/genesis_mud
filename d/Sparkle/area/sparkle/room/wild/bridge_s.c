/* 	bridge_s.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("South end of bridge");
    set_long("\n"+
             "You are standing on the south side of a stone bridge. \n"+
             "It looks old and well walked upon just like an old bridge should. Still,\n"+
             "you feel there is more to this bridge than meets the eye. The dark road\n"+
             "continues over and past the bridge in a north - south direction.\n"+
             "");

    add_exit("bridge_n","north");
    add_exit("field1","west");
    add_exit("n_road2","south");

    add_item(({"bridge" }),
             "It looks ancient and for some reason you feel uneasy...\n"+
             "");
    add_item(({"road" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

