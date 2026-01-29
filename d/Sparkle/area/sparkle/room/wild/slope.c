/* 	slope.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Slope");
    set_long("\n"+
             "Orc road.\n"+
             "The forest grows thinner here as the land slopes westwards.\n"+
             "Orc road bends south to west down the slope into a valley.\n"+
             "");

    add_exit (S_AREA_ROOM_DIR + S_AREA_FORT + "orc_vall1","west");
    add_exit ("orc_road4","south");
    add_exit ("forest1","east");

    add_item(({"forest","road","slope" }),
             "");
    add_item(({"valley" }),
             "A luscious green valley.\n"+
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

