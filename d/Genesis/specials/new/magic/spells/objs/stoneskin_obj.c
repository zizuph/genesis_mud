/*
 * Standard Stoneskin Object
 *
 * This is the spell object for the standard Genesis Magic System Stoneskin
 * spell. When started, this spell object clones the damage modification
 * effect to essentially provide damage reduction based on the combat aid
 * specified by the spell.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Petros, September 2009
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
#define STONESKIN_SUBLOC        "_stoneskin_subloc"

// Global Variables
public object       damage_object = 0;
public string       damage_file = 0;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_stoneskin_object_");
    set_short("stoneskin spell object");    
    set_long("This is the standard stoneskin spell's object. It turns "
        + "one's skin to stone.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the stoneskin spell.\n");
    set_spell_effect_desc("stoneskin");    
}

/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{
    if (!strlen(damage_file))
    {
        return DAM_MOD_OBJ_BASE;
    }
    
    return damage_file;
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
    // Spell class and skills now determine spell duration

    set_dispel_time(get_default_spell_time());
    
    // Combat aid determines the AC of the object
    float aid = query_spell_effect_input();

    setuid(); seteuid(getuid());
    // Clone the damage reduction object
    damage_object = clone_object(query_damage_modification_file());
    damage_object->set_dam_mod_combat_aid(ftoi(aid));
    damage_object->set_effect_caster(query_effect_caster());
    damage_object->set_effect_target(query_effect_target());
    object target = query_effect_target();
    damage_object->move(target, 1);
    damage_object->start();
    
    // Setting evade stats and skills simply allows a downward adjustment
    // based on having low values for either one. If you want to have maximum
    // granted by combat aid, just set both to 100.
    damage_object->set_dam_mod_stats(query_spell_stats()); // wisdom and intelligence 
    damage_object->set_dam_mod_skills( ({ SKILL_VALUE, 100 }) ); // no skills
    
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
    
    // Remove the damage absorbing object
    if (objectp(damage_object))
    {
        damage_object->remove_object();
        damage_object = 0;
    }
    
    return 1;
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
        target->catch_tell("Your skin hardens and turns to stone.\n");
        tell_room(environment(target), QCTNAME(target) + "'s skin hardens "
            + "and turns to stone.\n", ({ target }));
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
        target->catch_tell("Your skin turns back to normal.\n");
        tell_room(environment(target), QCTPNAME(target) + " skin "
            + "turns back to normal.\n", ({ target }));
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
        target->catch_tell("You feel the toughness of your skin begin "
            + "to soften.\n");
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
            + "the hardness of your skin.\n");
    }    
}

/*
 * Function:    query_stoneskin_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_stoneskin_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You have skin that is as hard as a rock.\n";
    else
        return capitalize(on->query_pronoun()) + " has skin that looks like "
            + "stone.\n";
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
        to->add_subloc(STONESKIN_SUBLOC, this_object());        
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
        old->remove_subloc(STONESKIN_SUBLOC);
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != STONESKIN_SUBLOC)
    {
        return "";
    }
    
    return query_stoneskin_subloc_description(on, for_obj);
}

