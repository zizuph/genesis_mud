/*
 * /d/Gondor/common/dwarf_guild/path_3.c
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
        "goes down to the south and southeast and goes up slightly to the " +
        "west."));

#include "mountain.h"

    add_exit(DWARF_DIR + "path_2", "west");
    add_exit(DWARF_DIR + "path_4", "south");
    add_exit(DWARF_DIR + "path_5", "southeast");
}