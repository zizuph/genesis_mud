/*
 * Poison effect object to turn someone into an undead creature. This is
 * different from the previous implementation using a shadow in that
 * it merely sets the property rather than masking query_prop. This allows
 * guilds to catch when the undead property is being added and deal with
 * it accordingly if it is according to their theme.
 *
 * Created by Petros, October 2008
 */
#pragma strict_types
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>

// Defines
#define UNDEAD_DURATION 180
#define UNDEAD_SUBLOC   "undead_subloc"

void 
create_poison_effect()
{
    ::create_poison_effect();
    set_name("Faerun Convert To Undead Poison");
    set_short("undead conversion poison");
    set_interval(UNDEAD_DURATION); // set interval to the full time.
    set_silent(2);
    set_damage( ({ POISON_USER_DEF, 15 }) ); // no regular damage
    set_time(UNDEAD_DURATION);
    set_poison_type("faerun_undead_convert");
    set_no_cleanse(); // This poison cannot be cleansed
    
    // People who quit with this should be able to come back no longer
    // as an undead. This is to prevent them from being kicked out from
    // guilds that do not accept undead. (SCoP, Worshippers, Dragon Order)
    recovery = 0; 
}

public void
remove_object()
{
    if (objectp(poisonee))
    {
        poisonee->catch_msg("You feel yourself returning to a more "
            + "natural state.\n");
        poisonee->remove_prop(LIVE_I_UNDEAD);
        poisonee->remove_subloc(UNDEAD_SUBLOC);
    }
    ::remove_object();    
}

public varargs void
start_poison(object poisoner)
{
    object target;

    target = environment(this_object());
    if (!objectp(target))
    {
        remove_object();
        return;
    }
    
    // Check if target is already an undead. If so, there's no point in
    // adding this poison
    if (target->query_prop(LIVE_I_UNDEAD))
    {
        remove_object();
        return;
    }
    
    // Now start the poison.
    ::start_poison(poisoner);    

    target->catch_msg("You feel different, as if the life "
        + "was drained out of you.\n");
    target->add_prop(LIVE_I_UNDEAD, 1);
    // Check if the undead prop was successfully applied. If not,
    // we need to remove this poison
    if (!target->query_prop(LIVE_I_UNDEAD))
    {
        remove_object();
        return;
    }    
    target->add_subloc(UNDEAD_SUBLOC, this_object());
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc == UNDEAD_SUBLOC)
    {
        if (on == for_obj)
        {
            return "You are looking a little pale.\n";
        }
        return capitalize(for_obj->query_pronoun())+" is looking "
            + "a little pale.\n";
    }
}
