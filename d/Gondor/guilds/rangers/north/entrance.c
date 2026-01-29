/*
 *  /d/Gondor/guilds/rangers/north/entrance.c
 *
 *  A secret tunnel in the North Hideout.
 *
 *  Coded by Alto, 16 July 2001
 *  Updated long and add_actions, Tigerlily--March 9, 2004
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

#define RANGER_I_PEEKED "_ranger_i_peeked"
#define RANGER_WAS_STEALTHY "_ranger_was_stealthy"
#define RANGER_WAS_MASKED   "_ranger_was_masked"

public string      long_desc();
public int         peek_hatch(string str);
public int         enter_hideout(string str);
public int         exit_cave(string str);

string
long_desc()
{
    return "You are standing in a small cellar somewhere among the "
        + "ruins of Fornost. An iron torch stand is mounted "
        + "providing some small amount of light. The entrance "
        + "to the cellar is blocked by a dense thicket of bushes. "
        + "You notice that the ground beneath your feet "
        + "is surprisingly dry and smooth.\n";
}

void
create_gondor()
{
    set_short("a cellar behind some bushes");
    set_long(&long_desc());

    add_item(({"cellar", "room"}), &long_desc());
    add_item(({"wall", "walls"}), "The walls of the cellar are smooth "
        + "and unadorned, save for the iron torch stand.\n");
    add_item(({"ground", "floor"}), "On closer inspection, you see a small "
        + "wooden hatch set into the floor. It is hard to see, because it "
        + "is mounted flush with the surface of the floor, and has a "
        + "recessed handle.\n");
    add_item(({"hatch", "wooden hatch", "small hatch"}), "The small hatch "
        + "is mounted flush with the surface of the floor. You might be "
        + "able to open it by turning the handle.\n");
    add_item(({"handle", "handle on hatch"}), "A small iron handle is "
        + "attached to the center of the hatch. It looks like it could be "
        + "turned.\n");
    add_item(({"bushes", "thicket", "bush"}), "The bushes blocking the "
        + "cellar appear impassable at first glance, but you think you see "
        + "a way to squeeze through them. You also notice a very tiny gap "
        + "through which a small amount of light passes.\n");
    add_item(({"gap", "tiny gap", "very tiny gap"}), "The casual eye would "
        + "miss this tiny gap in the thicket of bushes. You "
        + "realize it might be useful to squint through the gap at the "
        + "outside environment to make sure the coast is clear.\n");
    add_item(({"torch", "torch stand", "stand"}), "The iron torch "
        + "stand contains a lit torch that sheds light in the "
        + "room.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_M_NO_SCRY, 1);

}


int
exit_cave(string str)
{
    object tp = this_player();

    if (str != "through bushes")
    {
        notify_fail("Squeeze through bushes?\n");
        return 0;
    }

    if (tp->query_prop(RANGER_I_PEEKED))
    {

        tell_room(environment(tp), QCTNAME(tp) + " squeezes through "
            + "the dense bushes.\n", tp);
        tp->move_living("M", FORNOST_DIR + "l_building", 1, 0);
        write("You squeeze through a gap between the bushes.\n");
        tell_room(environment(tp), QCTNAME(tp) + " enters " +
            "from the bushes.\n", tp);
        tp->remove_prop(RANGER_I_PEEKED);
        return 1;
    }

    write("Why don't you squint through the gap and " + 
        "make sure nobody's there first?\n");
    return 1;
}


int
enter_hideout(string str)
{
    object tp = this_player();

    if (str != "handle")
    {
        notify_fail("Turn handle?\n");
        return 0;
    }

    // check for valid ranger entrance
    if (check_ranger(1) != 0)
    {
        notify_fail("The handle jams and will not turn.\n");
        return 0;
    }

    write("You turn the handle and open the small hatch.\n"
        + "Quietly, you slip beneath the hatch and drop through "
        + "momentary darkness.\n");
    tell_room(environment(tp), QCTNAME(tp) + " turns the handle "
        + "and opens the small hatch.\n", tp);
    say(QCTNAME(tp) + " drops quietly through the small hatch, which "
        + "immediately closes again.\n");
    tp->move_living("M", RANGERS_NOR_DIR + "n_corridor", 1, 0);
    tell_room(environment(tp), QCTNAME(tp) + " drops down "
        + "through a small hatch in the ceiling, which immediately "
        + "closes again.\n", tp);

    if (tp->query_autosneak())
    {
        tp->set_autosneak(0);
        write("You stop being stealthy as you enter the halls "
            + "of the Arnor hideout.\n");
        tp->add_prop(RANGER_WAS_STEALTHY, 1);
    }

    // remove hood in ranger hideout
    if (tp->query_prop("_rangers_mask_closed"))
    {
        tp->add_prop(RANGER_WAS_MASKED, 1);
        tp->command("$unpin cloak");
        tp->command("$unmask me");
    }
     return 1;


    
}


public void
init()
{
    ::init();
    add_action(&peek_hatch(), "squint");
    add_action(&exit_cave(), "squeeze");
    add_action(&enter_hideout(), "turn");
}

/* directory path to be determined */
int
peek_hatch(string str)
{
    object actor, *items;
    string outside, surroundings;

    if (!strlen(str))
    {
        notify_fail("Squint through what?\n");
        return 0;
    }

    actor = TP;

    switch (str)
    {
    case "gap":
    case "through gap":
    case "through the gap":
        outside = ARNOR_DIR + "fornost/l_building";
        outside->teleledningsanka();
        if (!objectp(find_object(outside)))
        {
            surroundings = "Shadows obscure the view " +
                "and prevent you from seeing the surroundings.\n";
            return 1;
        }
        surroundings = (find_object(outside))->long();

        items = FILTER_CAN_SEE(all_inventory(find_object(outside)), actor);

        if (items) 
        {
            if (sizeof(FILTER_DEAD(items)))
                surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n";
            if (sizeof(FILTER_LIVE(items)))
                surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n";
        }

        actor->add_prop(RANGER_I_PEEKED, 1);
        actor->catch_tell("You squint through the tiny gap in the "
            + "bushes.\nThis is what you see:\n\n" + surroundings
            + "\nYou quickly lean back again so that you do not "
            + "reveal yourself.\n");
        tell_room(environment(actor), QCTNAME(actor) + " squints through "
            + "the tiny gap in the bushes.\n", actor);
        return 1;

    default:
        notify_fail("What do you want to squint through? The gap?\n");
        return 0;
    }
}
