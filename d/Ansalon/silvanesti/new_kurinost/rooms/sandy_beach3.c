/*
 * sandy_beach3.c
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
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

// I N H E R I T E D   F I L E S
inherit BEACHBASE;

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S
public string show_the_sand();
public string show_cracks();

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
        "you, washing the grey sand. You are at the base of a " +
        "tall cliffside that blocks any movement towards the " +
        "south. You can head back north along the beach from " +
        "here.");
    
    set_short("small and narrow beach");
    set_long(show_me_long_desc);

    add_tell("Distant thunder is carried through the cove, as " +
        "giant waves crash on the rocky shore further out.\n");

    add_item(({ "cove", "sheltered cove", "giant pillars",
        "pillars" }), "Distant thunder is carried through the " +
        "cove, as the large ocean waves crash onto the rocky " +
        "shore further out. Giant pillars of granite protect this " +
        "beach from the wild ocean, creating a sheltered cove, " +
        "where the water is calm.\n");

    remove_item("cliffs");
    add_item(({ "cliff", "cliffs", "steep cliff", "steep cliffs",
        "dark wall", "wall", "granite wall", "cliffside" }),
        "Rising like a dark grey wall that reaches almost a " +
        "hundred meters towards the sky in some places, the steep " +
        "granite cliffs of the coast are almost barren with only " +
        "a few small bushes and cactus plants growing on the " +
        "cliffside. Rising nearly twenty meters into the air " +
        "right next to you is a barren and very steep cliffside " +
        "with some large cracks at the base.\n");
    add_item(({ "crack", "cracks", "large crack", "large cracks",
        "base", "dark cave", "cave" }), show_cracks);
    
    add_exit(RSROOMS + "sandy_beach2", "north", 0, 5);
    add_invis_exit(RSROOMS + "rs_cave", "southwest", "@@enter_cave");

    setup_tells();
    KURINOSTMAP;

    reset_room();
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


/*
 *  FUNCTION : show_cracks
 *  Arguments: none
 *  Returns  : string - the description
 * 
 *  Returns a description of the cliffside.
 *
 */
public string
show_cracks()
{
    TP->add_prop(RSCAVEFOUND, 1);

    return "Looking closer at the large cracks, you notice that " +
        "one of them leads into a dark cave. You can enter it by " +
        "going southwest from here.\n";
}

int
enter_cave()
{
    // Anyone can walk into the cave, but they still have to
    // examine the cracks to find the exit.

    if(!TP->query_prop(RSCAVEFOUND))
    {
        write("You walk aimlessly in to the cliff. Ooof.\n");
        return 1;
    }

    say(QCTNAME(TP) + " walks to the face of the cliff and " +
        "squeezes through a crack, entering the darkness beyond.\n");

    write("Walking to the base of the cliff, you squeeze through " +
        "the crack and enter the darkness beyond.\n");

    return 0;
}

