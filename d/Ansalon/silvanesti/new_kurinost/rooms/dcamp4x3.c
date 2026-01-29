/*
 * dcamp4x3.c
 *
 * Draconian camp  -  04 x 03
 *
 * Copyright (C): Kellon, august 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit CAMPBASE;

// G L O B A L   V A R S

// P R O T O T Y P E S
public int ascend_path();
public int mud_path();

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
    // Set up basic camp descriptions.
    generate_camp(DCAMP_MUDDYPIT,
        "Blocking any passage west and south of here is an " +
        "especially large and smelly pile of refuse.");

    // Set up descriptions about the paved path.
    generate_path("east and southeast, further into the mudfilled " +
        "pit, or northeast up towards the rest of the encampment.");

    set_short("muddy refuse pit");
    set_long(show_long_desc);

    add_exit(RSROOMS + "dcamp5x2", "northeast", ascend_path, 5);
    add_exit(RSROOMS + "dcamp5x3", "east", mud_path, 5);
    add_exit(RSROOMS + "dcamp4x4", "southeast", mud_path, 5);

    setup_tells();
    KURINOSTMAP;
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
    write("With a final sucking noise, you practically tear your " +
        "feet out of the wet mud of the pit and start climbing " +
        "the path. Nearly at the top of the short climb, the path " +
        "turns north.\n");

    return 0;
}


/*
 *  FUNCTION : descend_path
 *  Arguments: none
 *  Returns  : int - 0, always allow move.
 * 
 *  Called when you walk through the mud of the pit. Show
 *  additional description of the path.
 *
 */
public int
mud_path()
{
    write("Slosh! Slosh! Tearing your feet out of the wet sucking " +
        "mud with each step, you walk through the pit.\n");

    return 0;
}
