/*
 * /d/Gondor/common/dwarf_guild/path_4.c
 *
 * A path in Ered Luin.
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
    set_short("somewhere in Ered Luin");
    set_long(BSN("You are on a path in the Blue Mountains, Ered Luin. " +
        "You are surrounded by the mountains in all directions. The slope " +
        "goes up to the north. It goes down rapidly to the south and to " +
        "the east you will remain at the same level. You suspect that the " +
        "path to the south will take you further into the mountains."));

#include "mountain.h"

    add_exit(DWARF_DIR + "path_3", "north");
    add_exit(DWARF_DIR + "path_6", "south");
    add_exit(DWARF_DIR + "path_5", "east");
}