/* 	slope.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

void
create_room()
{
    set_short("Slope");
    set_long("\n"+
             "Orc road.\n"+
             "The forest grows thinner here as the land slopes westwards.\n"+
             "Orc road bends south to west down the slope into a valley.\n"+
             "");

    add_exit(WILD_DIR + "orc_vall1","west");
    add_exit(THIS_DIR + "orc_road4","south");
    add_exit(THIS_DIR + "orc_road3","southeast",0,1,1);
    add_exit(THIS_DIR + "forest1","east");

    add_item(({"forest","road","slope" }),
             "");
    add_item(({"valley" }),
             "A luscious green valley.\n"+
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}
