/*
 * dcamp5x2.c
 *
 * Draconian camp  -  05 x 02
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
public int descend_path();
public int leave_camp();

object drac1, drac2, drac3;

#define DRAC "/d/Krynn/std/sivak"

void
reset_kurinost_room()
{
     if (!objectp(drac1)) 
     {
         drac1 = clone_object(DRAC);
         drac1->set_color("green");
         drac1->move(TO, 1);
     }

     if (!objectp(drac2)) 
     {
         drac2 = clone_object(DRAC);
         drac2->set_color("green");
         drac2->move(TO, 1);
     }

     if (!objectp(drac3)) 
     { 
         drac3 = clone_object(RSLIVING + "sivak_leader");
         drac3->set_color("green");
         drac3->move(TO, 1);
     }
}

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
    generate_camp(DCAMP_BROKENPATH,
        "Standing at the entrance to the camp on the northern side, " +
        "your eyes are drawn to the central depression of the camp " +
        "just below you towards the south.");

    // Set up descriptions about the paved path.
    generate_path("east and west towards two small campsites, " +
        "north out of the camp towards the coast, south down into " +
        "the pit and southeast, climbing in a wide circle around " +
        "the center of the camp.");

    set_short("northern entrance to a dragonarmy encampment");
    set_long(show_long_desc);

    add_exit(RSROOMS + "dcamp5x1", "north", leave_camp);
    add_exit(RSROOMS + "dcamp4x2", "west");
    add_exit(RSROOMS + "dcamp6x2", "east");
    add_exit(RSROOMS + "dcamp6x3", "southeast", ascend_path, 3);
    add_exit(RSROOMS + "dcamp4x3", "south", descend_path, 3);

    setup_tells();
    KURINOSTMAP;

    reset_kurinost_room();
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
    write("Following the narrow path on a gentle upward slope, " +
        "you head southeast in a wide circle around the inside of " +
        "the encampment.\n");

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
    write("Walking down the final steps towards the central " +
        "depression of the camp, the path turns southwest. " +
        "With a sucking noise, you step down into the wet " +
        "mudfilled pit.\n");

    return 0;
}


/*
 *  FUNCTION : leave_camp
 *  Arguments: none
 *  Returns  : int - 0, always allow move.
 * 
 *  Called when you walk out of the camp.
 *
 */
public int
leave_camp()
{
    write("Heading north, you exit through the crude wooden " +
        "palisade and walk out of the camp.\n");

    return 0;
}

