/*
 * /d/Gondor/morgul/tower/tower_4c.c
 * The central room on the fourth floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 *
 *	Copyright (c) 1996 by Christian Markus
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

//	Prototypes
public void   check_level();

public void
create_morgul_tower_room()
{
    set_level(4);
    set_room_type("dark staircase");
    set_extra_long("There is a spiral staircase running up and " +
        "down here, and dark passages lead west and east.");

    add_walls();
    add_no_roof();
    add_floor();
    add_staircase();

    add_exit(MAGES_DIR  + "startroom",      "north", 0,           1);
    add_exit(MAGES_DIR  + "crystalroom",    "east",  0,           1);
    add_exit(MAGES_DIR  + "tower/tower_4s", "south", 0,           1);
    add_exit(MAGES_DIR  + "train_low",      "west",  0,           1);
    add_exit(MAGES_DIR  + "tower/tower_5c", "up",    check_level, 4);
    add_exit(MAGES_DIR  + "tower/tower_3c", "down",  0,           4);
}

public int
check_level()
{
    if (TP->query_wiz_level())
    {
        write("Welcome, wizard!\n" +
              "This exit is blocked for the lower ranks of the Society!\n");
        return 0;
    }
    if ((TP->query_morgul_level() <= APPRENTICE_LEVEL) &&
        (MORGUL_NAZGUL_MASTER->check_votes() != TP->query_real_name()))
    {
        write("The upper levels of the tower are only accessible to the " +
                  "higher ranks of the Society!\n");
        return 1;
    }
    return 0;
}

