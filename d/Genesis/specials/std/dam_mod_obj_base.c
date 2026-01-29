/*
 * Damage Modifier Effect Object
 * 
 * This is the base damage modifier effect object that handles damage
 * modifications in conjunction with the damage mod shadow. Damage modifier
 * objects may stack with one another (and do by default).
 *
 * Damage modifers may be two types:
 * - Absorb     :   Reduces the incoming wpen (damage).
 * - Amplify    :   Increases the incoming wpen (damage).
 *
 * Damage modifers stack in three basic ways:
 * - Additive :     Default status.  These effects stack with all other
 *                  (additive) damage modifier effects.
 * - Non-Additive : These effects stack only with other damage modifier
 *                  objects of the same type (name).  Note that this means
 *                  it is important that effects have unique names
 *                  rather than generic ones (use 'werewolf_absorb' instead
 *                  of 'absorb', etc).
 * - Exclusive :    These effects do not stack with any other damage 
 *                  modifer effect, even ones of the same type (name).
 *
 * When damage is taken, valid damage modifer effects will be separated
 * as indicated by their additive/exclusive status into groups.  The
 * group with the largest effect will then be the one to take effect.
 *
 * Absorb and Amplify modifiers are calculated separately, and then
 * both take effect.  So if an absorb decreases the damage by 15 and
 * an amplify increases the damage by 15, the net result will be 0
 * modification.
 *
 * Some important functions:
 * set_dam_mod_absorb(int i); //Defaults to 1.  Set to 0 to make the
 *                            effect a damage amplify modifier.
 * set_dam_mod_additive(int i);  //Defaults to 1.  Set to 0 to make
 *                           the effect only stack with effects of
 *                           the same name.
 * set_dam_mod_exclusive(int i); //Defaults to 0.  Set to 1 to make
 *                           the effect not stack with any other effect.
 * query_dam_mod_valid(object player, object attacker, int attack_id);
 *          //Overwrite to indicate if the damage modifer object should
 *              be used.
 * damage_modified(object player, object attacker, int attack_id);
 *          //Overwrite to perform actions when the effect object is
 *              used, such as writing out messages to the player.
 *
 * Created by Louie, Oct 2008
 *      Based heavily on the evade object by Petros, May 2008.
 *
 * Modifications:
 *   9/18/2009 - put runtime check in attack_modified (Petros, September 2009)
 */
 
#pragma strict_types

#include "/d/Genesis/specials/defs.h"

inherit EFFECT_BASE_OBJ;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define DAM_MOD_SH ("/d/Genesis/specials/std/dam_mod_sh")

// Prototypes
public void set_dam_mod_combat_aid(int caid);

//Variables
private int Damage_modifier_additive        = 1;
private int Damage_modifier_exclusive       = 0;
private int Damage_modifier_absorb          = 1;

/*
 * Function     : set_dam_mod_skills
 * Description  : Set the skills that will be used in calculating
 *                the strength of the dam_mod
 * Arguments    : skills
 * Returns      : nothing
 */
public nomask void 
set_dam_mod_skills(mixed skills)
{
    set_effect_skills(skills);
}

/*
 * Function     : query_dam_mod_skills
 * Description  : Returns the skills being used to calculate dam_mod strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public mixed 
query_dam_mod_skills()
{
    return query_effect_skills();
}

/*
 * Function     : set_dam_mod_stats
 * Description  : Set the stats that will be used in calculating
 *                the strength of the dam_mod
 * Arguments    : stats
 * Returns      : nothing
 */
public nomask void 
set_dam_mod_stats(mixed stats)
{
    set_effect_stats(stats);
}

/*
 * Function     : query_dam_mod_stats
 * Description  : Returns the stats being used to calculate dam_mod strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public mixed 
query_dam_mod_stats()
{
    return query_effect_stats();
} /* query_dam_mod_stats */

/*
 * Function     : set_dam_mod_absorb
 * Description  : Sets whether this object modifies damage in a negative
 *                  (absorbtion) or positive (amplification) way.
 * Arguments    : 1 - effect absorbs damage / 0 - effect amplifies damage
 * Returns      : none 
 */
public void 
set_dam_mod_absorb(int i) 
{
    Damage_modifier_absorb = i;
}

/*
 * Function     : query_dam_mod_absorb
 * Description  : Returns whether this object modifies damage in a negative
*                   (damage absorbtion) or positive (damage amplification)way.
 * Arguments    : none
 * Returns      : 1 - effect absorbs damage / 0 - effect amplifies damage
 */
public int 
query_dam_mod_absorb()
{
    return Damage_modifier_absorb;
}

/*
 * Function     : set_dam_mod_additive
 * Description  : Sets whether this object 'stacks' with ALL other damage 
 *                  modifier objects or not.  If it does not, the highest
 *                  positive and highest negative objects (or sets) will be 
 *                  used.
 * Arguments    : 0 - not additive, 1 - additive
 * Returns      : none 
 */
public void 
set_dam_mod_additive(int i)
{
    Damage_modifier_additive = i;
}

/*
 * Function     : query_dam_mod_additive
 * Description  : Returns whether this object 'stacks' with ALL other damage 
 *                  modifier objects or not.  If it does not, the highest
 *                  positive and highest negative objects (or sets) will be 
 *                  used.
 *                NOTE:  Exclusive objects are automatically non-additive.
 * Arguments    : none
 * Returns      : 0 - not additive, 1 - additive
 */
public int 
query_dam_mod_additive()
{
    return (Damage_modifier_additive && !Damage_modifier_exclusive);
}

/*
 * Function     : query_dam_mod_exclusive
 * Description  : Returns whether this object 'stacks' with other damage 
 *                  modifier objects OF THE SAME TYPE.  If it does not, 
 *                  the most powerful object of this type will be used.
 * Arguments    : none
 * Returns      : 0 - not exclusive, 1 - exclusive
 */
public int 
query_dam_mod_exclusive()
{
    return Damage_modifier_exclusive;
}

/*
 * Function     : set_dam_mod_exclusive
 * Description  : Sets whether this object 'stacks' with other damage 
 *                  modifier objects OF THE SAME TYPE.  If it does not, 
 *                  the most powerful object will be used.
 * Arguments    : 0 - not exclusive, 1 - exclusive
 * Returns      : none 
 */
public void 
set_dam_mod_exclusive(int i)
{
    Damage_modifier_exclusive = i;
}

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_base_dam_mod_object_");
    add_name( ({"base_dam_mod_obj" }) );
    set_short("hidden base damage modifer object");    
    set_long("A basic damage modifier object. One should not be able to see "+
           "it in their inventory.\n");

    setuid();
    seteuid(getuid());

    // Damage increases equal the combat aid. Damage decreases need to
    // be calculated differently. For example, a 100% combat aid damage
    // reduction means that they reduce 50% of damage. A 100% combat
    // aid increase would mean they double their aid.
    // Example:
    //   25% combat aid == 20% damage reduction
    //   25% combat aid == 25% damage increase
    set_dam_mod_combat_aid(25);
    set_dam_mod_additive(1);
    set_dam_mod_absorb(1);
    
    // By default, it doesn't modify by skills nor stats
    set_dam_mod_stats( TS_CON );
    set_dam_mod_skills( SS_DEFENCE );
}

/*
 * Function     : set_dam_mod_combat_aid
 * Description  : Sets the damage modifier combat aid which is used to 
 *                determine the modifier percentage
 * Arguments    : combat aid number
 * Returns      : nothing
 */
public nomask void
set_dam_mod_combat_aid(int caid)
{
    set_effect_combat_aid(caid);
}

/*
 * Function     : query_dam_mod_combat_aid
 * Description  : returns the damage modifier combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public int
query_dam_mod_combat_aid(object player)
{
    return query_effect_combat_aid(player);
}

/*
 * Function     : query_dam_mod_percentage
 * Description  : Returns the max percentage set during creation
 * Arguments    : none
 * Returns      : the damage modifier percentage
 */
public nomask int 
query_dam_mod_percentage(object player)
{
    if (query_dam_mod_absorb())
    {
        // damage absorbs need to use the new percentage.
        return ::query_effect_percentage(player);
    }
    
    // If damage increase, we just return the same number as combat aid
    return query_dam_mod_combat_aid(player);
}

/*
 * Function     : query_dam_mod_strength
 * Description  : Function that will be used to gauge the strength of
 *                the damage modifier based on the situation. 
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the damage modifier percentage
 */
public int
query_dam_mod_strength(object player, object attacker, int attack_id)
{
    // Strength of the object is equivalent to its percentage.
    //return query_dam_mod_percentage(player);
    return ::query_effect_strength(player, attacker, attack_id);
}

/*
 * Function     : query_dam_mod_valid
 * Description  : Validation function to see whether this damage modifier 
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 *                dt        - int, damage type
 * Returns      : 0/1 - invalid/valid
 */
public int
query_dam_mod_valid(object player, object attacker, int attack_id, int dt)
{
    return 1;
}

/*
 * Function     : damage_modified
 * Description  : Function to display messages that the damage was somehow
 *                  modified.  Empty (silent) by default.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
damage_modified(object player, object attacker, int attack_id)
{
}

/*
/*
 * Function name: remove_dam_mod_effect
 * Description:   Remove this damage modifier from a target, also removing 
 *                  the damage modifier shadow as needed
 * Arguments:     object target - the one affected by the damage modifier
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
remove_dam_mod_effect(object target)
{
    if (!target)
    {
        // We only care if the environment is a living person.
        // Master objects will simply be removed.
        send_debug_message("base_dam_mod", "Master object, will not process "
                                       + "shadow check.");
        return 0;
    }
    
    // Remove the effect from the shadow
    target->remove_dam_mod_effect(this_object());
    if (!sizeof(target->query_dam_mod_effects()) 
        && target->has_dam_mod_shadow())
    {
        send_debug_message("base_dam_mod", "Removing shadow because there "
                         + "are no more effects.");
        target->remove_dam_mod_shadow();
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
    foreach (object shadowobj : query_shadow_list())
    {
        remove_dam_mod_effect(shadowobj->query_shadow_who());
    }
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
    remove_dam_mod_effect(effect_target);
    return ::dispel_effect(dispeler);
}
    

/*
 * Function name: add_dam_mod_effect
 * Description;   Add this effect to a target
 * Returns:       1/0 - effect added/not added
 */
public int add_dam_mod_effect(object target)
{
    if (target && living(target))
    {
        if (!target->has_dam_mod_shadow())
        {
            send_debug_message("base_dam_mod", 
                               "Did not find shadow, creating shadow.");
            object sh = clone_object(DAM_MOD_SH);
            if (!sh->shadow_me(target)) {
                sh->remove_object();
                send_debug_message("base_dam_mod", "Shadowing failed.");
                send_debug_message("shadow_failure", "Shadowing failed.\n");
            }
        }
        else
        {
            send_debug_message("base_dam_mod", "Found damage modifier shadow.");
        }
        
        target->add_dam_mod_effect(this_object());
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
    add_dam_mod_effect(query_effect_target());
    return 1;
}

public void
attack_modified(object player, object attacker, int attack_id)
{
    if (!objectp(attacker) || !objectp(player))
    {
        return;
    }
    
    if (query_dam_mod_absorb())
    {
        // absorbs damage
        player->catch_msg("The attack from " + QTNAME(attacker)
            + " strikes you, but the impact seems to be deadened "
            + "so that it does not hurt you as much as it should "
            + "have.\n");
        attacker->catch_msg("Your attack on " + QTNAME(player)
            + " deadens as it strikes and it does not seem to hurt "
            + player->query_objective() + " as much as you think it "
            + "should.\n");
        player->tell_watcher(QCTNAME(attacker) + " strikes " + QTNAME(player)
            + ", but the blow deadens on contact and doesn't appear to "
            + "hurt as much as it should have.\n", ({ player, attacker }));
    }
    else
    {
        // amplifies damage
        player->catch_msg("The attack from " + QTNAME(attacker)
            + " strikes you and seems to strike truer than it should "
            + "have, hurting you greatly.\n");
        attacker->catch_msg("Your attack on " + QTNAME(player)
            + " strikes more truly than it should, and it seems to hurt " 
            + player->query_objective() + " greatly.\n");
        player->tell_watcher(QCTNAME(attacker) + " strikes " + QTNAME(player)
            + " and the blow seems to strike more truly than it should, "
            + "causing great harm.\n", ({ player, attacker }));
    }        
}
