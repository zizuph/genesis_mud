/*
 * Standard Magical Evade Object
 *
 * This is the spell object for the standard Genesis Magic System Evade
 * spell. When started, this spell object clones the evade
 * effect to essentially provide evade protection based on the combat aid
 * specified by the spell.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Petros, March 2010
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "defs.h"

inherit SPELL_OBJ_DIR + "spell_obj_base";

// Defines
#define EVADE_SUBLOC        "_evade_subloc"

// Global Variables
public object       evade_object = 0;

// Prototypes
public void         hook_describe_evade_effect(object player, object attacker, int attack_id);

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_evade_object_");
    set_short("evade spell object");    
    set_long("This is the standard evade spell's object. It allows casters to "
        + "dodge a certain amount of hits.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the evade spell.\n");
    set_spell_effect_desc("evade");    
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

    int power = query_spell_effect_power();
    // Power determines how long the spell lasts
    // int duration = ftoi(log(itof(power)) * 300.0);

    // Duration now determined by spell class and skills
    set_dispel_time(get_default_spell_time());
    
    // Combat aid determines the AC of the object
    float aid = query_spell_effect_input();

    // Clone the damage reduction object
    evade_object = clone_object(EVADE_OBJ_BASE);
    evade_object->set_evade_combat_aid(ftoi(aid));
    // Setting evade stats and skills simply allows a downward adjustment
    // based on having low values for either one. If you want to have maximum
    // granted by combat aid, just set both to 100.
    evade_object->set_evade_stats(query_spell_stats());
    evade_object->set_evade_skills( ({ SKILL_VALUE, 100 }) ); // no skills
    evade_object->set_effect_caster(query_effect_caster());
    evade_object->set_effect_target(query_effect_target());
    
    evade_object->set_blocked_function(hook_describe_evade_effect);
    object target = query_effect_target();
    evade_object->move(target, 1);
    evade_object->start();
    
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }
    
    // Remove the evade object
    if (objectp(evade_object))
    {
        evade_object->remove_object();
        evade_object = 0;
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
        target->catch_tell("Your body begins to blink in and out of the "
            + "material plane.\n");
        tell_room(environment(target), QCTNAME(target) + "'s body begins to "
            + "blink in and out of the material plane.\n", ({ target }));
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
        target->catch_tell("Your body returns fully to the material plane.\n");
        tell_room(environment(target), QCTPNAME(target) + " body "
            + "returns fully to the material plane.\n", ({ target }));
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
        target->catch_tell("You feel the rate of your body blinking out "
            + "of the material plane begin to slow down.\n");
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
            + "the blinking of your body in the material plane.\n");
    }    
}

/*
 * Function:    query_evade_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_evade_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "Your body is blinking in and out of the material plane.\n";
    else
        return capitalize(on->query_pronoun()) + " is blinking in and out "
            + "of the material plane.\n";
}

// Subloc Information

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
    {
        to->add_subloc(EVADE_SUBLOC, this_object());        
    }
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
    {
        old->remove_subloc(EVADE_SUBLOC);
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    return query_evade_subloc_description(on, for_obj);
}

/*
 * Function     : hook_describe_evade_effect
 * Description  : Function to display messages that the attack was
 *                blocked.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
hook_describe_evade_effect(object player, object attacker, int attack_id)
{
    player->catch_msg(QCTNAME(attacker) + " misses you with "
        + attacker->query_possessive() + " attack as you blink "
        + "out of the material plane.\n");
    attacker->catch_msg(QCTNAME(player)+" blinks out of the material plane "
        + "and causes you to miss your attack.\n");
    tell_room(environment(player), QCTNAME(attacker) + " tries to "
            + "attack " + QTNAME(player) + ", but the attack misses as "
            + QTNAME(player) + " blinks out of the material plane.\n", 
            ({ player, attacker }), player);
}
