/* 	orc_road4.c			Styles.   3 Mar 1993
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
             "You are in a luscious green forest in an east-west valley.\n"+
             "Orc road runs east and north from here and one way seems as\n"+
             "good as the other. Through the trees to the south you see the\n"+
             "gray face of the mountainside.\n"+
             "");

    add_exit ("slope","north");
    add_exit ("forest2","west");
    add_exit ("orc_road3","east");

    add_item(({"road","forest","valley","trees","mountainside" }),
             "");
    add_item(({"face" }),
             "Your face is as ugly as ever.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

