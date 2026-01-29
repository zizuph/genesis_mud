/*
 * Elementalist Fire Shield Spell Shadow (Schirmo)
 *
 * Based on the reflect spell shadow, the fire shield provides Elementalists
 * with the ability to reflect some damage ability back at their attacker.
 *
 * Created by Petros, February 2013
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/std/spells/obj/reflect_sh";

#include "defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

// Defines
#define FIRE_SHIELD_SUBLOC          "_schirmo_fire_shield_subloc"

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("schirmo fire shield");
    spell_object->set_short("schirmo fire shield spell object");
    spell_object->set_name("_schirmo_fire_shield_object_");
    spell_object->add_prop(OBJ_M_NO_DROP,1);
    
    int power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    int duration = ftoi(log(itof(power)) * 300.0);
    spell_object->set_dispel_time(duration);

    // Set the specific for this instance
    set_allow_specials(1); 
    set_allow_magic_attacks(1);
    set_excluded_target_hit_locations(0); 
    set_reflect_damage_type(MAGIC_DT);
    set_reflect_resistance_types( ({ MAGIC_I_RES_FIRE, MAGIC_I_RES_MAGIC }) );
    set_reflect_damage_combat_aid(spell_input["combat_aid"]);
    set_reflect_damage_likelihood(25); // reflects back once every 4 times
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

    if (!objectp(target))
    {
        return;
    }
    object caster = spell_object->query_effect_caster();
    
    string caster_message = "As you complete your prayer to Lord Pyros, "
        + "you sense him grant his vengeance against those who would harm "
        + "you. ";
    string target_message = "A single flame begins to stir in the air in "
        + "front of you and suddenly bursts into a molten liquid ball that "
        + "engulfs you completely before settling into a fiery shield. The "
        + "shield, though made of flames, gently pulses along your skin "
        + "without harming you.\n";
    string watcher_message = "A single flame begins to stir in the air in "
        + "front of " + QTNAME(target) + " and suddenly bursts into a "
        + "molten liquid ball that engulfs " + target->query_objective() 
        + " completely before settling into a fiery shield. The shield, "
        + "though made of flames, gently pulses along "
        + target->query_possessive() + " skin without harming " 
        + target->query_objective() + ".\n";
    if (target == spell_object->query_effect_caster())
    {
        caster->catch_msg(caster_message + target_message);
    }
    else
    {
        caster->catch_msg(caster_message + "\n");
        target->catch_msg(target_message);
    }
    tell_room(environment(target), watcher_message, ({ target, caster }));
    shadow_who->add_subloc(FIRE_SHIELD_SUBLOC, this_object());    
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

    if (!objectp(target))
    {
        return;
    }
    
    target->catch_tell("The flames gently pulsing along your skin "
        + "flicker and dissipate, taking their warmth with them.\n");
    tell_room(environment(target), "The flames along " + QTPNAME(target)
        + " skin flickers and dissipates.\n", ({ target }));
    shadow_who->remove_subloc(FIRE_SHIELD_SUBLOC);
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
        return;
    }
    target->catch_tell("The flames along your skin "
        + "begin to pulse more quickly and then slow "
        + "down.\n");
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
        caster->catch_tell("Mentally drained, you lose control of "
            + "the fiery elemental powers sustaining the "
            + "schirmo gift of Lord Pyros.\n");
    }    
}

/*
 * Function:    hook_reflect_damage_description
 * Description: Override this function to set your own descriptions on
 *              what happens when the damage gets reflected.
 */
public void
hook_reflect_damage_description(object attacker, mixed hitme_results)
{
    if (attacker->query_hp() < 1)
    {
        // Describe killing blow
        attacker->catch_msg("As you strike " + QTNAME(shadow_who) + ", the "
            + "fiery liquid shield surrounding " 
            + shadow_who->query_objective()
            + " takes hold of you, engulfing your entire body. You manage "
            + "to take one last breath in shock as the flames end your "
            + "life.\n");
        shadow_who->catch_msg("Flames from your fiery liquid shield takes "
            + "hold of " + QTPNAME(attacker) + ", engulfing the entire "
            + "body. You hear " + QTNAME(attacker) + " draw one last "
            + "breath in shock as the flames end " 
            + attacker->query_possessive() + " life.\n");
        tell_room(environment(shadow_who), QCTPNAME(attacker) + " attack on "
            + QTNAME(shadow_who) + " backfires as the fiery liquid shield "
            + "surrounding " + QTNAME(shadow_who) + " takes a hold of " 
            + QTNAME(attacker) + ", engulfing " 
            + attacker->query_possessive()
            + " entire body. " + QCTNAME(attacker) + " manages to draw one "
            + "last breath in shock as the flames end " 
            + attacker->query_possessive() + " life.\n",
            ({ attacker, shadow_who }));
    }
    else
    {            
        attacker->catch_msg("You complete your attack on " + QTNAME(shadow_who) 
            + ", but the liquid flames surrounding " 
            + shadow_who->query_objective() + " scorches you in response.\n");
        shadow_who->catch_msg(QCTPNAME(attacker) + " attack on you backfires "
            + "as your fiery liquid shield scorches " 
            + attacker->query_objective() + " in response.\n");
        tell_room(environment(shadow_who), QCTPNAME(attacker) + " attack on "
            + QTNAME(shadow_who) + " backfires as the fiery liquid shield "
            + "surrounding " + QTNAME(shadow_who) + " scorches " 
            + QTNAME(attacker) + " in response.\n",({ attacker, shadow_who }));
    }
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
        return  "You are engulfed in a liquid shield of fire.\n";
    else
        return capitalize(on->query_pronoun()) + " is engulfed in a "
            + "liquid shield of fire.\n";
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return shadow_who->show_subloc(subloc, on, for_obj);

    if (subloc != FIRE_SHIELD_SUBLOC)
    {
        return shadow_who->show_subloc(subloc, on, for_obj);
    }
    
    return query_reflect_subloc_description(on, for_obj);
}

