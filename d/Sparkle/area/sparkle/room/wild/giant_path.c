/* 	giant_path.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Giant path");
    set_long("\n"+
        "You are on a path going in east/west direction.\n"+
        "There are some VERY big footprints here.\n"+
        "");

    add_exit("giant_conf","west");
    add_exit("grove","east");

    add_item(({"footprints" }),
        "They are indeed BIG. Who or rather what could have made them?\n"+
        "");
    add_item(({"path" }),
    "There is nothing special about it except for the footprints.\n"+
        "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

