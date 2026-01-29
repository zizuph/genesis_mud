/*
 * /d/Gondor/morgul/tower/tower_1c.c
 * The central room on the first floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 *
 * ChangeLog:
 * 
 * Palmer April 22, 2006
 * Removed exit block if you're a wizard.
 *
 * Toby Jan 06, 2007
 * Added descriptions for wizards entering the tower.
 *    They no longer get "Welcome home, 0!"
 *
 * Finwe Feb 2019
 * Fixed wizard block
 */

inherit "/d/Gondor/morgul/tower/tower.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

public int 
block_strangers()
{
    if(TP->query_wiz_level())
    {
        write("Welcome to the Dark Lord's closest servants inner sanctum!\n");
        return 0;
    }

    if (!(TP->query_wiz_level()) && !IS_MEMBER(TP))
    {
        write("A powerful magic field prevents you from ascending the stairs.\n");
        return 1;
    }
    
    if (IS_TUVALE(TP)) {
        write("You are not yet worthy of entering the upper levels of the Tower.\n");
        return 1;
    }


    write("Welcome home, "+TP->query_morgul_title()+"!\n");
    return 0;
}

public void 
create_morgul_tower_room()
{
    set_level(2);
    set_room_type("staircase");
    set_extra_long("There is a spiral staircase running up and " +
        "down here, and a dark passage leads north.");

    add_walls();
    add_no_roof();
    add_floor();
    add_staircase();

    add_exit(MORGUL_ROOM_DIR + "tower_2n", "north", 0, 1);
    add_exit(MORGUL_ROOM_DIR + "tower_2e", "east",  0, 1);
    add_exit(MORGUL_ROOM_DIR + "tower_2s", "south", 0, 1);
    add_exit(MORGUL_ROOM_DIR + "tower_2w", "west",  0, 1);
    add_exit(MORGUL_ROOM_DIR + "tower_3c", "up",    block_strangers, 4);
    add_exit(TOWER_DIR  + "tower_1c",       "down",  0, 2);
}

