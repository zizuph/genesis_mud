/*
 *  /d/Gondor/guilds/rangers/ambush/ambush_1_top.c
 *
 *  A vantage/ambush point for the rangers
 *    (a room for spying on the environment nearby)
 *
 *  Coded by Alto, 05 August 2001
 *
 *  Modification log:
 *    Gwyneth, 4 May 2004 - Changed so that it inherits a base
 *                          ambush top file.
 */
#include "../rangers.h"
#include "/d/Gondor/defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

inherit RANGERS_AMB_DIR + "ambush_top.c";

void
create_ambush_top()
{
    set_long("You are crouched near a crossing of roads just west of "
        + "the village of Bree. Two small platforms have been lashed "
        + "here so that you may rest during the long hours you may need "
        + "to remain hidden. From here you can scan the crossroads, as "
        + "well as the entrance where you left the road. When you are "
        + "ready to depart, you may <return> to the road or <ambush> "
        + "the crossroads.\n");
    set_ambush_move(RANGERS_AMB_DIR + "ambush_1e");
    set_top_exit("/d/Shire/bree/rooms/road/crossroad");
    set_ambush_desc("crossroads");
    add_prop(ROOM_M_NO_SCRY, 1);

}

int
scan_here(string str)
{
    string target, entrance, exit, surroundings;
    object *items, actor = TP;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "[the] %s", target))
    {
        notify_fail("Scan the environment?\n");
        return 0;
    }

    switch (target)
    {
    case "environment":
        write("From here you can probably scan the crossroads.\n");
        return 1;

    case "crossroads":
    case "crossroad":
         entrance = "/d/Shire/bree/rooms/road/crossroad";
        entrance->teleledningsanka();
        surroundings = find_object(entrance)->long();

        items = FILTER_CAN_SEE(all_inventory(find_object(entrance)), actor);

        if (items)
        {
            if (sizeof(FILTER_DEAD(items)))
               surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n";
            if (sizeof(FILTER_LIVE(items)))
               surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n";
        }

        actor->catch_tell("You carefully examine the crossroads from your "
            + "place of hiding.\nThis is what you see:\n\n"
            + surroundings + "\nYou quickly lean back again so that you "
            + "do not reveal your hiding place.\n");
        tell_room(environment(actor), QCTNAME(actor) + " scans the "
            + "crossroads carefully.\n", actor);

        return 1;

    case "entrance":
        exit = "/d/Gondor/arnor/greenway/nr1";
        exit->teleledningsanka();
        surroundings = find_object(exit)->long();

        items = FILTER_CAN_SEE(all_inventory(find_object(exit)), actor);

        if (items)
        {
            if (sizeof(FILTER_DEAD(items)))
               surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n";
            if (sizeof(FILTER_LIVE(items)))
               surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n";
        }

        actor->catch_tell("You carefully examine the place where you left "
            + "the road.\nThis is what you see:\n\n"
            + surroundings + "\nYou quickly lean back again so that you "
            + "do not reveal your hiding place.\n");
        tell_room(environment(actor), QCTNAME(actor) + " scans the "
            + "road for signs of trouble.\n", actor);

        return 1;

    default:
        NF("What do you want to scan? The crossroads or the entrance?\n");
        return 0;
    }
}

