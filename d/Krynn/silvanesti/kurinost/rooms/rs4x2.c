/*
 * rs4x2.c
 *
 * Rocky shore  -  04 x 02
 * Path on the rocky shore climbing towards a narrow pass.
 *
 * Copyright (C): Kellon, november 2010
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit SHOREBASE;

// G L O B A L   V A R S

// P R O T O T Y P E S
public int ascend_path();
public int descend_path();
public string show_me_ledge();
public void give_hint(object who);

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : enter_inv
 *  Arguments: object who, object from
 *  Returns  : void
 * 
 *  When a player enters the room, check for properties, then give a hint
 *  if the correct props are found.
 *
 */
public void
enter_inv(object who, object from)
{
    ::enter_inv(who, from);

    // If player has found the ledge elsewhere:
    if (interactive(who) && who->query_prop(LEDGEFOUND))
    {
        // If player has not already been give a hint and we are not currently
        // waiting to give the player a hint, then:
        if (!who->query_prop(LEDGEHINT) && !who->query_prop(LEDGENOTIFY))
        {
            who->add_prop(LEDGENOTIFY, 1);

            // Add an alarm to let the player get a hint.
            set_alarm(2.0, 0.0, &give_hint(who));
        }
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
    set_height_above_ocean("twenty");

    if (!SETVEGETATION)
    {
        add_vegetation(random(2) + 1);
    }
    else
    {
        add_vegetation(0);
    }

    generate_path("southeast",
                  "Turning southeast, following the side of the " +
                  "cliff, the path gradually becomes steeper and " +
                  "harder to climb.");

    generate_cliffs();
    
    set_short("Narrow path");
    set_long(show_me_long_desc);

    // Add the ledge, visible if the player has found it.
    add_item(({ "ledge", "tiny ledge" }), show_me_ledge);

    // Other possible exits:
    set_climb_dirs(({ 0, 0 }),
        ({ "Being much too steep, the cliff seems impossible to " +
           "climb here.\n",
           "A near vertical drop prevents you from climbing down " +
           "that way.\n" }));

    add_exit(RSROOMS + "rs3x2", "west", descend_path, 2);
    add_exit(RSROOMS + "rs5x3", "southeast", ascend_path, MOUNT_FATIGUE);

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
    write("Turning southeast, you follow the narrow path as it " +
        "climbs up the shelf.\n");

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
        "west.\n");

    return 0;
}


/*
 *  FUNCTION : show_me_ledge
 *  Arguments: none
 *  Returns  : string - description of the ledge.
 * 
 *  If the player has found the tiny ledge, describe it here.
 *
 *  ADD: If the player finishes the quest to find the hobgoblin, add
 *       a check for the quest bit also.
 *
 */
public string
show_me_ledge()
{
    if (TP->query_prop(LEDGEFOUND))
    {
        return "Stepping to the very edge of the cliff, you can " +
            "barely make out a small 20 centimeter wide ledge a " +
            "meter below the path. Climbing down to the ledge " +
            "would not be easy. Finding the ledge from here would " +
            "have been near impossible if you had not spotted it " +
            "from higher ground.\n";
    }

    if (TP->query_prop(LEDGESEEN))
    {
        return "Stepping to the very edge of the cliff, you see " +
            "nothing but a steep cliffside with very few handholds " +
            "to use for climbing. Heading down that way would be " +
            "quite dangerous.\n";
    }

    return "You find no ledge.\n";
}


/*
 *  FUNCTION : climb_cliff
 *  Arguments: string - arguments that follow the climb command.
 *  Returns  : int - 1 if command succeeded, 0 if fail.
 * 
 *  Checks if the cliffs are climbable here and handles the climbing
 *  being attempted.
 *  This place you can climb down to a tiny ledge that is invisible
 *  from here, but usable nonetheless.
 *  If the arguments are not exactly as we want it, pass the command
 *  to the shore_base and see if the climb command can be solved
 *  there.
 *
 */
public int
climb_cliff(string arg)
{
    object *people;
    status moved = 0;
    int index;

    if (TP->query_prop(LEDGEFOUND) &&
       (arg == "down to ledge" || arg == "to ledge" || arg == "ledge"))
    {
        write("Lowering yourself over the cliffside, your feet " +
            "quickly catch the ledge below the side. You begin " +
            "edging your way down the ledge and after turning a " +
            "rocky outcropping the ledge widens to a few meters.\n");
        say(QCTNAME(TP) + " lowers " + HIM(TP) + "self down over " +
            "the side of the cliff and seems to stand on " +
            "something about a meter below the path. Edging " +
            HIM(TP) + "self east around a rocky outcropping, " +
            QNAME(TP) + " disappears from sight.\n");

        moved = 1;

        TP->move_living("M", RSROOMS + "ledge1", 1, 0);

        tell_room(RSROOMS + "ledge1", QCTNAME(TP) + " arrives, " +
            "climbing around the outcropping.\n", ({ TP }), TP);
    }

    if (TP->query_prop(LEDGESEEN) &&
       (arg == "down to ledge" || arg == "to ledge" || arg == "ledge"))
    {
        write("Lowering yourself over the cliffside, you search for " +
            "a secure footing. Just as you are about to give up, " +
            "your feet catch a tiny ledge about a meter below the " +
            "path. Slowly, you begin edging your way east down the " +
            "ledge and after turning a rocky outcropping the ledge " +
            "widens to a few meters.\n");
        say(QCTNAME(TP) + " lowers " + HIM(TP) + "self down over " +
            "the side of the cliff and almost seems to slip over " +
            "the edge a few times. Finally, as " + QCTNAME(TP) +
            " is about to give up, " + HE(TP) + " manages to find " +
            "something to stand on. Slowly, " + HE(TP) + " begins " +
            "to edge " + HIM(TP) + "self east along the cliffside " +
            "and passes a rocky outcropping, disappearing from " +
            "sight.\n");

        moved = 1;

        TP->move_living("M", RSROOMS + "ledge1", 1, 0);

        tell_room(RSROOMS + "ledge1", QCTNAME(TP) + " arrives, " +
            "climbing around the outcropping.\n", ({ TP }), TP);
    }

    if (moved)
    {
        // Find all players in this room, except the current player.
        people = FILTER_PLAYERS(all_inventory(TO));       

        if (sizeof(people))
        {
            // If you see someone using this exit, you get a property.
            for (index = 0; index < sizeof(people); index++)
            {
                people[index]->add_prop(LEDGESEEN, 1);
            }
        }

        return 1;
    }

    ::climb_cliff(arg);
}



/*
 *  FUNCTION : give_hint
 *  Arguments: object - player
 *  Returns  : void
 * 
 *  If the player is still in the room, then give a hint
 *  and set a prop.
 *
 */
public void
give_hint(object who)
{
    // Is the player still here after the two second delay?
    if (TO == E(who))
    {
        who->add_prop(LEDGEHINT, 1);
        who->catch_msg("Taking a careful look around, you notice " +
            "that you are in the exact spot you studied earlier " +
            "from a higher vantagepoint on the cliffside. This is " +
            "the place where you found the ledge that you might " +
            "be able to climb down to.\n", 0);
    }

    // We are no longer waiting to notify the player, so remove the
    // prop again.
    who->remove_prop(LEDGENOTIFY);
}

