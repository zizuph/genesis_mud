/* 	top2.c			Styles.   3 Mar 1993
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
             "You are traveling a mountain canyon and the high altitude makes you\n"+
             "breathe heavily. Moving is difficult amongst the rocks and debris so\n"+
             "you better move slowly. The canyon continues north and west.\n"+
             "");

    add_exit ("top1","north");
    add_exit ("top3","west");

    add_item(({"canyon","mountain","rocks","debris" }),
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

}

