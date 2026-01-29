/*
 * /d/Gondor/common/dwarf_guild/cave_5.c
 *
 * The underground path to the Dwarven race guild.
 *
 * /Mercade, 9 January 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "dwarf.h"

void
create_room()
{
    set_short("cave deep in Ered Luin");
    set_long(BSN("You are in a cave, deep in the Blue Mountains, Ered " +
        "Luin. The tunnel consists of some stairs leading up and down."));

#include "cavedesc.h"

    add_item( ({ "stairs", "stair" }),
        BSN("The stairs are hewn out of solid rock and lead up higher into " +
        "and down into the mountains."));

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "cave_6", "up");
    add_exit(DWARF_DIR + "cave_3", "down");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
}