/* 	orc_vall2.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Orc valley");
    set_long("\n"+
             "Orc road.\n"+
             "You're standing in the western part of orc valley. The mountains rise\n"+
             "high to the north and south. The valley opens up a little to the west\n"+
             "and east you can see some low houses.\n"+
             "");

    add_exit ("orc_vall3","west");
    add_exit ("orc_sett","east");

    add_item(({"mountains" }),
             "They are quite high and unclimbable.\n"+
             "");
    add_item(({"valley" }),
             "A luscious green valley.\n"+
             "");
    add_item(({"houses" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

