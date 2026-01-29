/*
 *  ledge1.c
 *
 *  Rocky shore  -  ledge1.c
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

    // Always put a bush here!
    add_vegetation(1);

    // Do not use generate_path here, instead use:
    set_path_desc("The steep, narrow ledge ends abruptly here and " +
        "it is only possible to go down towards the east.",
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
        "dangerous to travel. The ledge ends here as it grows " +
        "more and more narrow and it only seems possible to go " +
        "down by heading east. You know the path towards the pass " +
        "in the cliffs is just around an outcropping a meter away " +
        "and you can easily climb up to get to the path.\n");
    add_item("outcropping", "Only about a meter away along the " +
        "narrowing ledge, you see the outcropping you climbed to " +
        "get to this overgrown ledge. It would be easy to climb " +
        "up to the path from here.\n");
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
   
    add_exit(RSROOMS + "ledge2", "east", descend_path, 5);

    // Other possible exits:
    set_climb_dirs(({ 1, 0 }),
        ({ "rs4x2",
           "Even though you are only twenty meters above the sea, " +
           "a near vertical drop prevents you from climbing down " +
           "that way.\n" }));

    setup_tells();
    KURINOSTMAP;

    reset_room();
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
        "down towards the east.\n");
    return 0;
}

