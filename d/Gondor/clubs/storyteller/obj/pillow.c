/*
 * /d/Gondor/clubs/storyteller/obj/pillow.c
 *
 * A small pillow in the Storyteller club house that can be
 * thrown, among other things.
 *
 * Coded by Gwyneth, 11/05/02
 */
inherit "/std/object";
inherit "/lib/commands";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_object()
{
    string color = one_of_list(({ "red", "orange", "yellow", "green",
                   "blue", "purple", "violet", "pink", "black", "white",
                   "gold", "silver" }));
    set_name(({ "pillow", "_story_pillow" }));
    set_pname("pillows");
    set_adj(({ "small", "fluffy" }));
    set_long("The outer covering of this pillow is made of smooth " +
        color + " satin. The pillow is incredibly fluffy and soft, " +
        "perfect for squeezing, cuddling, sleeping and even throwing!\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 20);
    add_prop(OBJ_M_NO_SELL, 1);
}

public int
do_squeeze(string str)
{
    object *oblist = ({});
    string vb, *adv_list = ({});

    vb = capitalize(query_verb());
    if (!strlen(str))
    {
        notify_fail(vb + " pillow [how]?\n");
        return 0;
    }

    adv_list = parse_adverb(str, "happily", 1);
    if (!sizeof(adv_list) || !strlen(adv_list[0]))
    {
        notify_fail(vb + " pillow [how]?\n");
        return 0;
    }

    oblist = parse_this(adv_list[0], "%i", 0, 1);

    if (!sizeof(oblist))
    {
        notify_fail(vb + " pillow [how]?\n");
        return 0;
    }

    if (oblist[0] != TO)
    {
        notify_fail(vb + " pillow [how]?\n");
        return 0;
    }

    write("You " + lower_case(vb) + " the " + TO->short() +
        " " + adv_list[1] + ". It's so soft!\n");
    say(QCTNAME(TP) + " " + lower_case(vb) + "s the " + TO->short() + " " +
        adv_list[1] + ". It looks so soft!\n");
    return 1;
}

public int
do_sleep(string str)
{
    object *oblist = ({});

    if (!strlen(str))
    {
        notify_fail("Sleep on what?\n");
        return 0;
    }

    oblist = parse_this(str, "[on] %l");

    if (!sizeof(oblist))
    {
        oblist = parse_this(str, "[on] %i", 0, 1);
        if (!sizeof(oblist))
        {
            notify_fail("Sleep on what?\n");
            return 0;
        }

        if (oblist[0] != TO)
        {
            notify_fail("Sleep on what?\n");
            return 0;
        }

        write("You close your eyes and rest your head on the " + TO->short() +
            ".\n");
        say(QCTNAME(TP) + " closes " + POSSESSIVE(TP) + " eyes and rests " + 
            POSSESSIVE(TP) + " head on the " + TO->short() + ".\n");
        return 1;
    }

    write("You place your " + TO->short() + " on " +
        oblist[0]->query_the_possessive_name(TP) + " shoulder and rest your " +
        "head on it.\n");
    oblist[0]->catch_tell(TP->query_The_name(oblist[0]) + " places " +
        POSSESSIVE(TP) + " " + TO->short() + " on your shoulder and rests " +
        POSSESSIVE(TP) + " head on it.\n");
    say(QCTNAME(TP) + " places " + POSSESSIVE(TP) + " " + TO->short() +
        " on " + QTPNAME(oblist[0]) + " shoulder and rests " +
        POSSESSIVE(TP) + " head on it.\n", ({ TP, oblist[0] }));
    return 1;
}

public int
do_throw(string str)
{
    mixed *pillow = ({});
    object *oblist = ({});
    string str1;

    if (!strlen(str))
    {
        notify_fail("Throw pillow at whom?\n");
        return 0;
    }

    if (!parse_command(str, all_inventory(TP) + all_inventory(ENV(TP)),
      "%i [at] %s", pillow, str1) ||
      !parse_command(str1, all_inventory(ENV(TP)), "%l", oblist) ||
      !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)) ||
      !sizeof(pillow = NORMAL_ACCESS(pillow, 0, 0)))
    {
        notify_fail("Throw the pillow at whom?\n");
        return 0;
    }

    if (oblist[0] == TP)
    {
        write("You whack yourself in the head with the " +
            TO->short() + ".\n");
        say(QCTNAME(TP) + " whacks " + OBJECTIVE(TP) + "self in the " +
            "head with the " + TO->short() + ".\n");
        return 1;
    }

    write("You throw your " + TO->short() + " at " +
        oblist[0]->query_the_name(TP) + "!\n");
    oblist[0]->catch_tell(TP->query_The_name(oblist[0]) + " throws " +
        POSSESSIVE(TP) + " " + TO->short() + " at you!\n");
    say(QCTNAME(TP) + " throws " + POSSESSIVE(TP) + " " + TO->short() +
        " at " + QTNAME(oblist[0]) + "!\n", ({ TP, oblist[0] }));

    if (random(3))
    {
        write("The " + TO->short() + " hits " + oblist[0]->query_the_name(TP) +
            " with a loud WHOMP!\n");
        oblist[0]->catch_tell("The " + TO->short() + " hits you with a " +
            "loud WHOMP!\n");
        say("The " + TO->short() + " hits " + QTNAME(oblist[0]) +
            " with a loud WHOMP!\n", ({ TP, oblist[0] }));
    }
    else
    {
        write("The " + TO->short() + " misses " + oblist[0]->query_the_name(TP) +
            "! Oh no!\n");
        oblist[0]->catch_tell("The " + TO->short() + " misses you! Phew!\n");
        say("The " + TO->short() + " misses " + QTNAME(oblist[0]) + "!\n",
            ({ TP, oblist[0] }));
    }

    if (random(3))
    {
        tell_room(ENV(TP), "The " + TO->short() + " falls on the floor.\n");
        TO->move(ENV(TP));
        return 1;
    }
    else
    {
        tell_object(oblist[0], "You snag the " + TO->short() +
            " in the air.\n");
        tell_room(ENV(TP), QCTNAME(oblist[0]) + " snags the " + TO->short() +
            " in the air.\n", oblist[0]);
        TO->move(oblist[0]);
        return 1;
    }

    return 1;
}

void
walk_off()
{
    remove_object();
}

void
run_away_alarm()
{
    set_alarm(1200.0, 0.0, walk_off);
}

public void
init()
{
    ::init();

    add_action(do_squeeze, "squeeze");
    add_action(do_squeeze, "cuddle");
    add_action(do_sleep, "sleep");
    add_action(do_throw, "throw");
}
