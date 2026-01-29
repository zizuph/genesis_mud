/*
 * wishingwell.c
 *
 * Used in nyreese/orc_road3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Changed throw to toss, due to changes in driver. Damaris 01/2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <language.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

mapping tried;
int totalsum;
int winners;
int jackpot;

void givep(int amount, object tp);

void
reset_well()
{
    winners = 0;
    jackpot = !random(10);
    tried = ([]);
}

void
create_object()
{
    if (!IS_CLONE)
        return;

    set_short("wishing well");
    set_name("well");
    set_adj("wishing");
    set_long("This is a wishing well, or at least that's what the " +
             "sign on it claims. Perhaps you should throw some " +
             "coins in it and see for yourself.\n");

    add_item("sign", "The sign says: Ye olde wishing well.\n");
    add_cmd_item("sign", "read", "Ye olde wishing well.\n");

    add_prop(OBJ_I_NO_GET, "It's way too heavy!\n");
    add_prop(CONT_M_NO_INS, "Maybe you should try throwing it?\n");
    add_prop(CONT_I_IN, 1);

    totalsum = 0;

    reset_well();
}

void
init()
{
    ::init();
    add_action("throw", "throw");
    add_action("climb", "climb");
    add_action("enter", "enter");
}

int
climb(string s)
{
    NF("Climb what?\n");
    if (!s) return 0;

    if (!parse_command(s, TO,
                      "[in] [into] [the] [wishing] 'well'"))
        return 0;

    write("Climbing into the wishing well is no good idea.\n");
    return 1;
}

int
enter(string s)
{
    NF("Enter what?\n");
    if (!s) return 0;

    if (s != "well" && s != "wishing well")
        return 0;

    write("Entering the wishing well is no good idea.\n");
    return 1;
}

int
toss(string s)
{
    string apa, bepa;
    object ob, *obs;
    int amount, stat, val;
    mixed pob;

    NF("You toss yourself around a little, but decide against it " +
       "when you almost fall into the well.\n");
    if (!s)
        return 0;

    if (s == TP->query_real_name())
    {
        NF("And how do you think you could do that ?\n");
        return 0;
    }

    NF("I don't really understand you...\n");
/*    if (!parse_command(s, TO,
                       "%w %w 'coin' / 'coins' 'in' / 'into' [the] [wishing] 'well'",
                       apa, bepa))
                       {*/
    if (!parse_command(s, TP, "%i 'in' / 'into' [the] [wishing] 'well'", pob))
        return 0;

    obs = NORMAL_ACCESS(pob, 0 , 0);
    ob = obs[0];

    NF("That is too large to fit in the well.\n");
    if (living(ob))
        return 0;
    NF("You can't do that.\n");
    if (ob->query_prop(OBJ_I_NO_DROP))
        return 0;

    if (!ob->id("coin"))
    {
        write("Your " + ob->query_name() +
              " sinks to the bottom and disappears.\n" +
              "Nothing else seems to happen.\n");
        say(QCTNAME(TP) + " tosses something in the well.\n");
        ob->remove_object();
        return 1;
    }

    amount = ob->query_prop(OBJ_I_VALUE);

    if (!amount)
    {
        write("Thought that would work, did you?\n");
        say("The well kicks " + QTNAME(TP) + " in the stomach.\n");
        return 1;
    }

    write("You toss " + ob->short() + " into the well.\n");
    say(QCTNAME(TP) + " tosses some coins in the well.\n");

    ob->force_heap_split();
    ob->remove_object();

    totalsum += amount;

    //    tell_room("/d/Roke/gresolle/workroom", "*pling*\n");
    set_alarm(15.0, 0.0, &givep(amount, TP));
    return 1;
}

void
givep(int amount, object tp)
{
    string name;
    if (!tp || ENV(tp) != ENV(TO))
        return;

    name = tp->query_real_name();

    // More winners gives less chance
    if (random(5 + 5*winners) < 2)
    {
        if (!tried[name])
            tried[name] = 1;
        tp->catch_msg("Nothing seems to happen.\n");
        return;
    }

    if (tried[name] > 1)
    {
        tp->catch_msg("You feel that the well won't give you more today.\n");
        return;
    }
    // A player only gets a jackpot on the first try
    if (!tried[name] && jackpot)
    {
        amount *= 10;
        jackpot = 0;
    }

    winners++;
    tp->catch_msg("You feel your pockets fill with money!\n");
    tried[name] = 2;

    MONEY_MAKE_CC(amount * 2)->move(tp);
    totalsum -= amount * 2;
}
