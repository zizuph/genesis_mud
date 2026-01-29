/*  /d/Sparkle/area/jade/obj/dyed_skin.c
 *  Pseudo-poison that applies a custom adjective to a living's noun via a
 *  description subloc, with a weakening adverb depending on
 *  the remaining duration of the effect:
 *  "Her skin looks very green."
 *  No messages between beginning and end;
 *  appears in player description;
 *  used by Jade farm.
 *
 *  Created 2017-03-12 by Martin Berka (Mar) for Genesis MUD
 */
#pragma save_binary
#pragma strict_types

/* Definitions */
#define IDENT       "_dyed_skin_" /*Also used in jade_room*/
#define ENV         environment(this_object())

inherit "/std/poison_effect";
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>

/* Global variables */
string  skin_adj, //e.g. color of the skin, can be set/read externally
        skin_noun; //"Skin" can be replaced with any noun for added flexibility.
int     ending_alarm; //Removes the effect.

/*
 * Function name: create_object
 * Description  : Dye constructor
 */
void
create_poison_effect()
{
    set_name("_skin_dye_");
    set_poison_type("dyed");
    set_time(600);
    interval = 0.0;
    silent = 2;

    skin_adj = "green"; //Defaults; creator can alter with setter functions
    skin_noun = "skin";
}

/*
 * Function name: start_poison
 * Description  : Inform when the jam starts to change skin appearance
 * Arguments    : (object) What caused the poison.
 */
void
start_poison(object poisoner)
{
    ENV->add_subloc(IDENT, file_name(this_object()));
    ENV->catch_msg("You notice that your " + skin_noun + " looks different "
        + "than normal: rather " + skin_adj + "!\n");
    ::start_poison(poisoner);
}

/*
 * Function name: end_effect
 * Description  : Return skin to normal appearance
 */
void
timeout()
{
    ENV->catch_msg("You notice that your " + skin_noun
        + " has returned to its usual appearance.\n");
    ENV->remove_subloc(IDENT);
    ::timeout();
}

/*
 * Function name: enter_env
 * Description  : When the poison enters a living, activate effect
 * Returns      : 1 (success) / 0 (removed self)
 */
int
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if (living(env) && !a_time)
    {
        //Check if this player is already dyed; if yes, increase duration, and
        //thus tone.
        object dye = present(IDENT, env);
        if (dye && dye->query_skin_adj() == skin_adj
            && dye->query_skin_noun() == skin_noun
            && dye->query_time_remaining())
        {
            dye->prolong_effect(600.0);
            this_object()->remove_object();
            return 0;
        }

        add_name(IDENT);

        set_alarm(60.0, 0.0, &start_poison(env)); //Notify of skin change

        return 1;
    }
    else
    {       //Poison cannot exist outside a living
        this_object()->remove_object();
        return 0;
    }
}


/*
 * Function name: init_poison_recover
 * Description  : Called when player returns after brief absence
 * Arguments    : string str - the recover argument.
 */
public void
init_poison_recover(string str)
{
    string  foobar;
    int     time_left;
    if (sscanf(str, "%s#%s#%d#%s", foobar, skin_adj, time_left, foobar ) >= 3)
    {
        ENV->add_subloc(IDENT, file_name( this_object() ));
        //ending_alarm = set_alarm(itof(time_left) * 1.3, 0.0, timeout);
        //Make up for greenness missed during sign-out.
    }
    else
    {
        timeout();
    }
} /* init_poison_recover */

/*
 * Function name: query_poison_recover
 * Description  : Called to see whether this object may recover.
 */
public string
query_poison_recover()
{
    string file = MASTER;
    tell_object(find_player("mar"), file + "#" + skin_adj + "#" + ftoi(get_alarm(ending_alarm)[2]) + "#" + "\n");
    return file + "#" + skin_adj + "#" + ftoi(get_alarm(ending_alarm)[2]) + "#";
} /* query_poison_recover */


/*
 * Function name: query_skin_adj
 * Description  : Returns the adjective currently applied to the skin
 * Returns      : (string) The adjective, e.g. "green"
 */
string
query_skin_adj()
{
    return skin_adj;
}


/*
 * Function name: query_skin_noun
 * Description  : Returns the noun that is being described
 * Returns      : (string) The noun, e.g. "skin", arm, leg, etc.
 */
string
query_skin_noun()
{
    return skin_noun;
}


float
query_time_remaining()
{
    //mixed effect_info = get_alarm(ending_alarm);
    //return effect_info[2]; //See man get_alarm
    return get_alarm(ending_alarm)[2];
}


/*
 * Function name: describe_skin / show_subloc
 * Description  : Returns the description of the skin
 * Returns      : (string) One-line description
 */
string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop( TEMP_SUBLOC_SHOW_ONLY_THINGS ))
    {
        return ""; //Hide from "inventory" command
    }

    //ADD VISIBILITY CONDITIONS?
    float time_left = get_alarm(ending_alarm)[2];

    string *adv;
    if (time_left > 600.0)
    {
        adv = ({ "quite", "a strong", "very" });
    }
    else if (time_left > 300.0)
    {
        adv = ({ "somewhat", "rather", "distinctly", "clearly" });
    }
    else
    {
        adv = ({ "faintly", "slightly", "barely", "vaguely" });
    }

    return ( on == for_obj ? "Your" : capitalize(on->query_possessive()) )
        + " " + skin_noun + " is " + adv[random( sizeof(adv) )] + " "
        + skin_adj + ".\n";
}


/*
 * Function name: set_skin_adj
 * Description  : Set the adjective that will be applied to the skin
 * Arguments    : (string) The adjective, e.g. "green"
 */
void
set_skin_adj(string new_adj)
{
    skin_adj = new_adj;
}

/*
 * Function name: set_skin_noun
 * Description  : Set the name that will be used for the skin
 * Arguments    : (string) The noun, e.g. "leg" or "hand" - or "skin"!
 */
void
set_skin_noun(string new_noun)
{
    skin_noun = new_noun;
}

/*
 * Function name: prolong_effect
 * Description  : Replace (extend) the ending alarm if player re-dyes their skin
 * Arguments    : (float) Number of extra seconds
 */
void
prolong_effect(float extra_duration)
{
    float time_left = get_alarm(a_time)[2]; /*man get_alarm*/
    remove_alarm(a_time);
    a_time = set_alarm(time_left + extra_duration, 0.0, timeout);
}
