/*
 * rs6x2.c
 *
 * Rocky shore  -  06 x 02
 * Path on the rocky shore climbing towards a narrow pass.
 *
 * Copyright (C): Kellon, november 2010
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
public string show_me_pillars();
public string show_me_ledge();

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
    set_height_above_ocean("thirty");

    // Always a Cactus here.
    add_vegetation(2);

    generate_path("southeast",
                  "Turning into a sharp and steep bend, the " +
                  "path climbs southeast a while and then turns " +
                  "southwest.");
    generate_cliffs();
    
    set_short("Narrow path");
    set_long(show_me_long_desc);

    remove_item("view");
    add_item(({ "view", "spectacular view" }), "A strong ocean " +
        "wind tugs at you as you gaze out over the sea. Standing " +
        "on this spot, some thirty meters above the ocean, you " +
        "have a spectacular view of the shore with its ragged " +
        "granite pillars and rare sandy beaches. Directly beneath " +
        "you, in a sheltered cove is a small sandy beach.\n");
    remove_item("beach");
    add_item(({ "beaches", "sandy beaches" }),
        "Greyish sand cover the few beaches you can see from " +
        "here. Hidden well beneath pillars of granite, a lot of " +
        "climbing would be needed to reach one of those beaches. " +
        "Directly beneath you, in a sheltered cove is a small " +
        "sandy beach.\n");
    add_item(({ "beach", "sandy beach", "small beach",
        "small sandy beach" }), "Greyish sand cover the small " +
        "beach directly below you. Hidden well in a sheltered " +
        "cove with tall granite pillars guarding the entrance, " +
        "only a few small waves land on the beach. The cliffside " +
        "probably hides the small sandy beach from view " +
        "everywhere along the narrow path, except from this " +
        "place.\n");
    add_item(({ "cove", "sheltered cove" }), "Tall granite " +
        "pillars guard the entrance to a small sheltered cove " +
        "some thirty meters beneath you. Hidden well beneath tall " +
        "cliffsides, the cove seems dark and quiet as only a few " +
        "waves enter the cove and land on the small sandy beach " +
        "down there.\n");
    add_item(({ "pillars", "granite pillars", "tall pillars",
        "tall granite pillars" }), show_me_pillars);
    add_item(({ "ledge", "narrow ledge", "track",
        "small track" }), show_me_ledge);

    // Other possible exits:
    set_climb_dirs(({ 1, 0 }),
        ({ "rsc6x2",
           "A near vertical drop prevents you from climbing down " +
           "that way.\n" }));

    add_exit(RSROOMS + "rs5x3", "southwest", descend_path, 2);
    add_exit(RSROOMS + "rs6x4", "southeast", ascend_path, MOUNT_FATIGUE);

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
    write("Climbing the narrow path you head southeast up the " +
        "cliff. After a while, the path turns southwest and " +
        "climbs steeply onto a new shelf going west.\n");

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
        "southwest.\n");

    return 0;
}


/*
 *  FUNCTION : show_me_pillars
 *  Arguments: none
 *  Returns  : string - description of pillars.
 * 
 *  Based on player tracking skill, returns a description of the
 *  granite pillars 30 meters beneath the player.
 *
 */
public string
show_me_pillars()
{
    string pillar_desc = "Guarding the entrance to a small " +
    	"sheltered cove about 30 meters beneath you, these tall " +
    	"granite pillars reach almost to the height where you are " +
    	"standing. Being a part of a larger rock formation that " +
    	"partially breaks the waves of the ocean, the pillars " +
    	"also steal away much of the light in the cove, " +
        "leaving a small sandy beach shrouded in shadows and " +
        "silence. Marred by millennia of tear and wear from the " +
        "waves of the ocean, the pillars are smooth and rounded " +
        "near the water's edge, while being a bit more ragged " +
        "higher up.";

    // If player skill is GREATER than 11-20. Normal max is 30, so
    // this make it possible for all players who have trained their
    // TRACKING skill.
    if ((TP->query_skill(SS_TRACKING) > (random(10) + 11)) ||
        TP->query_prop(LEDGEFOUND) || TP->query_prop(LEDGESEEN))
    {
        if (TP->query_prop(LEDGESEEN))
        {
            TP->remove_prop(LEDGESEEN);
        }

        TP->add_prop(LEDGEFOUND, 1);

        return pillar_desc + " Barely visible on the northwestern " +
            "cliffside, between the pillars directly below you, " +
            "you notice a narrow ledge that seems to lead from " +
            "the beach up towards the path somewhere to the west " +
            "of your current location.\n";
    }

    return pillar_desc + "\n";
}


/*
 *  FUNCTION : show_me_ledge
 *  Arguments: none
 *  Returns  : string - description
 * 
 *  Returns a description of the ledge far below if it has been
 *  found by the player.
 *
 */
public string
show_me_ledge()
{
    if (TP->query_prop(LEDGEFOUND))
    {
        return "Having spotted the narrow ledge below you, it is " +
            "easy to trace the small track that leads from the " +
            "sheltered cove, up the side of the cliff walls until " +
            "it ends just below the twisting path about 30 meters " +
            "west and 10 meters below you. Someone brave enough " +
            "might climb down to that ledge and try to follow the " +
            "track down to the beach in the cove.\n";
    }

    return "You find no ledge.\n";
}
