/*
 * rs3x2.c
 *
 * Rocky shore  -  03 x 02
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
    set_height_above_ocean("twenty");

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

    generate_path("east",
                  "Having climbed onto a shelf going east, the " +
                  "path flattens a little and becomes easier to " +
                  "climb.");
    generate_cliffs();
    
    set_short("narrow path overlooking the Bay of Balifor");
    set_long(show_me_long_desc);

    // Other possible exits:
    set_climb_dirs(({ 1, 0 }),
        ({ "rsc3x2",
           "A near vertical drop prevents you from climbing down " +
           "that way.\n" }));

    add_exit(RSROOMS + "rs4x1", "northeast", descend_path, 2);
    add_exit(RSROOMS + "rs4x2", "east", ascend_path, MOUNT_FATIGUE);

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
    write("Climbing the narrow path you head east up the cliff.\n");

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
        "northeast. After a few meters, the path turns east onto " +
        "a lower shelf.\n");

    return 0;
}

