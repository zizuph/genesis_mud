/*
 * rs2x6.c
 *
 * Rocky shore  -  02 x 06
 * Inside the narrow pass on top of the coastal cliffs.
 *
 * Copyright (C): Kellon, June 2013
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
    set_height_above_ocean("seventy");

    // No vegetation inside the pass.
    add_vegetation(0);

    add_item(({ "path", "narrow path", "small path",
        "small narrow path" }), "Sloping gently downhill towards " +
        "the southeast, the small narrow path approaches a " +
        "roughly circular encampment. Peering over the edge, you " +
        "are treated to a spectacular view. Here, some seventy " +
        "meters above the ocean, you can see far in all " +
        "directions.\n");

    generate_cliffs();
    
    set_short("shadowy pass between two cliffs");
    set_long("You stand in a shadowy pass between two steep cliffs. To " +
        "your north you can make out the spectacular view of the shore, " +
        "the Bay of Balifor, while through the pass to your southeast " +
        "you notice a fortified encampment and an immense forest beyond it. " +
        generate_season() + "\n");

    remove_item("shore");
    remove_item("beach");
    remove_item("pillars");
    remove_item("cliffs");
    remove_item("pass");
    add_item(({ "shore", "coast", "shoreline", "beach",
        "small beach", "beaches", "small beaches", "pillars",
        "pillars of granite" }), "From inside the pass you are " +
        "unable to see the coast, but you can certainly hear the " +
        "waves crashing onto the shore far below.\n");

    add_item(({"shadowy pass", "pass"}), "Running between two steep " +
        "cliffs is a narrow pass cloaked in shadows. It leads north " +
        "towards the shore of the Bay of Balifor and southeast towards " +
        "the forest kingdom of the Silvanesti elves.\n");

    add_item(({"cliffs", "two cliffs", "steep cliffs", "granite cliffs",
        "cliff"}),
        "Two steep granite cliffs rise on either side of you, forming " +
        "a shadowy pass that provides passage through the steep cliffs " +
        "of the Bay of Balifor to the northern borders of the elven " +
        "forest kingdom of Silvanesti.\n");

    remove_item("view");
    add_item(({ "view", "spectacular view", "nice view" }),
        "A strong ocean wind tugs at you as you gaze out over " +
        "the cliffs towards the south. Standing on this spot, " +
        "some seventy meters above the ocean, you have a " +
        "spectacular view of an immense forest below the cliffs. " +
        "Only twenty meters from here, though, the narrow path " +
        "leads to a roughly circular encampment, that seems to " +
        "rest in the shadow below the cliffside.\n");

    add_item(({ "forest", "immense forest", "silvanesti", "elven kingdom",
        "kingdom" }), 
        "Stretching like a huge green blanket in all directions except " +
        "north, you have a quite spectacular view of an immense forest " +
        "below the cliffs - the northern borders of the elven kingdom of " +
        "Silvanesti.\n");

    add_item(({ "camp", "encampment", "circular camp",
        "circular encampment", "fortified encampment" }), 
        "Dark smoke from a few " +
        "scattered campfires inside the roughly circular " +
        "encampment does little to light up the place. Nestled " +
        "close to the coastal cliffs, the camp seems to hide " +
        "beneath the cliffside, never getting any light from the " +
        "sun or the moons. Through the shadow of the encampment, " +
        "you estimate that the entire camp is about fourty meters " +
        "across. A crude wooden palisade is guarding the camp and " +
        "the center seems to consist of a large pit. Guarding the " +
        "pass through the cliffs, a slender white tower reaches " +
        "towards the sky.\n");

    add_item(({ "tower", "elven tower", "white tower",
        "slender tower", "slender white tower" }), "Towering " +
        "above the encampment, the slender tower is the only part " +
        "of the camp that reaches high enough to guard the pass " +
        "through the cliffs. At first glance, the tower seemed " +
        "white and perfect, but that might be the fact that it is " +
        "always tall enough to reach the light, whereas the camp " +
        "itself is hidden below the coastal cliffs in eternal " +
        "shadow. Careful examination reveals that the tower is " +
        "greyed from exposure to weather. Ages of disrepair " +
        "has worn down the tower, and it now stands decayed and " +
        "partly broken. Most of the upper part, the roof and " +
        "northern side of the tower has collapsed into a heap at " +
        "the base of the tower, just outside the camp. Reaching " +
        "almost fifteen meters into the air, the tower must have " +
        "been almost double the size before it fell apart.\n");

    add_item(({ "palisade", "crude palisade", "crude wooden palisade",
        "wooden palisade", "wall" }), "Surrounded entirely by a " +
        "crude wooden palisade, the encampment seems well " +
        "protected. Thick wooden beams, some up to five meters " +
        "long, have been dug into the rough ground, side by side. " +
        "Each trunk has been cut at the top, giving it a " +
        "sharpened tip and all the beams seems to have been " +
        "blackened by fire.\n");

    add_item(({ "smoke", "pillars of smoke", "campfire",
        "campfires" }), "Pillars of smoke from a few scattered " +
        "campfires rise slowly above the camp. Though most of the " +
        "smoke rises away from the camp, some of it seems to " +
        "settle like a dark cloud over the camp, and especially " +
        "over the central pit. Surrounded by a simple palisade of " +
        "thick wooden beams, the camp is roughly circular and " +
        "bowl-shaped with a muddy pit in the center. Along the " +
        "northern and sourthern parts of the palisade, crude grey " +
        "tents have been erected into four small camps along the " +
        "path, each group close to a small campfire.\n");


    // Other possible exits:
    set_climb_dirs(({ 0, 0 }),
        ({ "Being much too steep, the cliff seems impossible to " +
           "climb here.\n",
           "There is no way to climb down from here. Turning away " +
           "from the coast, the road is now surrounded by cliffs " +
           "on all sides.\n" }));

    add_exit(RSROOMS + "rs2x5", "north", ascend_path, 2);
    add_exit(RSROOMS + "dcamp5x1", "southeast", descend_path, 2);

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
    write("You leave the pass to the narrow path along running along " +
        "the granite cliffside to your north.\n");

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
    write("Following the narrow path through the pass, you head southeast " +
        "towards the encampment.\n");

    return 0;
}

