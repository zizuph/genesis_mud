/*
 * sandy_beach1.c
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

    generate_beach("Waves crash onto the cliffs beyond this " +
        "sheltered cove, carrying a distant thunder towards you. " +
        "Small waves land gently on the beach a few meters from " +
        "you, washing the grey sand. An overgrown ledge climbs up " +
        "and away towards the southwest and the beach stretches " +
        "away towards the southeast.");
    
    set_short("small and narrow beach");
    set_long(show_me_long_desc);

    add_tell("Distant thunder is carried through the cove, as " +
        "giant waves crash on the rocky shore further out.\n");
  
    add_item(({ "path", "narrow path", "small path",
        "small narrow path", "steep path", "steep narrow path",
        "narrow ledge", "ledge" }), "A small, steep and overgrown " +
        "ledge climbs steeply away from the beach towards the " +
        "southwewst. Only about a meter wide, the ledge seems " +
        "quite dangerous to travel, but it should be possible. " +
        "The narrow ledge turns slightly about ten meters up as " +
        "it follows the cliffside towards the top of the ledge.\n");

    add_item(({ "cove", "sheltered cove", "giant pillars",
        "pillars" }), "Distant thunder is carried through the " +
        "cove, as the large ocean waves crash onto the rocky " +
        "shore further out. Giant pillars of granite protect this " +
        "beach from the wild ocean, creating a sheltered cove, " +
        "where the water is calm.\n");
    
    add_exit(RSROOMS + "sandy_beach2", "southeast", 0, 2);
    add_exit(RSROOMS + "ledge3", "southwest", ascend_path, 5);

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
    write("Leaving the small beach, you climb onto the steep " +
        "narrow ledge. After a short climb, the ledge turns " +
        "towards the west and continues uphill.\n");

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
        "small waves wash calmly onto the beach.\n";
}

