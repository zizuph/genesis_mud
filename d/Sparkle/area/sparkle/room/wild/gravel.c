/* 	gravel.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Gravel slope");
    set_long("\n"+
             "You are standing on a gravel slope behind the old foundation.\n"+
             "The terrain is getting rougher to the north and you can see\n"+
             "a steep trail leading west up amongst the mountains.\n"+
             "");

    add_exit("lawn","north");
    add_exit("top1","west");

    add_item(({"foundation","foundations" }),
             "Once here must have been a great building.\n"+
             "");
    add_item(({"trail" }),
             "It is quite steep and it seems to be a long climb.\n"+
             "");
    add_item(({"slope" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

