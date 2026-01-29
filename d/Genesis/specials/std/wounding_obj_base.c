/*
 * Wounding Effect Object
 * 
 * This is the base wounding effect object that sets up how much damage
 * a player receives from a wound.
 *
 * Created by Petros, January 2009
 */
 
#pragma strict_types

#include "defs.h"

inherit "/std/poison_effect";
inherit EFFECT_OBJECT_LIB;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <poison_types.h>
#include <files.h>
#include "../debugger/debugger_tell.h"

// Global Variables
public int          wounding_hitloc;
public int          wounding_damage;
public int          damage_dealt; // keeps track of actual damage dealt

// Prototypes
public void         set_wounding_time(int seconds);
public void         set_wounding_interval(int seconds);
public void         set_wounding_damage(int total_damage);
public void         set_wounding_hitloc(int hitloc);
public int          query_wounding_time();
public int          query_wounding_interval();
public int          query_wounding_damage();
public int          query_wounding_hitloc();

public void
set_wounding_time(int seconds)
{
    set_time(seconds);
}

public void
set_wounding_interval(int seconds)
{
    set_interval(seconds);
}

public void
set_wounding_damage(int total_damage)
{
    wounding_damage = total_damage;
}

public void
set_wounding_hitloc(int hitloc)
{
    wounding_hitloc = hitloc;
}

public int          
query_wounding_time()
{
    return ::query_time();
}

public int          
query_wounding_interval()
{
    return ::query_interval();
}

public int          
query_wounding_damage()
{
    return wounding_damage;
}

public int
query_damage_dealt()
{
    return damage_dealt;
}

public int
query_wounding_hitloc()
{
    object combat_object, player;
    
    player = environment(this_object());
    if (!objectp(player) || !IS_LIVING_OBJECT(player))
    {
        return 0;
    }
    
    combat_object = player->query_combat_object();
    if (!IN_ARRAY(wounding_hitloc, combat_object->query_hitloc_id()))
    {
        // If an invalid hit location was specified, we just pick
        // one from the available ones.
        wounding_hitloc = one_of_list(combat_object->query_hitloc_id());
    }
    
    return wounding_hitloc;  
}

public string
query_wounding_hitloc_desc()
{
    object player;
    int hitloc;
    
    hitloc = query_wounding_hitloc();
    if (!hitloc)
    {
        return "somewhere on the body";
    }

    player = environment(this_object());    
    mixed hitloc_results = 
        player->query_combat_object()->query_hitloc(hitloc);
    if (pointerp(hitloc_results))
    {
        return hitloc_results[2];
    }
    
    return "somewhere on the body";
}

/*
 * Function name: create_poison_effect
 * Description  : The normal create for the poison_effect. Redefine this
 *                function if you want to create your own poison.
 */
public void
create_poison_effect()
{
    set_name("_wounding_object_");
    add_name("wounding_object");
    set_short("wounding effect object");
    set_long("This resides in a player's inventory, but should not be "
        + "seen.\n");
        
    // Set some defaults
    set_wounding_damage(450);
    // set_wounding_hitloc(0);
    set_wounding_interval(F_INTERVAL_BETWEEN_HP_HEALING); // Same as normal healing
    set_wounding_time(300); // 5 minutes
    set_strength(1000);
    set_poison_type("wounding");
    set_silent(2); // target will receive no messages
    set_no_cleanse(); // can't be cleansed. must run its course.
    // Indicates that we want to call special_damage
    set_damage( ({ POISON_USER_DEF, 15 }) );
}

/*
 * Function name: special_damage
 * Description  : This function is called for any non-standard values of the
 *                poison.  This function should be redefined when you want to
 *                get a different damage type.
 *
 *                To get special damages in simply use POISON_USER_DEF as the
 *                poison type, followed by the damage value. For example:
 *                    ({ POISON_USER_DEF, 15 })
 *
 * Arguments    : int damage - the damage value for the user defined damage.
 */
public void
special_damage(int damage)
{
    int num_intervals, damage_per_interval;
    
    num_intervals = query_wounding_time() / query_wounding_interval();
    damage_per_interval = wounding_damage / num_intervals;
    
    damage_dealt += damage_per_interval;
    poisonee->reduce_hit_point(damage_per_interval);
    poisonee->add_wounding_damage(damage_per_interval);
    send_debug_message("base_wounding", "Bleeding wound effect "
        + "causes " + damage_per_interval + " damage on "
        + capitalize(poisonee->query_name()) + ".");
    // The next lines are solely for damage tracker shadow used for testing
    // purposes.
    object poisoner;
    if (objectp(poisoner = query_effect_caster()))
    {
        poisoner->add_damage_dealt(damage_per_interval);
    }

    // If the wound damage kills the player, we go ahead and call the
    // code to kill them off.
    if (objectp(poisonee) 
        && poisonee->query_hp() <= 0)
    {        
        // The correct call is kill_player(). However, because the mudlib
        // doesn't correctly give xp to the poisoner (responsible living)
        // we need to call do_die here to give the xp.
        // kill_player();
        
        // Temporary call until mudlib fixes giving xp correctly to
        // poisons
        if (objectp(poisoner))
        {
            poisonee->do_die(poisoner);
        }
        else
        {
            kill_player();
        }
    }
}

/*
 * Function     : enter_env
 * Description  : When the effect object enters the inventory, it will
 *                set the effect target of the living that it is entering.
 *                This is a convenience as this is the case for most
 *                effects.
 * Arguments    : dest - where the object is entering
 *                old  - where the object came from
 * Returns      : nothing
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (dest && living(dest) && !query_effect_target())
    {
        send_debug_message("base_wounding", "Entering living "
                         + "environment. Setting effect target to "
                         + "container.");
        set_effect_target(dest);
    }        
}

/*
/*
 * Function name: remove_wounding_effect
 * Description:   Remove this wound from a target, also removing the
 *                wounding shadow as needed
 * Arguments:     object target - the one affected by the effect
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
remove_wounding_effect(object target)
{
    if (!target)
    {
        // We only care if the environment is a living person.
        // Master objects will simply be removed.
        send_debug_message("base_wounding", "Master object, will not process "
            + "shadow check.");
        return 0;
    }
    
    // Remove the effect from the shadow
    target->remove_wounding_effect(this_object());
    if (!sizeof(target->query_wounding_effects()) 
        && target->has_wounding_shadow())
    {
        send_debug_message("base_wounding", "Removing shadow because there "
                         + "are no more effects.");
        target->remove_wounding_shadow();
    }
    return 1;
}

/*
 * Function name: remove_object
 * Description:   Called upon object destruction. This will need to
 *                be done so that the shadow can be properly removed
 *                when there are no more effects.
 * Arguments:     none
 * Returns:       nothing
 */
public void
remove_object()
{
    object player;
    
    player = environment(this_object());
    if (!objectp(player) || !IS_LIVING_OBJECT(player))
    {
        ::remove_object();
        return;
    }    
    
    remove_wounding_effect(player);
    ::remove_object();
}

/*
/*
 * Function name: dispel_effect
 * Description:   Cause this effect to be dispelled.
 *                If the effect is removed, 1 should be returned,
 *                else 0.  Returning 0 should be a rare occurance,
 *                since there generally should not be spell effects
 *                that cannot be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_effect(object dispeler)
{
    remove_object();
    return ::dispel_effect(dispeler);
}
    
public void
hook_add_wounding_effect(object target)
{
    target->catch_tell("You feel yourself bleeding from a wound on your "
        + query_wounding_hitloc_desc() + ".\n");
}

/*
 * Function name: add_wounding_effect
 * Description;   Add this effect to a target
 * Returns:       1/0 - effect added/not added
 */
public int add_wounding_effect(object target)
{
    setuid();
    seteuid(getuid());
    
    if (target && living(target))
    {
        if (!target->has_wounding_shadow())
        {
            send_debug_message("base_wounding", "Did not find shadow, creating shadow.");
            object sh = clone_object(WOUNDING_SH);

            int ret;
            if (!(ret = sh->shadow_me(target))) {
                sh->remove_object();
                send_debug_message("shadow_failure", "Failed to shadow " + file_name(target) + " shadow_me() returned " + ret);
            }
        }
        else
        {
            send_debug_message("base_wounding", "Found wounding shadow.");
        }
        
        target->add_wounding_effect(this_object());
        return 1;
    }   
     
    return 0;
}


/*
 * Function name: start
 * Description;   Start up the spell effect.  This should be redefined
 *                to provide specific behaviour for a given spell
 *                effect.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    object wounder;
    
    wounder = query_effect_caster();
    if (!objectp(wounder))
    {
        int sequence = 0;
        while (objectp(wounder = previous_object(sequence)))
        {
            if (IS_LIVING_OBJECT(wounder))
            {
                break;
            }
            --sequence;
        }
        if (!objectp(wounder))
        {
            wounder = this_player();
        }
        set_effect_caster(wounder);
    }
    
    add_wounding_effect(query_effect_target());
    hook_add_wounding_effect(query_effect_target());    
    start_poison(wounder); // starts and sets the person
                           // responsible for wounding.
    return 1;
}

/*
 * Function name: query_poison_recover
 * Description  : To add more information to the recover string, you should
 *                mask this function to return that information. Do not
 *                make a call to ::query_poison_recover!
 * Returns      : string - the extra recover string.
 */
public string
query_poison_recover()
{
    return "" + wounding_hitloc + "," + wounding_damage + "," + damage_dealt;
}

/*
 * Function name: init_posion_recover
 * Description  : To add more information to the recover string, you should
 *                mask this function to process that information after you
 *                have added it with query_poison_recover().
 * Arguments    : string arg - the extra recover string.
 */
public void
init_poison_recover(string arg)
{
    string * arglist;
    
    wounding_hitloc = 0;
    wounding_damage = 500;
    if (!arg || !strlen(arg))
    {
        return;
    }

    arglist = explode(arg, ",");
    sscanf(arglist[0], "%d", wounding_hitloc);
    sscanf(arglist[1], "%d", wounding_damage);
    sscanf(arglist[2], "%d", damage_dealt);
}

/*
 * Function name: set_strength
 * Description  : This sets the strength of the poison to overcome player
 *                resistance. We override this because we want to set
 *                the strength so high that it causes damage every time.
 * Arguments    : int s - The strength of the poison.
 */
public void 
set_strength(int s) 
{ 
    strength = s;
}
