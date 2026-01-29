/*
 * rs_shore.c
 *
 * One of the small beaches you can find near Kurinost.
 *
 * Copyright (C): Kellon, oktober 2012
 *                Poul Erik Jensen
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

// I N H E R I T E D   F I L E S
inherit BEACHBASE;

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S
public int ascend_path();
public string show_the_sand();

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
    // We need to add these items before the rest is generated.
    add_item(({ "beach", "small beach", "sand", "coarse sand",
        "grey sand", "coarse grey sand" }), show_the_sand);

    generate_beach("Thundering waves crash onto the shore about " +
        "ten meters from you, spraying the beach with foam and " +
        "salty water. Jutting out into the stormy sea, barely " +
        "staying above the frothing wavetops, is a long wooden " +
        "pier. Leaving the beach, going southwest and climbing " +
        "steeply towards the top of the cliffs is a small narrow " +
        "path.");
    
    set_short("small and narrow beach");
    set_long(show_me_long_desc);
  
    add_item(({ "path", "narrow path", "small path",
        "small narrow path", "steep path", "steep narrow path",
        "narrow ledge" }), "Going steeply uphill towards the " +
        "southwest, a small narrow path twists and turns its way " +
        "up the side of the cliffside like a great black snake. " +
        "From down here you have a spectacular view of the entire " +
        "cliff.\n");

    add_exit(RSROOMS + "rs5x1", "southwest", ascend_path, 5);
    add_exit(RSROOMS + "kurinost_dock", "north");

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
    write("Leaving the small beach, you start climbing up the " +
        "steep and narrow path, walking slowly up the side of the " +
        "cliffs.\n");

    return 0;
}


/*
 *  FUNCTION : show_the_sand
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  Generates a description of the sand. Maybe there are items
 *  to be found in the sand.
 *
 */
public string
show_the_sand()
{
    string item_desc = show_items();

    return "Small waves wash onto the coarse grey sand of this " +
        "short stretch of the beach. Covered mostly with dark " +
        "grey pebbles, you also notice larger rocks in several " +
        "places on the beach. " + item_desc + "You hear the " +
        "distant thundering of the much larger waves of the ocean " +
        "crash onto the cliffs further out. Here inside the cove, " +
        "only much smaller waves wash calmly onto the beach.\n";
}

