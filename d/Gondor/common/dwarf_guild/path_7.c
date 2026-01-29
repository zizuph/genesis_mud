/*
 * /d/Gondor/common/dwarf_guild/path_7.c
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
        "You see several openings of caves here. However, they are too " +
        "small to enter. You shall have to return north if ever you want " +
        "to leave this place. The mountains seem unclimbable here."));

#include "mountain.h"

    add_item( ({ "cave", "caves", "entrance", "entrances", "cavern",
        "caverns", "opening", "openings" }),
        BSN("There are indeed many openings in the rock-face here. They " +
        "are too small to enter for they are about one foot in diameter. " +
        "In the caves you cannot see a thing."));

    add_exit(DWARF_DIR + "path_5", "north");
}