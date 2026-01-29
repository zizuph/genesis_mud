/* 	field9.c			Styles.   3 Mar 1993
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
        "The road bends north into a narrow mountain pass and or if you look\n"+
        "east you see it trail away across the field. This part of the field\n"+
        "is somewhat greener than the south part. It might be due to the small\n"+
        "trickles of rain-water coming down from the mountainside.\n"+
        "");

    add_exit("pass","north");
    add_exit("wfall","west");
    add_exit("pond","south");
    add_exit("field10","east");

    add_item(({"road","trail","field","mountainside" }),
        "");
    add_item(({"pass","mountain pass" }),
        "The pass is high and narrow. A perfect place for an ambush.\n"+
        "");
    add_item(({"rain-water","rain water","water" }),
        "It's not much but sufficient to support the vegetation\n"+
        "on the north part of the field.\n"+
        "");
    add_item(({"vegetation" }),
        "It grows very well here due to the water coming down from\n"+
        "the mountainside. This is not a bad place to grow things.\n"+
        "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

