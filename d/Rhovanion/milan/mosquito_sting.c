/*
 * /d/Gondor/common/poison/mosquito_sting.c
 *
 * This is the poison that enters your body after a mosquito stings you
 * in Torech Ungol.
 *
 * There will be an antidote for it: 
 *
 * /Mercade, May 16 1994
 *
 * Revision history:
 */

inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

/*
 * The substring "PART" means that in that location the variable body_part
 * should be added.
 */
#define ITCH_FEELING ({ \
    "You would like to scratch all over your PART.",                         \
    "The itchy feeling seems to kill you.",                                  \
    "As much as you would want to, you cannot suppress that itchy feeling.", \
    "The itchy feeling on your PART drives you crazy.",                      \
    "AAARRRGGGHHH!!! itchy! itchy! ITCHY!!!",                                \
    "Scratching only spreads the poison through your PART.",                 \
    "Scratching your PART only makes the itchy feeling worse!",              \
    "Now who said mosquito poison was harmless? You keep scratching!" })

/*
 * Global variable
 */
private static string *itch_feeling = ITCH_FEELING;
private static string body_part;

void
create_poison_effect()
{
    remove_name("poison");
    set_short("mosquito sting");

    set_time(600);
    set_interval(30);
    set_damage( ({
        POISON_FATIGUE, 15,
        POISON_HP, 20,
        POISON_STAT, SS_CON,
        POISON_STAT, SS_DEX }) );
    set_strength(25);
    set_silent(2);
    set_poison_type("mosquito");
}

void
set_body_part(string part)
{
    body_part = part;
}

/*
 * Give the player an itchy feeling.
 */
void
tell_damage_player(int phit, string feeling)
{
    string *tmp;

/*
    if (random(2))
    {
        return;
    }
*/
    feeling = ONE_OF_LIST(itch_feeling) + "\n";
    tmp = explode(feeling, "PART");
    if(sizeof(tmp) > 1)
    {
        feeling = tmp[0] + body_part + tmp[1];
    }

    poisonee->catch_msg(feeling);
}

void
timeout()
{
    poisonee->catch_msg("You don't notice that itchy feeling on your " +
        body_part + " any longer.\n");

    ::timeout();
}
