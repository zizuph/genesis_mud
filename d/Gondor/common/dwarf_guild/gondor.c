/*
 * /d/Gondor/common/dwarf_guild/gondor.c
 *
 * A path in Ered Luin. This is the room that you enter from the great
 * east road.
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

#define SHIRE "/d/Shire/common/greyhaven/dwarf1"

void
create_room()
{
    set_short("somewhere in Ered Luin");
    set_long(BSN("You are on a path in the Blue Mountains, Ered Luin. " +
        "The mountains extend to the south. To the west you see the Gulf " +
        "of Lune. The path to the southeast will take you further into " +
        "the mountains."));

#include "mountain.h"

    add_exit(SHIRE,                "north");
    add_exit(DWARF_DIR + "path_1", "southeast");

    add_prop(OBJ_S_WIZINFO,
        BSN("Indeed. This is Gondorian territory. It leads to the " +
        DWARVEN_RACE_GUILD_NAME + ", coded by /Mercade. For \"historical\" " +
        "reasons we put that guild here and needed to make a link with the " +
        "Shire here."));
}