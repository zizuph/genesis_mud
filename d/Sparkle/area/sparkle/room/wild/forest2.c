/* 	forest2.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Green forest");
    set_long("\n"+
             "In a forest.\n"+
             "You are in a large valley containing a beautiful green forest.\n"+
             "Only the mountains to the north and south provide you with a sense\n"+
             "of direction. The forest seems to get deeper to the west.\n"+
             "");

    add_exit("forest3","west");
    add_exit("orc_road4","east");

    add_item(({"mountains","valley" }),
             "");
    add_item(({"forest" }),
             "This is nice. You could probably stay here quite a while.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

