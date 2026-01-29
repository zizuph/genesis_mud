/*
 * rs1x2.c
 *
 * Rocky shore  -  01 x 02
 * Path on the rocky shore climbing towards a narrow pass.
 *
 * Copyright (C): Kellon, november 2010
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
    set_height_above_ocean("sixty");

    // 33% chance for a bush/cactus.
    if (!SETVEGETATION)
    {
        // Random bush or cactus. Bush = 1, cactus = 2.
        add_vegetation(random(2) + 1);
    }
    else
    {
        add_vegetation(0);
    }

    generate_path("southwest",
                  "Having climbed up the final shelf, the path " +
                  "turns southwest and later southeast, heading " +
                  "straight towards the pass in the cliffs.");
    generate_cliffs();
    
    set_short("narrow path high up on the cliffs overlooking the Bay " +
        "of Balifor");
    set_long(show_me_long_desc);
    
    add_exit(RSROOMS + "rs2x3", "southeast", descend_path, 2);
    add_exit(RSROOMS + "rs1x4", "southwest", ascend_path, MOUNT_FATIGUE);

    // Other possible exits:
    set_climb_dirs(({ 1, 0 }),
        ({ "rsc1x2",
           "A near vertical drop prevents you from climbing down " +
           "that way.\n" }));

    setup_tells();
    KURINOSTMAP;

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
    write("Climbing the narrow path you head southwest up the " +
        "cliff. After a few meters, the path turns southeast and " +
        "continues steeply towards the approaching pass.\n");

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
        "southeast.\n");

    return 0;
}

