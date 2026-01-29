/*
 *  ledge3.c
 *
 *  Rocky shore  -  ledge3.c
 *  Hidden path on the rocky shore leading down to a sandy beach.
 *
 *  Copyright (C): Kellon, september 2012
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
inherit SHOREBASE;

// G L O B A L   V A R S

// P R O T O T Y P E S
public int descend_path();
public int ascend_path();

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
    set_height_above_ocean("ten");

    // Always put a bush here!
    add_vegetation(1);

    // Do not use generate_path here, instead use:
    set_path_desc("Following the cliffside down towards a small " +
        "beach, the narrow ledge turns slightly here.",
        "In the middle of the thick underbrush, you find a small " +
        "bush.");
    
    generate_cliffs();
   
    set_short("Narrow ledge");
    set_long(show_me_long_desc);

    // Add the items that needs to be changed from the shore_base.
    add_item(({ "path", "narrow path", "small path",
        "small narrow path", "steep path", "steep narrow path",
        "narrow ledge", "ledge" }), "Barely a path at all, you " +
        "are following a small and steep ledge overgrown with " +
        "thick underbrush that seems to lead down towards a small " +
        "beach. Only about a meter wide, the ledge is quite " +
        "dangerous to travel. Turning slightly, the narrow ledge " +
        "follows the cliffside down towards a small beach. " +
        "Heading northwest would take you up towards the top of " +
        "the ledge and east the ledge leads downwards.\n");
    add_item(({ "bend", "turn" }), "Twisting and turning as it " +
        "follows the cliffside down, the small narrow ledge is " +
        "barely passable. Though you can see most of the way " +
        "down, as it runs steeply down towards a small sandy " +
        "beach, it is quite difficult to keep your footing. The " +
        "ledge is overgrown with a thick layer of ferns and small " +
        "shrubby bushes, making it hard to see where to put your " +
        "feet down.\n");
    add_item(({ "underbrush", "ferns" }), "Covering every part of " +
        "this narrow ledge is a thick layer of underbrush made up " +
        "from low shrubby bushes and small ferns. The thick cover " +
        "of underbrush makes it quite difficult to keep your " +
        "footing as it is hard to see where to put your feet down " +
        "safely.\n");

    remove_item("soil");
    add_item(({ "soil", "dirt" }), "Barely visible here and " +
        "there, scattered about on the ledge beneath the thick " +
        "underbrush of ferns and bushes are small patches of " +
        "soil. A nearby bush has grown out of one of these small " +
        "patches of soil.\n");
    remove_item("bushes");
    add_item(({ "bush", "bushes", "small bush", "small bushes",
        "caper bush", "small caper bush" }),
        "Neatly tucked away in a sheltered corner, in the middle " +
        "of the thick underbrush of ferns and other bushes, you " +
        "find a small shrubby bush. This small shrubby caper bush " +
        "has many branches and thick, shiny and ovate shaped " +
        "leaves. Growing out of a nearly invisible patch of soil, " +
        "this plant is known to be able to survive almost " +
        "anywhere. Growing on the branches of this kind of bush, " +
        "are the green flowerbuds known as capers.\n");
    remove_item("beach");
    add_item(({ "beach", "sandy beach", "beaches", "sandy beaches" }),
        "Greyish sand cover the few beaches you can see from " +
        "here. Hidden well beneath pillars of granite, a lot of " +
        "climbing would be needed to reach one of those beaches, " +
        "but this narrow ledge you are on leads steeply down to " +
        "one of the beaches.\n");
   
    add_exit(RSROOMS + "ledge2", "southwest", ascend_path, MOUNT_FATIGUE);
    add_exit(RSROOMS + "sandy_beach1", "east", descend_path, 5);

    // Other possible exits:
    set_climb_dirs(({ 0, 1 }),
        ({ "Being much too steep, the cliff seems impossible to " +
           "climb here.\n",
           "sandy_beach1" }));

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
    write("Being careful to watch your footing, you climb up the " +
        "steep ledge towards the southwest.\n");

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
    write("Following the steep narrow ledge, you climb carefully " +
        "down towards the east. Turning slightly towards the " +
        "northeast, you follow the ledge the final few meters and " +
        "step down onto a small beach.\n");

    return 0;
}

