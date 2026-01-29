/* 	bridge_n.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("North end of bridge");
    set_long("\n"+
             "You are standing on the north side of a stone bridge.\n"+
             "A field extends far to your west. Looking east towards the coast\n"+
             "you see a thin mist covering the moor slanting down towards the shore.\n"+
             "");

    add_exit("field7","north");
    add_exit("field6","west");
    add_exit("bridge_s","south");
    add_exit("moor1","east");

    add_item(({"bridge" }),
             "It looks ancient and for some reason you feel uneasy...\n"+
             "");
    add_item(({"moor" }),
             "It's misty.\n"+
             "");
    add_item(({"field","mist","shore","coast" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

