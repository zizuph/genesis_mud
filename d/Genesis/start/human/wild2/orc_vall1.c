/* 	orc_vall1.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

void
create_room()
{
    set_short("Orc valley");
    set_long("\n"+
             "Orc road.\n"+
             "This could be a beautiful valley but for some reason a foul stench \n"+
             "lingers in the air. The fact that this region is inhabited by orcs\n"+
             "might have something to do with it...\n"+
             "");

    add_exit(THIS_DIR + "orc_sett","north");
    add_exit(THIS_DIR + "slope","east");

    add_item(({"road","region","valley" }),
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

}
