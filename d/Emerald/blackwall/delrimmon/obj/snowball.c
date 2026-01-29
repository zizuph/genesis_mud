/*
 *  /d/Emerald/blackwall/delrimmon/obj/snowball.c
 *
 *  Everyone loves a snowball fight! Here we have one. These little
 *  babies can be found on a glacier high atop the western cliffs
 *  of the Blackwall Mountains in Emerald.
 *
 *  Copyright (c) March 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/food";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define    BLOCKED       ("em_i_blocked_snowball")
#define    DUCKED        ("em_i_ducked_snowball")
#define    THROWN        ("em_i_thrown_snowball")

/* global variables */
public object  Target;       /* who is the snowball thrown at? */

/* prototypes */
public void    create_food();
public string  snowball_short();
public string  snowball_long();
public void    init();
public int     throw_snowball(string arg);
public void    snowball_hit(object tp, object victim);
public int     duck_snowball(string arg);
public mixed   get_snowball();
public string  snowball_hit_result(int type, object victim, int hit_type);
public void    melt_snowball();


/*
 * function name:        create_food
 * description  :        set up the food
 */
public void
create_food()
{
    set_name("snowball");
    add_adj( ({ "round", "white", "cold" }) );

    set_short(snowball_short);
    set_long(snowball_long);

    set_amount(1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 30);

    add_prop(OBJ_M_NO_GET, get_snowball);
    set_alarm(200.0, 0.0, &melt_snowball() );
} /* create_object */


/*
 * function name:        snowball_short
 * description  :        provides a short desc for the snowball,
 *                       variable depending on if it is being thrown
 * returns      :        string -- the short description
 */
public string
snowball_short()
{
    if (query_prop(THROWN))
    {
        set_pshort("snowballs, sailing through the air");
        return "snowball, sailing through the air";
    }

    return "snowball";
} /* snowball_short */


/*
 * function name:        snowball_long
 * description  :        provides a long description of the snowball,
 *                       variable depending on if it is being thrown
 * returns      :        string -- the long description
 */
public string
snowball_long()
{
    if (query_prop(THROWN))
    {
        if (Target->query_real_name() == TP->query_real_name() )
        {
            return BSN("It is coming right at you!");
        }

        return BSN("This snowball has obviously been thrown by someone,"
                 + " as it is sailing through the air dangerously"
                 + " fast!");
    }

    return BSN("This snowball is almost perfectly round, and formed of"
             + " very cold compacted snow. Throwing it at someone will"
             + " almost certainly prove to be fascinating.");
} /* snowball_long */


/*
 * function name:        init
 * description  :        add some verbs to the player
 */
public void
init()
{
    ::init();

    add_action(throw_snowball, "throw");
    add_action(throw_snowball, "hurl");
    add_action(duck_snowball, "duck");
    add_action(duck_snowball, "dodge");
} /* init */


/*
 * function name:        throw_snowball
 * description  :        heh heh heh ...
 * arguments    :        string -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
throw_snowball(string arg)
{
    mixed   victim;
    mixed   snowball;

    if (query_prop(THROWN))
    {
        return 0;
    }

    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (parse_command(arg, ({}),
        "[the] [cold] [round] [white] 'snowball'"))
    {
        NFN0("What do you want to throw the snowball at?");
    }

    if (!parse_command(arg, ENV(TP),
        "[the] [cold] [round] [white] %i 'at' / 'towards' %i",
        snowball, victim))
    {
        return 0;
    }

    snowball = NORMAL_ACCESS(snowball, 0, 0)[0];
    victim = NORMAL_ACCESS(victim, 0, 0)[0];

    if (!snowball->id("snowball"))
    {
        NFN0("Throwing the snowball would be more fun.");
    }

    if (!living(victim))
    {
        NFN0("It would probably be more interesting to throw it at"
           + " something that knows the difference.");
    }

    if (TP->query_real_name() == victim->query_real_name())
    {
        NFN0("Even if it were possible, you have more self respect"
           + " than that.");
    }

    TP->catch_msg("You throw the snowball at " + QTNAME(victim) + ".\n");
    victim->catch_msg(QCTNAME(TP) + " throws a snowball at you!\n");
    tell_room(ENV(TP), QCTNAME(TP) + " throws a snowball at "
      + QTNAME(victim) + ".\n", ({ victim, TP }) );

    Target = victim;
    add_prop(THROWN, 1);
    TO->move(ENV(TP));
    set_alarm(3.0, 0.0, &snowball_hit(TP, victim) );

    return 1;
} /* throw_showball */


/*
 * function name:        snowball_hit
 * description  :        determines whether or not the snowball hit
 *                       the target, and prints appropriate messages
 * arguments    :        object tp -- who threw the snowball?
 *              :        object victim -- who is the target?
 */
public void
snowball_hit(object tp, object victim)
{
    int    hit_type = random(11);

    if (ENV(victim) != ENV(TO))
    {
        tell_room(ENV(TO), "The snowball bursts apart as it hits the"
                         + " ground.\n");
        TO->remove_object();

        return;
    }

    if (query_prop(DUCKED))
    {
        victim->catch_msg("The snowball thrown by " + QTNAME(tp)
          + " sails harmlessly over your head.\n");
        tell_room(ENV(TO), QCTNAME(victim) + " grins as the snowball"
          + " sails harmlessly over " + victim->query_possessive()
          + " head.\n", victim);
    }

    if (!query_prop(BLOCKED) && !query_prop(DUCKED) )
    {
        victim->catch_msg(snowball_hit_result(0, victim, hit_type));
        tell_room(ENV(TO), snowball_hit_result(1, victim, hit_type),
                  victim);
    }

    TO->remove_object();
    return;
}


/*
 * function name:        duck_snowball
 * description  :        let the victim try to duck the snowball!
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 - failure
 */
public int
duck_snowball(string arg)
{
    if (!query_prop(THROWN))
    {
        return 0;
    }

    if (query_prop(DUCKED))
    {
        NFN0("You've already attempted to " + QVB + ".");
    }

    if (TP->query_real_name() != Target->query_real_name())
    {
        NFN0("There is no need to do that, none are coming at you.");
    }

    if (!random(3))
    {
        WRITE("You quickly duck down to avoid being hit.");

        switch(random(2))
        {
            default:
            case 0:
                tell_room(ENV(TP), QCTNAME(TP) + " deftly ducks to"
                                + " avoid being hit.\n", TP);
                break;
            case 1:
                tell_room(ENV(TP), QCTNAME(TP) + " dodges to the side"
                                + " to avoid being hit.\n", TP);
                break;
            case 2:
                tell_room(ENV(TP), QCTNAME(TP) + " dives for cover.\n",
                          TP);
                break;
        }

        add_prop(DUCKED, 1);
        return 1;
    }

    WRITE("You attempt to dodge the snowball, but are too late!");
    tell_room(ENV(TP), QCTNAME(TP) + " frantically attempts to"
      + " duck.\n", TP);

    return 1;
} /* duck_snowball */


/*
 * function name:        get_snowball
 * description  :        VBFC to prevent players from getting the
 *                       snowballs that are in mid-flight
 * returns      :        string -- fail message, or
 *                       int 0 -- let them get it
 */
public mixed
get_snowball()
{
    if (query_prop(THROWN))
    {
        return "The snowball is moving too fast.\n";
    }

    return 0;
} /* get_snowball */


/*
 * function name:        snowball_hit_result
 * description  :        rolls a random text message to describe how
 *                       successful the snowball throw was
 * arguments    :        int type: 1 -- message is for the room,
 *                                 0 -- message is for the victim
 *                       object victim: the target of the snowball
 *                       int hit_type: the severity of the impact on
 *                                     the target (higher is better)
 * returns      :        string -- the text message
 */
public string
snowball_hit_result(int type, object victim, int hit_type)
{
    string  hit_txt;
    string  name = (type ? QTNAME(victim) : "you");
    string  him  = (type ? victim->query_objective() : "you");
    string  his  = (type ? victim->query_possessive() : "your");
    string  side = (random(1) ? "left" : "right");

    switch(hit_type)
    {
        default:
        case 0:
            if (type)
            {
                hit_txt = "The snowball flies lamely over " + name
                        + "'s head, hitting the ground about twenty"
                        + " feet behind " + him + ".\n";
            }
            else
            {
                hit_txt = "The snowball flies lamely over " + name
                        + " head, hitting the ground about twenty"
                        + " feet behind " + him + ".\n";
            }
            break;
        case 1:
            hit_txt = "The snowball whirls past " + name
                    + " missing " + him + " by about five feet on"
                    + " the " + side + ".\n";
            break;
        case 2:
            hit_txt = "The snowball smashes into the ground right in"
                    + " front of " + name + ".\n";
            break;
        case 3:
            if (type)
            {
                hit_txt = "The snowball shoots right between " + name
                        + "'s legs, nearly hitting " + him + " on the"
                        + " thigh.\n";
            }
            else
            {
                hit_txt = "The snowball shoots right between " + his
                        + " legs, nearly hitting " + him + " on the"
                        + " thigh.\n";
            }
            break;
        case 4:
            if (type)
            {
                hit_txt = "The snowball just nicks " + name
                        + "'s " + side + " shoulder, breaking into"
                        + " pieces as it continues in its flight.\n";
            }
            else
            {
                hit_txt = "The snowball just nicks " + his + " "
                        + side + " shoulder, breaking into pieces"
                        + " as it continues in its flight.\n";
            }
            break;
        case 5:
            if (type)
            {
                hit_txt = "The snowball slams into " + name + "'s "
                        + side + " shin, sending " + him + " hopping!\n";
            }
            else
            {
                hit_txt = "The snowball slams into " + his + " "
                        + side + " shin, somewhat painfully!\n";
            }
            break;
        case 6:
            if (type)
            {
                hit_txt = "The snowball explodes as it connects with "
                        + name + "'s " + side + " arm!\n";
            }
            else
            {
                hit_txt = "The snowball connects painfully with your "
                        + side + " arm, sending snow flying out in front"
                        + " of you!\n";
            }
            break;
        case 7:
            if (type)
            {
                hit_txt = "The snowball splatters right in the middle"
                        + " of " + name + "'s stomach, knocking"
                        + " some of the wind out of him!\n";
            }
            else
            {
                hit_txt = "The snowball splatters right into your"
                        + " stomach, knocking a bit of the wind out"
                        + " of you!\n";
            }
            break;
        case 8:
            if (type)
            {
                hit_txt = "The snowball shatters against " + name
                         + "'s chest, sending " + him + " stumbling"
                         + " backwards!\n";
            }
            else
            {
                hit_txt = "The snowball shatters against your chest"
                         + " with surprising force, sending you"
                         + " stumbling backwards!\n";
            }
            break;
        case 9:
            if (type)
            {
                hit_txt = CAP(name) + " turns " + his + " head"
                         + " just in time, as the snowball impacts"
                         + " against " + his + " ear and jawbone"
                         + " with a loud crack!\n";
            }
            else
            {
                hit_txt = CAP(name) + " turn your head just in time,"
                         + " as the snowball impacts painfully against"
                         + " your ear and jawbone with a loud crack!\n";
            }
            break;
        case 10:
            if (type)
            {
                hit_txt = CAP(name) + " wails in dismay as the snowball"
                        + " plows right into " + his + " face, knocking "
                        + him + " backwards onto the ground!\n";
            }
            else
            {
                hit_txt = "You wail in dismay as the snowball plows"
                        + " right into your face, knocking you backwards"
                        + " onto the ground!\n";
                Target->command("$scream");
            }
            break;
    }

    return hit_txt;
} /* snowball_hit_result */


/*
 * function name:        melt_snowball
 * description  :        after a certain period, the snowball will melt,
 *                       unless it is sitting happily near to the
 *                       glacier from which it was formed (a cold place)
 */
public void
melt_snowball()
{
    if (ENV(TO)->id("high_cliffs") || ENV(TO)->id("pack"))
    {
        set_alarm(200.0, 0.0, &melt_snowball() );
    }

    if (interactive(ENV(TO)))
    {
        ENV(TO)->catch_msg("The snowball melts in your hands.\n");
    }

    else
    {
        tell_room(ENV(TO), "The snowball melts and disappears.\n");
    }

    TO->remove_object();
} /* melt_snowball */
