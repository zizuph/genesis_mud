/*
 * rs2x5.c
 *
 * Rocky shore  -  02 x 05
 * Path on the rocky shore climbing towards a narrow pass.
 *
 * Copyright (C): Kellon, december 2010
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit SHOREBASE;

// G L O B A L   V A R S

// P R O T O T Y P E S
public int ascend_path();
public int descend_path();

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: None
 *  Returns  : Void
 * 
 *  create_room function that sets up descriptions and exits.
 *
 */
public void
create_kurinost_room()
{
    set_height_above_ocean("seventy");

    // No vegetation inside the pass.
    add_vegetation(0);

    generate_path("south",
        "Tall granite cliffsides surround the narrow path on both " +
        "sides now. Walking south takes you on the final incline, " +
        "up through the pass at the top of the cliffs.");

    generate_cliffs();
    
    set_short("Narrow path");
    set_long(show_me_long_desc);

    remove_item("pass");
    add_item("pass", "Rising above you on both sides of the " +
        "narrow path, the cliffs now form a pass through the top " +
        "of the cliffside. Though you are unable to see far " +
        "through the pass, you guess that this is the highest " +
        "part of the path.\n");

    // Other possible exits:
    set_climb_dirs(({ 0, 0 }),
        ({ "Being much too steep, the cliff seems impossible to " +
            "climb here.\n",
            "There is no way to climb down from here. Turning away " +
            "from the coast, the narrow path is now surrounded by " +
            "tall cliffs on both sides.\n" }));

    add_exit(RSROOMS + "rs1x4", "northwest", descend_path, 2);
    add_exit(RSROOMS + "rs2x6", "south", ascend_path, MOUNT_FATIGUE);

    setup_tells();

    reset_room();
}


/*
 *  FUNCTION : ascend_path
 *  Arguments: none
 *  Returns  : int - 0, always allow move.
 * 
 *  Called when you climb up the path. Show additional description
 *  of the path.
 *
 */
public int
ascend_path()
{
    write("Climbing the final short incline, you walk south " +
        "and quicly enter the pass at the top of the cliffside.\n");

    return 0;
}


/*
 *  FUNCTION : descend_path
 *  Arguments: none
 *  Returns  : int - 0, always allow move.
 * 
 *  Called when you walk down the path. Show additional description
 *  of the path.
 *
 */
public int
descend_path()
{
    write("Following the narrow path, you climb down towards the " +
        "northwest.\n");

    return 0;
}

