/*
 * wishingwell.c
 *
 * Used in nyreese/orc_road3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <language.h>
#include <money.h>
#include <macros.h>

#define SAVEFILE ROKEDIR + "obj/well"
int totalsum;
int loosers;

void givep(mixed * mu);

int
query_sum()
{
    return totalsum;
}

void
anka()
{
    seteuid(getuid());
    restore_object(SAVEFILE);
}

void
create_object()
{
    if (!IS_CLONE)
        return;

    set_short("wishing well");
    set_name("well");
    set_adj("wishing");

    add_prop(OBJ_I_NO_GET, "It's way too heavy!\n");

    totalsum = 0;
    loosers = 0;

    set_long("This is a wishing well, or at least that's what the " +
             "sign on it claims. Perhaps you should throw some " +
             "coins in it and see for yourself.\n");

    set_alarm(1.0, 0.0, anka);
}

void
init()
{
    ::init();
    add_action("throw", "throw");
}

int
throw(string s)
{
    string apa, bepa;
    object ob;
    int amount, stat, val;

    NF("You throw yourself around a little, but decide against it " +
       "when you almost fall into the well.\n");
    if (!s)
        return 0;

    if (s == TP->query_real_name())
    {
        NF("And how do you think you could do that ?\n");
        return 0;
    }

    NF("I don't really understand you...\n");
    if (!parse_command(s, TO,
                       "%w %w 'coin' / 'coins' 'in' / 'into' [the] [wishing] 'well'",
                       apa, bepa))
    {
        if (parse_command(s, TP, "%o 'in' / 'into' [the] [wishing] 'well'", ob))
        {
            NF("That is too large to fit in the well.\n");
            if (living(ob))
                return 0;
            NF("You can't do that.\n");
            if (ob->query_prop(OBJ_I_NO_DROP))
                return 0;

            NF("You don't want to do that.\n");
            if (member_array("coin", ob->query_names()) > -1)
                return 0;


            write("Your " + ob->query_name() +
                          " sinks to the bottom and disappears.\n" +
                          "Nothing else seems to happen.\n");
            say(QCTNAME(TP) + " throws something in the well.\n");
            ob->remove_object();
            return 1;
        }
        else
            return 0;
    }

    amount = LANG_NUMW(apa);

    if (!amount)
    {
        write("Thought that would work, did you?\n");
        say("The well kicks " + QCTNAME(TP) + " in the stomach.\n");
        return 1;
    }

    switch (bepa)
    {
    case "copper":
        stat = MONEY_MOVE(amount, "copper", TP, 0);
        val = 1;
        break;
    case "silver":
        stat = MONEY_MOVE(amount, "silver", TP, 0);
        val = 12;
        break;
    case "gold":
        stat = MONEY_MOVE(amount, "gold", TP, 0);
        val = 144;
        break;
    case "platinum":
        stat = MONEY_MOVE(amount, "platinum", TP, 0);
        val = 1728;
        break;
    default:
        write("You should specify what kind of money to throw in the well.\n");
        return 1;
    }

    if (stat != 0)
    {
        write("You can't throw what you don't have.\n");
        return 1;
    }
    write("You throw the coins into the well.\n");
    say(QCTNAME(TP) + " throws some coins in the well.\n");

    totalsum += amount * val;

    //    tell_room("/d/Roke/gresolle/workroom", "*pling*\n");
    save_object(SAVEFILE);
    set_alarm(15.0, 0.0, &givep(({amount * val, TP})));
    return 1;
}

void
givep(mixed * mu)
{
    object tp;
    int amount;

    amount = mu[0];
    tp = mu[1];

    if (!tp || E(tp) != E(TO))
        return;
       
    // Jag fattar inte. Vinner all i borjan? FIXA
    if (random(10 * (loosers > 5)))
    {
        tp->catch_msg("Nothing seems to happen.\n");
        return;
    }

    if (loosers < 6)
        if (tp->query_prop("_wishingwell_has_won"))
        {
            tp->catch_msg("You feel that the well won't give you more today.\n");
            return;
        }
        else
            amount *= 10;

    loosers++;
    tp->catch_msg("You feel your pockets fill with money!\n");
    tp->add_prop("_wishingwell_has_won", 1);

    MONEY_MAKE_CC(amount * 2)->move(tp);
    totalsum -= amount * 2;
    save_object(SAVEFILE);
}
