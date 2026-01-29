/*
 * rs4x4.c
 *
 * Rocky shore  -  04 x 04
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
    set_height_above_ocean("fifty");

    // Always put a random bush or cactus here. Bush = 1, cactus = 2.
    add_vegetation(random(2) + 1);

    generate_path("northwest", 
                  "Turning northwest, following the side of the " +
                  "cliff, the path gradually becomes steeper and " +
                  "harder to climb.");
    generate_cliffs();
    
    set_short("narrow path on the side of a cliff overlooking the Bay " +
        "of Balifor");
    set_long(show_me_long_desc);

    // Other possible exits:
    set_climb_dirs(({ 0, 1 }),
        ({ "Being much too steep, the cliff seems impossible to " +
           "climb here.\n",
           "rsc4x4" }));

    add_exit(RSROOMS + "rs5x4", "east", descend_path, 2);
    add_exit(RSROOMS + "rs3x3", "northwest", ascend_path, MOUNT_FATIGUE);

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
    write("Climbing the narrow path you head northwest up the cliff.\n");

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
        "east.\n");

    return 0;
}

