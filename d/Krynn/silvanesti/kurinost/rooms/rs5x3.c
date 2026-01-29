/*
 * rs5x3.c
 *
 * Rocky shore  -  05 x 03
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
    set_height_above_ocean("twentyfive");

    // Always put a random bush or cactus here. Bush = 1, cactus = 2.
    add_vegetation(random(2) + 1);

    generate_path("east and northeast",
                  "Reaching the end of the shelf, the path " +
                  "approaches another sharp turn east and " +
                  "northeast from here.");
    generate_cliffs();
    
    set_short("Narrow path");
    set_long(show_me_long_desc);

    // Other possible exits:
    set_climb_dirs(({ 1, 0 }),
        ({ "rsc5x4",
           "A near vertical drop prevents you from climbing down " +
           "that way.\n" }));

    add_exit(RSROOMS + "rs4x2", "northwest", descend_path, 2);
    add_exit(RSROOMS + "rs6x2", "east", ascend_path, MOUNT_FATIGUE);

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
    write("Climbing the narrow path you head east up the cliff. " +
        "After a few meters, the path turns northeast and climbs " +
        "into a high turn.\n");

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

