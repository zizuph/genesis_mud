/*
 * /d/Gondor/common/dwarf_guild/path_6.c
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
    set_short("deadend, somewhere in Ered Luin");
    set_long(BSN("You are on a path in the Blue Mountains, Ered Luin. " +
        "Here the mountains loom up to all directions save north. It is " +
        "a dead end and you have no choice but to retrace your steps."));

#include "mountain.h"

    add_exit(DWARF_DIR + "path_4", "north");
}