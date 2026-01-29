/*
 * /d/Gondor/common/dwarf_guild/path_5.c
 *
 * A path in Ered Luin. Here is the entrance to the guild.
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
	"Here you see the opening of a cavern to the southeast. The slope " +
	"goes up to the northwest and is at the same level to the west. " +
	"Further to the south you think you see more cave-entrances."));

#include "mountain.h"

    add_item( ({ "cave", "caves", "entrance", "entrances", "cavern",
	"caverns", "cave-entrance", "cave-entrances" }),
	BSN("Peering into the gloom you cannot make out much. The only " +
	"thing you see it that it goes down even further in the cavern. " +
	"The caverns to the south are too distant to really get a good " +
	"look at them."));

    add_exit(DWARF_DIR + "path_3", "northwest");
    add_exit(DWARF_DIR + "path_4", "west");
    add_exit(DWARF_DIR + "cave_6", "southeast");
    add_exit(DWARF_DIR + "path_7", "south");
}
