/*
 * Wounding Effect Object
 * 
 * This is the base wounding effect object that sets up how much damage
 * a player receives from a wound.
 *
 * Created by Petros, January 2009
 */
 
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "/d/Genesis/specials/defs.h"
#include "guild.h"

inherit "/d/Genesis/specials/std/wounding_obj_base";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <poison_types.h>
#include <files.h>

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

#define LIVE_I_NO_BLEED "_live_i_no_bleed"

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

public void
hook_add_wounding_effect(object target)
{
    string * wound_type_target = ({ "bleeding", "weakened" });
    string * wound_type_all = ({ "bleeds from", "is weakened by" });
    int wound_type = 0;

    if(target->query_prop(LIVE_I_UNDEAD) || target->query_prop(LIVE_I_NO_BODY) ||
        target->query_prop(LIVE_I_NO_BLEED))
        wound_type = 1;

    target->catch_tell("You feel yourself " +wound_type_target[wound_type]+
        " from a wound on your " + query_wounding_hitloc_desc() + ".\n");

    tell_room(environment(target), QCTNAME(target)+ " " +wound_type_all[wound_type]+
        " a " + "wound on " +HIS(target)+ " " +query_wounding_hitloc_desc() + 
        ".\n", ({ target }), target);
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

    int current_health = poisonee->query_hp();

    hook_add_wounding_effect(query_effect_target());
    
    damage_dealt += damage_per_interval;
    poisonee->reduce_hit_point(damage_per_interval);
    poisonee->add_wounding_damage(damage_per_interval);

    // DEBUG("Bleeding wound damage dealt per interval: " +damage_per_interval+ ".");
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

