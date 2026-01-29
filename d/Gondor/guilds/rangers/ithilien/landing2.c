/*
 *  /d/Gondor/guilds/rangers/ithilien/landing2.c
 *
 * Modification log:
 * 20-Jul-2001,Alto: tidy up, change inheritance for new
 *                   rangers. Added scanning function.
 * Cotillion - 2020-10-04
 * - Fixed type confusion
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "exit.c"

#define POOL   (RANGERS_ITH_DIR + "pool")

/* Prototypes */
public string  exa_pool();
public int     do_dive(string arg);
public int     scan_here(string str);

/* Global variables */
object gActor, *gItems;
string gEntrance, gExit;


public void
create_gondor()
{
    set_short("At the brink of a wide flat stone");
    set_long("You are standing at the brink of a wide flat stone. The "
        + "stone is wet from the mist rising from the falls. Far below "
        + "you the waters pour into a foaming bowl, then swirling darkly "
        + "about a deep oval basin in the rocks. East you can see the dark "
        + "entrance to the passages. It occurs to you that scanning the "
        + "environment from this high place might be useful.\n");
    add_item(({ "basin", "bowl", "waterfall", "falls", "fall", "torrent",
        "pool", "water", "waters" }), &exa_pool());
    add_item("stone", "The flat stone is wet with mist from the falls.\n");
    add_item("mist", "The mist rises from the falls.\n");
    add_item(({ "passages", "passage", "entrance"}),
        "The entrance to the underground passages is back east.\n");
    add_item(({"terrace", "terraces"}), "The terraces consist of large, "
        + "flat rocks, smoothed by thousands of years of water passing.\n");
    add_exit(RANGERS_ITH_DIR + "landing", "east", &check_ranger());
    add_prop(ROOM_M_NO_SCRY, 1);
}

public void
init()
{
    ::init();
    add_action(do_dive, "dive");
    add_action(do_dive, "enter");
    add_action(scan_here, "scan");

}

public int
do_dive(string arg)
{
    string dest;

    if ( !strlen(arg) )
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if ( !sscanf(arg, "into %s", dest) && !sscanf(arg, "in %s", dest) )
        dest = arg;

    if ( dest == "pool" || dest == "water" || dest == "waters" ||
      dest == "basin" || dest == "bowl" || dest == "waterfall" ||
      dest == "falls" || dest == "fall" || dest == "torrent" )
    {
        write("You are much too high above the water; you would surely "
            + "injure yourself if you dove from here.\n");
        return 1;
    }

    notify_fail(capitalize(query_verb()) + " where?\n");
    return 0;
}

public string
exa_pool()
{
    return("The torrent falls, splashing over many terraces, and then "
        + "pours down a steep race, into a foaming bowl, then swirling darkly "
        + "about in a deep oval basin in the rocks. There the white waters "
        + "find their way out again through a narrow gate, and flow away, "
        + "fuming and chattering, into calmer and more level reaches. "
        + POOL->query_swimmers() + "\n");
}

public int
scan_here(string str)
{
    string target;
    gActor = TP;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "[the] %s", target))
    {
        notify_fail("Scan the environment?\n");
        return 0;
    }

    switch (target)
    {
    case "environment":
    case "crossroads":
        write("From here you can probably scan the western or eastern "
            + "crossroads.\n");
        return 1;

    case "western crossroad":
    case "western crossroads":
    case "west crossroad":
    case "west crossroads":
        gEntrance = "/d/Gondor/ithilien/osgiliath/eosg5";
        gEntrance->teleledningsanka();
        string surroundings = find_object(gEntrance)->long();

        gItems = FILTER_CAN_SEE(all_inventory(find_object(gEntrance)), gActor);

        if (gItems)
        {
            if (sizeof(FILTER_DEAD(gItems)))
                surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(gItems))) + ".\n";
            if (sizeof(FILTER_LIVE(gItems)))
                surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(gItems))) + ".\n";
        }

        gActor->catch_tell("You scan the environment to the southwest of the "
            + "hideout.\nThis is what you see:\n\n"
            + surroundings + "\nYou quickly lean back again so that you "
            + "do not reveal your hiding place.\n");
        tell_room(environment(gActor), QCTNAME(gActor) + " scans the "
            + "environment to the southwest of the hideout.\n",
            ({ gActor }));

        return 1;

    case "eastern crossroad":
    case "eastern crossroads":
    case "east crossroad":
    case "east crossroads":
        gExit = "/d/Gondor/ithilien/road/crossroads";
        gExit->teleledningsanka();
        surroundings = find_object(gExit)->long();

        gItems = FILTER_CAN_SEE(all_inventory(find_object(gExit)), gActor);

        if (gItems)
        {
            if (sizeof(FILTER_DEAD(gItems)))
                surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(gItems))) + ".\n";
            if (sizeof(FILTER_LIVE(gItems)))
                surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(gItems))) + ".\n";
        }

        gActor->catch_tell("You scan the environment to the southeast of "
            + "the hideout.\nThis is what you see:\n\n"
            + surroundings + "\nYou quickly lean back again so that you "
            + "do not reveal your hiding place.\n");
        tell_room(environment(gActor), QCTNAME(gActor) + " scans the "
            + "environment to the southeast of the hideout.\n",
            ({ gActor }));

        return 1;

    default:
        notify_fail("What do you want to scan? The environment?\n");
        return 0;
    }

}

