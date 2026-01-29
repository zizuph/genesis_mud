/*
 * /d/Gondor/common/dwarf_guild/cave_3.c
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
        "Luin. The tunnel continues to the west and the east. Some stairs " +
        "lead up."));

#include "cavedesc.h"

    add_item( ({ "stairs", "stair" }),
        BSN("The stairs lead up higher into the mountains."));

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "cave_5", "up");
    add_exit(DWARF_DIR + "cave_4", "east");
    add_exit(DWARF_DIR + "cave_2", "west");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
}