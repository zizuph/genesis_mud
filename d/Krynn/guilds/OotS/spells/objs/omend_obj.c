/* 
 * obless object - blessed by divine forces
 */

#include "/d/Ansalon/common/defs.h"
#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>

inherit STD_SPELL_SYSTEM + "objs/regeneration_obj";

#include "../../oots_god_descs.h"


/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_omend_object_");
    set_short("OotS omend spell object");    
    set_long("This is the OotS mend spell object, based on the standard " +
      "regeneration spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the " +
      "omend spell.\n");
    set_spell_effect_desc("blessing of mending");    
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
	target->catch_tell("You feel the healing embrace of " +
	  oots_god_name(target) + " surround you. Your body will now " +
	  "recover more quickly from injury than before.\n");
	tell_room(environment(target), QCTNAME(target) + " is " +
	  "surrounded by the divine healing embrace of " +
	  oots_god_name(target) + ".\n", ({ target }));
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
    object caster = query_effect_caster();

    if(target->query_ghost())
	return;

    if (objectp(caster))
    {
	caster->catch_tell("You feel the healing embrace of " +
	  oots_god_name(caster) + " leave you.\n");
    }

    if (objectp(target))
    {
	tell_room(environment(target), QCTNAME(target) + " is no "
	  + "longer surrounded by the healing embrace of "+
	  oots_god_name(target)+".\n", ({ target }));
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
	target->catch_tell("You feel the healing embrace of " + 
	  oots_god_name(target) + " begin to wane.\n");
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
	caster->catch_tell("Mentally drained, the healing embrace of " +
	  oots_god_name(caster) + " leave you.\n");
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
    // DEBUG("Mend heal amount: " +amount);      
    target->catch_tell("The healing embrace of " + oots_god_name(target) + 
      " rejuvenates you, and you feel healthier.\n");
}

public int
calculate_heal_amount(object target)
{
    // We base the amount of healing on the following steps:
    // 1. Use F_PENMOD(40, 100) to start with 280 Penetration value
    // 2. Use F_NEW_DAMAGE(280, 60, 60) to get 160 as the starting value.
    // 
    // Given this, we will calculate the actual amount for the aid given. 
    // For 100% combat aid, this should equal 80. For 25%, this should 
    // equal 32.
    //
    // Input Variables will be:
    // A. Player Wisdom (variable => WIS)
    // B. Player's Life Skill (variable => LIFE)
    // C. Starting Damage Amount (variable => DAM)
    //
    // We make adjustments as below (before adjusted for aid):
    // (DAM / 2) + (MIN(100, MAX(WIS - 50, 0)) * DAM / 400) + 
    // (MIN(100, LIFE) * DAM / 400)
    //
    // In other words, half the amount will be guaranteed. A quarter 
    // will be based on the player's wisdom, and the other quarter 
    // will be based on the player's life skill.

    int penetration = F_PENMOD(40, 100);
    int max_healing = F_NEW_DAMAGE(penetration, 60, 60);
    int wisdom = target->query_stat(SS_WIS);
    int water_skill = target->query_skill(SS_ELEMENT_LIFE);

    int adjusted_healing = (max_healing / 2) + 
    (min(100, max(wisdom - 50, 0)) * max_healing / 400) +
    (min(100, water_skill) * max_healing / 400);

    adjusted_healing = adjusted_healing * F_INTERVAL_BETWEEN_HP_HEALING / 5;

    // Adjust healing for combat aid
    adjusted_healing = query_regeneration_percentage() * adjusted_healing / 100;

    // Adjust healing for if the player is in combat or not relaxed. 
    // If that's the case, then we reduce the regeneration by a factor.
    if (!target->query_relaxed_from_combat()) 
    {
	adjusted_healing = adjusted_healing / 2;

    }
    // Return the final result
    return adjusted_healing;
}
