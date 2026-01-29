/*
 * Reflect Damage Shadow
 */
 
#pragma strict_types
#pragma save_binary

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "reflect_obj";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

// Defines
#define LIZARD_WARD_EFFECT        "_reflect_effect"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    ::create_spell_object();
    set_spell_effect_desc("retributive ward");
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();
    string caster_name = query_effect_caster()->query_real_name();

    if (objectp(target))
    {
        target->catch_tell("You are now surrounded by wards that will react " +
           "retributively when you are attacked.\n");
        tell_room(environment(target), QCTNAME(target) + " is surrounded with "
            + "wards of magic that seem to pulse retributively.\n", 
            ({ target }));
    } 

    target->add_prop(LIZARD_WARD_EFFECT, caster_name);  
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

    target->remove_prop(LIZARD_WARD_EFFECT);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("You are no longer surrounded by retributive wards.\n");
        tell_room(environment(target), QCTNAME(target) + " no longer is "
            + "surrounded by retributive wards.\n", ({ target }));
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
        target->catch_tell("You sense your retributive wards begin to fade.\n");
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
            + "the retributive ward.\n");
    }    
}


// BELOW THIS LINE IS THE ACTUAL REFLECT DAMAGE SHADOW SPECIFIC CODE

/*
 * Function:    hook_reflect_damage_description
 * Description: Override this function to set your own descriptions on
 *              what happens when the damage gets reflected.
 */
public void
hook_describe_reflect_effect(object player, object attacker, mixed results)
{

    int phurt = results[0];
    int dam = results[3];
    string dam_desc;

    // DEBUG("Retributive ward: phurt " +phurt+ ", damage: " +dam+".");

    switch (phurt) // percentage hurt
    {
        case 0..7:
          dam_desc = " slightly";
        break;
        case 8..20:
          dam_desc = "";
        break;
        case 21..45:
          dam_desc = " badly";
        break;
        default:
          dam_desc = " severely";
        break; 
    }

    attacker->catch_msg("Your attack on " + QTNAME(player) + " gets "
        + "violently rebuffed by " + this_player()->query_possessive() 
        +" retributive wards, hurting you" +dam_desc+ " with magical energies.\n");
    player->catch_msg("The attack on you by " + QTNAME(attacker)
        + " gets violently rebuffed by your retributive wards, hurting " +
          attacker->query_objective() +dam_desc+ " with magical energies.\n");
    tell_room(environment(player), QCTNAME(attacker) + " is hurt"+dam_desc+ 
          " by "+ "magical energies warding " + QTNAME(player) + ".\n", 
        ({ attacker, player }));

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
        return  "You are protected by retributive wards.\n";
    else
        return capitalize(on->query_pronoun()) + " is protected by "
            + "magical retributive wards.\n";
}