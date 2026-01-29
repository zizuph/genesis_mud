/*
 * /d/Gondor/common/dwarf_guild/entrance.c
 *
 * The entrance to the Dwarven race guild.
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

#define TEDDYBEAR_ID (DWARVEN_RACE_GUILD_PREFIX +  "bear")

void
create_room()
{
    set_short("the entrance to the " + DWARVEN_RACE_GUILD_NAME);
    set_long(BSN("This is the entrance to the " + DWARVEN_RACE_GUILD_NAME +
	". To the south you see a great hall. North of here is the exit " +
	"from the complex. There are some stairs going up."));

#include "cavedesc.h"

    add_item( ({ "hall", "great hall" }),
	BSN("To the south you look into a great hall. It must be the " +
	"central hall of the " + DWARVEN_RACE_GUILD_NAME + "."));
    add_item( ({ "stair", "stairs" }),
	BSN("The stairs lead up into the mountain and will bring you to " +
	"the smithy of the " + DWARVEN_RACE_GUILD_NAME + "."));

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "cave_1", "north", "@@carry_bear@@");
    add_exit(DWARF_DIR + "guild",  "south");
    add_exit(DWARF_DIR + "smithy", "up");

    add_prop(ROOM_I_INSIDE, 1);
}

int
carry_bear()
{
    /* This also returns true if the player carries the bear in a box. */
    if (objectp(present(TEDDYBEAR_ID, ({ TP }) + deep_inventory(TP))))
    {
	write(BSN("The teddybear you are carrying is property of the " +
	    DWARVEN_RACE_GUILD_NAME +
	    ". While you are carrying it, you may not leave the premises."));
	return 1;
    }

    return 0;
}