// OBJECT:  turtle helper

    /* Calia Domain

    HISTORY

    [2002-10-06] Created by Uhclem from [C:\CALIA\WEENWARE\TURTLE_H.DOC].

    PURPOSE

    A player who swallows a sea turtle (we Calian wizards like to prepare for
    all contingencies) gets this invisible object which stays with him until he
    expels the turtle, which he will be compelled to do after a few minutes.
    The player can't eat or drink while the turtle is inside him; trying to
    regurgitate or puke will hasten its expulsion.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

// GLOBAL VARIABLES

int Gag_Limit = random(8);  /*  higher value expels turtle quicker  */

// FUNCTIONS

// Function:  out_comes_the_turtle()

/*

Purpose:  function name says it all.

Arguments:  none.

Returns:  nothing.

*/

void
out_comes_the_turtle()

{

    object tp = environment();
    object room = environment(tp);
    object turtle;
    string tp_pos = tp->query_possessive();
    string tp_obj = tp->query_objective();
    string tp_pro = tp->query_pronoun();

    tell_room(room,
        QCTNAME(tp) + " makes one last supreme effort to expel" +
        " the blockage in " + tp_pos + " throat, and " +
        ({
        "after a few practice heaves of increasing intensity,",
        "with prespiration running down " + tp_pos +
        " face and " + tp_pos + " eyes bugging out as if" +
        " they will burst,",
        "making a sound that you ordinarily only associate with" +
        " a water buffalo giving birth,"
        })[random(3)] +
        " " + tp_pro + " convulses and explosively expels a" +
        " baby sea turtle!\n",
        tp);

    tp->catch_msg("You make one last supreme effort to expel" +
        " the blockage in your throat, and " +
        ({
        "after a few practice heaves of increasing intensity,",
        "with prespiration running down your face and your eyes" +
        " bugging out as if they will burst,",
        "making a sound that you ordinarily only associate with" +
        " a water buffalo giving birth,"
        })[random(3)] +
        " you convulse ferociously, and out pops the" +
        " baby sea turtle!\n");

    turtle = clone_object(TURTLE);
    turtle->move(room);
    turtle->command("glare " + tp->query_real_name());
    remove_object();

}

// Function:  gag_and_choke()

/*

Purpose:  teach players not to swallow turtles.

Arguments:  none.

Returns:  nothing.

*/

void
gag_and_choke()

{

    object tp = environment();
    object room = environment(tp);
    string tp_pos = tp->query_possessive();
    string tp_obj = tp->query_objective();
    string tp_pro = tp->query_pronoun();
    int selector;

    if (Gag_Limit > 9)

    {

        set_alarm(2.2, 0.0, out_comes_the_turtle);

    }

    else

    {

        selector = random(5);

        switch (selector)

        {

            case 0:

            tell_room(room,
                QCTNAME(tp) + " clutches " + tp_pos +
                " chest and doubles over, wheezing, choking," +
                " and grimacing in pain.\n",
                tp);

            tp->catch_msg("You clutch your chest and" +
                " double over, wheezing, choking, and grimacing as" +
                " the baby sea turtle kicks and bites in" +
                " an attempt to escape.\n");

            break;

            case 1:

            tell_room(room,
                QCTNAME(tp) + " suddenly freezes for a second," +
                " then suffers an explosive convulsion that" +
                " causes " + tp_pos + " chest to heave and " + tp_pos +
                " head to recoil violently in reaction to a" +
                " series of forceful spasms.\n",
                tp);

            tp->catch_msg("For a moment the entire" +
                " world seems immobilized, then suddenly everything" +
                " is a blur as your head is whipped back and forth" +
                " by a series of forceful spasms triggered" +
                " by the struggling baby sea turtle lodged" +
                " in your gullet.\n");

            break;

            case 2:

            tell_room(room,
                QCTNAME(tp) + " staggers and strains to catch " + tp_pos +
                " breath and pounds " + tp_pos + " chest" +
                " in a desperate effort to dislodge something that" +
                " seems to be choking " + tp_obj + ".\n",
                tp);

            tp->catch_msg("You stagger and strain to catch" +
                " your breath and pound your chest in a" +
                " desperate effort to dislodge the baby" +
                " sea turtle, whose presence in your chest" +
                " causes a sensation that can only" +
                " be described as terrifying and... alien.\n");

            break;

            case 3:

            tell_room(room,
                QCTNAME(tp) + " closes " + tp_pos + " eyes tightly," +
                " opens " + tp_pos + " mouth wide, and" +
                " arduously struggles to cough up something" +
                " that's hindering " + tp_pos +
                " breathing and swallowing.\n",
                tp);

            tp->catch_msg("You close your eyes tightly, open" +
                " your mouth wide, and laboriously strain to cough" +
                " up the baby sea turtle.\n");

            break;

            case 4:

            tell_room(room,
                QCTNAME(tp) + " turns blue in the face" +
                " and twitches frightfully as " + tp_pos +
                " chest heaves so savagely that it seems" +
                " about to explode!\n",
                tp);

            tp->catch_msg("Your vision fades and your ears ring as" +
                " lack of air begins to take its toll, and your" +
                " chest heaves so savagely in an attempt to get" +
                " a full breath that it seems about to explode!\n");

        }

        Gag_Limit += 1;
        set_alarm(13.3, 0.0, gag_and_choke);

    }

}

// Function:  in_goes_the_turtle()

/*

Purpose:  stop the swallowed turtle somewhere between mouth and stomach.

Arguments:  none.

Returns:  nothing.

*/

void
in_goes_the_turtle()

{

    object tp = environment();
    object room = environment(tp);
    string tp_pos = tp->query_possessive();

    tell_room(room,
        QCTNAME(tp) + " makes an ominous gurgling noise," +
        " and " + tp_pos + " eyes bug out alarmingly as the" +
        " turtle gets stuck somewhere between " + tp_pos +
        " mouth and stomach!\n",
        tp);

    tp->catch_msg("A sudden pain in your chest and" +
        " difficulty breathing suggest that the turtle did not make" +
        " it all the way to your stomach.\n");

    set_alarm(13.3, 0.0, gag_and_choke);

}

// Function:  no_eat_or_drink()

/*

Purpose:  prevent player from eating or drinking.

Arguments:  none.

Returns:  1.

*/

int
no_eat_or_drink()

{

    write("With a turtle stuck in your gullet, you don't feel well" +
        " enough to " + query_verb() + " anything right now.\n");

    return 1;

}

// Function:  enter_env()

/*

Purpose:  called by system when this object moves to a new environment.

Arguments:  object moved to, object moved from.

Returns:  nothing.

*/

void
enter_env(object ob_to, object ob_from)

{

    object holiday_room;

    ::enter_env(ob_to, ob_from);

    /*
     *  This object prevents a player from eating or drinking and causes 
     *  occasional fits of gagging and coughing.  The effects last only a few
     *  minutes; when its task is complete, the object removes itself from the
     *  game.    
     */

    add_action(no_eat_or_drink, "eat");
    add_action(no_eat_or_drink, "drink");
    add_action(gag_and_choke, "puke");
    add_action(gag_and_choke, "regurgitate");

    holiday_room = find_object(HOLIDAY_ROOM);

    if (!holiday_room)

    {

        holiday_room = call_other(HOLIDAY_ROOM, "this_object");

    }

    set_alarm(0.5, 0.0, in_goes_the_turtle);

    tell_room(holiday_room,
        ob_to->query_name() + " swallows a turtle.\n");

}

// Function:  create_object()

void
create_object()

{

    set_no_show();
    set_name("_calia_turtle_helper");
    set_short("turtle_helper");

    set_long("This invisible object is given to players" +
        " who swallow the baby sea turtles found on the beaches" +
        " of Calia at Halloween.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);

    setuid();  /*  "uid" settings required for cloning. */
    seteuid(getuid());

}
