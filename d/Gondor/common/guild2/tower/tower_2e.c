/*
 *  The Tower of the Society of the Morgul Mages
 *
 *  A room on the second level of the tower.
 *
 *	Copyright (c) 1996 by Christian Markus
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower";
 
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
 
public void
create_morgul_tower_room()
{
    set_level(2);
    set_room_type("dark chamber");
    set_extra_long("The chamber is empty and windowless. The "
      + "doorway leads west into the dark staircase.");

    add_prop(ROOM_I_LIGHT, 1);

    add_exit(TOWER_DIR + "tower_2c", "west", 0, 0);

    add_roof();
    add_walls();
    add_floor();
}
 
