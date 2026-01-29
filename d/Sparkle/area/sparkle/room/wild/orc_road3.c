/* 	orc_road3.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Orc road");
    set_long("\n"+
             "Orc road.\n"+
             "You are in a beautiful green forest. The forest seems deeper to the\n"+
             "west and north while to the east you can see open terrain. The road\n"+
             "continues east and west through the valley.\n"+
             "");

    add_exit ("forest1","north");
    add_exit ("orc_road4","west");
    add_exit ("orc_road2","east");

    add_item(({"road","valley","open terrain","terrain" }),
             "");
    add_item(({"forest" }),
             "Isn't it lovely.\n"+
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

