/* 	pond.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("By the pond");
    set_long("\n"+
             "You are standing at the edge of a small pond.\n"+
             "The field extends in all directions but you seem unable to\n"+
             "cross either the pond or the stream. East you can see a ruin.\n"+
             "");

    add_exit ("field9","north");
    add_exit ("ruin","east");

    add_item(({"pond" }),
             "A very nice little pond. With a few ducks it would be perfect.\n"+
             "");
    add_item(({"ruin" }),
             "It's too far away to see any details.\n"+
             "");
    add_item(({"field","stream" }),
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

