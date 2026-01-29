/*
 *  /d/Gondor/guilds/rangers/north/exit.c
 *
 *  A secret tunnel in the North Hideout.
 *
 *  Coded by Alto, 16 July 2001
 *  Updated Tigerlily, March 8, 2004 to move cmds
 *          to add_action functions
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

#define RANGER_WAS_STEALTHY          "_ranger_was_stealthy"
#define RANGER_WAS_MASKED            "_ranger_was_masked"
#define RANGER_I_PEEKED_EXIT         "_ranger_i_peeked_exit"

public string      long_desc();
public int         exit_descend(string str);
public int         move_ranger(object who);
public int         exit_hideout(string str);
public int         move_outside(object who);
public int         peek_hatch(string str);

public string
long_desc()
{
    return "You are at the top of a small ladder somewhere beneath " 
        + "the ruins of Fornost. Set into the west wall is an iron "
        + "torch stand from which a warm flickering light plays "
        + "off the walls, floor and ceiling. There is a large " 
        + "wooden hatch directly above you.\n";
}

void
create_gondor()
{
    set_short("atop a small ladder");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "tunnel"}), &long_desc());
    add_item(({"walls"}), "There are two primary walls in the room, the "
        + "west wall and the east wall.\n");
    add_item(({"west wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The west wall is unadorned save the "
        + "iron torch stand mounted upon it.\n");
    add_item(({"east wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. Mounted on the east wall is a small "
        + "ladder. You are standing on top of it.\n");
    add_item(({"ladder", "small ladder", "wooden ladder"}), "A sturdy wooden "
        + "ladder is mounted against the east wall, leading down into a "
        + "tunnel. You could reach the tunnel by descending the ladder.\n");
    add_item(({"hatch", "wooden hatch", "large hatch"}), "This is a large "
        + "hatch made of sturdy wood. A latch is affixed to one side "
        + "opposite several well-oiled hinges on the other. You can open "
        + "the latch by turning it. You also notice a very tiny gap where "
        + "the latch mounts onto the hatch.\n");
    add_item(({"gap", "tiny gap", "very tiny gap"}), "The casual eye would "
        + "miss this tiny gap where the latch is affixed to the hatch. You "
        + "realize it might be useful to squint through the gap at the "
        + "outside environment to make sure the coast is clear.\n");
    add_item(({"latch"}), "You could open the hatch by turning it.\n");
    add_item(({"hinge", "hinges"}), "The brass hinges have been well-oiled "
        + "so that the hatch will open with almost no noise.\n");
    add_item(({"torch", "torch stand", "stand"}), "The iron torch "
        + "stand contains a lit torch that sheds light in the "
        + "room.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

}


public int
exit_descend(string str)
{
    object tp = this_player();
    
    if (str != "ladder")
    {
        notify_fail("Descend ladder?\n");
        return 0;
    }

    write("You quickly descend the small ladder.\n");
    say(QCTNAME(tp) + " quickly descends the small ladder.\n");
    set_alarm(1.0, 0.0, &move_ranger(tp));        
    return 1;
}

public int
move_ranger(object who)
{
    say(QCTNAME(who) + " leaves climbing down the small ladder.\n");
    who->move_living("M", RANGERS_NOR_DIR + "tunnel_f", 1, 0);
    tell_room(environment(who), QCTNAME(who) + " arrives climbing " +
        "down the small ladder.\n", who);
    return 1;
}

public int
exit_hideout(string str)
{
    object tp = this_player();

    if (str != "latch")
    {
        notify_fail("Turn latch?\n");
        return 0;
    }

    if (tp->query_prop(RANGER_I_PEEKED_EXIT))
    {
        write("You turn the latch and open the sturdy hatch.\n");

        say(QCTNAME(tp) + " turns the latch "
            + "and opens the sturdy hatch.\n");

        tp->remove_prop(RANGER_I_PEEKED_EXIT);
        set_alarm(1.0, 0.0, &move_outside(tp));        
        return 1;
    }

    notify_fail("Maybe you should squint through the gap " +
        "and see if anyone is there before you leave.\n");
    return 0;
}

public int
move_outside(object who)
{
    object mcloak = present("_mottled_cloak_", who);

    say(QCTNAME(who) + " leaves quietly through the sturdy hatch.\n");
    if (who->query_prop(RANGER_WAS_STEALTHY))
    {
        who->remove_prop(RANGER_WAS_STEALTHY);
        if (!who->query_autosneak())
            who->set_autosneak(1);
        write("You prepare to move stealthily again as you were "
            + "when you entered the Arnor hideout.\n");
    }


    if (objectp(mcloak->query_worn()) &&
        who->query_prop(RANGER_WAS_MASKED))
    {
        if (!who->query_prop("_rangers_incognito"))
            who->command("$hood myself");
        who->command("$mask myself");
        who->command("$pin cloak");
    }
    who->move_living("M", FORNOST_DIR + "outer_wall", 1, 0);
    return 1;
}

public void
init()
{
    ::init();
    add_action(&peek_hatch(), "squint");
    add_action(&exit_descend(), "descend");
    add_action(&exit_hideout(), "turn");

}

public int
peek_hatch(string str)
{
    object *items, out;
    object tp = this_player();
    string outside, surroundings;

    if (!strlen(str))
    {
        notify_fail("Squint through what?\n");
        return 0;
    }

    switch (str)
    {
    case "gap":
    case "through gap":
    case "through the gap":
        outside = ARNOR_DIR + "fornost/outer_wall";
        outside->teleledningsanka();
        out = find_object(outside);
        if (objectp(out))
        {
            items = FILTER_CAN_SEE(all_inventory(out), TP);
            surroundings = out->long();
        }
        else
        {
            items = ({});
            surroundings = "Shadow obscures the area outside, " + 
                "making it difficult to see.\n";
        }


        if (sizeof(items)) 
        {
            if (sizeof(FILTER_DEAD(items)))
               surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n";
            if (sizeof(FILTER_LIVE(items)))
               surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n";
        }

        tp->add_prop(RANGER_I_PEEKED_EXIT, 1);
        write("You squint through the tiny gap beside the "
            + "latch.\nThis is what you see:\n\n" + surroundings
            + "\nYou quickly lean back again so that you do not "
            + "reveal the entryway.\n");
        say(QCTNAME(tp) + " squints through "
            + "the tiny gap beside the latch.\n");
        return 1;

    default:
        notify_fail("What do you want to squint through? The gap?\n");
        return 0;
    }
}
