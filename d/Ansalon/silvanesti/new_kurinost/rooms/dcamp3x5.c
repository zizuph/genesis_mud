/*
 * dcamp3x5.c
 *
 * Draconian camp  -  03 x 05
 *
 * Copyright (C): Kellon, august 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit CAMPBASE;

// G L O B A L   V A R S
object mob1, mob2, mob3, mob4;
object *gMlist = ({ mob1, mob2, mob3, mob4 });

#define TENT_NUMBER "_kurinost_outpost_tent"

// P R O T O T Y P E S
public int enter_tent();

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : reset_kurinost_room
 *  Arguments: None
 *  Returns  : Void
 * 
 *  reset_room functions, create draconians.
 *
 */
public void
reset_kurinost_room()
{
    for (int ct = 0; ct < 4; ct++)
    {
        // First mob is always here and always a Sivak!
        if (ct == 0 && !gMlist[0])
        {
            gMlist[0] = clone_object(RSLIVING + "sivak_leader");            
            gMlist[0]->move(TO);

            tell_room(TO, "Exiting a crude grey tent, " +
                QNAME(gMlist[0]) + " arrives.\n", gMlist[0],
                gMlist[0]);
        }
        else
        // If mob does not exist and 90% chance, then clone new mob!
        if (!gMlist[ct] && random(10))
        {
            gMlist[ct] = choose_mob();
            gMlist[ct]->move(TO);

            switch (random(4))
            {
                case 0:
                    tell_room(TO, "Exiting one of the crude grey " +
                        "tents, " + QNAME(gMlist[ct]) +
                        " arrives.\n", gMlist[ct], gMlist[ct]);
                    break;

                case 1:
                    tell_room(TO, "Opening the flap of a tent, " +
                        QNAME(gMlist[ct]) + " arrives to stand " +
                        "guard near the campfire.\n", gMlist[ct],
                        gMlist[ct]);
                    break;

                case 2:
                    tell_room(TO, "Staring darkly at you, " +
                        QNAME(gMlist[ct]) + " arrives to stand " +
                        "guard outside the tents.\n", gMlist[ct],
                        gMlist[ct]);
                    break;

                case 3:
                default:
                    tell_room(TO, "Scampering out of a tent, " +
                        "throwing the tentflap aside, " +
                        QNAME(gMlist[ct]) + " arrives, " +
                        "brandishing its weapons.\n", gMlist[ct],
                        gMlist[ct]);
            }
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
    // Set up basic camp descriptions.
    generate_camp(DCAMP_TENTCAMP,
        "You have come as far west as you can on this paved path. " +
        "From the middle of this small camp of tents, you are " +
        "quite close to the slender white tower that rises out of " +
        "the shadow above you, some fifteen meters north of here.");

    // Set up descriptions about the paved path.
    generate_path("east, back towards the southern entrance to " +
        "the encampment.");

    set_short("southwestern corner of a shady encampment");
    set_long(show_long_desc);

    add_cmd_parse("[the] / [a] [crude] [grey] 'tent'",
        ({ "enter", "open" }), enter_tent);

    add_exit(RSROOMS + "dcamp4x5", "east");
    add_exit(RSROOMS + "dtent3x5", "tent", enter_tent);

    setup_tells();
    KURINOSTMAP;

    reset_room();
}

/*
 *  FUNCTION : enter_tent
 *  Arguments: None
 *  Returns  : int - Are we allowed to enter the tent?
 *              1 - No passage, blocked by a draconian!
 *              0 - You can enter!
 * 
 *  Try to enter a tent.
 *
 */
public int
enter_tent()
{
    string dratext = ONE_OF(({
        "say Hey! Get out of that tent! Get lost before I kill you!",
        "say Hey! Get lost or you will die!",
        "say Get lost scum! You are not getting inside that tent!",
        "say Get out of there you stiking pile of trash!" }));

    string gobtext = ONE_OF(({
        "say Oi! Yoo get it out! My tent!",
        "say Yoo git out! Lots hurt yoo!",
        "say Oi! Git out o my tent!",
        "say Oi'll kill yoo! Git lost or me eat yoo!" }));

    string stext;
    int ct = 0;

    while (ct < 4)
    {
        if (objectp(gMlist[ct]))
        {
            if (gMlist[ct]->query_race_name() == "draconian")
            {
                stext = dratext;
            }
            else
            {
                stext = gobtext;
            }

            gMlist[ct]->command(stext);
            return 1;
        }

        ct++;
    }

    if(TP->query_prop(TENT_NUMBER) == 3)
    {
        write("Opening the flap you step inside the open tent and search " +
            "it thoroughly, finding a blank piece of parchment!\n");
        say(QCTNAME(TP) + " opens the flap of one of the small crude tents " +
            "and searches it thoroughly, finding a blank piece of " +
            "parchment!\n");

        object parchment = clone_object(RSOBJS + "dc_document_blank");
        parchment->move(TP, 1);
        TP->remove_prop(TENT_NUMBER);
        return 1;
    }

    say(QCTNAME(TP) + " opens the flap of one of the small crude " +
        "tents and steps inside briefly, but doesn't find anything of " +
        "interest.\n");

    write("Opening the flap you step inside the open tent and briefly " +
        "explore it, however do not find anything of interest.\n");

    return 1;
}

