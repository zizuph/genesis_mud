/*
 * Standard Regeneration Object
 *
 * This is the spell object for the standard Genesis Magic System Regeneration
 * spell. When started, this spell object will provide healing boosts to
 * the target every specified interval.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Petros, May 2010
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

#include "defs.h"

inherit SPELL_OBJ_DIR + "spell_obj_base";

// Defines
#define NOTIFICATION_INTERVAL   30

// Global Variables
public int        Heal_alarm    = 0;
public int        Heal_number   = 0; // number of times that player has been regenerated
public int        Heal_combat_aid = 25;
public int        Notify_timestamp = 0;

// Prototypes
public void         do_regeneration();

/*
 * Function:    set_regeneration_combat_aid
 * Description: Sets the combat aid that this regeneration object
 *              will perform. It translates into accelerated healing
 *              rate.
 */
public void
set_regeneration_combat_aid(int aid)
{
    Heal_combat_aid = aid;
}

/*
 * Function:    query_regeneration_combat_aid
 * Description: Returns the combat aid that this regeneration object
 *              will perform. It translates into accelerated healing
 *              rate.
 */
public int
query_regeneration_combat_aid()
{
    return Heal_combat_aid;
}

/*
 * Function:    query_regeneratio_percentage
 * Description: Returns the percentage modifier based on the combat
 *              aid using the standard caid => percentage calculation.
 */
public int
query_regeneration_percentage()
{
    int caid = query_regeneration_combat_aid();
    // Formula for Calculating effect percentage from the combat aid (c)
    //   (100 * c) / (100 + c)
    // eg. 25% combat aid => (100 * 25) / (100 + 25) = 20%
    int percentage = max(0, min(100, (100 * caid) / (100 + caid)));
    return percentage;
}

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_regeneration_object_");
    set_short("regeneration spell object");    
    set_long("This is the standard regeneration spell's object. It continuously "
        + "heals the target.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the regeneration spell.\n");
    set_spell_effect_desc("regeneration");    
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    int power = max(2, query_spell_effect_power());
    // Power determines how long the spell lasts. Regeneration spells
    // should not last longer than ~6 minutes. Because they are
    // maintained spells, the healing effects at such low mana costs
    // needs to be carefully weighed.
    // int duration = ftoi(log(itof(power)) * 60.0);

    // duration now determined by spell class and skills
    set_dispel_time(get_default_spell_time());
    
    // Combat aid determines the amount that should be healed per interval
    float aid = query_spell_effect_input();
    if (aid)
    {
        set_regeneration_combat_aid(ftoi(aid));
    }

    // Set the actual alarm that will perform the regeneration  
    float interval = itof(F_INTERVAL_BETWEEN_HP_HEALING);  
    remove_alarm(Heal_alarm);
    Heal_alarm = set_alarm(interval, interval, do_regeneration);

    return result;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You start to heal quickly.\n");
        tell_room(environment(target), QCTNAME(target) + " is healing more "
            + "quickly.\n", ({ target }));
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You metabolism returns to normal.\n");
        tell_room(environment(target), QCTPNAME(target) + " stops healing "
            + "as quickly.\n", ({ target }));
    }
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel your metabolism start to slow down.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the fast metabolism.\n");
    }    
}

/*
 * Function:    hook_describe_regeneration
 * Description: Mask this to give messages for when the target gets healed
 *              by the regeneration effect.
 */
public void
hook_describe_regeneration(object target, int amount)
{       
    target->catch_tell("You feel healthier from your quick healing.\n");
}

public int
calculate_heal_amount(object target)
{
    // We base the amount of healing on the following steps:
    // 1. Use F_PENMOD(40, 100) to start with 280 Penetration value
    // 2. Use F_NEW_DAMAGE(280, 60, 60) to get 160 as the starting value.
    //
    // Given this, we will calculate the actual amount for the aid given. For
    // 100% combat aid, this should equal 80. For 25%, this should equal 32.
    //
    // Input Variables will be:
    // A. Player Wisdom (variable => WIS)
    // B. Player's Water Skill (variable => WATER)
    // C. Starting Damage Amount (variable => DAM)
    //
    // We make adjustments as below (before adjusted for aid):
    // (DAM / 2) + (MIN(100, MAX(WIS - 50, 0)) * DAM / 400) + (MIN(100, WATER) * DAM / 400)
    //
    // In other words, half the amount will be guaranteed. A quarter will be based on
    // the player's wisdom, and the other quarter will be based on the player's water
    // skill.
    int penetration = F_PENMOD(40, 100);
    int max_healing = F_NEW_DAMAGE(penetration, 60, 60);
    int wisdom = target->query_stat(SS_WIS);
    int water_skill = target->query_skill(SS_ELEMENT_WATER);
    
    int adjusted_healing = (max_healing / 2) + (min(100, max(wisdom - 50, 0)) * max_healing / 400) + (min(100, water_skill) * max_healing / 400);
    send_debug_message("regeneration_obj", "Initial adjusted healing: " + adjusted_healing);
    // Adjust healing for actual interval
    adjusted_healing = adjusted_healing * F_INTERVAL_BETWEEN_HP_HEALING / 5;
    send_debug_message("regeneration_obj", "Adjusted healing after adjusting for interval: " + adjusted_healing);    
    // Adjust healing for combat aid
    adjusted_healing = query_regeneration_percentage() * adjusted_healing / 100;
    send_debug_message("regeneration_obj", "Adjusted healing after adjusting for combat aid: " + adjusted_healing);        
    // Adjust healing for if the player is in combat or not relaxed. If that's the case, then we reduce the regeneration by a factor.
    if (!target->query_relaxed_from_combat()) {
        adjusted_healing = adjusted_healing / 2;
        send_debug_message("regeneration_obj", "Adjusted healing after adjusting for not being relaxed: " + adjusted_healing);                
    }

    // Return the final result
    return adjusted_healing;
}

/*
 * Function:    do_regeneration
 * Description: The function that gets called every interval to heal
 *              the target.
 */
public void
do_regeneration()
{
    object target = query_effect_target();
    if (!objectp(target) || target->query_linkdead() 
        || target->query_linkdead_in_combat())
    {
        return;
    }

    int maxhp = target->query_max_hp();
    int currenthp = target->query_hp();
    if (maxhp == currenthp)
    {
        // No need for regeneration
        return;
    }
    
    int heal_amount = calculate_heal_amount(target);
    int adjusted_heal_amount = min(heal_amount, maxhp - currenthp);
    
    target->heal_hp(adjusted_heal_amount);
    if (heal_amount == adjusted_heal_amount)
    {
        send_debug_message("regeneration_obj", "Regenerating "
                           + adjusted_heal_amount + " hit point(s).");
    }
    else
    {
        send_debug_message("regeneration_obj", "Regenerating "
                           + adjusted_heal_amount + " hit point(s) instead of "
                           + heal_amount + " because the target is fully healed.");
    }
        
    ++Heal_number;
    
    // Only notify if the notification interval has passed
    if (Notify_timestamp + NOTIFICATION_INTERVAL < time())
    {
        hook_describe_regeneration(target, heal_amount);
        Notify_timestamp = time();
    }
}
