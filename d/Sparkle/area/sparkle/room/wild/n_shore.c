/* 	n_shore.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("North shore");
    set_long("\n"+
             "This is the north shore outside the stockade of Sparkle.\n"+
             "You can walk west along the stockade or north to follow the shore.\n"+
             "");

    add_exit ("moor3","north");
    add_exit ("stockade","west");

    add_item(({"stockade" }),
             "The stockade continues about 10 metres out into the water.\n"+
             "");
    add_item(({"sparkle","Sparkle","village" }),
             "Sparkle is a small human village by the shore of Pensea.\n"+
             "");
    add_item(({"shore" }),
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

