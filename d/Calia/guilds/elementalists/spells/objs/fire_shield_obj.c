/*
 * Elementalist Fire Shield Spell Object (Schirmo)
 *
 * Based on the reflect spell object, the fire shield provides Elementalists
 * with the ability to reflect some damage ability back at their attacker.
 *
 * Created by Jaacar, January 2018
 */
 
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "reflect_obj";
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define REFLECT_SUBLOC          "_reflect_spell_effect_subloc"

/* Prototypes */
public void hook_describe_reflect_effect(object player, object attacker,
                                         mixed results);
/* Global Variables*/
public object       reflect;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_schirmo_fire_object_");
    add_name( ({"spell_reflect_object" }) );
    set_short("schirmo fire shield object");    
    set_long("This is the schirmo fire shield object. It reflects "
        + "incoming damage.\n");
    add_prop(OBJ_M_NO_DROP, 1);

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the schirmo elemental shield spell.\n");
}

public int
setup_spell_effect()
{
    set_spell_effect_desc("schirmo fire shield");  
    return ::setup_spell_effect();
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
    object caster = query_effect_caster();
    
    if (!objectp(target))
    {
        return;
    }        
    
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
    if (target == query_effect_caster())
    {
        caster->catch_msg(caster_message + target_message);
    }
    else
    {
        caster->catch_msg(caster_message + "\n");
        target->catch_msg(target_message);
    }
    tell_room(environment(target), watcher_message, ({ target, caster }));
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

    if (!objectp(target))
    {
        return;
    }
    
    target->catch_tell("The flames gently pulsing along your skin "
        + "flicker and dissipate, taking their warmth with them.\n");
    tell_room(environment(target), "The flames along " + QTPNAME(target)
        + " skin flickers and dissipates.\n", ({ target }));
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
    
    if (!objectp(target))
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
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("Mentally drained, you lose control of "
            + "the fiery elemental powers sustaining the "
            + "schirmo gift of Lord Pyros.\n");
    }
}

/*
 * Function:    hook_describe_reflect_effect
 * Description: Override this function to set your own descriptions on
 *              what happens when the damage gets reflected.
 */
public void
hook_describe_reflect_effect(object player, object attacker, mixed results)
{
    if (attacker->query_hp() < 1)
    {
        // Describe killing blow
        attacker->catch_msg("As you strike " + QTNAME(player) + ", the "
            + "fiery liquid shield surrounding " 
            + player->query_objective()
            + " takes hold of you, engulfing your entire body. You manage "
            + "to take one last breath in shock as the flames end your "
            + "life.\n");
        player->catch_msg("Flames from your fiery liquid shield takes "
            + "hold of " + QTPNAME(attacker) + ", engulfing the entire "
            + "body. You hear " + QTNAME(attacker) + " draw one last "
            + "breath in shock as the flames end " 
            + attacker->query_possessive() + " life.\n");
        tell_room(environment(player), QCTPNAME(attacker) + " attack on "
            + QTNAME(player) + " backfires as the fiery liquid shield "
            + "surrounding " + QTNAME(player) + " takes a hold of " 
            + QTNAME(attacker) + ", engulfing " 
            + attacker->query_possessive()
            + " entire body. " + QCTNAME(attacker) + " manages to draw one "
            + "last breath in shock as the flames end " 
            + attacker->query_possessive() + " life.\n",
            ({ attacker, player }));
    }
    else
    {            
        attacker->catch_msg("You complete your attack on " + QTNAME(player) 
            + ", but the liquid flames surrounding " 
            + player->query_objective() + " scorches you in response.\n");
        player->catch_msg(QCTPNAME(attacker) + " attack on you backfires "
            + "as your fiery liquid shield scorches " 
            + attacker->query_objective() + " in response.\n");
        tell_room(environment(player), QCTPNAME(attacker) + " attack on "
            + QTNAME(player) + " backfires as the fiery liquid shield "
            + "surrounding " + QTNAME(player) + " scorches " 
            + QTNAME(attacker) + " in response.\n",({ attacker, player }));
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
