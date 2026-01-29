/*
 * Reflect Effect Object for the Genesis Magic System reflect Spell
 * 
 * This is the reflect effect object for the reflect spell in the Genesis
 * Magic System. 
 *
 * Created by Carnak, January 2018
 *
 */
 
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";
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
    set_name("_spell_reflect_object");
    add_name( ({"spell_reflect_object" }) );
    set_short("hidden spell reflect object");    
    set_long("A spell reflect object. One should not be able to see it in "
    + "their inventory.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the reflect "
    + "spell.\n");
    
    set_spell_effect_desc("reflect");    
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintenance stuff.
 */
public int
setup_spell_effect()
{
    mapping input;
    int     power, duration,
            result = ::setup_spell_effect();
    
    if (!result)
        return result;

    power = query_spell_effect_power();
    // Power determines how long the spell lasts
    duration = ftoi(log(itof(power)) * 300.0);
    set_dispel_time(duration);

    // Combat aid determines the AC of the object
    input = query_spell_effect_input();
    
    // Clone the damage reduction object
    reflect = clone_object("/d/Genesis/specials/std/reflect_obj_base");
    // Setting reflect stats and skills simply allows a downward adjustment
    // based on having low values for either one. If you want to have maximum
    // granted by combat aid, just set both to 100.
    reflect->set_reflect_stats( ({ TS_INT, TS_WIS }) ); // wis and int
    reflect->set_reflect_skills( ({ SKILL_VALUE, 100 }) ); // no skills
    
    reflect->set_allow_specials(input["allow_specials"]); 
    reflect->set_allow_magic_attacks(input["allow_magic_attacks"]);
    reflect->set_allow_white_attacks(input["allow_white_attacks"]);
    reflect->set_excluded_target_hit_locations(input["excluded_hit_locations"]); 
    reflect->set_reflect_damage_type(input["damage_type"]);
    reflect->set_reflect_combat_aid(input["combat_aid"]);
    reflect->set_reflect_damage_likelihood(input["likelihood"]);
    send_debug_message("reflect_obj","likelihood: " + input["likelihood"] +
    "\nCombatAid: " + input["combat_aid"] + "\nDamageType: " + input["damage_type"]
    + "\nSpecials: " + input["allow_specials"] + "\nMagic: " + input["allow_magic_attacks"] 
    + "\nWhite: " + input["allow_white_attacks"] + "\n");
    
    reflect->set_reflected_function(hook_describe_reflect_effect);
    object target = query_effect_target();
    reflect->move(target, 1);
    reflect->start();
    
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    
    if (!result)
        return result;
    
    // Remove the reflect object
    if (objectp(reflect))
    {
        reflect->remove_object();
        reflect = 0;
    }
    
    return 1;
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
    
    if (objectp(target))
    {
        target->catch_tell("You feel you can reflect damage.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to be able to "
        + "reflect damage.\n", ({ target }));
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
        target->catch_tell("You can no longer reflect damage.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to be unable "
        + "to reflect damage anymore.\n", ({ target }));
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
        target->catch_tell("You sense your ability to reflect damage start to "
        + "decrease.\n");
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
        caster->catch_tell("You are mentally unable to maintain the reflect "
        + "damage effect.\n");
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
    attacker->catch_msg("Your attack on " + QTNAME(player) + " ends up hurting "
    + "you also.\n");
    player->catch_msg("The attack on you by " + QTNAME(attacker) + " backfires "
    + "and ends up hurting " + attacker->query_objective() + " also.\n");
    tell_room(environment(player), QCTNAME(attacker) + " is hurt by some "
    + "reflected damage from " + QTNAME(player) + ".\n",
    ({ attacker, player }));
}

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person has a beating heart now
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (interactive(to))
        to->add_subloc(REFLECT_SUBLOC, this_object());
}

/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 */
public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    
    if (interactive(old))
        old->remove_subloc(REFLECT_SUBLOC);
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
        return  "You are reflecting damage.\n";
    else
        return capitalize(on->query_pronoun()) + " has something that reflects "
        + "damage.\n";
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
        subloc != REFLECT_SUBLOC)
        return "";
    
    return query_reflect_subloc_description(on, for_obj);
}