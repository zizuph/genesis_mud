/*
 * Reflect Damage Shadow
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/std/spells/obj/reflect_sh";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "defs.h"

// Defines
#define RESIST_LIBRARY          "/d/Genesis/specials/resist"
#define EC_REFLECT_SUBLOC       "_ec_reflect_spell_effect_subloc"

#define EC_REFLECT_EFFECT "_ec_reflect_effect"

/*
 * Function:    has_reflect_shadow
 * Description: Indicates that the person shadowed has the reflect_damage
 *              effect on them.
 */
public int
has_reflect_shadow()
{
    return has_spell_shadow();
}

/*
 * Function:    remove_reflect_shadow
 * Description: Removes this particular shadow
 */
public void
remove_reflect_shadow()
{
    remove_spell_shadow();
}

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("reflect damage");
    spell_object->set_short("reflect damage spell object");
    
    int power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    int duration = ftoi(log(itof(power)) * 300.0);
    spell_object->set_dispel_time(duration);

}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your skin has hardened and will now have a chance "+
           "to reflect damage when you are attacked.\n");
        tell_room(environment(target), QCTPNAME(target) + " skin seems to harden.\n", 
            ({ target }));
        shadow_who->add_subloc(EC_REFLECT_SUBLOC, this_object());
    } 

    target->add_prop(EC_REFLECT_EFFECT, 1);  
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    target->remove_prop(EC_REFLECT_EFFECT);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("Your skin is no longer hardened.\n");
        tell_room(environment(target), QCTPNAME(target) + " is no longer "+
            "hardened.\n", ({ target }));
        shadow_who->remove_subloc(EC_REFLECT_SUBLOC);
    }

}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel your skin becoming less hardened from "+
            "the aspida prayer.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the aspida prayer.\n");
    }    
}


// BELOW THIS LINE IS THE ACTUAL REFLECT DAMAGE SHADOW SPECIFIC CODE

/*
 * Function:    hook_reflect_damage_description
 * Description: Override this function to set your own descriptions on
 *              what happens when the damage gets reflected.
 */
public void
hook_reflect_damage_description(object attacker, mixed hitme_results)
{
    attacker->catch_msg("Your attack on " + QTNAME(shadow_who) + " gets "
        + "hurled back at you by " +shadow_who->query_possessive()+ 
        " hardened skin, hurting you.\n");
    shadow_who->catch_msg("The attack on you by " + QTNAME(attacker)
        + " gets hurled back at " +attacker->query_objective() +
        "by your hardened skin, hurting " +attacker->query_objective() +".\n");
    tell_room(environment(shadow_who), QCTNAME(attacker) + " is hurt by the "
        + "hardened skin of " + QTNAME(shadow_who) + " hurling the attack "+
        "back at "+attacker->query_objective()+".\n", 
        ({ attacker, shadow_who }));

}

/*
 * Function:    query_reflect_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_reflect_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "Your skin is hardened by the aspida prayer.\n";
    else
        return capitalize(on->query_pronoun()) + " is protected by "
            + "hardened skin.\n";
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != EC_REFLECT_SUBLOC)
    {
        return "";
    }
    
    return query_reflect_subloc_description(on, for_obj);
}