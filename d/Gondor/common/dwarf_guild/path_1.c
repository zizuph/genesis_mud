/*
 * /d/Gondor/common/dwarf_guild/path_1.c
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
        "The mountains extend to the south. The path will take you further " +
        "into the mountains to the southeast. The slope goes down slightly " +
        "to the northwest."));

#include "mountain.h"

    add_exit(DWARF_DIR + "gondor", "northwest");
    add_exit(DWARF_DIR + "path_2", "southeast");
}