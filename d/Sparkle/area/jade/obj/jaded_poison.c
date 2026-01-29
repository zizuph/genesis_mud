/*  /d/Sparkle/area/jade/jaded_poison.c
 *  "Poison" to apply the lingering effect of Sparkle's "Neh fruit".
 *  Changes in the player's alignment are limited, the effect depending on how
 *  world-weary the fruit was. Not recovered, because one should not awaken
 *  cynical.
 *
 *  Modeled on Amelia's /d/Genesis/herbs/poisons/skunk_poison.c
 *
 *  Created 2017-02-04 by Martin Berka (Mar) for Genesis MUD
 */
#pragma save_binary
#pragma strict_types

inherit "/std/poison_effect";
#include <macros.h> //MASTER for recover
#include <poison_types.h> //POISON_USER_DEF
#include <stdproperties.h>

/* Global variables */
int stored_align, //For detecting changes in alignment
    reduction_factor; //Percentage of change remaining after reduction

/* Definitions */
#define ENV         environment(this_object())

/*
 * Function name: create_poison_effect
 * Description  : Poison constructor
 */
void
create_poison_effect()
{
    set_name("_jaded_poison_");
    set_poison_type("jaded");
    set_damage( ({ POISON_USER_DEF, 20 }) );
    set_time(100);
    interval = 30.0;
    silent = 2; //Like poison_effect.c, but need 3 to silence jaded_poison msgs
}

/*
 * Function name: special_damage
 * Description  : Periodically reduce changes in alignment.
 * Arguments    : (int) "damage" - unused
 */
void
special_damage(int damage = 80)
{
    int align_changed = poisonee->query_alignment() - stored_align;
    if (align_changed)
    {
        if (silent < 3)
        {
            switch (random(5))
            {
            case 0:
                tell_object(poisonee, "When you think about it, this is "
                    + "nothing new.\n");
                break;
            case 1:
                tell_object(poisonee, "In the grand scheme of things, "
                    + "you're not sure that really mattered.\n");
                break;
            case 2:
                tell_object(poisonee, "Your actions were necessary "
                    + "and in no way a statement about you.\n");
                break;
            case 3:
                tell_object(poisonee, "The last thirty seconds feel like "
                    + "the distant past, dull and irrelevant.\n");
                break;
            default:
                tell_object(poisonee, "You've seen good and evil - did your "
                    + "recent actions really count as one or the other?\n");
            }
        }
        stored_align = stored_align + (reduction_factor * align_changed / 100);
        poisonee->set_alignment(stored_align);
    }
    else if (silent < 3)
    {
        switch (random(10))
        {
            case 0:
                tell_object(poisonee,
                    "You are not sure you trust anyone, anywhere.\n");
                break;
            case 1:
                tell_object(poisonee, "This is a day like any other.\n");
                break;
            case 2:
                tell_object(poisonee, "You remember being young a moment ago - "
                    + "never again.\n");
                break;
            case 3:
                tell_object(poisonee, "Second by second, your life passes by, "
                    + "unchanged and changing nothing.\n");
                break;
            case 4:
                tell_object(poisonee, "Well. How surprising.\n");
                break;
            case 5:
                tell_object(poisonee,
                    "Everyone seems so cluelessly carefree today.\n");
            default:
        }
    }

    if (silent < 3)
    {
        switch (random(14))
        {
            case 0:
                poisonee->command("frown cynically");
                break;
            case 1:
                poisonee->command("brood idly");
                break;
            case 2:
                poisonee->command("smile insincerely");
                break;
            case 3:
                poisonee->command("chuckle dryly");
                break;
            case 4:
                poisonee->command("peer ambivalently");
                break;
            case 5:
                poisonee->command("sigh knowingly");
                break;
            case 6:
                poisonee->command("grin humourlessly");
                break;
            case 7:
                poisonee->command("laugh hollowly");
                break;
            case 8:
                poisonee->command("stare uncaringly");
                break;
            default:
        }
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
    if (sscanf(str, "%s#%d#%s", foobar, reduction_factor, foobar ) < 2)
    {
        reduction_factor = 80;
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
    return file + "#" + reduction_factor + "#";
} /* query_poison_recover */


/*
 * Function name: end_effect
 * Description  : End the cynicism
 */
void
timeout()
{
    poisonee->catch_msg("The world feels new and colourful again!\n");
    ::timeout();
}


/*
 * Function name: set_effect_strength
 * Description  : Set the multiplier used to reduce changes in alignment
 * Arguments    : (int) percentage by which changes are reduced
 * Returns      : 1 (success)
 */
int
set_effect_strength(int effect_value)
{
    reduction_factor = 100 - effect_value;
    return 1;
}

/*
 * Function name: prolong_effect
 * Description  : Replace the ending alarm if player eats the herb again
 * Arguments    : (int) Effect value of the other herb
 */
void
prolong_effect(int effect_value)
{
    if (effect_value > 100 - reduction_factor)
    {
        set_effect_strength(effect_value);
    }
    /*If anyone was clever enough to use an aged herb first, they can keep its
    strength*/

    float time_left = get_alarm(a_time)[2];     //man get_alarm
    remove_alarm(a_time);       //Replace the ending alarm
    a_time = set_alarm(time_left + 3.0 * itof(effect_value), 0.0, timeout);
}


/*
 * Function name: start_poison
 * Description  : Set the multiplier used to reduce changes in alignment
 * Arguments    : (object) Cause of the poison
 */
void
start_poison(object poisoner)
{
    if (!living(ENV))
    {
        timeout();
    }

    if (!reduction_factor) //Default
    {
        reduction_factor = 80;
    }

    //Check if this player is already jaded
    object poison = present("_activated_jaded_poison_", ENV);
    if (poison) //Replace existing poison, but stay cynical (prolong)
    {
        poison->prolong_effect(100 - reduction_factor);
        remove_object();
        return;
    }
    add_name("_activated_jaded_poison_");

    ENV->catch_msg("The world feels older and duller.\n");

    stored_align = poisonee->query_alignment();
    set_time(500 - 4 * reduction_factor);   //100 + 4 * (100 - reduction_factor)

    ::start_poison(poisoner);


}
