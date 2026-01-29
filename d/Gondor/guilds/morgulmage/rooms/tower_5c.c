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
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

int check_level();
int check_lounge();

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

    add_exit(MORGUL_ROOM_DIR + "train_high", "north", 0, 1);
    add_exit(MORGUL_ROOM_DIR + "morgul_lounge", "east", check_lounge, 1);
    add_exit(MORGUL_ROOM_DIR + "upper_throne_room", "south", check_level, 1);
    add_exit(MORGUL_ROOM_DIR + "tower_6c", "up",    0, 4);
    add_exit(MORGUL_ROOM_DIR + "tower_4c", "down",  0, 4);
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
    if (!TP->query_nazgul())
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


/*
 * Function name:        check_lounge
 * Description  :        We only allow full_mages into the lounge
 * Returns      :        1 - prevent, 0 - allow
 */
public int
check_lounge()
{
    if (TP->query_wiz_level())
    {
        write("Welcome, wizard!\n" +
              "This exit is blocked for mortals who are not full-mages"
            + " and above!\n");
        return 0;
    }

    if (TP->query_morgul_level() > APPRENTICE_LEVEL)
    {
        return 0;
    }

    write("Only full mages may enter the lounge. Begone, wretch!\n");
    return 1;
} /* check_lounge */
