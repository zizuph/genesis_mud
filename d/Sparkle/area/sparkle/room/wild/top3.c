/* 	top3.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("High plateau");
    set_long("\n"+
             "In a canyon.\n"+
             "You are moving through a mountain canyon and it isn't easy. In the shade\n"+
             "of a rock you can see some snow not touched by the warmth of the sun.\n"+
             "");

    add_exit ("top4","south");
    add_exit ("top2","east");

    add_item(({"canyon","mountain","rock","shade" }),
             "");
    add_item(({"snow" }),
             "This is ordinary ice cold snow. Funny to find it lying around\n"+
             "here in the open though, but since the ground is shaded under this\n"+
             "rock, the snow hasn't melted.\n"+
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

