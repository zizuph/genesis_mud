/*
 * /d/Gondor/common/poison/mosquito_sting.c
 *
 * Copyright (C) Stas van der Schaaf - May 16 1994
 *               Mercade @ Genesis
 *
 * This is the poison that enters your body after a mosquito stings you.
 *
 * Revision history:
 * Added argument to ITCH_FEELING for use in tell_damage_player.
 *       Olorin, 28-oct-1995
 * Changed mosquito-specific msg, since mosquito.c is inherited by
 *	other insects.  Gnadnar, 13-jan-99
 * Changed damage to be modest. One should not die of a mosquito bite.
 *	Gnadnar, Gorboth, 19-Feb-99
 */

inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define ITCH_FEELING(x) ({ \
    "You would like to scratch all over your "+x+".",                        \
    "The itchy feeling seems to kill you.",                                  \
    "As much as you would want to, you cannot suppress that itchy feeling.", \
    "The itchy feeling on your "+x+" drives you crazy.",                     \
    "AAARRRGGGHHH!!! Itchy! Itchy! ITCHY!!!",                                \
    "Scratching only spreads the poison through your "+x+".",                \
    "Scratching your "+x+" only makes the itchy feeling worse!",             \
    "Now who said an itch was harmless? You keep scratching!" })

/*
 * Global variable
 */
private static string body_part;

void
create_poison_effect()
{
    set_time(600);
    set_interval(30);
    set_damage( ({
        POISON_FATIGUE, 3,
        POISON_HP, 3 }) );
    set_strength(25);
    set_silent(2);
    set_poison_type("mosquito");
}

void
set_body_part(string part)
{
    body_part = part;
}

string
query_body_part()
{
    return body_part;
}

/*
 * Give the player an itchy feeling.
 */
void
tell_damage_player(int phit, string feeling)
{
    tell_object(poisonee, ONE_OF_LIST(ITCH_FEELING(body_part)) + "\n");
}

void
timeout()
{
    tell_object(poisonee, "You don't notice that itchy feeling on your " +
	body_part + " any longer.\n");

    ::timeout();
}

string
query_poison_recover()
{
    return body_part;
}

void
init_poison_recover(string arg)
{
    body_part = arg;
}

