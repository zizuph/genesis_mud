/*
 * dcamp4x5.c
 *
 * Draconian camp  -  04 x 05
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
object drac1, drac2, drac3, hob1, hob2;

#define DRAC  "/d/Krynn/std/sivak"
#define DRAC2 "/d/Krynn/std/bozak"

void
reset_kurinost_room()
{
     if (!objectp(hob1)) 
     {
         hob1 = clone_object(RSLIVING + "hobgoblin");
         hob1->arm_me();
         hob1->move(TO, 1);
     }

     if (!objectp(hob2)) 
     {
         hob2 = clone_object(RSLIVING + "hobgoblin");
         hob2->arm_me();
         hob2->move(TO, 1);
     }

     if (!objectp(drac1)) 
     {
         drac1 = clone_object(DRAC);
         drac1->set_color("green");
         drac1->move(TO, 1);
     }

     if (!objectp(drac2)) 
     {
         drac2 = clone_object(DRAC2);
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
    generate_camp(DCAMP_BROKENPATH,
        "Standing at the entrance to the camp on the southern side, " +
        "your eyes are drawn to the central depression of the camp " +
        "just below you towards the north.");

    // Set up descriptions about the paved path.
    generate_path("east and west towards two small campsites, " +
        "south out of the camp towards the coast, northeast in a " +
        "circle around the center of the camp and northwest up " +
        "towards the slender white tower.");

    set_short("southern entrance to a dragonarmy encampment");
    set_long(show_long_desc);

    add_exit(RSROOMS + "dcamp4x6", "south", leave_camp);
    add_exit(RSROOMS + "dcamp3x5", "west");
    add_exit(RSROOMS + "dcamp5x5", "east");
    add_exit(RSROOMS + "dcamp2x3", "northwest", ascend_path, 3);
    add_exit(RSROOMS + "dcamp6x3", "northeast", descend_path, 3);

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
        "you head northwest, up towards the slender white tower.\n");

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
    write("Following the narrow path on a gentle downward slope, " +
        "you head northeast in a wide circle around the inside of " +
        "the encampment.");

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
    write("Heading south, you exit through the crude wooden " +
        "palisade and walk out of the camp.\n");

    return 0;
}

