/* 	orc_vall3.c			Styles.   3 Mar 1993
 *
 * 06/01/15 Arandir	Enabled exit to new Faerie.
 *
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
        "You are in a little wider part of Orc valley. The road runs " +
        "east-west from here and the valley seems to continue far in " +
        "each direction.\n" + "");

    add_exit(THIS_DIR + "orc_vall2","east");
    add_exit("/d/Sparkle/area/faerie/rooms/forest/mtroad01", "west");

    add_item(({"road","valley" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
