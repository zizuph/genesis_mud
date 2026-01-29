/*
 *   /d/Gondor/ithilien/poros/manor/secret.c
 *
 *   The treasure room of the corsairs based in the manor.
 *
 *   Talisan  January 1996
 *
 *   16 June 1999, Gnadnar: put loot control on chest, as with
 *		the shades and the morgul chests.
 *   Added teleportation blocks, Finwe January 2020

 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>

private object chest;


void
create_manor()
{
    set_area("secret room");
    set_extraline("The room is empty except for a large chest along the "
      + "south wall. The secret passage leads back through the north wall.");

    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);

    add_exit(POROS_DIR + "manor/office", "north", 0, 1);

    add_item(({"walls", "room", "floor", "ground"}), BSN(
        "The room appears to be quite sturdy. You figure this is "
      + "undoubtably where the corsairs hide their ill-gotten booty."));
    reset_room();
}

public void
reset_room()
{
    if (!objectp(chest))
    {
	    (chest = clone_object(POROS_DIR + "obj/chest_treasure"))->move(TO);
    }
    else
    {
        if (sizeof(FILTER_PLAYERS(all_inventory(this_object()))))
        {
            return;
        }
	
        if (chest->got_looted())
        {
            chest->reset_container();
        }
    }
}
