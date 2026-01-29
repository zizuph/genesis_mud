/*
 *  The Tower of the Society of the Morgul Mages
 *
 *  A room on the second level of the tower.
 *
 *	Copyright (c) 1996 by Christian Markus
 * Moved to the new guild directory, Eowul, Februari 2009 
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

public void
create_morgul_tower_room()
{
    object rack, shaft;

    set_level(3);
    set_room_type("dark chamber");
    set_extra_long("The chamber is windowless and empty, save "
      + "for a weapon rack standing at the north wall. The "
      + "doorway leads west into the dark staircase and there is "
      + "a dark hole in the southeast corner.");

    add_prop(ROOM_I_LIGHT, 1);

    add_exit(MORGUL_ROOM_DIR + "tower_3c", "west", 0, 0);
    add_exit(TOWER_DIR + "tower_lookout", "east", 0, 0);

    add_roof();
    add_walls();
    add_floor();

    rack = clone_object(MORGUL_OBJ_DIR + "rack_3e");
    rack->move(this_object());
    rack->set_rack_type(1);

    shaft = clone_object(MORGUL_OBJ_DIR + "disposal_shaft");
    shaft->move(this_object());

    add_prop(ROOM_I_NO_CLEANUP, 1); // For droproom purposes
}

