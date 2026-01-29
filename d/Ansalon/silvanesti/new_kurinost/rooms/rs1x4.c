/*
 * rs1x4.c
 *
 * Rocky shore  -  01 x 04
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
    set_height_above_ocean("fiftyfive");

    // Always put a random bush or cactus here. Bush = 1, cactus = 2.
    add_vegetation(random(2) + 1);

    generate_path("southeast",
        "Approaching the pass through the cliffs, the narrow path " +
        "climbs towards the final part southeast from here.");

    generate_cliffs();
    
    set_short("narrow path high up on the cliffs overlooking the Bay " +
        "of Balifor");
    set_long(show_me_long_desc);

    // Other possible exits:
    set_climb_dirs(({ 0, 0 }),
        ({ "Being much too steep, the cliff seems impossible to " +
           "climb here.\n",
           "A near vertical drop prevents you from climbing down " +
           "that way.\n" }));

    remove_item("pass");
    add_item("pass", "Barely visible on the top of the cliff, it " +
        "seems the path leads south through a small pass in the " +
        "cliffs. Having climbed all the way towards the top of " +
        "the cliff, you are close to the pass.\n");

    add_exit(RSROOMS + "rs1x2", "northwest", descend_path, 2);
    add_exit(RSROOMS + "rs2x5", "southeast", ascend_path, MOUNT_FATIGUE);

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
    write("Climbing the towards the final part of the narrow " +
        "path, you head southeast up the cliff.\n");

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
        "northwest. After a few meters, the path turns northeast " +
        "and approaches a sharp turn.\n");

    return 0;
}

