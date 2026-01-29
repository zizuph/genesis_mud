/* 	field10.c			Styles.   3 Mar 1993
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
             "The road runs east-west over the field here. A little to your south\n"+
             "you see what appears to be a ruin. North are only mountains.\n"+
             "");

    add_exit("field9","west");
    add_exit("ruin","south");
    add_exit("field11","east");

    add_item(({"road","field","mountains" }),
             "");
    add_item(({"ruin" }),
             "It looks rather desolate from here.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}


