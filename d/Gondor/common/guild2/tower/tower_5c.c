/*
 * /d/Gondor/morgul/tower/tower_5c.c
 * The central room on the fifth floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

int check_level();

void
create_morgul_tower_room()
{
    set_level(5);
    set_room_type("dark staircase");
    set_extra_long("There is a spiral staircase running up and " +
        "down here, and dark passages leading into gloomy rooms " +
        "are to the north and south.");

    add_walls();
    add_no_roof();
    add_floor();
    add_staircase();

    add_exit(MAGES_DIR  + "train_high",     "north", 0, 1);
    add_exit(MAGES_DIR  + "throne_room",    "south", check_level, 1);
    add_exit(MAGES_DIR  + "tower/tower_6c", "up",    0, 4);
    add_exit(MAGES_DIR  + "tower/tower_4c", "down",  0, 4);
}

public int
check_level()
{
    if (TP->query_wiz_level())
    {
        write("Welcome, wizard!\n" +
              "This exit is blocked for mortals except for Nazgul!\n");
        return 0;
    }
    if (!TP->query_nazgul() && 
	(TP->query_morgul_level() < sizeof(MORGUL_MASTER->query_male_titles())) &&
        (MORGUL_NAZGUL_MASTER->check_votes() != TP->query_real_name()))
    {
        if(TP->query_prop(MORGUL_S_THRONE_GRANT))
        {
            write("Since the Lord of Morgul has granted you access, " +
                  "you may enter this once!\n\n\tBehold the King!\n\n");
            TP->remove_prop(MORGUL_S_THRONE_GRANT);
            return 0;
        }

        write("Only the Nazgul may enter the throne room of the Lord of Morgul!\n");
        return 1;
    }
    return 0;
}
